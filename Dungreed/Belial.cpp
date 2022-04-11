#include "Stdafx.h"
#include "Belial.h"

#include "Bullet.h"
#include "Effect.h"
#include "BelialSword.h"

Belial::Belial(float x, float y)
	: _skill(BELIAL_SKILL::NONE)
	, _lastSkill(BELIAL_SKILL::NONE)
	, _skillTick(0)
	, _skillActCnt(0)
	, _skillAuto(false)
	, _skillCooldown(TIMEMANAGER->getWorldTime())
	, _shootAngle(0.0f)
	, _shootDir(1)
	, _laserDir(1)
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

	_name = "������";
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

	if (KEYMANAGER->isStayKeyDown('B') && KEYMANAGER->isOnceKeyDown('0')) _skillAuto = !_skillAuto;
	if (KEYMANAGER->isStayKeyDown('B') && KEYMANAGER->isOnceKeyDown('1')) _skill = BELIAL_SKILL::SHOOTING_BULLET;
	if (KEYMANAGER->isStayKeyDown('B') && KEYMANAGER->isOnceKeyDown('2')) _skill = BELIAL_SKILL::THROW_SWORD;
	if (KEYMANAGER->isStayKeyDown('B') && KEYMANAGER->isOnceKeyDown('3')) _skill = BELIAL_SKILL::LASER;

	switch (_skill)
	{
	case Belial::BELIAL_SKILL::NONE:
		if (_skillAuto && _skillCooldown + SKILL_TIME < TIMEMANAGER->getWorldTime())
		{
			while (_skill == BELIAL_SKILL::NONE || _lastSkill == _skill)
			{
				_skill = (BELIAL_SKILL)RND->getInt((int)BELIAL_SKILL::SKILL_CNT);
			}
			_lastSkill = _skill;
		}
		break;
	case Belial::BELIAL_SKILL::SHOOTING_BULLET:
		this->shootingBullet();
		break;
	case Belial::BELIAL_SKILL::THROW_SWORD:
		this->throwSword();
		break;
	case Belial::BELIAL_SKILL::LASER:
		this->laser();
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

		if(_isDebug)
			CAMERAMANAGER->printRectangle(hdc, _hand[i].rc);
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

		OBJECTMANAGER->addObject(
			ObjectEnum::TYPE::EFFECT_BACK,
			new Effect(
				ImageName::Enemy::Belial::particle,
				RND->getFromIntTo(_rcBack.left + 5, _rcBack.right - 5),
				RND->getFromIntTo(_rcBack.top + 5, _rcBack.bottom - 5),
				50
			)
		);
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
	_vImages.push_back(IMAGEMANAGER->findImage(ImageName::Enemy::Belial::idle));
	_vImages.push_back(IMAGEMANAGER->findImage(ImageName::Enemy::Belial::attack));

	_imgBack = IMAGEMANAGER->findImage(ImageName::Enemy::Belial::back);
	_backFrameInfo.maxFrameX = _imgBack->getMaxFrameX();
	_rcBack = RectMakeCenter(_x + 23, _y + 60, _imgBack->getFrameWidth(), _imgBack->getFrameHeight());

	_imgWidth = _vImages[0]->getFrameWidth();
	_imgHeight = _vImages[0]->getFrameHeight();

	_imgHand[BELIAL_HAND_STATE::HAND_IDLE] = IMAGEMANAGER->findImage(ImageName::Enemy::Belial::hand);
	_imgHand[BELIAL_HAND_STATE::LASER] = IMAGEMANAGER->findImage(ImageName::Enemy::Belial::handAttack);

	_hand[R].isLeft = false;
	_hand[R].x = _x + 450;
	_hand[R].y = _y + 100;
	_hand[L].isLeft = true;
	_hand[L].x = _x - 410;
	_hand[L].y = _y - 50;

	for (int i = 0; i < RL; i++)
	{
		_hand[i].frameInfo.width =	_imgHand[0]->getFrameWidth();
		_hand[i].frameInfo.height = _imgHand[0]->getFrameHeight();
		_hand[i].frameInfo.maxFrameX = _imgHand[0]->getMaxFrameX();
		_hand[i].rc = RectMakeCenter(
			_hand[i].x, _hand[i].y, 
			_hand[i].frameInfo.width, 
			_hand[i].frameInfo.height
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
				ImageName::Enemy::Belial::bullet,
				_x + 23,
				_y + 55,
				_shootAngle,
				4.0f,
				1.0f,
				ImageName::Enemy::Belial::bulletEffect
			)
		);
	}
	
	_shootAngle += PI / 32 * _shootDir;

	if (++_skillActCnt > BULLET_CNT)
	{
		_skillTick = 0;
		_skillActCnt = 0;
		_skill = BELIAL_SKILL::NONE;
		_skillCooldown = TIMEMANAGER->getWorldTime();

		_frameInfo.startFrameX = 0;
		_shootDir = RND->getSigned();
		_state = IDLE;
		_imgWidth = _vImages[_state]->getFrameWidth();
		_imgHeight = _vImages[_state]->getFrameHeight();
	}
}

