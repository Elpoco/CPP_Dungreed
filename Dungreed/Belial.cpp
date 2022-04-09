#include "Stdafx.h"
#include "Belial.h"

#include "Bullet.h"
#include "Effect.h"
#include "BelialSword.h"

Belial::Belial(float x, float y)
	: _skill(BELIAL_SKILL::NONE)
	, _shootAngle(0.0f)
	, _skillActCnt(0)
	, _backFrameX(0)
	, _skillTick(0)
	, _shootDir(1)
{
	_startSpawn = TRUE;
	_isSpawn = TRUE;

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

	if (KEYMANAGER->isStayKeyDown('B') && KEYMANAGER->isOnceKeyDown('1')) _skill = BELIAL_SKILL::SHOOTING_BULLET;
	if (KEYMANAGER->isStayKeyDown('B') && KEYMANAGER->isOnceKeyDown('2')) _skill = BELIAL_SKILL::THROW_SWORD;
	if (KEYMANAGER->isStayKeyDown('B') && KEYMANAGER->isOnceKeyDown('3')) _skill = BELIAL_SKILL::LAZER;

	if (_skill == BELIAL_SKILL::NONE)
	{
		//_skill = (BELIAL_SKILL)RND->getInt((int)BELIAL_SKILL::SKILL_CNT);
	}

	switch (_skill)
	{
	case Belial::BELIAL_SKILL::NONE:
		break;
	case Belial::BELIAL_SKILL::SHOOTING_BULLET:
		this->shootingBullet();
		break;
	case Belial::BELIAL_SKILL::THROW_SWORD:
		this->throwSword();
		break;
	case Belial::BELIAL_SKILL::LAZER:
		this->lazer();
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

	switch (_skill)
	{
	case Belial::BELIAL_SKILL::NONE:
		break;
	case Belial::BELIAL_SKILL::SHOOTING_BULLET:
		break;
	case Belial::BELIAL_SKILL::THROW_SWORD:
		break;
	case Belial::BELIAL_SKILL::LAZER:
		break;
	default:
		break;
	}
}

void Belial::deleteEffect()
{
	OBJECTMANAGER->addObject(
		ObjectEnum::TYPE::EFFECT,
		new Effect(
			ImageName::Enemy::enemyDie,
			_x,
			_y
		)
	);
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

	_hand[R_L::RIGHT];
	// 왼손
	_handL.img = IMAGEMANAGER->findImage(ImageName::Enemy::belialHandL);
	_handL.isLeft = true;
	_handL.x = _x;
	_handL.y = _y;
	_handLFrameInfo.maxFrameX = _handL.img->getMaxFrameX();
	_handL.rc = RectMakeCenter(_x - 300, _y + 100, _handL.img->getFrameWidth(), _handL.img->getFrameHeight());

	// 오른손
	_handR.img = IMAGEMANAGER->findImage(ImageName::Enemy::belialHandR);
	_handR.isLeft = true;
	_handR.x = _x;
	_handR.y = _y;
	_handRFrameInfo.maxFrameX = _handR.img->getMaxFrameX();
	_handR.rc = RectMakeCenter(_x + 350, _y + 80, _handR.img->getFrameWidth(), _handR.img->getFrameHeight());
}

void Belial::shootingBullet()
{
	if (_frameInfo.startFrameX != 5)
	{
		_frameInfo.x = 0;
		_frameInfo.startFrameX = 5;
		_state = ATTACK;
	}

	if (_skillTick++ < 20) return;
	_skillTick = 0;

	for (int i = 0; i < 4; i++)
	{
		_shootAngle += PI / 2 * i;
		OBJECTMANAGER->addObject(
			ObjectEnum::TYPE::ENEMY_OBJ,
			new Bullet(
				ImageName::Enemy::belialBullet,
				_x + 23,
				_y + 55,
				cosf(_shootAngle),
				-sinf(_shootAngle),
				4.0f,
				1.0f,
				ImageName::Enemy::belialBulletEffect
			)
		);
	}
	
	_shootAngle += PI / 32 * _shootDir;

	if (++_skillActCnt > 25)
	{
		_skillTick = 0;
		_skillActCnt = 0;
		_skill = BELIAL_SKILL::NONE;
		_frameInfo.startFrameX = 0;
		_state = IDLE;
		_shootDir = RND->getSigned();
		return;
	}
}

void Belial::throwSword()
{
	if (_skillTick++ < 40) return;
	_skillTick = 0;

	OBJECTMANAGER->addObject(
		ObjectEnum::TYPE::ENEMY_OBJ, 
		new BelialSword(
			_x - 330 + _skillActCnt * 130,
			_y - 300,
			&_ptPlayer
		)
	);

	if (++_skillActCnt > 5)
	{
		_skillTick = 0;
		_skillActCnt = 0;
		_skill = BELIAL_SKILL::NONE;
		return;
	}
}

void Belial::lazer()
{
	_handL.y = _ptPlayer.y;
	_handL.rc = RectMakeCenter(_x - 300, _handL.y, _handL.img->getFrameWidth(), _handL.img->getFrameHeight());
}
