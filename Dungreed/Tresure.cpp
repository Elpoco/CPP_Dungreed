#include "Stdafx.h"
#include "Tresure.h"

Tresure::Tresure(float x, float y)
	: _isOpen(FALSE)
{
	_x = x;
	_y = y;
}

Tresure::~Tresure()
{
}

HRESULT Tresure::init()
{
	switch (MAPMANAGER->getCurMapCode())
	{
	case Code::MAP::BELIAL:
	case Code::MAP::NIFLHEIM:
		_type = TRESURE_TYPE::BOSS;
		
		break;
	default:
		_type = RND->getRndEnum(TRESURE_TYPE::BASIC, TRESURE_TYPE::TYPE_CNT);
		break;
	}

	switch (_type)
	{
	default:
	case Tresure::TRESURE_TYPE::BASIC:
		_img = FindImage(ImageName::Dungeon::BasicTresure);
		break;
	case Tresure::TRESURE_TYPE::BLUE:
		_img = FindImage(ImageName::Dungeon::BlueTresureClosed);
		break;
	case Tresure::TRESURE_TYPE::BOSS:
		_img = FindImage(ImageName::Dungeon::BossTresureClosed);
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

		int maxBullion;
		int maxCoin;
		switch (_type)
		{
		case Tresure::TRESURE_TYPE::BASIC:
			maxBullion = 1;
			maxCoin = 3;
			break;
		case Tresure::TRESURE_TYPE::BLUE:
			maxBullion = 3;
			maxCoin = 7;
			break;
		case Tresure::TRESURE_TYPE::BOSS:
			maxBullion = 7;
			maxCoin = 15;
			break;
		default:
			break;
		}

		for (int i = 0; i < 2; i++)
		{
			ITEMMANAGER->dropItem(Code::ITEM::BULLION, _x, _y, TRUE);
		}
		for (int i = 0; i < 5; i++)
		{
			ITEMMANAGER->dropItem(Code::ITEM::COIN, _x, _y, TRUE);
		}
		ITEMMANAGER->dropItem(RND->getRndEnum(Code::ITEM::WEAPON_S, Code::ITEM::WEAPON_CNT), _x, _y);
	}
}
