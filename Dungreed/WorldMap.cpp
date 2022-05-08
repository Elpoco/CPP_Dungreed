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
	if (!_isShow) return;

	UI::update();

	if (MouseInRect(_rcExitBtn))
	{
		if (IsOnceKeyUp(KEY::CLICK_L)) UIMANAGER->hideWorldMap();
	}

	for (int i = 0; i < MapManagerSet::MAP_CNT; i++)
	{
		if (MouseInRect(_rcRoom[i]))
		{
			_hoverIdx = i;

			if (_arrRoom[i].isWorm && IsOnceKeyUp(KEY::CLICK_L))
			{
				UIMANAGER->hideWorldMap();
				MAPMANAGER->clickWorm(i);
			}
		}
	}

	if (_curRoomTime + 0.5f < TIMEMANAGER->getWorldTime())
	{
		_curRoomTime = TIMEMANAGER->getWorldTime();
		_showCurRoom = !_showCurRoom;
	}

	int x = MAPMANAGER->getCurLocation() % MapManagerSet::MAP_X;
	int y = MAPMANAGER->getCurLocation() / MapManagerSet::MAP_Y;

	_uiCurRoom->setX(_uiBase->getX() - (_uiCurRoom->getWidth() + 6) * 1.5f + (_uiCurRoom->getWidth() + 6) * x);
	_uiCurRoom->setY(_uiBase->getY() - (_uiCurRoom->getHeight() + 6) * 1.5f + (_uiCurRoom->getHeight() + 6) * y);

	_arrIsClear = MAPMANAGER->getClearMap();
}

void WorldMap::render(HDC hdc)
{
	if (!_isShow) return;

	FindImage(ImageName::ChangeScene)->alphaRender(hdc, 0, 0, 200);
	_uiLabel->render(hdc);
	_imgButton->frameRender(hdc, _rcExitBtn.left, _rcExitBtn.top, 0, MouseInRect(_rcExitBtn));
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
			if(_arrRoom[i].door[DIR::LEFT]) FindImage(ImageName::UI::WorldMap::line_h)->render(hdc, _uiRoom[i]->getRect().left - 15, _uiRoom[i]->getY() - 2);
			if(_arrRoom[i].door[DIR::RIGHT]) FindImage(ImageName::UI::WorldMap::line_h)->render(hdc, _uiRoom[i]->getRect().right - 9, _uiRoom[i]->getY() - 2);
			if(_arrRoom[i].door[DIR::TOP]) FindImage(ImageName::UI::WorldMap::line_v)->render(hdc, _uiRoom[i]->getX() - 2, _uiRoom[i]->getRect().top - 15);
			if(_arrRoom[i].door[DIR::BOTTOM]) FindImage(ImageName::UI::WorldMap::line_v)->render(hdc, _uiRoom[i]->getX() - 2, _uiRoom[i]->getRect().bottom - 9);

			if (_arrRoom[i].isWorm)
			{
				string name = ImageName::UI::WorldMap::Worm;
				if (_hoverIdx == i) name = ImageName::UI::WorldMap::Worm_Selected;

				if (_shopIdx == i)
				{
					FindImage(name)->render(hdc, _uiRoom[i]->getX() - 4, _uiRoom[i]->getY() - 14);
					_iconShop->render(hdc);
				}
				else if (_foodIdx == i)
				{
					FindImage(name)->render(hdc, _uiRoom[i]->getX() - 4, _uiRoom[i]->getY() - 14);
					_iconFood->render(hdc);
				}
				else
				{
					FindImage(name)->render(hdc, _uiRoom[i]->getX() - 17, _uiRoom[i]->getY() - 14);
				}
			}
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
	_uiCurRoom->setX(_uiBase->getX() - (_uiCurRoom->getWidth() + 6) * 1.5f);
	_uiCurRoom->setY(_uiBase->getY() - (_uiCurRoom->getHeight() + 6) * 1.5f);

	_iconShop = new UI(ImageName::UI::WorldMap::ShopIcon);
	_iconFood = new UI(ImageName::UI::WorldMap::Food);

	for (int i = 0; i < MapManagerSet::MAP_CNT; i++)
	{
		int x = i % MapManagerSet::MAP_X;
		int y = i / MapManagerSet::MAP_Y;
		_uiRoom[i] = new UI(ImageName::UI::WorldMap::Room);
		_uiRoom[i]->setX(_uiBase->getX() - (_uiRoom[i]->getWidth() + 6) * 1.5f + (_uiRoom[i]->getWidth() + 6) * x);
		_uiRoom[i]->setY(_uiBase->getY() - (_uiRoom[i]->getHeight() + 6) * 1.5f + (_uiRoom[i]->getHeight() + 6) * y);
		_rcRoom[i] = _uiRoom[i]->getRect();
	}

	for (int i = 0; i < MapManagerSet::MAP_CNT; i++)
	{
		_arrRoom[i].isClear = FALSE;
		Code::MAP code = MAPMANAGER->getMapCode(i);
		MAP_INFO info = DBMANAGER->getInfo(code);
		_arrRoom[i].door[DIR::LEFT] = info.door[DIR::LEFT];
		_arrRoom[i].door[DIR::TOP] = info.door[DIR::TOP];
		_arrRoom[i].door[DIR::RIGHT] = info.door[DIR::RIGHT];
		_arrRoom[i].door[DIR::BOTTOM] = info.door[DIR::BOTTOM];

		if (info.ptWorm.x != 0)
		{
			_arrRoom[i].isWorm = TRUE;
		}

		if (code == Code::MAP::DUNGEON_SHOP)
		{
			_iconShop->setX(_uiRoom[i]->getX() - 14);
			_iconShop->setY(_uiRoom[i]->getY());
			_shopIdx = i;
		}
		if (code == Code::MAP::DUNGEON_FOOD)
		{
			_iconFood->setX(_uiRoom[i]->getX() - 14);
			_iconFood->setY(_uiRoom[i]->getY());
			_foodIdx = i;
		}
	}

	_arrIsClear = MAPMANAGER->getClearMap();

}
