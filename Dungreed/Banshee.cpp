#include "Stdafx.h"
#include "Banshee.h"

Banshee::Banshee(float x, float y)
{
	_x = x;
	_y = y;
}

Banshee::~Banshee()
{
}

HRESULT Banshee::init()
{
	this->initAnimation();
	Enemy::init();

	_isFlying = true;

	_info = DBMANAGER->getInfo(Code::UNIT::BANSHEE);
	_scanScale = { 30,15 };

	settingHp(_info.hp);

	_attackTime = TIMEMANAGER->getWorldTime();

	return S_OK;
}

void Banshee::release()
{
	Enemy::release();
}

void Banshee::update()
{
	Enemy::update();
	this->move();
	Unit::updateRect();
}

void Banshee::render(HDC hdc)
{
	Enemy::render(hdc);
}

void Banshee::move()
{
	if (_isPlayerScan)
	{
		if (_attackTime + _info.atkTime < TIMEMANAGER->getWorldTime()) this->attack();
	}
}

void Banshee::initAnimation()
{
	_vImages.push_back(FindImage(ImageName::Enemy::BansheeIdle));
	_vImages.push_back(FindImage(ImageName::Enemy::BansheeATK));

	_imgWidth = _vImages[0]->getFrameWidth();
	_imgHeight = _vImages[0]->getFrameHeight();

	_frameInfo.maxFrameX = _vImages[0]->getMaxFrameX();
	_frameInfo.tick = 13;
}

void Banshee::attack()
{
	_attackTime = TIMEMANAGER->getWorldTime();
	_state = ATTACK;
	_frameInfo.x = 0;

	SOUNDMANAGER->play(SoundName::Enemy::BansheeATK, _sound);

	for (int i = 0; i < 8; i++)
	{
		OBJECTMANAGER->addBullet(
			ObjectEnum::OBJ_TYPE::ENEMY_OBJ,
			ImageName::Enemy::BansheeBullet,
			_x,
			_y,
			PI * i * 0.25,
			3.0f,
			_info.dmg,
			ImageName::Enemy::BansheeBulletFX,
			1500,
			TRUE,
			FALSE
		);
	}
}

void Banshee::frameUpdateEvent()
{
	if (_state == ATTACK && _frameInfo.x > _frameInfo.maxFrameX)
	{
		_state = IDLE;
	}
}
