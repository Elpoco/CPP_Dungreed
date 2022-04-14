#include "Stdafx.h"
#include "Player.h"

#include "Inventory.h"

using namespace PlayerSet;

Player::Player()
{
}

Player::Player(float x, float y)
{
	_x = x;
	_y = y;
}

Player::~Player()
{
}

HRESULT Player::init()
{
	Unit::init();

	_rcResize = 35;
	this->initAnimation();

	CAMERAMANAGER->followCamera(this);

	_weapon = GPIMAGEMANAGER->findImage(ImageName::Item::Weapon::basicShotSword);
	_mainHandX = 15;
	_atkCnt = 0;

	_inventory = new Inventory();

	return S_OK;
}

void Player::release()
{
	Unit::release();
}

void Player::update()
{
	Unit::update();
	this->move();
	Unit::updateRect();
	this->animation();
	this->settingWeapon();
}

void Player::render(HDC hdc)
{
	Unit::render(hdc);

	CAMERAMANAGER->printRectangle(hdc, RectMakeCenter(_mainHandX, _y + 20, 5, 5));

	CAMERAMANAGER->render(hdc, _weapon, _rcWeapon.left, _rcWeapon.top, _angleWeapon, PointMake(_mainHandX, _y + 20));
}

void Player::hitAttack(int dmg, int dir)
{
	if (_hitTime + HIT_TIME > TIMEMANAGER->getWorldTime()) return;

	OBJECTMANAGER->addDynamicImageFont(_x, _rc.top, dmg, dir);

	_hitTime = TIMEMANAGER->getWorldTime();
	_isHit = true;
	_imgAlpha = HIT_ALPHA;
}

void Player::move()
{
	_state = PLAYER_MOTION::IDLE;

	if (KEYMANAGER->isStayKeyDown(KEY::LEFT))	this->moveLeft();
	if (KEYMANAGER->isStayKeyDown(KEY::RIGHT))	this->moveRight();
	if (KEYMANAGER->isOnceKeyUp(KEY::LEFT))		_state = PLAYER_MOTION::IDLE;
	if (KEYMANAGER->isOnceKeyUp(KEY::RIGHT))	_state = PLAYER_MOTION::IDLE;

	if (KEYMANAGER->isStayKeyDown(KEY::DOWN))
	{
		//_y += _moveSpeed;
	}
	if (KEYMANAGER->isStayKeyDown(KEY::UP))
	{
		//_y -= _moveSpeed;
	}


	if (KEYMANAGER->isOnceKeyDown(KEY::UP) ||
		KEYMANAGER->isOnceKeyDown(KEY::SPACE))  Unit::jump();

	_rcAttack = { 0,0,0,0 };
	if (KEYMANAGER->isOnceKeyDown(KEY::CLICK_L))
	{
		if (_atkCnt == 0) _atkCnt = 1;
		else _atkCnt = 0;

		float angle = GetAngle(CAMERAMANAGER->calRelX(_x), CAMERAMANAGER->calRelY(_y), _ptMouse.x, _ptMouse.y);

		float effectX = cosf(angle) * 30 + _x;
		float effectY = -sinf(angle) * 30 + _y;

		_rcAttack = OBJECTMANAGER->addEffect(
				ImageName::Effect::Weapon::effectBasic,
				effectX,
				effectY,
				angle / PI * 180,
				PointMake(effectX, effectY)
		);
	}

	if (KEYMANAGER->isOnceKeyDown(KEY::CLICK_R))
	{

	}

	if (_isJump || _isFall)
	{
		_state = PLAYER_MOTION::JUMP;
	}
}

void Player::animation()
{
	if (_ptMouse.x < CAMERAMANAGER->calRelX(_x))
	{
		_isLeft = true;
		_mainHandX = _x - 15;
	}
	else 
	{ 
		_isLeft = false; 
		_mainHandX = _x + 15;
	}

	if (_isHit)
	{
		if (_frameInfo.cnt == 0)
		{
			_imgAlpha = _imgAlpha == 0 ? HIT_ALPHA : 0;
		}

		if (_hitTime + HIT_TIME < TIMEMANAGER->getWorldTime())
		{
			_isHit = false;
			_imgAlpha = 0;
		}
	}

}

void Player::initAnimation()
{
	_vImages.push_back(IMAGEMANAGER->findImage(ImageName::Player::idle));
	_vImages.push_back(IMAGEMANAGER->findImage(ImageName::Player::run));
	_vImages.push_back(IMAGEMANAGER->findImage(ImageName::Player::jump));

	_imgWidth = _vImages[0]->getFrameWidth() - _rcResize;
	_imgHeight = _vImages[0]->getFrameHeight();
}

void Player::moveLeft()
{
	_state = PLAYER_MOTION::RUN;
	if (!_isCollision[ColliderEnum::DIRECTION::LEFT])
		_x -= _moveSpeed;
}

void Player::moveRight()
{
	_state = PLAYER_MOTION::RUN;
	if (!_isCollision[ColliderEnum::DIRECTION::RIGHT])
		_x += _moveSpeed;
}

void Player::settingWeapon()
{
	_rcWeapon = RectMakeCenter(_mainHandX, _y + 20, _weapon->getWidth(), _weapon->getHeight());
	_angleWeapon = GetAngleDeg(CAMERAMANAGER->calRelX(_x), CAMERAMANAGER->calRelY(_y), _ptMouse.x, _ptMouse.y);

	if (_isLeft)
	{
		if (_atkCnt == 0)
		{
			_angleWeapon -= 80;
		}
		else
		{
			_angleWeapon -= 190;
		}
	}
	else
	{
		if (_atkCnt == 0)
		{
			_angleWeapon += 80;
		}
		else
		{
			_angleWeapon += 190;
		}
	}
}
