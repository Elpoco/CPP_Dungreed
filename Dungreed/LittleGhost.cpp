#include "Stdafx.h"
#include "LittleGhost.h"

LittleGhost::LittleGhost(float x, float y)
{
	_x = x;
	_y = y;
}

LittleGhost::~LittleGhost()
{
}

HRESULT LittleGhost::init()
{
	Enemy::init();
	this->initAnimation();

	_isFlying = true;

	_info = DBMANAGER->getInfo(Code::UNIT::LITTLE_GHOST);
	_scanScale = { 15,15 };
	_moveSpeed = LittleGhostSet::MOVE_SPEED;

	settingHp(_info.hp);

	return S_OK;
}

void LittleGhost::release()
{
	Enemy::release();
}

void LittleGhost::update()
{
	Enemy::update();
	this->move();
	Unit::updateRect();
	this->animation();
}

void LittleGhost::render(HDC hdc)
{
	Enemy::render(hdc);
}

void LittleGhost::move()
{
	if (_isPlayerScan)
	{
		float angle = GetAngle(_x, _y, _ptPlayer.x, _ptPlayer.y);
		_x += cosf(angle) * _moveSpeed;
		_y -= sinf(angle) * _moveSpeed;
	}
}

void LittleGhost::animation()
{
}

void LittleGhost::initAnimation()
{
	_vImages.push_back(FindImage(ImageName::Enemy::littleGhostIdle));

	_imgWidth = _vImages[0]->getFrameWidth();
	_imgHeight = _vImages[0]->getFrameHeight();
}
