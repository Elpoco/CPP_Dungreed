#include "Stdafx.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

HRESULT Player::init()
{
	Unit::init();

	_reSize = 30;
	this->initAnimation();

	CAMERAMANAGER->followCamera(this);


	hand.image = IMAGEMANAGER->findImage(ImageName::Player::hand);
	_weapon = GPIMAGEMANAGER->findImage(ImageName::Item::Weapon::basicShotSword);
	angle = 0;
	attackAngle = 110;

	mainHandX = 15;
	mainWeaponX = mainHandX;
	tempAngle = 0;

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

	angle = GetAngle(CAMERAMANAGER->calRelX(_x), CAMERAMANAGER->calRelY(_y), _ptMouse.x, _ptMouse.y)  / PI *180;
}

void Player::render(HDC hdc)
{
	Unit::render(hdc);

	//CAMERAMANAGER->render(hdc, hand.image, _x + 15, _y + 15);
	CAMERAMANAGER->printRectangle(hdc, _x + 15, _y + 20, 5, 5);

	//CAMERAMANAGER->render(hdc, 
	//	_weapon, 
	//	_x + mainWeaponX,
	//	_y + 20 - _weapon->getHeight(),
	//	angle + attackAngle - 100 + tempAngle,
	//	{ _x + mainWeaponX, _y + 20 });

	//GPIMAGEMANAGER->render(ImageName::Item::Weapon::basicShotSword, hdc, 0, 0);

	// x 15 y 20
	//_img->render(hdc, CENTER_X, CENTER_Y, 90);
	//_img->render(hdc, CENTER_X, CENTER_Y, 180);
	//_img->render(hdc, CENTER_X, CENTER_Y, 270);

}

void Player::move()
{
	_state = PLAYER_MOTION::IDLE;

	if (KEYMANAGER->isStayKeyDown(KEY::LEFT))
	{
		_state = PLAYER_MOTION::RUN;
		if(!_isCollision[ColliderEnum::DIRECTION::RIGHT])
		_x -= _moveSpeed;
	}

	if (KEYMANAGER->isStayKeyDown(KEY::RIGHT))
	{
		_state = PLAYER_MOTION::RUN;
		if (!_isCollision[ColliderEnum::DIRECTION::RIGHT])
			_x += _moveSpeed;
	}

	if (KEYMANAGER->isStayKeyDown(KEY::DOWN))
	{
		//_y += _moveSpeed;
	}

	if (KEYMANAGER->isStayKeyDown(KEY::UP))
	{
		//_y -= _moveSpeed;
	}

	if (KEYMANAGER->isOnceKeyUp(KEY::LEFT))
	{
		_state = PLAYER_MOTION::IDLE;
	}

	if (KEYMANAGER->isOnceKeyUp(KEY::RIGHT))
	{
		_state = PLAYER_MOTION::IDLE;
	}

	if (KEYMANAGER->isOnceKeyDown(KEY::UP) ||
		KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		Unit::jump();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		attackAngle *= -1;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{

	}

	if (_isJump || _isFall)
	{
		//_state = PLAYER_MOTION::JUMP;
	}
}

void Player::animation()
{
	if (_ptMouse.x < CAMERAMANAGER->calRelX(_x))
	{
		_isLeft = true;
	}
	else 
	{ 
		_isLeft = false; 
	}

	_imgCurrent = _state;
	//if (!_isLeft) _imgCurrent += 1;

}

void Player::initAnimation()
{
	_vImages.push_back(IMAGEMANAGER->findImage(ImageName::Player::idle));
	_vImages.push_back(IMAGEMANAGER->findImage(ImageName::Player::run));
	_vImages.push_back(IMAGEMANAGER->findImage(ImageName::Player::jump));

	_imgWidth = _vImages[0]->getFrameWidth() - _reSize;
	_imgHeight = _vImages[0]->getFrameHeight();
}
