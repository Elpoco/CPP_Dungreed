#include "Stdafx.h"
#include "LittleGhost.h"

LittleGhost::LittleGhost()
{
}

LittleGhost::~LittleGhost()
{
}

HRESULT LittleGhost::init()
{
	Enemy::init();
	this->initAnimation();

	_x = 100;
	_y = 200;
	_isFlying = true;

	_name = "���� ����";
	_scanScale = { 15,15 };
	_moveSpeed = UnitSet::Enemy::LittleGhost::MOVE_SPEED;

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
		float angle = getAngle(_x, _y, _ptPlayer.X, _ptPlayer.Y);
		_x += cosf(angle) * _moveSpeed;
		_y -= sinf(angle) * _moveSpeed;
	}

	_rcScan = RectFMakeCenter(_x, _y, _imgWidth * _scanScale.x, _imgHeight * _scanScale.y);
}

void LittleGhost::animation()
{
	_imgCurrent = _state;
}

void LittleGhost::initAnimation()
{
	_vImages.push_back(IMAGEMANAGER->findImage(ImageName::Enemy::littleGhostIdle));

	_imgWidth = _vImages[0]->getFrameWidth();
	_imgHeight = _vImages[0]->getFrameHeight();
}
