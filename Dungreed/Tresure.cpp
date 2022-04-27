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
	if (MAPMANAGER->getCurMapCode() > Code::MAP::BOSS)
	{
		_img = FindImage(ImageName::Dungeon::tresureBoss);
	}
	else
	{
		_img = FindImage(ImageName::Dungeon::tresureNormal);
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
	CAMERAMANAGER->frameRender(hdc, _img, _rc.left, _rc.top, 0, _isOpen);
}

void Tresure::collisionObject()
{
	if (_isOpen) return;
	UIMANAGER->showKeyboard(KEY::F, _x, _rc.top);

	if (IsOnceKeyDown(KEY::F))
	{
		_isOpen = TRUE;
		SOUNDMANAGER->play(SoundName::Dungeon::OpenTresure, _sound);

		for (int i = 0; i < 4; i++)
		{
			ITEMMANAGER->dropItem(Code::ITEM::BULLION, _x, _y, TRUE);
		}
		for (int i = 0; i < 10; i++)
		{
			ITEMMANAGER->dropItem(Code::ITEM::COIN, _x, _y, TRUE);
		}
		ITEMMANAGER->dropItem(Code::ITEM::COLT, _x, _y);
	}
}
