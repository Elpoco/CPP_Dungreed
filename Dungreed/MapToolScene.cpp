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
	UIMANAGER->setCursorType(UIEnum::CURSOR_TYPE::NONE);

	_camera = new Object;
	CAMERAMANAGER->followCamera(_camera);
	CAMERAMANAGER->unlockCamera();

	_rcTileWindow = RectMake(0, 0, TOOL_START_X, WINSIZE_Y);
	_rcToolWindow = RectMake(TOOL_START_X, 0, TOOL_SIZE_X, WINSIZE_Y);

	_btnSave = RectMake(TOOL_START_X, WINSIZE_Y - 100, 100, 50);
	_btnLoad = RectMake(TOOL_START_X, WINSIZE_Y - 50, 100, 50);

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
	TILEMANAGER->update();

	if (IsStayKeyDown(KEY::UP))	 _camera->setY(_camera->getY() - CAMERA_SPPED);
	if (IsStayKeyDown(KEY::DOWN))  _camera->setY(_camera->getY() + CAMERA_SPPED);
	if (IsStayKeyDown(KEY::LEFT))  _camera->setX(_camera->getX() - CAMERA_SPPED);
	if (IsStayKeyDown(KEY::RIGHT)) _camera->setX(_camera->getX() + CAMERA_SPPED);

	if (IsOnceKeyDown(VK_LBUTTON))
	{
		_startCursor = _ptMouse;

		if (MouseInRect(_btnSave))
		{
			this->clickSave();
		}
		else if (MouseInRect(_btnLoad))
		{
			this->clickLoad();
		}
		else if (MouseInRect(_rcToolWindow))
		{
			this->clickChangeTile();
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (MouseInRect(_rcTileWindow))
		{
			this->clickDrawTile();
		}
		else if (MouseInRect(_rcToolWindow))
		{
			this->calSelectTile();
			this->settingSelectTileRect();
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
	}

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON) && MouseInRect(_rcTileWindow))
	{
		this->clickUndoTile();
	}

	if(MouseInRect(_rcToolWindow)) this->settingHoverTile();
}

void MapToolScene::render()
{
	TILEMANAGER->render(getMemDC());

	PrintRectangle(getMemDC(), _rcToolWindow);

	_imgMap->render(getMemDC(), TOOL_START_X, 0, _x, _y, _x + WINSIZE_X - TOOL_SIZE_X, _y + WINSIZE_Y);

	this->drawSelectTile(getMemDC());

	char str[128];
	wsprintf(str, String::btnSave);
	PrintRectangle(getMemDC(), _btnSave);
	TextOut(getMemDC(), _btnSave.left, _btnSave.top, str, strlen(str));
	wsprintf(str, String::btnLoad);
	PrintRectangle(getMemDC(), _btnLoad);
	TextOut(getMemDC(), _btnLoad.left, _btnLoad.top, str, strlen(str));
}

void MapToolScene::clickDrawTile()
{
	int idx = TILEMANAGER->getTileIndex(CAMERAMANAGER->calAbsPt(_ptMouse));

	for (int y = 0; y < _selectedTileCnt.y; y++)
	{
		for (int x = 0; x < _selectedTileCnt.x; x++)
		{
			TYPE type = TYPE::BLOCK;
			//MAP_OBJECT obj = MAP_OBJECT::MO_BLOCK;
			if (_curTile.x + x == 4 && _curTile.y + y == 0)
				type = TYPE::DIG_R;
				//obj = MAP_OBJECT::MO_DIG_R;
			if (_curTile.x + x == 3 && _curTile.y + y == 0)
				type = TYPE::DIG_L;

			TILEMANAGER->setTileFrame(
				idx + x + y * TILE_CNT_X,
				_curTile.x + x,
				_curTile.y + y,
				//TERRAIN::TR_NONE,
				type
			);
		}
	}
}

void MapToolScene::clickUndoTile()
{
	int idx = TILEMANAGER->getTileIndex(CAMERAMANAGER->calAbsPt(_ptMouse));

	TILEMANAGER->setTileFrame(idx, 0, 0, TYPE::NONE);//TERRAIN::TR_NONE, MAP_OBJECT::MO_NONE);
}

void MapToolScene::clickChangeTile()
{
	int x = (_ptMouse.x - TOOL_START_X) / TOOL_TILE_SIZE;
	int y = (_ptMouse.y) / TOOL_TILE_SIZE;

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
	_selectedTileCnt.x = (_ptMouse.x - TOOL_START_X) / TOOL_TILE_SIZE + 1;
	_selectedTileCnt.y = _ptMouse.y / TOOL_TILE_SIZE + 1;

	_selectedTileCnt.x -= _curTile.x;
	_selectedTileCnt.y -= _curTile.y;
	
	if (_selectedTileCnt.x < 1) _selectedTileCnt.x = 1;
	if (_selectedTileCnt.y < 1) _selectedTileCnt.y = 1;

}

void MapToolScene::settingSelectTileRect()
{
	_rcSelectTile = RectMake(
		_curTile.x * TOOL_TILE_SIZE + TOOL_START_X,
		_curTile.y * TOOL_TILE_SIZE,
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
