#include "Stdafx.h"
#include "MapToolScene.h"

#include "Object.h"

using namespace MapToolSceneSet;

MapToolScene::MapToolScene() 
	: _objectIdx(1)
	, _curTile({ 0,0 })
	, _selectedTileCnt({ 1,1 })
	, _tilePickX(0)
	, _tilePickY(0)
{
}

MapToolScene::~MapToolScene()
{
}

HRESULT MapToolScene::init()
{
	UIMANAGER->setCursorType(UIEnum::CURSOR_TYPE::NONE);

	_camera = new Object;
	_camera->setX(CENTER_X);
	_camera->setY(CENTER_Y);
	CAMERAMANAGER->followCamera(_camera);
	CAMERAMANAGER->unlockCamera();

	_imgTile = FindImage(ImageName::MapTool::mapTile);
	_imgTool = FindImage(ImageName::MapTool::mapToolTile);
	_imgObject = FindImage(ImageName::MapTool::mapToolObject);

	_rcTileWindow = RectMake(0, 0, TOOL_START_X, WINSIZE_Y);
	_rcToolWindow = RectMake(TOOL_START_X, 0, TOOL_SIZE_X, WINSIZE_Y);
	_rcObjectWindow = RectMake(TOOL_START_X, 0, TOOL_SIZE_X, TOOL_TILE_SIZE);
	_rcTilePickWindow = RectMake(TOOL_START_X, TOOL_TILE_SIZE, TOOL_SIZE_X, TOOL_TILE_SIZE + TOOL_TILE_SIZE*15);

	_btnSave = RectMake(TOOL_START_X, WINSIZE_Y - 100, 100, 50);
	_btnLoad = RectMake(TOOL_START_X, WINSIZE_Y - 50, 100, 50);

	this->settingSelectTileRect();

	return S_OK;
}

void MapToolScene::release()
{
	SAFE_DELETE(_camera);
}

void MapToolScene::update()
{
	TILEMANAGER->update();

	if(MouseInRect(_rcToolWindow)) hoverTile();

	if (IsStayKeyDown(KEY::UP))	   _camera->setY(_camera->getY() - CAMERA_SPPED);
	if (IsStayKeyDown(KEY::DOWN))  _camera->setY(_camera->getY() + CAMERA_SPPED);
	if (IsStayKeyDown(KEY::LEFT))  _camera->setX(_camera->getX() - CAMERA_SPPED);
	if (IsStayKeyDown(KEY::RIGHT)) _camera->setX(_camera->getX() + CAMERA_SPPED);

	if (IsOnceKeyDown('R') && _tilePickY > 0) _tilePickY--;
	if (IsOnceKeyDown('Q') && _tilePickX > 0) _tilePickX--;
	if (IsOnceKeyDown('F') && _tilePickY < _imgTool->getMaxFrameY()) _tilePickY++;
	if (IsOnceKeyDown('E') && _tilePickX < _imgTool->getMaxFrameX()) _tilePickX++;

	if (IsOnceKeyDown(KEY::CLICK_L))
	{
		_startCursor = _ptMouse;

		if (MouseInRect(_rcObjectWindow)) selectObjectTile();
		else if (MouseInRect(_rcTilePickWindow)) selectTile();
		else if (MouseInRect(_btnSave)) clickSave();
		else if (MouseInRect(_btnLoad)) clickLoad();
	}

	if (IsStayKeyDown(KEY::CLICK_L))
	{
		if (MouseInRect(_rcTileWindow)) clickDrawTile();
		else if (MouseInRect(_rcTilePickWindow))
		{
			calSelectTile();
			settingSelectTileRect();
		}
	}

	if (IsStayKeyDown(VK_RBUTTON) && MouseInRect(_rcTileWindow)) clickUndoTile();
	
	if(MouseInRect(_rcToolWindow)) settingHoverTile();
}

void MapToolScene::render()
{
	TILEMANAGER->render(getMemDC());

	PrintRectangle(getMemDC(), _rcToolWindow);

	_imgTool->frameRender(getMemDC(), _rcTilePickWindow.left, _rcTilePickWindow.top, _tilePickX, _tilePickY);

	this->drawSelectTile(getMemDC());

	_imgObject->render(getMemDC(), _rcObjectWindow.left, _rcObjectWindow.top);
	
	if (MouseInRect(_rcToolWindow)) PrintRectangleColor(getMemDC(), _rcHoverTile, Color::Blue);

	char str[128];
	wsprintf(str, String::btnSave);
	PrintRectangle(getMemDC(), _btnSave);
	TextOut(getMemDC(), _btnSave.left, _btnSave.top, str, strlen(str));
	wsprintf(str, String::btnLoad);
	PrintRectangle(getMemDC(), _btnLoad);
	TextOut(getMemDC(), _btnLoad.left, _btnLoad.top, str, strlen(str));
}

