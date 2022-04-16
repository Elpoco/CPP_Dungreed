#include "Stdafx.h"
#include "Player.h"

#include "Item.h"
#include "Inventory.h"

using namespace PlayerSet;

Player::Player()
	: _isDash(FALSE)
	, _mainHandX(15)
	, _dashMove(DASH_DISTANCE)
{
}

Player::Player(float x, float y)
	: _isDash(FALSE)
	, _mainHandX(15)
	, _dashMove(DASH_DISTANCE)
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

	this->initAnimation();

	CAMERAMANAGER->followCamera(this);

	ITEMMANAGER->setPlayerBody(&_body);
	ITEMMANAGER->setPlayerHand(&_hand);
	ITEMMANAGER->setPlayerLeft(&_isLeft);

	_inventory = new Inventory;
	OBJECTMANAGER->addUI(_inventory);
	UIMANAGER->setInventory(_inventory);

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
}

void Player::render(HDC hdc)
{
	Unit::render(hdc);
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
	if (_isJump || _isFall) _state = PLAYER_MOTION::JUMP;
	if (_isDash)
	{
		_state = PLAYER_MOTION::DASH;
		if (_dashMove > 0)
		{
			_gravity = 0.0f;
			_dashMove -= DASH_SPEED;
			_x += cosf(_dashAngle) * DASH_SPEED;
			_y -= sinf(_dashAngle) * DASH_SPEED;
		}
		else
		{
			_isDash = FALSE;
			_dashMove = DASH_DISTANCE;
		}
	}

	_rcAttack = { 0,0,0,0 };

	_hand = PointMake(_mainHandX, _y + 5);
	_body = PointMake(_x, _y);
	
	if (UIMANAGER->onInventory()) return;

	if (IsStayKeyDown(KEY::LEFT))	 this->moveLeft();
	if (IsStayKeyDown(KEY::RIGHT))	 this->moveRight();
	if (IsOnceKeyUp(KEY::LEFT))		 this->setIdle();
	if (IsOnceKeyUp(KEY::RIGHT))	 this->setIdle();
	if (IsStayKeyDown(KEY::CLICK_L)) this->attack();
	if (IsOnceKeyDown(KEY::CLICK_R)) this->dash();

	if (IsOnceKeyDown(KEY::UP) || IsOnceKeyDown(KEY::SPACE))  Unit::jump();

	// дЁ╦╞ем аб©Л
	if (_ptMouse.x < CAMERAMANAGER->calRelX(_x))
	{
		_isLeft = true;
		_mainHandX = _x - 20;
	}
	else
	{
		_isLeft = false;
		_mainHandX = _x + 20;
	}
}

void Player::animation()
{
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
	_vImages.push_back(FindImage(ImageName::Player::idle));
	_vImages.push_back(FindImage(ImageName::Player::run));
	_vImages.push_back(FindImage(ImageName::Player::jump));

	_imgWidth = _vImages[0]->getFrameWidth();
	_imgHeight = _vImages[0]->getFrameHeight();
}

void Player::moveLeft()
{
	_state = PLAYER_MOTION::RUN;

	if (!_isCollision[ColliderEnum::DIRECTION::LEFT]) _x -= _moveSpeed;

}

void Player::moveRight()
{
	_state = PLAYER_MOTION::RUN;

	if (!_isCollision[ColliderEnum::DIRECTION::RIGHT]) _x += _moveSpeed;
	//if(_frameInfo.cnt == 0)
	//OBJECTMANAGER->addEffect(ImageName::Player::runFX, _rc.left, _rc.bottom);
}

void Player::setIdle()
{
	_state = PLAYER_MOTION::IDLE;
}

void Player::attack()
{
	_rcAttack = _inventory->getEquipItem()->attack();
}

void Player::dash()
{
	_isDash = TRUE;
	_dashAngle = GetAngle(PointMake(_x, _y), CAMERAMANAGER->calAbsPt(_ptMouse));
	
	OBJECTMANAGER->addEffect(ImageName::Player::runFX, _rc.left, _rc.bottom);
}

void Player::getItem(Code::ITEM code)
{
	
}
