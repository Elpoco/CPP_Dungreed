#include "Stdafx.h"
#include "Niflheim.h"

#include "NiflheimPillar.h"

Niflheim::Niflheim(float x, float y)
{
	_startSpawn = TRUE;
	_isSpawn = TRUE;

	_x = x;
	_y = y;
}

Niflheim::~Niflheim()
{
}

HRESULT Niflheim::init()
{
	Enemy::init();
	this->initAnimation();
	Unit::updateRect();

	_name = "니플헤임";
	_isFlying = true;

	//OBJECTMANAGER->addObject(
	//	ObjectEnum::TYPE::ENEMY,
	//	new NiflheimPillar(_x - 100, _y)
	//);

	return S_OK;
}

void Niflheim::release()
{
	Enemy::release();
}

void Niflheim::update()
{
	Enemy::update();
	this->move();
	Unit::updateRect();
	this->animation();
}

void Niflheim::render(HDC hdc)
{
	Enemy::render(hdc);

	//CAMERAMANAGER->frameRender(hdc, ImageName::Enemy::Niflheim::pillar, _x, _y, 10, 0);
}

void Niflheim::deleteEffect()
{
}

void Niflheim::move()
{
}

void Niflheim::animation()
{
}

void Niflheim::initAnimation()
{
	_vImages.push_back(IMAGEMANAGER->findImage(ImageName::Enemy::Niflheim::idle));
	_vImages.push_back(IMAGEMANAGER->findImage(ImageName::Enemy::Niflheim::attack));

	_imgWidth = _vImages[0]->getFrameWidth();
	_imgHeight = _vImages[0]->getFrameHeight();
}