void MapToolScene::hoverTile()
{
	POINT pt = getMousePointIdx();

	_rcHoverTile = RectMake(
		pt.x * TOOL_TILE_SIZE + TOOL_START_X,
		pt.y * TOOL_TILE_SIZE,
		TOOL_TILE_SIZE,
		TOOL_TILE_SIZE
	);
}

void MapToolScene::selectObjectTile()
{
	_objectIdx = getMousePointIdx().x;
}

void MapToolScene::selectTile()
{
	_curTile = getMousePointIdx();
	_curTile.y -= 1;
	settingSelectTileRect();
}

POINT MapToolScene::getMousePointIdx()
{
	int x = (_ptMouse.x - TOOL_START_X) / TOOL_TILE_SIZE;
	int y = (_ptMouse.y) / TOOL_TILE_SIZE;

	return PointMake(x, y);
}

void MapToolScene::clickDrawTile()
{
	int idx = TILEMANAGER->getTileIndex(CAMERAMANAGER->calAbsPt(_ptMouse));

	for (int y = 0; y < _selectedTileCnt.y; y++)
	{
		for (int x = 0; x < _selectedTileCnt.x; x++)
		{
			TILEMANAGER->setTile(
				idx + x + y * TILE_CNT_X,
				_curTile.x + x + _tilePickX * 8,
				_curTile.y + y + _tilePickY * 16,
				_objectIdx
			);
		}
	}
}

void MapToolScene::clickUndoTile()
{
	int idx = TILEMANAGER->getTileIndex(CAMERAMANAGER->calAbsPt(_ptMouse));

	TILEMANAGER->setTile(idx, -1, -1, OBJECT::NONE);
}

void MapToolScene::clickSave()
{
	if (TILEMANAGER->saveMap(tempSaveFile))
		MSGBOXMANAGER->showMessage(String::msgSaveSuccess);
	else
		MSGBOXMANAGER->showMessage(String::msgSaveFail);
}

void MapToolScene::clickLoad()
{
	if (TILEMANAGER->loadMap(tempSaveFile))
		MSGBOXMANAGER->showMessage(String::msgLoadSuccess);
	else
		MSGBOXMANAGER->showMessage(String::msgLoadFail);
}

void MapToolScene::calSelectTile()
{
	_selectedTileCnt.x = (_ptMouse.x - TOOL_START_X) / TOOL_TILE_SIZE + 1;
	_selectedTileCnt.y = _ptMouse.y / TOOL_TILE_SIZE;
	
	_selectedTileCnt.x -= _curTile.x;
	_selectedTileCnt.y -= _curTile.y;
	
	if (_selectedTileCnt.x < 1) _selectedTileCnt.x = 1;
	if (_selectedTileCnt.y < 1) _selectedTileCnt.y = 1;

}

void MapToolScene::settingSelectTileRect()
{
	_rcSelectTile = RectMake(
		_curTile.x * TOOL_TILE_SIZE + TOOL_START_X,
		(_curTile.y+1) * TOOL_TILE_SIZE,
		_selectedTileCnt.x * TOOL_TILE_SIZE,
		_selectedTileCnt.y * TOOL_TILE_SIZE
	);
}


void MapToolScene::drawSelectTile(HDC hdc)
{
	PrintRectangleColor(hdc, _rcSelectTile, Color::Red);

	if (MouseInRect(_rcToolWindow)) PrintRectangleColor(hdc, _rcHoverTile, Color::Blue);

	SetTextColor(getMemDC(), ColorSet::RED);

	PrintPoint(getMemDC(), _rcSelectTile.left, _rcSelectTile.top, _selectedTileCnt.y, _selectedTileCnt.x);

	SetTextColor(getMemDC(), ColorSet::BLACK);
}

void MapToolScene::settingHoverTile()
{
	int x = (_ptMouse.x - TOOL_START_X) / TOOL_TILE_SIZE;
	int y = (_ptMouse.y) / TOOL_TILE_SIZE;

	_rcHoverTile = RectMake(
		x * TOOL_TILE_SIZE + TOOL_START_X,
		y * TOOL_TILE_SIZE,
		TOOL_TILE_SIZE,
		TOOL_TILE_SIZE
	);
}
