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

	_rcTileWindow = RectFMake(0, 0, TOOL_START_X, WINSIZE_Y);
	_rcToolWindow = RectFMake(TOOL_START_X, 0, TOOL_SIZE_X, WINSIZE_Y);

	_btnSave = RectFMake(TOOL_START_X, WINSIZE_Y - 100, 100, 50);
	_btnLoad = RectFMake(TOOL_START_X, WINSIZE_Y - 50, 100, 50);

	_imgMap = IMAGEMANAGER->findImage(ImageName::mapToolTile);
	_imgTile = IMAGEMANAGER->findImage(ImageName::mapTile);

	this->settingSelectTileRect();

	return S_OK;
}

void MapToolScene::release()
{
	SAFE_DELETE(_camera);
}

void MapToolScene::update()
{
	if (KEYMANAGER->isStayKeyDown(castingToInt(KEY::UP)))	 _camera->setY(_camera->getY() - CAMERA_SPPED);
	if (KEYMANAGER->isStayKeyDown(castingToInt(KEY::DOWN)))  _camera->setY(_camera->getY() + CAMERA_SPPED);
	if (KEYMANAGER->isStayKeyDown(castingToInt(KEY::LEFT)))  _camera->setX(_camera->getX() - CAMERA_SPPED);
	if (KEYMANAGER->isStayKeyDown(castingToInt(KEY::RIGHT))) _camera->setX(_camera->getX() + CAMERA_SPPED);

	//if (KEYMANAGER->isStayKeyDown(VK_UP))	 _y -= CAMERA_SPPED;
	//if (KEYMANAGER->isStayKeyDown(VK_DOWN))  _y += CAMERA_SPPED;
	//if (KEYMANAGER->isStayKeyDown(VK_LEFT))  _x -= CAMERA_SPPED;
	//if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _x += CAMERA_SPPED;

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_startCursor = _ptMouse;

		if (ptInRectF(_btnSave))
		{
			this->clickSave();
		}
		else if (ptInRectF(_btnLoad))
		{
			this->clickLoad();
		}
		else if (ptInRectF(_rcToolWindow))
		{
			this->clickChangeTile();
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (ptInRectF(_rcTileWindow))
		{
			this->clickDrawTile();
		}
		else if (ptInRectF(_rcToolWindow))
		{
			this->calSelectTile();
			this->settingSelectTileRect();
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
	}

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON) && ptInRectF(_rcTileWindow))
	{
		this->clickUndoTile();
	}

	TILEMANAGER->update();

	if(ptInRectF(_rcToolWindow)) this->settingHoverTile();
}

void MapToolScene::render()
{
	TILEMANAGER->render(getMemDC());

	RectangleMake(getMemDC(), _rcToolWindow, true, Color::Black);

	_imgMap->render(getMemDC(), TOOL_START_X, 0, _x, _y, _x + WINSIZE_X - TOOL_SIZE_X, _y + WINSIZE_Y);

	this->drawSelectTile(getMemDC());

	char str[128];
	wsprintf(str, String::btnSave);
	RectangleMakeRect(getMemDC(), _btnSave);
	TextOut(getMemDC(), _btnSave.GetLeft(), _btnSave.GetTop(), str, strlen(str));
	wsprintf(str, String::btnLoad);
	RectangleMakeRect(getMemDC(), _btnLoad);
	TextOut(getMemDC(), _btnLoad.GetLeft(), _btnLoad.GetTop(), str, strlen(str));
}

void MapToolScene::clickDrawTile()
{
	int idx = TILEMANAGER->getTileIndex(CAMERAMANAGER->calAbsPt(_ptMouse));

	for (int y = 0; y < _selectedTileCnt.y; y++)
	{
		for (int x = 0; x < _selectedTileCnt.x; x++)
		{
			TILEMANAGER->setTileFrame(
				idx + x + y * TILE_CNT_X,
				_curTile.x + x,
				_curTile.y + y, 
				getTileType(_curTile.x + x, _curTile.y + y)
			);
		}
	}
}

void MapToolScene::clickUndoTile()
{
	int idx = TILEMANAGER->getTileIndex(CAMERAMANAGER->calAbsPt(_ptMouse));

	TILEMANAGER->setTileFrame(idx, 0, 0, TILE_TYPE::NONE);
}

void MapToolScene::clickChangeTile()
{
	int x = (_ptMouse.X - TOOL_START_X) / TOOL_TILE_SIZE;
	int y = (_ptMouse.Y) / TOOL_TILE_SIZE;

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

void MapToolScene::calSelectTile()
{
	int disX = _ptMouse.X - _startCursor.X;
	int disY = _ptMouse.Y - _startCursor.Y;

	_selectedTileCnt.x = disX / TOOL_TILE_SIZE + 1;
	_selectedTileCnt.y = disY / TOOL_TILE_SIZE + 1;

	if (_selectedTileCnt.x < 1) _selectedTileCnt.x = 1;
	if (_selectedTileCnt.y < 1) _selectedTileCnt.y = 1;
}

void MapToolScene::settingSelectTileRect()
{
	_rcSelectTile = RectFMake(
		_curTile.x * TOOL_TILE_SIZE + TOOL_START_X,
		_curTile.y * TOOL_TILE_SIZE,
		_selectedTileCnt.x * TOOL_TILE_SIZE,
		_selectedTileCnt.y * TOOL_TILE_SIZE
	);
}


void MapToolScene::drawSelectTile(HDC hdc)
{
	RectangleMake(hdc, _rcSelectTile, false, Color::Red);

	if (ptInRectF(_rcToolWindow)) RectangleMake(hdc, _rcHoverTile, false, Color::Blue);

	SetTextColor(getMemDC(), ColorSet::RED);

	printPoint(getMemDC(), _rcSelectTile.GetLeft(), _rcSelectTile.GetTop(), _selectedTileCnt.y, _selectedTileCnt.x);

	SetTextColor(getMemDC(), ColorSet::BLACK);
}

void MapToolScene::settingHoverTile()
{
	int x = (_ptMouse.X - TOOL_START_X) / TOOL_TILE_SIZE;
	int y = (_ptMouse.Y) / TOOL_TILE_SIZE;

	_rcHoverTile = RectFMake(
		x * TOOL_TILE_SIZE + TOOL_START_X,
		y * TOOL_TILE_SIZE,
		TOOL_TILE_SIZE,
		TOOL_TILE_SIZE
	);
}

TILE_TYPE MapToolScene::getTileType(int x, int y)
{
	if (x == 3 && y == 0) return TILE_TYPE::DIG_L;
	return TILE_TYPE::BLOCK;
}