void Belial::throwSword()
{
	if (_skillTick++ < 35) return;
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
		_skillCooldown = TIMEMANAGER->getWorldTime() + 2;
		return;
	}
}

void Belial::laser()
{
	// �μմ� �������� �Ƚ�� �������� �Ѽ��� ���Ѵ�
	if (_hand[R].laserState == BELIAL_LASER_STATE::NONE &&
		_hand[L].laserState == BELIAL_LASER_STATE::NONE)
	{
		_laserDir = RND->getInt(2);
	}

	switch (_hand[_laserDir].laserState)
	{
	case BELIAL_LASER_STATE::NONE:
		_hand[_laserDir].playerY = _ptPlayer.y;
		_hand[_laserDir].laserState = BELIAL_LASER_STATE::START;
		break;
	case BELIAL_LASER_STATE::START:
	{
		float distance = _hand[_laserDir].playerY - _hand[_laserDir].y;
		_hand[_laserDir].y += distance / 10;
		if (abs(distance) < 5)
		{
			_hand[_laserDir].frameInfo.x = 0;
			_hand[_laserDir].laserState = BELIAL_LASER_STATE::FIND;
		}
		break;
	}
	case BELIAL_LASER_STATE::FIND:
		_hand[_laserDir].state = BELIAL_HAND_STATE::LASER;
		_hand[_laserDir].laserState = BELIAL_LASER_STATE::SHOOT;
		_hand[_laserDir].frameInfo.maxFrameX = _imgHand[_hand[_laserDir].state]->getMaxFrameX();
		break;
	case BELIAL_LASER_STATE::SHOOT:
		if (_hand[_laserDir].frameInfo.x >= 8)
		{
			_hand[_laserDir].laserState = BELIAL_LASER_STATE::SHOOTING;
			string imgName = _laserDir ? ImageName::Enemy::Belial::laserHeadL : ImageName::Enemy::Belial::laserHeadR;
			int direction = _laserDir ? 1 : -1;

			OBJECTMANAGER->addObject(
				ObjectEnum::TYPE::EFFECT,
				new Effect(
					imgName,
					_hand[_laserDir].x + 30 * direction,
					_hand[_laserDir].y + 20
				)
			);

			int headWidth = IMAGEMANAGER->findImage(ImageName::Enemy::Belial::laserHeadL)->getFrameWidth();
			int laserInterval = IMAGEMANAGER->findImage(ImageName::Enemy::Belial::laserBody)->getFrameWidth();
			for (int i = 0; i < LASER_CNT; i++)
			{
				OBJECTMANAGER->addObject(
					ObjectEnum::TYPE::EFFECT,
					new Effect(
						ImageName::Enemy::Belial::laserBody,
						_hand[_laserDir].x + (30 + headWidth + laserInterval * i) * direction,
						_hand[_laserDir].y + 18
					)
				);
			}
		}
		break;
	case BELIAL_LASER_STATE::SHOOTING:
		if (_hand[_laserDir].frameInfo.x >= _hand[_laserDir].frameInfo.maxFrameX - 1)
		{
			_hand[_laserDir].laserState = BELIAL_LASER_STATE::DONE; 
			_skillTick = 0;
			_skillActCnt = 0;
			_hand[_laserDir].state = BELIAL_HAND_STATE::HAND_IDLE;
			_hand[_laserDir].frameInfo.maxFrameX = _imgHand[_hand[_laserDir].state]->getMaxFrameX();

		}
		break;
	case BELIAL_LASER_STATE::DONE:
		// �������� ����� �ݴ��� ������ ����
		_laserDir = _laserDir ? R : L;
		break;
	default:
		break;
	}

	_hand[_laserDir].rc = RectMakeCenter(_hand[_laserDir].x, _hand[_laserDir].y,
		_imgHand[_hand[_laserDir].state]->getFrameWidth(),
		_imgHand[_hand[_laserDir].state]->getFrameHeight());

	// �μմ� ������ ����
	if (_hand[R].laserState == BELIAL_LASER_STATE::DONE &&
		_hand[L].laserState == BELIAL_LASER_STATE::DONE)
	{
		_skill = BELIAL_SKILL::NONE;
		_skillCooldown = TIMEMANAGER->getWorldTime();
		_hand[R].laserState = BELIAL_LASER_STATE::NONE;
		_hand[L].laserState = BELIAL_LASER_STATE::NONE;
	}
}
