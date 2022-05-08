#include "Stdafx.h"
#include "Scarecrow.h"

Scarecrow::Scarecrow(float x, float y)
{
	_x = x;
	_y = y;
}

Scarecrow::~Scarecrow()
{
}

HRESULT Scarecrow::init()
{
	this->initAnimation();
	Enemy::init();

	_info = DBMANAGER->getInfo(Code::UNIT::SCARECROW);

	settingHp(_info.hp);

	return S_OK;
}

void Scarecrow::release()
{
	Enemy::release();
}

void Scarecrow::update()
{
	Enemy::update();
	this->move();
	Unit::updateRect();

	_rcAttack = _rc;
}

void Scarecrow::render(HDC hdc)
{
	Enemy::render(hdc);
}

void Scarecrow::move()
{
}

void Scarecrow::initAnimation()
{
	_vImages.push_back(FindImage(ImageName::Enemy::Scarecrow));

	_imgWidth = _vImages[0]->getFrameWidth();
	_imgHeight = _vImages[0]->getFrameHeight();
}
