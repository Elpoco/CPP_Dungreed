#include "Stdafx.h"
#include "Player.h"

#include "Item.h"

using namespace PlayerSet;

Player::Player()
	: _isDash(FALSE)
	, _mainHandX(15)
	, _dashMove(DASH_DISTANCE)
	, _isStop(FALSE)
{
}

Player::Player(float x, float y)
	: _isDash(FALSE)
	, _mainHandX(15)
	, _dashMove(DASH_DISTANCE)
	, _isStop(FALSE)
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

	ITEMMANAGER->inventoryInit();
	ITEMMANAGER->getItem(Code::ITEM::SHOT_SWORD);
	ITEMMANAGER->getItem(Code::ITEM::COLT);
	ITEMMANAGER->getItem(Code::ITEM::COLT);
	ITEMMANAGER->getItem(Code::ITEM::COLT);
	ITEMMANAGER->getItem(Code::ITEM::COLT);
	ITEMMANAGER->getItem(Code::ITEM::COLT);
	ITEMMANAGER->getItem(Code::ITEM::COLT);

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
	if (!_isRender) return;
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

int Player::getDmg()
{
	if (!ITEMMANAGER->getEquipItem()) return 1;
	return ITEMMANAGER->getEquipItem()->getDmg();
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
	
	if (_isStop) return;
	if (UIMANAGER->onInventory()) return;

	if (IsStayKeyDown(KEY::LEFT))	 this->moveLeft();
	if (IsStayKeyDown(KEY::RIGHT))	 this->moveRight();
	if (IsOnceKeyUp(KEY::LEFT))		 this->setIdle();
	if (IsOnceKeyUp(KEY::RIGHT))	 this->setIdle();
	if (IsStayKeyDown(KEY::CLICK_L)) this->attack();
	if (IsOnceKeyDown(KEY::CLICK_R)) this->dash();

	if (IsOnceKeyDown(KEY::UP) || IsOnceKeyDown(KEY::SPACE))  Unit::jump();

	// 캐릭터 좌우
	if (_ptMouse.x < CAMERAMANAGER->calRelX(_x))
	{
		_isLeft = true;
		_mainHandX = _x - 20;
	}
	else
	{
		_isLeft = false;
		_mainHandX = _x + 19;
	}

	if (_isJump || _isFall) _state = PLAYER_MOTION::JUMP;
	if (_isDash) _state = PLAYER_MOTION::DASH;
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

	_rcResizeW = 20;
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
	if (ITEMMANAGER->getEquipItem())
	{
		_rcAttack = ITEMMANAGER->getEquipItem()->attack();
	}
	else
	{
		if (_isDebug)
		{
			// 디버그모드 공격 (무기 안들어야함)
			_rcAttack = RectMakeCenter(_hand.x, _hand.y, WINSIZE_X * 2, WINSIZE_Y * 2);
		}
	}
}

void Player::dash()
{
	_isDash = TRUE;
	_isJump = FALSE;
	_dashAngle = GetAngle(PointMake(_x, _y), CAMERAMANAGER->calAbsPt(_ptMouse));
	
	SOUNDMANAGER->play(SoundName::Player::dash, _sound);
	OBJECTMANAGER->addEffect(ImageName::Player::runFX, _rc.left, _rc.bottom);
}

void Player::getItem(Code::ITEM code)
{
	if (code > Code::ITEM::ITEM)
		ITEMMANAGER->getItem(code);
}
