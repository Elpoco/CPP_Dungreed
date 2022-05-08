	#include "Stdafx.h"
#include "Worm.h"

Worm::Worm()
{
}

Worm::~Worm()
{
}

HRESULT Worm::init()
{
	_img = FindImage(ImageName::Dungeon::WormPassageIdle);
	_imgEat = FindImage(ImageName::Dungeon::WormPassageEat);

	_frameInfo.maxFrameX = _img->getMaxFrameX();
	_frameInfo.width = _img->getFrameWidth();
	_frameInfo.height = _img->getFrameHeight();

	_state = WORM_STATE::IDLE;

	return S_OK;
}

void Worm::release()
{
}

void Worm::update()
{
	animation();
}

void Worm::render(HDC hdc)
{
	if (_state == WORM_STATE::IDLE)
	{
		CAMERAMANAGER->frameRender(hdc, _img, _rc.left, _rc.top, _frameInfo.x, _frameInfo.y);
	}
	else
	{
		CAMERAMANAGER->frameRender(hdc, _imgEat, _rc.left, _rc.top, _frameInfo.x, _frameInfo.y);
	}
}

void Worm::collisionObject()
{
	UIMANAGER->showKeyboard(KEY::F, _x + _frameInfo.width * 0.5f, _rc.top);
	if (IsOnceKeyDown(KEY::F)) UIMANAGER->showWorldMap();
}

void Worm::animation()
{
	if (_frameInfo.cnt++ > _frameInfo.tick)
	{
		_frameInfo.cnt = 0;
		if (++_frameInfo.x > _frameInfo.maxFrameX)
		{
			_frameInfo.x = 0;
			if (_state == WORM_STATE::EAT) _state = WORM_STATE::IDLE;
		}
	}
}

void Worm::setPos(POINT pt)
{
	_x = pt.x;
	_y = pt.y;
	_rc = RectMake(_x, _y - _frameInfo.height, _frameInfo.width, _frameInfo.height);
}

void Worm::changeRoom()
{
	_state = WORM_STATE::EAT;
	_frameInfo.x = 0;
	SOUNDMANAGER->play(SoundName::dungeonEat, _sound);
}
