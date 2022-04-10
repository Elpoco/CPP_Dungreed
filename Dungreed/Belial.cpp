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

	_name = "º§¸®¾Ë";
	_isFlying = true;
	_scanScale = { 4,3 };

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

	for (int i = 0; i < RL; i++)
	{
		CAMERAMANAGER->frameRender(
			hdc,
			_imgHand[_hand[i].state],
			_hand[i].rc.left, _hand[i].rc.top,
			_hand[i].frameInfo.x, i);
	}

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
	_backFrameInfo.cnt++;
	if (_backFrameInfo.cnt > _backFrameInfo.tick)
	{
		_backFrameInfo.cnt = 0;
		_backFrameInfo.x++;

		bool checkFrame = _backFrameInfo.maxFrameX < _backFrameInfo.x;
		if (checkFrame) _backFrameInfo.x = 0;

		OBJECTMANAGER->addObject(ObjectEnum::TYPE::EFFECT,
			new Effect(ImageName::Enemy::Belial::belialParticle, _x + 300, _y));
	}

	for (int i = 0; i < RL; i++)
	{
		_hand[i].frameInfo.cnt++;
		if (_hand[i].frameInfo.cnt > _hand[i].frameInfo.tick)
		{
			_hand[i].frameInfo.cnt = 0;
			_hand[i].frameInfo.x++;

			bool checkFrame = _hand[i].frameInfo.maxFrameX < _hand[i].frameInfo.x;
			if (checkFrame) _hand[i].frameInfo.x = 0;
		}
	}
}

void Belial::initAnimation()
{
	_vImages.push_back(IMAGEMANAGER->findImage(ImageName::Enemy::Belial::belialIdle));
	_vImages.push_back(IMAGEMANAGER->findImage(ImageName::Enemy::Belial::belialAttack));

	_imgBack = IMAGEMANAGER->findImage(ImageName::Enemy::Belial::belialBack);
	_backFrameInfo.maxFrameX = _imgBack->getMaxFrameX();
	_rcBack = RectMakeCenter(_x + 23, _y + 60, _imgBack->getFrameWidth(), _imgBack->getFrameHeight());

	_imgWidth = _vImages[0]->getFrameWidth();
	_imgHeight = _vImages[0]->getFrameHeight();

	_imgHand[BELIAL_HAND_STATE::HAND_IDLE] = IMAGEMANAGER->findImage(ImageName::Enemy::Belial::belialHand);
	_imgHand[BELIAL_HAND_STATE::LAZER] = IMAGEMANAGER->findImage(ImageName::Enemy::Belial::belialHandAttack);

	_hand[R].isLeft = false;
	_hand[R].x = _x + 450;
	_hand[R].y = _y + 100;
	_hand[L].isLeft = true;
	_hand[L].x = _x - 410;
	_hand[L].y = _y - 50;

	for (int i = 0; i < RL; i++)
	{
		_hand[i].frameInfo.width = _imgHand[0]->getFrameWidth();
		_hand[i].frameInfo.height = _imgHand[0]->getFrameWidth();
		_hand[i].frameInfo.maxFrameX = _imgHand[0]->getMaxFrameX();
		_hand[i].state = BELIAL_HAND_STATE::HAND_IDLE;
		_hand[i].rc = RectMakeCenter(
			_hand[i].x, _hand[i].y, 
			_imgHand[0]->getFrameWidth(), _imgHand[0]->getFrameWidth()
		);
	}
}

void Belial::shootingBullet()
{
	if (_frameInfo.startFrameX != 5)
	{
		_frameInfo.x = 0;
		_frameInfo.startFrameX = 5;
		_state = ATTACK;
		_imgWidth = _vImages[_state]->getFrameWidth();
		_imgHeight = _vImages[_state]->getFrameHeight()+30;
	}

	if (_skillTick++ < 20) return;
	_skillTick = 0;

	for (int i = 0; i < 4; i++)
	{
		_shootAngle += PI / 2 * i;
		OBJECTMANAGER->addObject(
			ObjectEnum::TYPE::ENEMY_OBJ,
			new Bullet(
				ImageName::Enemy::Belial::belialBullet,
				_x + 23,
				_y + 55,
				cosf(_shootAngle),
				-sinf(_shootAngle),
				4.0f,
				1.0f,
				ImageName::Enemy::Belial::belialBulletEffect
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
		_shootDir = RND->getSigned();
		_state = IDLE;
		_imgWidth = _vImages[_state]->getFrameWidth();
		_imgHeight = _vImages[_state]->getFrameHeight();
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
	_hand[L].state = BELIAL_HAND_STATE::LAZER;
	if (_hand[L].y != _ptPlayer.y)
	{
		float distance =  _ptPlayer.y - _hand[L].y;
		_hand[L].y += distance / 10;
	}
	_hand[L].rc = RectMakeCenter(_hand[L].x, _hand[L].y, _imgHand[_hand[L].state]->getFrameWidth(),
		_imgHand[_hand[L].state]->getFrameHeight());
	//_handStateR = BELIAL_HAND_STATE::LAZER;
	//_hand[R].rc;
	//_hand[R].rc = RectMakeCenter(_hand[R].x, _hand[R].y,
	//	_imgHand[_handStateR]->getFrameWidth(),
	//	_imgHand[_handStateR]->getFrameHeight());
	//_hand[R].rc;
	//int al;
}
