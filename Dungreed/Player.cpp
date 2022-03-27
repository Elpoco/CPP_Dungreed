#include "Stdafx.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

HRESULT Player::init(void)
{
	Unit::init();

	this->initAnimation();

	_moveSpeed = MOVE_SPEED;

	return S_OK;
}

void Player::release(void)
{
	Unit::release();
}

void Player::update(void)
{
	Unit::update();

	this->move();
	this->animation();
}

void Player::render(HDC hdc)
{
	Unit::render(hdc);
}

void Player::initAnimation(void)
{
	_vImages.push_back(IMAGEMANAGER->findImage("PlayerIdle"));
	_vImages.push_back(IMAGEMANAGER->findImage("PlayerRun"));
}

void Player::move(void)
{
	if (KEYMANAGER->isStayKeyDown(castingToInt(KEY::LEFT)))
	{
		_state = PLAYER_STATE::RUN;
		_x -= _moveSpeed;
		CAMERAMANAGER->moveX(-_moveSpeed);
	}

	if (KEYMANAGER->isStayKeyDown(castingToInt(KEY::RIGHT)))
	{
		_state = PLAYER_STATE::RUN;
		_x += _moveSpeed;
		CAMERAMANAGER->moveX(_moveSpeed);
	}

	if (KEYMANAGER->isStayKeyDown(castingToInt(KEY::DOWN)))
	{

	}

	if (KEYMANAGER->isOnceKeyUp(castingToInt(KEY::LEFT)) ||
		KEYMANAGER->isOnceKeyUp(castingToInt(KEY::RIGHT)))
	{
		_state = PLAYER_STATE::IDLE;
	}

	if (KEYMANAGER->isOnceKeyUp(castingToInt(KEY::UP)) ||
		KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		Unit::jump();
	}


	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{

	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{

	}
}

void Player::animation(void)
{
	switch (_state)
	{
	case PLAYER_STATE::IDLE:
		_imgCurrent = castingToInt(PLAYER_STATE::IDLE);
		break;
	case PLAYER_STATE::RUN:
		_imgCurrent = castingToInt(PLAYER_STATE::RUN);
		break;
	default:
		break;
	}

	if (_ptMouse.x < _x) _isLeft = true;
	else _isLeft = false;
}
