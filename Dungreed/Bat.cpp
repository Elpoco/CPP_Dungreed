#include "Stdafx.h"
#include "Bat.h"

using namespace BatSet;

Bat::Bat(float x, float y, Code::UNIT code)
{
	_x = x;
	_y = y;

	switch (code)
	{
	case Code::UNIT::BAT:
		_batType = BAT_TYPE::NORMAL;
		break;
	case Code::UNIT::GIANT_BAT:
		_batType = BAT_TYPE::GIANT;
		break;
	case Code::UNIT::RED_GIANT_BAT:
		_batType = BAT_TYPE::RED;
		break;
	default:
		break;
	}
}

Bat::~Bat()
{
}

HRESULT Bat::init()
{
	this->initAnimation();
	Enemy::init();

	_isFlying = true;

	switch (_batType)
	{
	default:
	case Bat::BAT_TYPE::NORMAL:
		_info = DBMANAGER->getInfo(Code::UNIT::BAT);
		break;
	case Bat::BAT_TYPE::GIANT:
		_info = DBMANAGER->getInfo(Code::UNIT::GIANT_BAT);
		break;
	case Bat::BAT_TYPE::RED:
		_info = DBMANAGER->getInfo(Code::UNIT::RED_GIANT_BAT);
		break;
	}

	_scanScale = { 10,10 };

	settingHp(_info.hp);

	_attackTime = TIMEMANAGER->getWorldTime();
	_moveSpeed = 2.0f;
	_distance = 500;

	return S_OK;
}

void Bat::release()
{
	Enemy::release();
}

void Bat::update()
{
	Enemy::update();
	this->move();
	Unit::updateRect();
}

void Bat::render(HDC hdc)
{
	Enemy::render(hdc);
}

void Bat::move()
{
	if (_isPlayerScan)
	{
		if (_attackTime + _info.atkTime < TIMEMANAGER->getWorldTime()) this->attack();

		if (GetDistance(PointMake(_x, _y), _ptPlayer) > _distance)
		{
			if (_state == IDLE)
			{
				_distance = RND->getFromFloatTo(400, 700);
				_angle = GetAngle(PointMake(_x, _y), _ptPlayer);
				_x += cosf(_angle) * _moveSpeed;
				_y -= sinf(_angle) * _moveSpeed;
			}
		}
	}

	if (_state == ATTACK)
	{
		switch (_batType)
		{
		case Bat::BAT_TYPE::NORMAL:
			if (_shootTime + 0.5f > TIMEMANAGER->getWorldTime()) break;
			_shootTime = TIMEMANAGER->getWorldTime();

			SOUNDMANAGER->play(SoundName::FireBall, _sound);
			OBJECTMANAGER->addBullet(
				ObjectEnum::OBJ_TYPE::ENEMY_OBJ,
				ImageName::Enemy::BatBullet,
				_x,
				_y,
				_angle,
				BULLET_SPEED,
				_info.dmg,
				ImageName::Enemy::BatBulletHit
			);

			break;
		case Bat::BAT_TYPE::GIANT:
			if (_shootTime + 0.2f > TIMEMANAGER->getWorldTime()) break;
			_shootTime = TIMEMANAGER->getWorldTime();

			for (int i = 0; i < 3; i++)
			{
				SOUNDMANAGER->play(SoundName::FireBall, _sound);
				OBJECTMANAGER->addBullet(
					ObjectEnum::OBJ_TYPE::ENEMY_OBJ,
					ImageName::Enemy::BatBullet,
					_x,
					_y,
					_angle + (PI / 10) - (PI / 10) * i,
					BULLET_SPEED,
					_info.dmg,
					ImageName::Enemy::BatBulletHit
				);
			}
			break;
		case Bat::BAT_TYPE::RED:
			if (_shootTime + 0.5f > TIMEMANAGER->getWorldTime()) break;
			_shootTime = TIMEMANAGER->getWorldTime();

			for (int i = 0; i < 360; i += 30)
			{
				SOUNDMANAGER->play(SoundName::FireBall, _sound);
				OBJECTMANAGER->addBullet(
					ObjectEnum::OBJ_TYPE::ENEMY_OBJ,
					ImageName::Enemy::BatBullet,
					_x + cosf(DegToRad(i)) * 50,
					_y + sinf(DegToRad(i)) * 50,
					_angle,
					BULLET_SPEED,
					_info.dmg,
					ImageName::Enemy::BatBulletHit
				);
			}
			break;
		default:
			break;
		}
	}
}

void Bat::initAnimation()
{
	switch (_batType)
	{
	default:
	case Bat::BAT_TYPE::NORMAL:
		_vImages.push_back(FindImage(ImageName::Enemy::BatIdle));
		_vImages.push_back(FindImage(ImageName::Enemy::BatAttack));
		break;
	case Bat::BAT_TYPE::GIANT:
		_vImages.push_back(FindImage(ImageName::Enemy::GiantBat));
		_vImages.push_back(FindImage(ImageName::Enemy::GiantBatAttack));
		break;
	case Bat::BAT_TYPE::RED:
		_vImages.push_back(FindImage(ImageName::Enemy::RedGiantBat));
		_vImages.push_back(FindImage(ImageName::Enemy::RedGiantBatAttack));
		break;
	}

	_imgWidth = _vImages[0]->getFrameWidth();
	_imgHeight = _vImages[0]->getFrameHeight();

	_frameInfo.maxFrameX = _vImages[1]->getMaxFrameX();
}

void Bat::attack()
{
	_shootTime = _attackTime = TIMEMANAGER->getWorldTime();
	_state = ATTACK;
	_frameInfo.x = 0;
	_angle = GetAngle(PointMake(_x, _y), _ptPlayer);

	switch (_batType)
	{
	case Bat::BAT_TYPE::NORMAL:
		SOUNDMANAGER->play(SoundName::Enemy::Bat, _sound);
		break;
	case Bat::BAT_TYPE::GIANT:
		SOUNDMANAGER->play(SoundName::Enemy::Bat_giant, _sound);
		break;
	case Bat::BAT_TYPE::RED:
		SOUNDMANAGER->play(SoundName::Enemy::Bat_red, _sound);
		break;
	default:
		break;
	}
}

void Bat::frameUpdateEvent()
{
	if (_state == ATTACK && _frameInfo.x > _frameInfo.maxFrameX)
	{
		_state = IDLE;
	}
}
