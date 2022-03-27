#include "Stdafx.h"
#include "MapToolScene.h"

MapToolScene::MapToolScene() :
	_x(0.f),
	_y(0.f),
	_curTile({ 0,0 }),
	_isBtn(false)
{
}

MapToolScene::~MapToolScene()
{
}

HRESULT MapToolScene::init(void)
{
	CAMERAMANAGER->setCameraPos(0.f, 0.f);
	_cX = 0.0f;
	_cY = 0.f;

	_rcTileWindow = { 0,0, TOOL_START_X, WINSIZE_Y };
	_rcToolWindow = { TOOL_START_X, 0, WINSIZE_X, WINSIZE_Y };
	_btnSave = { 0, WINSIZE_Y - 100, 100, WINSIZE_Y - 50 };
	_btnLoad = { 0, WINSIZE_Y - 50, 100, WINSIZE_Y };


	mapImg = IMAGEMANAGER->findImage("MapToolTile");
	tileImg = IMAGEMANAGER->findImage("MapTile");

	return S_OK;
}

void MapToolScene::release(void)
{
}

void MapToolScene::update(void)
{
	if (KEYMANAGER->isStayKeyDown('A')) CAMERAMANAGER->moveX(-CAMERA_SPPED);
	if (KEYMANAGER->isStayKeyDown('W')) CAMERAMANAGER->moveY(-CAMERA_SPPED);
	if (KEYMANAGER->isStayKeyDown('D')) CAMERAMANAGER->moveX(CAMERA_SPPED);
	if (KEYMANAGER->isStayKeyDown('S')) CAMERAMANAGER->moveY(CAMERA_SPPED);

	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _x -= CAMERA_SPPED;
	if (KEYMANAGER->isStayKeyDown(VK_UP)) _y -= CAMERA_SPPED;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _x += CAMERA_SPPED;
	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) _y += CAMERA_SPPED;

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_btnSave, _ptMouse))
		{
			_isBtn = true;
			clickSave();
		}
		else if (PtInRect(&_btnLoad, _ptMouse))
		{
			_isBtn = true;
			clickLoad();
		}
		else if (PtInRect(&_rcTileWindow, _ptMouse))
		{
			clickDrawTile();
		}
		else if (PtInRect(&_rcToolWindow, _ptMouse))
		{
			clickChangeTile();
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && !_isBtn && PtInRect(&_rcTileWindow, _ptMouse))
	{
		clickDrawTile();
	}
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON) && PtInRect(&_rcTileWindow, _ptMouse))
	{
		clickUndoTile();
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) _isBtn = false;

	TILEMANAGER->update();
}

void MapToolScene::render(void)
{
	TILEMANAGER->render();

	Rectangle(getMemDC(), MapTool::TOOL_START_X, 0, WINSIZE_X, WINSIZE_Y);
	mapImg->render(getMemDC(), MapTool::TOOL_START_X, 0, _x, _y, _x + WINSIZE_X - MapTool::TOOL_START_X, _y + WINSIZE_Y);

	char str[128];
	wsprintf(str, "SAVE");
	RectangleMakeRect(getMemDC(), _btnSave);
	TextOut(getMemDC(), _btnSave.left, _btnSave.top, str, strlen(str));
	wsprintf(str, "LOAD");
	RectangleMakeRect(getMemDC(), _btnLoad);
	TextOut(getMemDC(), _btnLoad.left, _btnLoad.top, str, strlen(str));
}

void MapToolScene::clickDrawTile()
{
	int x = (_ptMouse.x + CAMERAMANAGER->getAbsX()) / TILE_SIZE;
	int y = (_ptMouse.y + CAMERAMANAGER->getAbsY()) / TILE_SIZE;
	int idx = y * TILE_CNT_X + x;

	TILEMANAGER->setTileFrame(idx, _curTile.x, _curTile.y, TILE_TYPE::BLOCK);
}

void MapToolScene::clickUndoTile()
{
	int x = (_ptMouse.x + CAMERAMANAGER->getAbsX()) / TILE_SIZE;
	int y = (_ptMouse.y + CAMERAMANAGER->getAbsY()) / TILE_SIZE;
	int idx = y * TILE_CNT_X + x;

	TILEMANAGER->setTileFrame(idx, 0, 0, TILE_TYPE::NONE);
}

void MapToolScene::clickChangeTile()
{
	int x = (_ptMouse.x - TOOL_START_X) / TILE_SIZE_MAPTOOL;
	int y = (_ptMouse.y) / TILE_SIZE_MAPTOOL;

	_curTile = { x,y };
}

void MapToolScene::clickSave()
{
	TILEMANAGER->saveMap();
}

void MapToolScene::clickLoad()
{
	TILEMANAGER->loadMap();
}
