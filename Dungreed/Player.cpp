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
	Object::updateRect();
	this->animation();

	angle = getAngle(CAMERAMANAGER->calRelX(_x), CAMERAMANAGER->calRelY(_y), _ptMouse.X, _ptMouse.Y)  / PI *180;
}

void Player::render(HDC hdc)
{
	Unit::render(hdc);

	//CAMERAMANAGER->render(hdc, hand.image, _x + 15, _y + 15);
	CAMERAMANAGER->printRectangle(hdc, RectFMakeCenter(_x + 15, _y + 20, 5, 5));

	CAMERAMANAGER->render(hdc, 
		_weapon, 
		_x + mainWeaponX,
		_y + 20 - _weapon->getHeight(),
		angle + attackAngle - 110 + tempAngle,
		{ _x + mainWeaponX, _y + 20 });


	// x 15 y 20
	//_img->render(hdc, CENTER_X, CENTER_Y, 90);
	//_img->render(hdc, CENTER_X, CENTER_Y, 180);
	//_img->render(hdc, CENTER_X, CENTER_Y, 270);

}

void Player::initAnimation()
{
	_vImages.push_back(IMAGEMANAGER->findImage(ImageName::Player::idle));
	_vImages.push_back(IMAGEMANAGER->findImage(ImageName::Player::run));

	_imgWidth = _vImages[0]->getFrameWidth();
	_imgHeight = _vImages[0]->getFrameHeight();
}

void Player::move()
{
	if (KEYMANAGER->isStayKeyDown(KEY::LEFT))
	{
		_state = PLAYER_STATE::RUN;
		//if(!_isCollision[ColliderEnum::DIRECTION::LB])
			_x -= _moveSpeed;
	}

	if (KEYMANAGER->isStayKeyDown(KEY::RIGHT))
	{
		_state = PLAYER_STATE::RUN;
		//if (!_isCollision[ColliderEnum::DIRECTION::LT])
			_x += _moveSpeed;
	}

	if (KEYMANAGER->isStayKeyDown(KEY::DOWN))
	{
		_y += _moveSpeed;
	}

	if (KEYMANAGER->isStayKeyDown(KEY::UP))
	{
		_y -= _moveSpeed;
	}

	if (KEYMANAGER->isOnceKeyUp(KEY::LEFT) ||
		KEYMANAGER->isOnceKeyUp(KEY::RIGHT))
	{
		_state = PLAYER_STATE::IDLE;
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

	if (_isJump)
	{
		_y -= _jumpSpeed;
		//if (_isCollision)
		//{
		//	_isJump = false;
		//}
	}
}

void Player::animation()
{
	switch (_state)
	{
	case PLAYER_STATE::IDLE:
		_imgCurrent = PLAYER_STATE::IDLE;
		break;
	case PLAYER_STATE::RUN:
		_imgCurrent = PLAYER_STATE::RUN;
		break;
	default:
		break;
	}

	if (_ptMouse.X < CAMERAMANAGER->calRelX(_x))
	{
		_isLeft = true;
		mainWeaponX = mainHandX * -1;
		tempAngle = 180;
	}
	else 
	{ 
		_isLeft = false; 
		mainWeaponX = mainHandX;
		tempAngle = 0;
	}
}
