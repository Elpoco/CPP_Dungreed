#include "Stdafx.h"
#include "MapToolScene.h"

#include "Object.h"

MapToolScene::MapToolScene() :
	_x(0.f),
	_y(0.f),
	_curTile({ 0,0 }),
	_selectedTileCnt({ 1,1 })
{
}

MapToolScene::~MapToolScene()
{
}

HRESULT MapToolScene::init()
{
	_camera = new Object;
	CAMERAMANAGER->followCamera(_camera);
	CAMERAMANAGER->unlockCamera();

	_rcTileWindow = { 0,0, MapToolSet::TOOL_START_X, WINSIZE_Y };
	_rcToolWindow = { MapToolSet::TOOL_START_X, 0, WINSIZE_X, WINSIZE_Y };
	_btnSave = { MapToolSet::TOOL_START_X, WINSIZE_Y - 100, MapToolSet::TOOL_START_X + 100, WINSIZE_Y - 50 };
	_btnLoad = { MapToolSet::TOOL_START_X, WINSIZE_Y - 50, MapToolSet::TOOL_START_X + 100, WINSIZE_Y };

	_mapImg = IMAGEMANAGER->findImage(ImageName::mapToolTile);
	_tileImg = IMAGEMANAGER->findImage(ImageName::mapTile);

	_rcSelectTile = {
		MapToolSet::TOOL_START_X,
		0,
		MapToolSet::TOOL_START_X + MapToolSet::TOOL_TILE_SIZE,
		MapToolSet::TOOL_TILE_SIZE
	};

	return S_OK;
}

void MapToolScene::release()
{
}

void MapToolScene::update()
{
	if (KEYMANAGER->isStayKeyDown(castingToInt(KEY::UP)))	 _camera->setY(_camera->getY() - MapToolSet::CAMERA_SPPED);
	if (KEYMANAGER->isStayKeyDown(castingToInt(KEY::DOWN)))  _camera->setY(_camera->getY() + MapToolSet::CAMERA_SPPED);
	if (KEYMANAGER->isStayKeyDown(castingToInt(KEY::LEFT)))  _camera->setX(_camera->getX() - MapToolSet::CAMERA_SPPED);
	if (KEYMANAGER->isStayKeyDown(castingToInt(KEY::RIGHT))) _camera->setX(_camera->getX() + MapToolSet::CAMERA_SPPED);

	if (KEYMANAGER->isStayKeyDown(VK_UP))	 _y -= MapToolSet::CAMERA_SPPED;
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))  _y += MapToolSet::CAMERA_SPPED;
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))  _x -= MapToolSet::CAMERA_SPPED;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _x += MapToolSet::CAMERA_SPPED;

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_startCursor = _ptMouse;

		int saveBtn		= PtInRect(&_btnSave, _ptMouse);
		int loadBtn		= PtInRect(&_btnLoad, _ptMouse);
		int drawTile	= PtInRect(&_rcTileWindow, _ptMouse);
		int changeTile	= PtInRect(&_rcToolWindow, _ptMouse);

		if (saveBtn)
		{
			this->clickSave();
		}
		else if (loadBtn)
		{
			this->clickLoad();
		}
		else if (drawTile)
		{
			this->clickDrawTile();
		}
		else if (changeTile)
		{
			this->clickChangeTile();
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		_isDrag = true;

		int drawTile	= PtInRect(&_rcTileWindow, _ptMouse);
		int changeTile	= PtInRect(&_rcToolWindow, _ptMouse);

		if (drawTile)
		{
			this->clickDrawTile();
		}
		else if (changeTile)
		{
			this->settingSelectTileRect();
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		_isDrag = false;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON) && PtInRect(&_rcTileWindow, _ptMouse))
	{
		this->clickUndoTile();
	}

	TILEMANAGER->update();
}

