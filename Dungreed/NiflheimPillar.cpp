#include "Stdafx.h"
#include "NiflheimPillar.h"

using namespace NiflheimPillarSet;

NiflheimPillar::NiflheimPillar(float x, float y)
	: _skill(Niflheim::NIFLHEIM_SKILL::NONE)
	, _spinSpeed(0.01f)
	, _isInit(false)
	, _isDestory(false)
	, _wideAngle(0)
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

	settingHp(UnitSet::Enemy::NiflheimPillar::HP);
	
	_bossAngle = GetAngle(_x, _y, *_niflheimX, *_niflheimY);
	_bossDistance = GetDistance(_x, _y, *_niflheimX, *_niflheimY);

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
	Enemy::updateRect();
	this->animation();

	_wideLeft = *_niflheimX - 300;
	_wideRight = *_niflheimX + 300;
	_wideTop = 200; // *_niflheimY - 400;
	_wideBottom = 700; //*_niflheimY + 100;
}

void NiflheimPillar::render(HDC hdc)
{
	Enemy::render(hdc);

}

void NiflheimPillar::hitAttack(int dmg)
{
	_hp -= dmg;
	if (_hp < 1)
	{
		_isDestory = true;
	}
}

void NiflheimPillar::move()
{
	if (!_isInit) return;

	switch (_skill)
	{
	case Niflheim::NIFLHEIM_SKILL::NONE:
	case Niflheim::NIFLHEIM_SKILL::AROUND:
		if (_skill == Niflheim::NIFLHEIM_SKILL::NONE)
		{
			_spinSpeed = IDLE_SPEED;
			_wideAngle = 0.0f;
			_x = cosf(_bossAngle) * _bossDistance + *_niflheimX;
			_y = sinf(_bossAngle) * _bossDistance + *_niflheimY;
			this->settingOrder();
		}
		else
		{
			_spinSpeed = AROUND_SPEED;
			_x = cosf(_bossAngle) * (_bossDistance - 50) + *_niflheimX;
			_y = sinf(_bossAngle) * (_bossDistance - 50) + *_niflheimY;
		}
		
		_imgAngle = GetAngleDeg(_x, _y, *_niflheimX, *_niflheimY) + 90;
		_bossAngle -= _spinSpeed;
		break;
	case Niflheim::NIFLHEIM_SKILL::WIDE:
	case Niflheim::NIFLHEIM_SKILL::WIDE_LINE:
	case Niflheim::NIFLHEIM_SKILL::LINE_UP:
		_spinSpeed = 0.0f;

		if (//_skill == Niflheim::NIFLHEIM_SKILL::LINE_UP &&
			abs(_movePoint.x - _x) > 100) _imgAngle = 120;

		_imgAngle += 1;

		switch (_order)
		{
		case NiflheimPillar::LT:
			if (_skill == Niflheim::NIFLHEIM_SKILL::LINE_UP)
				_movePoint = PointMake(_wideRight, _wideTop + 50);
			else
				_movePoint = PointMake(_wideRight, _wideBottom);
			break;
		case NiflheimPillar::RT:
			if (_skill == Niflheim::NIFLHEIM_SKILL::LINE_UP)
				_movePoint = PointMake(_wideLeft, _wideTop + 50);
			else
				_movePoint = PointMake(_wideLeft, _wideBottom);
			break;
		case NiflheimPillar::LB:
			if (_skill == Niflheim::NIFLHEIM_SKILL::LINE_UP)
				_movePoint = PointMake(_wideRight - 200, _wideTop + 50);
			else
				_movePoint = PointMake(_wideRight, _wideTop);
			break;
		case NiflheimPillar::RB:
			if (_skill == Niflheim::NIFLHEIM_SKILL::LINE_UP)
				_movePoint = PointMake(_wideLeft + 200, _wideTop + 50);
			else
				_movePoint = PointMake(_wideLeft, _wideTop);
			break;
		default:
			break;
		}

		if(!_wideAngle)
			_wideAngle = GetAngle(_x, _y, _movePoint.x, _movePoint.y);

		_x += cosf(_wideAngle) * (abs(_movePoint.x - _x) / 10);
		_y -= sinf(_wideAngle) * (abs(_movePoint.y - _y) / 10);
		break;
	case Niflheim::NIFLHEIM_SKILL::FULL_ATTACK:
		_spinSpeed = 0.0f;
		break;
	default:
		break;
	}
}

void NiflheimPillar::animation()
{
	if (_frameInfo.x >= 11)
	{
		_frameInfo.startFrameX = 12;
		_frameInfo.tick = 15;
		_isInit = true;
	}
	else
	{
		_imgAngle = GetAngleDeg(_x, _y, *_niflheimX, *_niflheimY) + 90;
	}
	_rotateCenter = PointMake(_x, _y);
}

void NiflheimPillar::initAnimation()
{
	_vImages.push_back(GPIMAGEMANAGER->findImage(ImageName::Enemy::Niflheim::pillar));
	_imgWidth = _vImages[0]->getFrameWidth();
	_imgHeight = _vImages[0]->getFrameHeight();
	_frameInfo.maxFrameX = _vImages[0]->getMaxFrameX();
}

void NiflheimPillar::settingOrder()
{
	if (_x <= *_niflheimX && _y <= *_niflheimY)
	{
		_order = LT;
	}
	else if (_x > *_niflheimX && _y <= *_niflheimY)
	{
		_order = RT;
	}
	else if (_x <= *_niflheimX && _y >= *_niflheimY)
	{
		_order = LB;
	}
	else if(_x >= *_niflheimX && _y > *_niflheimY)
	{
		_order = RB;
	}
}
