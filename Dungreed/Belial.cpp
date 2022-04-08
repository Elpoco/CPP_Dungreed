#include "Stdafx.h"
#include "Belial.h"

#include "BelialBullet.h"

Belial::Belial(float x, float y) :
	_backFrameX(0),
	_skill(BELIAL_SKILL::NONE),
	_skillTick(0),
	_skillActCnt(0),
	_shootAngle(0.0f)
{
	_x = x;
	_y = y;
}

Belial::~Belial()
{
}

HRESULT Belial::init()
{
	Enemy::init();
	this->initAnimation();
	Unit::updateRect();

	_name = "벨리알";
	_isFlying = true;
	_scanScale = { 4,3 };
	_rcBack = RectMakeCenter(_x + 25, _y + 60, _imgBack->getFrameWidth(), _imgBack->getFrameHeight());

	settingHp(UnitSet::Enemy::Belial::HP);

	return S_OK;
}

void Belial::release()
{
	Enemy::release();
}

void Belial::update()
{
	Enemy::update();
	this->move();
	Unit::updateRect();
	this->animation();

	_rcBack = RectMakeCenter(_x + 23, _y + 55, _imgBack->getFrameWidth(), _imgBack->getFrameHeight());

	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_skill = BELIAL_SKILL::SHOOTING_BULLET;

	}

	switch (_skill)
	{
	case Belial::BELIAL_SKILL::NONE:
		break;
	case Belial::BELIAL_SKILL::SHOOTING_BULLET:
		shootingBullet();
		break;
	default:
		break;
	}
}

void Belial::render(HDC hdc)
{
	CAMERAMANAGER->frameRender(hdc, _imgBack, _rcBack.left, _rcBack.top, _backFrameInfo.x, 0);
	Enemy::render(hdc);

	CAMERAMANAGER->frameRender(hdc, _handL.img, _handL.rc.left, _handL.rc.top, _handLFrameInfo.x, 0);
	CAMERAMANAGER->frameRender(hdc, _handR.img, _handR.rc.left, _handR.rc.top, _handRFrameInfo.x, 0);

	for (int i = 0; i < 7; i++)
	{
		CAMERAMANAGER->render(
			hdc, GPIMAGEMANAGER->findImage(ImageName::Enemy::belialSword), rcTemp.left + i * 100, rcTemp.top,
			GetAngleDeg(_x - 300 + i * 100, _y - 200, _ptPlayer.x, _ptPlayer.y) - 90, PointMake(_x- 300 + i * 100, _y - 200)
		);
	}

}

void Belial::move()
{
}

void Belial::animation()
{
	_imgWidth = _vImages[_imgCurrent]->getFrameWidth();
	_imgHeight = _vImages[_imgCurrent]->getFrameHeight();

	_backFrameInfo.cnt++;
	if (_backFrameInfo.cnt > _backFrameInfo.tick)
	{
		_backFrameInfo.cnt = 0;
		_backFrameInfo.x++;

		bool checkFrame = _backFrameInfo.maxFrameX < _backFrameInfo.x;
		if (checkFrame) _backFrameInfo.x = 0;
	}

	_handLFrameInfo.cnt++;
	if (_handLFrameInfo.cnt > _handLFrameInfo.tick)
	{
		_handLFrameInfo.cnt = 0;
		_handLFrameInfo.x++;

		bool checkFrame = _handLFrameInfo.maxFrameX < _handLFrameInfo.x;
		if (checkFrame) _handLFrameInfo.x = 0;
	}

	_handRFrameInfo.cnt++;
	if (_handRFrameInfo.cnt > _handRFrameInfo.tick)
	{
		_handRFrameInfo.cnt = 0;
		_handRFrameInfo.x++;

		bool checkFrame = _handRFrameInfo.maxFrameX < _handRFrameInfo.x;
		if (checkFrame) _handRFrameInfo.x = 0;
	}
}

void Belial::initAnimation()
{
	_vImages.push_back(IMAGEMANAGER->findImage(ImageName::Enemy::belialIdle));
	_vImages.push_back(IMAGEMANAGER->findImage(ImageName::Enemy::belialAttack));

	_imgBack = IMAGEMANAGER->findImage(ImageName::Enemy::belialBack);
	_backFrameInfo.maxFrameX = _imgBack->getMaxFrameX();

	_imgWidth = _vImages[0]->getFrameWidth();
	_imgHeight = _vImages[0]->getFrameHeight();

	// 왼손
	_handL.img = IMAGEMANAGER->findImage(ImageName::Enemy::belialHandL);
	_handL.isLeft = true;
	_handL.x = _x;
	_handL.y = _y;
	_handLFrameInfo.maxFrameX = _handL.img->getMaxFrameX();
	_handL.rc = RectMakeCenter(_x - 200, _y + 100, _handL.img->getFrameWidth(), _handL.img->getFrameHeight());

	// 오른손
	_handR.img = IMAGEMANAGER->findImage(ImageName::Enemy::belialHandR);
	_handR.isLeft = true;
	_handR.x = _x;
	_handR.y = _y;
	_handRFrameInfo.maxFrameX = _handR.img->getMaxFrameX();
	_handR.rc = RectMakeCenter(_x + 250, _y + 80, _handR.img->getFrameWidth(), _handR.img->getFrameHeight());

	rcTemp = RectMakeCenter(_x - 300, _y - 200, 72, 220);
}

void Belial::shootingBullet()
{
	if (_frameInfo.startFrameX != 5)
	{
		_frameInfo.x = 0;
		_frameInfo.startFrameX = 5;
		_state = ATTACK;
	}
	_skillTick++;

	if (_skillTick < 20) return;

	_skillActCnt++;
	_skillTick = 0;

	for (int i = 0; i < 4; i++)
	{
		_shootAngle += PI / 2 * i;
		OBJECTMANAGER->addObject(
			ObjectEnum::TYPE::ENEMY_OBJ,
			new BelialBullet(
				ImageName::Enemy::belialBullet,
				_x + 23,
				_y + 55,
				cosf(_shootAngle),
				-sinf(_shootAngle),
				4.0f
			)
		);
	}
	// 방향 전환
	_shootAngle += PI / 32;

	if (_skillActCnt > 25)
	{
		_skillActCnt = 0;
		_skill = BELIAL_SKILL::NONE;
		_frameInfo.startFrameX = 0;
		_state = IDLE;
	}
}
