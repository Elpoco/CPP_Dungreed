#include "Stdafx.h"
#include "Skel.h"

Skel::Skel(float x, float y, Code::UNIT code)
{
	_x = x;
	_y = y;

	switch (code)
	{
	case Code::UNIT::SKEL:
		_skelType = SKEL_TYPE::SWORD;
		break;
	case Code::UNIT::SKEL_BOW:
		_skelType = SKEL_TYPE::BOW;
		break;
	default:
		break;
	}
}

Skel::~Skel()
{
}

HRESULT Skel::init()
{
	this->initAnimation();
	Enemy::init();

	_info = DBMANAGER->getInfo(Code::UNIT::SKEL);
	_scanScale = { 25, 15 };

	settingHp(_info.hp);

	_attackTime = TIMEMANAGER->getWorldTime();

	return S_OK;
}

void Skel::release()
{
	Enemy::release();
}

void Skel::update()
{
	Enemy::update();
	this->move();
	Unit::updateRect();
}

void Skel::render(HDC hdc)
{
	Enemy::render(hdc);

	CAMERAMANAGER->frameRender(hdc, _imgWeapon, _x, _y + 10, _weaponFrame.x, _weaponFrame.y, _angleWeapon);
}

void Skel::move()
{
	if (_isPlayerScan)
	{
		_state = IDLE;
		_rcAttack = { 0,0,0,0 };
		_anglePlayer = GetAngle(PointMake(_x, _y), _ptPlayer);

		switch (_skelType)
		{
		case Skel::SKEL_TYPE::SWORD:
			if (_isLeft)
			{
				if (_atkCnt == 0) _angleWeapon = DegToRad(60);
				else _angleWeapon = DegToRad(210);
			}
			else
			{
				if (_atkCnt == 0) _angleWeapon = DegToRad(120);
				else _angleWeapon = DegToRad(330);
			}

			if (GetDistance(PointMake(_x, _y), _ptPlayer) > 110)
			{
				int h = _ptPlayer.y - _y;
				if (h > 150)
				{
					Unit::downJump();
				}
				if (h < -170)
				{
					Unit::jump();
				}
				_x += _moveSpeed * _isLeft ? -1 : 1;
				_state = MOVE;
				break;
			}
			else
			{
				if (_attackTime + _info.atkTime < TIMEMANAGER->getWorldTime()) this->attack();
			}
			break;

		case Skel::SKEL_TYPE::BOW:
			_angleWeapon = _anglePlayer;

			if (_weaponFrame.x > 3 && _weaponFrame.cnt++ > _weaponFrame.maxFrameX)
			{
				_weaponFrame.cnt = 0;
				_weaponFrame.x++;
				if (_weaponFrame.x > _weaponFrame.maxFrameX)
				{
					_weaponFrame.x = 0;
				}

			}

			if (_attackTime + _info.atkTime < TIMEMANAGER->getWorldTime())
			{
				if (_weaponFrame.cnt++ > _weaponFrame.maxFrameX)
				{
					_weaponFrame.cnt = 0;
					if (_weaponFrame.x == 0) SOUNDMANAGER->play(SoundName::Enemy::arrow_load, _sound);

					_weaponFrame.x++;
					if (_weaponFrame.x == 4) this->attack();
				}
			}
		
			break;

		default:
			break;
		}
	}
}

void Skel::initAnimation()
{
	_vImages.push_back(FindImage(ImageName::Enemy::SkelIdle));
	_vImages.push_back(FindImage(ImageName::Enemy::SkelWalk));

	if (_skelType == SKEL_TYPE::BOW)
	{
		_imgWeapon = FindImage(ImageName::Enemy::SkelBow);
		_weaponFrame.maxFrameX = _imgWeapon->getMaxFrameX();
	}
	else
	{
		_imgWeapon = FindImage(ImageName::Enemy::SkelSword);
	}
	_atkCnt = 0;

	_imgWidth = _vImages[0]->getFrameWidth();
	_imgHeight = _vImages[0]->getFrameHeight();

	_weaponFrame.maxFrameX = _vImages[1]->getMaxFrameX();
}

void Skel::attack()
{
	_attackTime = TIMEMANAGER->getWorldTime();

	switch (_skelType)
	{
	case Skel::SKEL_TYPE::SWORD:
	{
		_atkCnt = !_atkCnt;
		float effectX = _x + cos(_anglePlayer) * 40;
		float effectY = _y - sin(_anglePlayer) * 40;
		_rcAttack = OBJECTMANAGER->addEffect(
			ImageName::Effect::Weapon::basicSwing,
			effectX,
			effectY,
			RadToDeg(_anglePlayer),
			PointMake(effectX, effectY)
		);

		SOUNDMANAGER->play(SoundName::Item::Weapon::swing0, _sound);
		break;
	}

	case Skel::SKEL_TYPE::BOW:
		OBJECTMANAGER->addBullet(
			ObjectEnum::OBJ_TYPE::ENEMY_OBJ,
			ImageName::Enemy::SkelArrow,
			_x,
			_y + 10,
			_anglePlayer,
			5.0f,
			_info.dmg,
			ImageName::Enemy::SkelArrowEffect
		);

		SOUNDMANAGER->play(SoundName::Enemy::arrow_shoot, _sound);
		break;
	default:
		break;
	}

	
}

void Skel::frameUpdateEvent()
{
}
