#include "Stdafx.h"
#include "Player.h"

#include "Item.h"
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

	_item = ITEMMANAGER->getItem(Code::ITEM::SHOT_SWORD);
	_item->setPos(&_hand);
	_item->setIsLeft(&_isLeft);
	_item->equip();
	OBJECTMANAGER->addObject(ObjectEnum::TYPE::ITEM, _item);

	_mainHandX = 15;

	_inventory = new Inventory();
	OBJECTMANAGER->addUI(_inventory);

	return S_OK;
}

void Player::release()
{
	Unit::release();
	_inventory->release();
}

void Player::update()
{
	Unit::update();
	this->move();
	Unit::updateRect();
	this->animation();
	_inventory->update();
}

void Player::render(HDC hdc)
{
	Unit::render(hdc);

	CAMERAMANAGER->printRectangle(hdc, RectMakeCenter(_mainHandX, _y + 20, 5, 5));

	_inventory->render(hdc);
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
	if (_inventory->isOpen()) return;
	_state = PLAYER_MOTION::IDLE;

	if (IsStayKeyDown(KEY::LEFT))	this->moveLeft();
	if (IsStayKeyDown(KEY::RIGHT))	this->moveRight();
	if (IsOnceKeyUp(KEY::LEFT))		_state = PLAYER_MOTION::IDLE;
	if (IsOnceKeyUp(KEY::RIGHT))	_state = PLAYER_MOTION::IDLE;

	if (IsStayKeyDown(KEY::DOWN))
	{
		//_y += _moveSpeed;
	}
	if (IsStayKeyDown(KEY::UP))
	{
		//_y -= _moveSpeed;
	}

	if (IsOnceKeyDown(KEY::UP) ||
		IsOnceKeyDown(KEY::SPACE))  Unit::jump();

	_rcAttack = { 0,0,0,0 };
	if (IsOnceKeyDown(KEY::CLICK_L))
	{
		_rcAttack = _item->attack();
	}

	if (IsOnceKeyDown(KEY::CLICK_R))
	{

	}

	if (_isJump || _isFall)
	{
		_state = PLAYER_MOTION::JUMP;
	}

	// Ä³¸¯ÅÍ ÁÂ¿ì
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

	_hand = PointMake(_mainHandX, _y + 20);
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
