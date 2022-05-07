#include "Stdafx.h"
#include "WorldMap.h"

WorldMap::WorldMap()
	: _showCurRoom(TRUE)
{
}

WorldMap::~WorldMap()
{
}

HRESULT WorldMap::init()
{
	UI::init();
	initUI();

	return S_OK;
}

void WorldMap::release()
{
	UI::release();
}

void WorldMap::update()
{
	UI::update();

	if (MouseInRect(_rcExitBtn))
	{
		if (IsOnceKeyUp(KEY::CLICK_L)) UIMANAGER->offUI();
	}

	if (_curRoomTime + 0.5f < TIMEMANAGER->getWorldTime())
	{
		_curRoomTime = TIMEMANAGER->getWorldTime();
		_showCurRoom = !_showCurRoom;
	}

	int x = MAPMANAGER->getCurLocation() % MapManagerSet::MAP_X;
	int y = MAPMANAGER->getCurLocation() / MapManagerSet::MAP_Y;
	_uiCurRoom->setX(_uiBase->getX() + _uiCurRoom->getWidth() * x);
	_uiCurRoom->setY(_uiBase->getY() + _uiCurRoom->getHeight() * y);

	_arrIsClear = MAPMANAGER->getClearMap();
}

void WorldMap::render(HDC hdc)
{
	if (!_isShow) return;

	FindImage(ImageName::ChangeScene)->alphaRender(hdc, 0, 0, 200);
	_imgButton->frameRender(hdc, _rcExitBtn.left, _rcExitBtn.top, 0, MouseInRect(_rcExitBtn));
	_uiLabel->render(hdc);
	_uiBase->render(hdc);

	for (int i = 0; i < MapManagerSet::MAP_CNT; i++)
	{
		if(_arrIsClear[i] || MAPMANAGER->getCurLocation() == i) _uiRoom[i]->render(hdc);
	}

	if(_showCurRoom) _uiCurRoom->render(hdc);

	for (int i = 0; i < MapManagerSet::MAP_CNT; i++)
	{
		if (_arrIsClear[i] || MAPMANAGER->getCurLocation() == i)
		{
			Code::MAP code = MAPMANAGER->getCurMapCode();
			MAP_INFO info = DBMANAGER->getInfo(code);
			if (info.door[DIR::LEFT]) FindImage(ImageName::UI::WorldMap::line_h)->render(hdc, _uiRoom[i]->getX() - 12, _uiRoom[i]->getY());
			if (info.door[DIR::RIGHT]) FindImage(ImageName::UI::WorldMap::line_h)->render(hdc, _uiRoom[i]->getX() + 12, _uiRoom[i]->getY());
		}
	}
}

void WorldMap::initUI()
{
	_imgButton = FindImage(ImageName::UI::Button::Exit);

	_uiLabel = new UI(ImageName::UI::WorldMap::MapBaseTitle);
	_uiLabel->setX(CENTER_X);
	_uiLabel->setY(_uiLabel->getHeight() * 0.5f);

	_rcExitBtn = RectMakeCenter(
		_uiLabel->getRect().right - _imgButton->getFrameWidth() + 15,
		_uiLabel->getY(),
		_imgButton->getFrameWidth(),
		_imgButton->getFrameHeight()
	);

	_uiBase = new UI(ImageName::UI::WorldMap::MapBase);
	_uiBase->setX(CENTER_X);
	_uiBase->setY(CENTER_Y + _uiLabel->getHeight() * 0.5f);

	_uiCurRoom = new UI(ImageName::UI::WorldMap::CurrentRoom);
	_uiCurRoom->setX(_uiBase->getX());
	_uiCurRoom->setY(_uiBase->getY());

	for (int i = 0; i < MapManagerSet::MAP_CNT; i++)
	{
		int x = i % MapManagerSet::MAP_X;
		int y = i / MapManagerSet::MAP_Y;
		_uiRoom[i] = new UI(ImageName::UI::WorldMap::Room);
		_uiRoom[i]->setX(_uiBase->getX() + _uiRoom[i]->getWidth() * x);
		_uiRoom[i]->setY(_uiBase->getY() + _uiRoom[i]->getHeight() * y);
	}
}
