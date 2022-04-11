#include "Stdafx.h"
#include "NiflheimPillar.h"

NiflheimPillar::NiflheimPillar(float x, float y)
	: _angle(0.0f)
{
	_x = x;
	_y = y;

	_startSpawn = TRUE;
	_isSpawn = TRUE;
}

NiflheimPillar::~NiflheimPillar()
{
}

HRESULT NiflheimPillar::init()
{
	Enemy::init();
	this->initAnimation();

	_isFlying = true;

	_name = "¾óÀ½ ±âµÕ";

	return S_OK;
}

void NiflheimPillar::release()
{
	Enemy::release();
}

void NiflheimPillar::update()
{
	Enemy::update();
	this->move();
	Unit::updateRect();
	this->animation();
}

void NiflheimPillar::render(HDC hdc)
{
	//Enemy::render(hdc);
	CAMERAMANAGER->frameRender(
		hdc,
		_vImages[_imgCurrent],
		_rc.left,
		_rc.top,
		_frameInfo.x,
		_frameInfo.y,
		radToDeg(_angle),
		PointMake(_x,_y)
	);
	   	if (_isDebug)
	{
		CAMERAMANAGER->printRectangle(hdc, _rc, Color::Green);
		CAMERAMANAGER->printPoint(hdc, _rc.left, _rc.top, _x, _y, "x: %d, y: %d");
	}
}

void NiflheimPillar::move()
{
}

void NiflheimPillar::animation()
{
	if (_frameInfo.x >= 12)
	{
		_frameInfo.startFrameX = 12;
		_frameInfo.tick = 15;
		_angle += 0.03f;
	}
}
void NiflheimPillar::initAnimation()
{
	_vImages.push_back(GPIMAGEMANAGER->findImage(ImageName::Enemy::Niflheim::pillar));

	_imgWidth = _vImages[0]->getFrameWidth();
	_imgHeight = _vImages[0]->getFrameHeight();
}