void MapToolScene::render()
{
	TILEMANAGER->render(getMemDC());

	Rectangle(getMemDC(), MapToolSet::TOOL_START_X, 0, WINSIZE_X, WINSIZE_Y);
	_mapImg->render(getMemDC(), MapToolSet::TOOL_START_X, 0, _x, _y, _x + WINSIZE_X - MapToolSet::TOOL_START_X, _y + WINSIZE_Y);

	drawSelectTile(getMemDC());

	char str[128];
	wsprintf(str, String::btnSave);
	RectangleMakeRect(getMemDC(), _btnSave);
	TextOut(getMemDC(), _btnSave.left, _btnSave.top, str, strlen(str));
	wsprintf(str, String::btnLoad);
	RectangleMakeRect(getMemDC(), _btnLoad);
	TextOut(getMemDC(), _btnLoad.left, _btnLoad.top, str, strlen(str));
}

void MapToolScene::clickDrawTile()
{
	int idx = TILEMANAGER->getTileIndex(_ptMouse);

	for (int y = 0; y < _selectedTileCnt.y; y++)
	{
		for (int x = 0; x < _selectedTileCnt.x; x++)
		{
			TILEMANAGER->setTileFrame(idx + x + y*MapToolSet::TILE_CNT_X, _curTile.x + x, _curTile.y+y, MapToolEnum::TILE_TYPE::BLOCK);
		}
	}
}

void MapToolScene::clickUndoTile()
{
	int idx = TILEMANAGER->getTileIndex(_ptMouse);

	TILEMANAGER->setTileFrame(idx, 0, 0, MapToolEnum::TILE_TYPE::NONE);
}

void MapToolScene::clickChangeTile()
{
	int x = (_ptMouse.x - MapToolSet::TOOL_START_X) / MapToolSet::TOOL_TILE_SIZE;
	int y = (_ptMouse.y) / MapToolSet::TOOL_TILE_SIZE;

	_curTile = { x,y };

	settingSelectTileRect();
}

void MapToolScene::clickSave()
{
	if (TILEMANAGER->saveMap()) 
		MSGBOXMANAGER->showMessage(String::msgSaveSuccess);
	else
		MSGBOXMANAGER->showMessage(String::msgSaveFail);
}

void MapToolScene::clickLoad()
{
	if (TILEMANAGER->loadMap())
		MSGBOXMANAGER->showMessage(String::msgLoadSuccess);
	else
		MSGBOXMANAGER->showMessage(String::msgLoadFail);
}

void MapToolScene::settingSelectTileRect()
{
	int startX = (_startCursor.x - MapToolSet::TOOL_START_X) / MapToolSet::TOOL_TILE_SIZE;
	int startY = (_startCursor.y) / MapToolSet::TOOL_TILE_SIZE;

	int endX = (_ptMouse.x - MapToolSet::TOOL_START_X) / MapToolSet::TOOL_TILE_SIZE + 1;
	int endY = (_ptMouse.y) / MapToolSet::TOOL_TILE_SIZE + 1;

	if (startX > endX) swap(startX, endX);
	if (startY > endY) swap(startY, endY);

	_selectedTileCnt.x = endX - startX;
	_selectedTileCnt.y = endY - startY;

	_rcSelectTile = {
		startX * MapToolSet::TOOL_TILE_SIZE + MapToolSet::TOOL_START_X,
		startY * MapToolSet::TOOL_TILE_SIZE,
		endX * MapToolSet::TOOL_TILE_SIZE + MapToolSet::TOOL_START_X,
		endY * MapToolSet::TOOL_TILE_SIZE
	};
}


void MapToolScene::drawSelectTile(HDC hdc)
{
	ColorRectangleMake(hdc, _rcSelectTile, ColorSet::RED, true);

	SetTextColor(getMemDC(), ColorSet::RED);

	printPoint(getMemDC(), _rcSelectTile.left, _rcSelectTile.top, _selectedTileCnt.y, _selectedTileCnt.x);

	SetTextColor(getMemDC(), ColorSet::BLACK);
}
