#include "Stdafx.h"
#include "Tresure.h"

Tresure::Tresure(float x, float y, Code::TRESURE_TYPE type)
	: _isOpen(FALSE)
	, _isStop(FALSE)
	, _type(type)
{
	_x = x;
	_y = y;
}

Tresure::~Tresure()
{
}

HRESULT Tresure::init()
{
	if (_type == Code::TRESURE_TYPE::NONE)
	{
		switch (MAPMANAGER->getCurMapCode())
		{
		case Code::MAP::BELIAL:
		case Code::MAP::NIFLHEIM:
			_type = Code::TRESURE_TYPE::BOSS;
			break;
		default:
			_type = RND->getRndEnum(Code::TRESURE_TYPE::BASIC, Code::TRESURE_TYPE::TYPE_CNT);
			break;
		}
	}

	switch (_type)
	{
	default:
	case Code::TRESURE_TYPE::BASIC:
		_img = FindImage(ImageName::Dungeon::BasicTresure);
		break;
	case Code::TRESURE_TYPE::BLUE:
		_img = FindImage(ImageName::Dungeon::BlueTresure);
		break;
	case Code::TRESURE_TYPE::GOLD:
		_img = FindImage(ImageName::Dungeon::GoldTresure);
		break;
	case Code::TRESURE_TYPE::BOSS:
		_img = FindImage(ImageName::Dungeon::BossTresure);
		break;
	}

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	OBJECTMANAGER->addEffect(
		ImageName::Enemy::sapwn,
		_x,
		_y,
		0,
		ObjectEnum::OBJ_TYPE::EFFECT_BACK
	);

	return S_OK;
}

void Tresure::release()
{
}

void Tresure::update()
{
	if (!_isStop)
	{
		_y++;
		_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
	}
}

void Tresure::render(HDC hdc)
{
	CAMERAMANAGER->frameRender(hdc, _img, _rc.left, _rc.top, _isOpen, 0);
}

void Tresure::collisionObject()
{
	if (_isOpen) return;
	UIMANAGER->showKeyboard(KEY::F, _x, _rc.top);

	if (IsOnceKeyDown(KEY::F))
	{
		_isOpen = TRUE;
		SOUNDMANAGER->play(SoundName::Dungeon::OpenTresure, _sound);
		SOUNDMANAGER->play(SoundName::Item::coin, _sound);

		int maxBullion = 0;
		int maxCoin = 1;
		BOOL dropItem = TRUE;
		switch (_type)
		{
		case Code::TRESURE_TYPE::BASIC:
			maxBullion = 1;
			maxCoin = 3;
			break;
		case Code::TRESURE_TYPE::BLUE:
			maxBullion = 3;
			maxCoin = 7;
			break;
		case Code::TRESURE_TYPE::GOLD:
			dropItem = FALSE;
			maxBullion = 5;
			maxCoin = 12;
			break;
		case Code::TRESURE_TYPE::BOSS:
			maxBullion = 7;
			maxCoin = 15;
			break;
		default:
			break;
		}

		for (int i = 0; i < maxBullion; i++)
		{
			ITEMMANAGER->dropItem(Code::ITEM::BULLION, _x, _y, TRUE);
		}
		for (int i = 0; i < maxCoin; i++)
		{
			ITEMMANAGER->dropItem(Code::ITEM::COIN, _x, _y, TRUE);
		}

		if(dropItem)
			ITEMMANAGER->dropItem(RND->getRndEnum(Code::ITEM::SHOT_SWORD, Code::ITEM::ITEM_CNT), _x, _y);
	}
}
