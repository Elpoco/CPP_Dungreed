#include "Stdafx.h"
#include "Player.h"

#include "Item.h"

using namespace PlayerSet;

Player::Player()
	: _mainHandX(15)
	, _dashMove(DASH_DISTANCE)
	, _isStop(FALSE)
{
}

Player::Player(float x, float y)
	: _mainHandX(15)
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
	this->initAnimation();
	Unit::init();

	CAMERAMANAGER->followCamera(this);
	CAMERAMANAGER->lockCamera();

	PLAYERMANAGER->init();

	PLAYERMANAGER->setPlayerBody(&_body);
	PLAYERMANAGER->setPlayerHand(&_hand);
	PLAYERMANAGER->setPlayerLeft(&_isLeft);

	UIMANAGER->initInventory();
	ITEMMANAGER->giveItem(Code::ITEM::SHOT_SWORD);

	if (_isDebug)
	{
		ITEMMANAGER->giveItem(Code::ITEM::BAMBOO_SWORD);
		ITEMMANAGER->giveItem(Code::ITEM::LIGHTSABER);
		ITEMMANAGER->giveItem(Code::ITEM::COLT);
		ITEMMANAGER->giveItem(Code::ITEM::MULTI_BULLET);
		ITEMMANAGER->giveItem(Code::ITEM::MAGNIFYINGGLASS);
		ITEMMANAGER->giveItem(Code::ITEM::WINGBOOTS);
		ITEMMANAGER->giveItem(Code::ITEM::GATLINGGUN);
		ITEMMANAGER->giveItem(Code::ITEM::COSMOSSWORD);
		ITEMMANAGER->giveItem(Code::ITEM::LALA);
	}

	return S_OK;
}

void Player::release()
{
	Unit::release();

	PLAYERMANAGER->release();
	PLAYERMANAGER->releaseSingleton();
}

void Player::update()
{
	Unit::update();
	this->move();
	Unit::updateRect();
	this->animation();
	PLAYERMANAGER->update();
}

void Player::render(HDC hdc)
{
	if (!_isRender) return;
	Unit::render(hdc);
}

void Player::hitAttack(int dmg, int dir)
{
	if (_hitTime + HIT_TIME > TIMEMANAGER->getWorldTime()) return;
	_hitTime = TIMEMANAGER->getWorldTime();
	_isHit = true;
	_imgAlpha = HIT_ALPHA;

	PLAYERMANAGER->hit(dmg);

	OBJECTMANAGER->addDynamicImageFont(_x, _rc.top, dmg, dir);
	SOUNDMANAGER->play(SoundName::Player::hit, _sound);
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

	_rcAttack = { 0,0,0,0 };

	_hand = PointMake(_mainHandX, _y + 5);
	_body = PointMake(_x, _y);
	
	if (_isStop) return;
	if (UIMANAGER->isUI() || CAMERAMANAGER->isCameraMove()) return;

	if (IsStayKeyDown(KEY::LEFT))	 this->moveLeft();
	if (IsStayKeyDown(KEY::RIGHT))	 this->moveRight();
	if (IsOnceKeyUp(KEY::LEFT))		 this->setIdle();
	if (IsOnceKeyUp(KEY::RIGHT))	 this->setIdle();
	if (IsStayKeyDown(KEY::CLICK_L)) this->attack();
	if (IsOnceKeyDown(KEY::CLICK_R)) this->dash();
	if (IsOnceKeyDown(KEY::SKILL))	 this->skill();

	if (IsStayKeyDown(KEY::DOWN) && IsOnceKeyDown(KEY::SPACE)) Unit::downJump();
	if (IsOnceKeyDown(KEY::UP) || IsOnceKeyDown(KEY::SPACE))  this->jump();

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

	if (_isDash)
	{
		_state = PLAYER_MOTION::DASH;
		if (_dashMove > 0)
		{
			if (_isJump) _dashMove = 0;

			if (_dashMove % 50 < DASH_SPEED)
			{
				OBJECTMANAGER->addEffect(_dashImgName, _x, _y, 180, ObjectEnum::OBJ_TYPE::EFFECT);
			}

			_gravity = 0.0f;
			_dashMove -= DASH_SPEED;
			_x += cosf(_dashAngle) * DASH_SPEED;
			_y -= sinf(_dashAngle) * DASH_SPEED;
		}
		else
		{
			_isDash = FALSE;
			_isDownFlag = FALSE;
			_dashMove = DASH_DISTANCE;
		}
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
			_imgAlpha = _imgAlpha == 255 ? HIT_ALPHA : 255;
		}

		if (_hitTime + HIT_TIME < TIMEMANAGER->getWorldTime())
		{
			_isHit = false;
			_imgAlpha = 255;
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

void Player::frameUpdateEvent()
{
	if (_state == PLAYER_MOTION::RUN && (_frameInfo.x == 1 || _frameInfo.x == 5))
	{
		_isDust = TRUE;
	}
}

void Player::moveLeft()
{
	_state = PLAYER_MOTION::RUN;

	_x -= _moveSpeed;

	if (_isDust)
	{
		_isDust = FALSE;
		OBJECTMANAGER->addEffect(ImageName::Player::runEffectL, _rc.right, _rc.bottom - 24);
	}
}

void Player::moveRight()
{
	_state = PLAYER_MOTION::RUN;

	if (!_isCollision[Direction::DIR::RIGHT]) _x += _moveSpeed;
	
	if (_isDust)
	{
		_isDust = FALSE;
		OBJECTMANAGER->addEffect(ImageName::Player::runEffectR, _rc.left, _rc.bottom - 24);
	}
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
			_rcAttack = RectMakeCenter(_hand.x, _hand.y, WINSIZE_X * 3, WINSIZE_Y * 3);
		}
	}
}

void Player::skill()
{
	if (ITEMMANAGER->getEquipItem())
	{
		ITEMMANAGER->getEquipItem()->skill();
	}
}

void Player::dash()
{
	if (_isDash) return;
	if (PLAYERMANAGER->canDash()) return;
	PLAYERMANAGER->dash();

	_isDash = TRUE;
	_isJump = FALSE;
	_isDownFlag = TRUE;
	_dashAngle = GetAngle(PointMake(_x, _y), CAMERAMANAGER->calAbsPt(_ptMouse));
	
	if (_isLeft)
	{
		_dashImgName = ImageName::Player::dashEffectL;
	}
	else
	{
		_dashImgName = ImageName::Player::dashEffectR;
	}

	SOUNDMANAGER->play(SoundName::Player::dash, _sound);
}

void Player::jump()
{
	if (_isJumpFlag && !_isDebug) return;

	SOUNDMANAGER->play(SoundName::Player::Jumping, _sound);
	Unit::jump();
	OBJECTMANAGER->addEffect(ImageName::Player::jumpEffect, _x, _rc.bottom - 25);
}

BOOL Player::getItem(Code::ITEM code)
{
	if (code < Code::ITEM::ITEM_CNT)
	{
		ITEMMANAGER->giveItem(code);
	}
	else
	{
		if (code == Code::ITEM::COIN)
		{
			PLAYERMANAGER->addCoin(10);
		}
		else
		{
			PLAYERMANAGER->addCoin(100);
		}
		return true;
	}
}
