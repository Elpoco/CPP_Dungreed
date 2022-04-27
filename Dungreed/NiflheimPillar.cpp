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
	this->initAnimation();
	Enemy::init();

	_info = DBMANAGER->getInfo(Code::UNIT::NIFLEHEIM_PILLAR);
	_isFlying = true;

	settingHp(_info.hp);
	
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

	_wideLeft = 460;//*_niflheimX - 300;
	_wideRight = 1030;// *_niflheimX + 300;
	_wideTop = 185;//*_niflheimY - 300;
	_wideBottom = 580;// *_niflheimY + 100;
}

void NiflheimPillar::render(HDC hdc)
{
	Enemy::render(hdc);
}

void NiflheimPillar::hitAttack(int dmg, int dir)
{
	OBJECTMANAGER->addDynamicImageFont(_x, _rc.top, dmg, dir);
	_curHp -= dmg;
	if (_curHp < 1)
	{
		_isDestory = true;
	}
}

void NiflheimPillar::deleteEffect()
{
	OBJECTMANAGER->addEffect(ImageName::Enemy::dieSmall, _x, _y);
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
		}
		else
		{
			_spinSpeed = AROUND_SPEED;
			_x = cosf(_bossAngle) * (_bossDistance - 50) + *_niflheimX;
			_y = sinf(_bossAngle) * (_bossDistance - 50) + *_niflheimY;
		}
		
		_imgAngle = GetAngle(_x, _y, *_niflheimX, *_niflheimY);
		_bossAngle -= _spinSpeed;
		break;
	case Niflheim::NIFLHEIM_SKILL::WIDE:
	case Niflheim::NIFLHEIM_SKILL::WIDE_LINE:
	case Niflheim::NIFLHEIM_SKILL::LINE_UP:
		_spinSpeed = 0.0f;

		if (//_skill == Niflheim::NIFLHEIM_SKILL::LINE_UP &&
			abs(_movePoint.x - _x) > 100) _imgAngle = 2.0f;

		_imgAngle += 0.03f;

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
		}

		//if(!_wideAngle)
			_wideAngle = GetAngle(_x, _y, _movePoint.x, _movePoint.y);

		_x += cosf(_wideAngle) * (abs(_movePoint.x - _x) / 10);
		//_y -= sinf(_wideAngle) * (abs(_movePoint.y - _y) / 5);
		if (_y != _movePoint.y)
		{
			_y += (_movePoint.y - _y) / 3;
		}
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
		_imgAngle = GetAngle(_x, _y, *_niflheimX, *_niflheimY);
	}
	_rotateCenter = PointMake(_x, _y);
}

void NiflheimPillar::initAnimation()
{
	_vImages.push_back(FindImage(ImageName::Enemy::Niflheim::pillar));
	_imgWidth = _vImages[0]->getFrameWidth();
	_imgHeight = _vImages[0]->getFrameHeight();
	_frameInfo.maxFrameX = _vImages[0]->getMaxFrameX();
}

void NiflheimPillar::settingOrder(int idx)
{
	_order = (PILLAR_ORDER)idx;
}

