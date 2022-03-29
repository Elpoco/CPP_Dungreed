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

	_rcTileWindow = { 0,0, MapTool::TOOL_START_X, WINSIZE_Y };
	_rcToolWindow = { MapTool::TOOL_START_X, 0, WINSIZE_X, WINSIZE_Y };
	_btnSave = { MapTool::TOOL_START_X, WINSIZE_Y - 100, MapTool::TOOL_START_X + 100, WINSIZE_Y - 50 };
	_btnLoad = { MapTool::TOOL_START_X, WINSIZE_Y - 50, MapTool::TOOL_START_X + 100, WINSIZE_Y };

	_mapImg = IMAGEMANAGER->findImage(ImageName::mapToolTile);
	_tileImg = IMAGEMANAGER->findImage(ImageName::mapTile);

	_rcSelectTile = {
		MapTool::TOOL_START_X,
		0,
		MapTool::TOOL_START_X + MapTool::TOOL_TILE_SIZE,
		MapTool::TOOL_TILE_SIZE
	};

	return S_OK;
}

void MapToolScene::release()
{
}

void MapToolScene::update()
{
	if (KEYMANAGER->isStayKeyDown(castingToInt(KEY::UP)))	 _camera->setY(-MapTool::CAMERA_SPPED + _camera->getY());
	if (KEYMANAGER->isStayKeyDown(castingToInt(KEY::DOWN)))  _camera->setY( MapTool::CAMERA_SPPED + _camera->getY());
	if (KEYMANAGER->isStayKeyDown(castingToInt(KEY::LEFT)))  _camera->setX(-MapTool::CAMERA_SPPED + _camera->getX());
	if (KEYMANAGER->isStayKeyDown(castingToInt(KEY::RIGHT))) _camera->setX( MapTool::CAMERA_SPPED + _camera->getX());

	if (KEYMANAGER->isStayKeyDown(VK_UP))	 _y -= MapTool::CAMERA_SPPED;
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))  _y += MapTool::CAMERA_SPPED;
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))  _x -= MapTool::CAMERA_SPPED;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _x += MapTool::CAMERA_SPPED;

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

	Rectangle(getMemDC(), MapTool::TOOL_START_X, 0, WINSIZE_X, WINSIZE_Y);
	_mapImg->render(getMemDC(), MapTool::TOOL_START_X, 0, _x, _y, _x + WINSIZE_X - MapTool::TOOL_START_X, _y + WINSIZE_Y);

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
			TILEMANAGER->setTileFrame(idx + x + y*MapTool::TILE_CNT_X, _curTile.x + x, _curTile.y+y, MapTool::TILE_TYPE::BLOCK);
		}
	}
}

void MapToolScene::clickUndoTile()
{
	int idx = TILEMANAGER->getTileIndex(_ptMouse);

	TILEMANAGER->setTileFrame(idx, 0, 0, MapTool::TILE_TYPE::NONE);
}

void MapToolScene::clickChangeTile()
{
	int x = (_ptMouse.x - MapTool::TOOL_START_X) / MapTool::TOOL_TILE_SIZE;
	int y = (_ptMouse.y) / MapTool::TOOL_TILE_SIZE;

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
	int startX = (_startCursor.x - MapTool::TOOL_START_X) / MapTool::TOOL_TILE_SIZE;
	int startY = (_startCursor.y) / MapTool::TOOL_TILE_SIZE;

	int endX = (_ptMouse.x - MapTool::TOOL_START_X) / MapTool::TOOL_TILE_SIZE + 1;
	int endY = (_ptMouse.y) / MapTool::TOOL_TILE_SIZE + 1;

	if (startX > endX) swap(startX, endX);
	if (startY > endY) swap(startY, endY);

	_selectedTileCnt.x = endX - startX;
	_selectedTileCnt.y = endY - startY;

	_rcSelectTile = {
		MapTool::TOOL_START_X + startX * MapTool::TOOL_TILE_SIZE,
		startY * MapTool::TOOL_TILE_SIZE,
		MapTool::TOOL_START_X + endX * MapTool::TOOL_TILE_SIZE,
		endY * MapTool::TOOL_TILE_SIZE
	};
}


void MapToolScene::drawSelectTile(HDC hdc)
{
	ColorRectangleMake(hdc, _rcSelectTile, Color::RED, true);

	SetTextColor(getMemDC(), Color::RED);

	printPoint(getMemDC(), _rcSelectTile.left, _rcSelectTile.top, _selectedTileCnt.y, _selectedTileCnt.x);

	SetTextColor(getMemDC(), Color::BLACK);
}
