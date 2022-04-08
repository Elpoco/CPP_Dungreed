#include "Stdafx.h"
#include "Belial.h"

#include "Bullet.h"

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

	_rcBack = RectMakeCenter(_x + 25, _y + 60, _imgBack->getFrameWidth(), _imgBack->getFrameHeight());

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
}

void Belial::initAnimation()
{
	_vImages.push_back(IMAGEMANAGER->findImage(ImageName::Enemy::belialIdle));
	_vImages.push_back(IMAGEMANAGER->findImage(ImageName::Enemy::belialAttack));

	_imgBack = IMAGEMANAGER->findImage(ImageName::Enemy::belialBack);
	_backFrameInfo.maxFrameX = _imgBack->getMaxFrameX();
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
			new Bullet(ImageName::Enemy::belialBullet, _x + 25, _y + 60, cosf(_shootAngle), -sinf(_shootAngle), 3.0f));
	}
	// 방향 전환
	_shootAngle += PI / 32;

	if (_skillActCnt > 20)
	{
		_skillActCnt = 0;
		_skill = BELIAL_SKILL::NONE;
		_frameInfo.startFrameX = 0;
		_state = IDLE;
	}
}
