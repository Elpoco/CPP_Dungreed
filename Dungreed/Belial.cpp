#include "Stdafx.h"
#include "Belial.h"

#include "BelialSword.h"

using namespace BelialSet;

Belial::Belial(float x, float y)
	: _skill(BELIAL_SKILL::NONE)
	, _lastSkill(BELIAL_SKILL::NONE)
	, _skillTick(0)
	, _skillActCnt(0)
	, _skillAuto(TRUE)
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
	this->initAnimation();
	Enemy::init();
	Unit::updateRect();

	_info = DBMANAGER->getInfo(Code::UNIT::BELIAL);
	_isFlying = true;
	_scanScale = { 4,3 };

	settingHp(_info.hp);

	_moveHpBarX = 23;
	_moveHpBarY = 50;

	// 임시로 막기
	SOUNDMANAGER->stop(SoundName::dungeon);
	SOUNDMANAGER->play(SoundName::belialBG, _sound);
	SOUNDMANAGER->play(SoundName::Enemy::Skeletonking, _sound);

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

	if (IsStayKeyDown('B') && IsOnceKeyDown('0')) _skillAuto = !_skillAuto;
	if (IsStayKeyDown('B') && IsOnceKeyDown('1')) _skill = BELIAL_SKILL::SHOOTING_BULLET;
	if (IsStayKeyDown('B') && IsOnceKeyDown('2')) _skill = BELIAL_SKILL::THROW_SWORD;
	if (IsStayKeyDown('B') && IsOnceKeyDown('3')) _skill = BELIAL_SKILL::LASER;
	if (IsStayKeyDown('B') && IsOnceKeyDown('9')) _isLive = FALSE;

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
	OBJECTMANAGER->addEffect(ImageName::Enemy::die, _x, _y); 
	MAPMANAGER->dieMonster();
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

		OBJECTMANAGER->addEffect(
			ImageName::Enemy::Belial::particle,
			RND->getFromIntTo(_rcBack.left + 3, _rcBack.right - 3),
			RND->getFromIntTo(_rcBack.top + 3, _rcBack.bottom - 3),
			50,
			ObjectEnum::OBJ_TYPE::EFFECT_BACK
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
	_vImages.push_back(FindImage(ImageName::Enemy::Belial::idle));
	_vImages.push_back(FindImage(ImageName::Enemy::Belial::attack));

	_imgBack = FindImage(ImageName::Enemy::Belial::back);
	_rcBack = RectMakeCenter(_x + 23, _y + 60, _imgBack->getFrameWidth(), _imgBack->getFrameHeight());
	_backFrameInfo.maxFrameX = _imgBack->getMaxFrameX();

	_imgWidth = _vImages[0]->getFrameWidth();
	_imgHeight = _vImages[0]->getFrameHeight();

	_imgHand[BELIAL_HAND_STATE::HAND_IDLE] = FindImage(ImageName::Enemy::Belial::hand);
	_imgHand[BELIAL_HAND_STATE::LASER] = FindImage(ImageName::Enemy::Belial::handAttack);

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
		_imgHeight = _vImages[_state]->getFrameHeight() + 30;
	}

	if (_skillTick++ < 20) return;
	_skillTick = 0;

	for (int i = 0; i < 4; i++)
	{
		_shootAngle += PI * 0.5f * i;
		OBJECTMANAGER->addBullet(
			ObjectEnum::OBJ_TYPE::ENEMY_OBJ,
			ImageName::Enemy::Belial::bullet,
			_x + 23,
			_y + 55,
			_shootAngle,
			BULLET_SPEED,
			BULLET_DMG,
			ImageName::Enemy::Belial::bulletEffect
		);
	}

	SOUNDMANAGER->play(SoundName::Enemy::BelialBullet, _sound);
	
	_shootAngle += PI / 32 * _shootDir;

	if (++_skillActCnt >= BULLET_CNT)
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
		ObjectEnum::OBJ_TYPE::ENEMY_OBJ, 
		new BelialSword(
			_x - 330 + _skillActCnt * 130,
			_y - 300,
			&_ptPlayer
		)
	);

	if (++_skillActCnt >= SWORD_CNT)
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
	_rcAttack = { 0,0,0,0 };
	// 두손다 레이저를 안쏘면 랜덤으로 한손을 정한다
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

			RECT rc1;
			RECT rc2;

			rc1 = OBJECTMANAGER->addEffect(
				imgName,
				_hand[_laserDir].x + 30 * direction,
				_hand[_laserDir].y + 20
			);

			int headWidth = FindImage(ImageName::Enemy::Belial::laserHeadL)->getFrameWidth();
			int laserInterval = FindImage(ImageName::Enemy::Belial::laserBody)->getFrameWidth();
			for (int i = 0; i < LASER_CNT; i++)
			{
				rc2 = OBJECTMANAGER->addEffect(
					ImageName::Enemy::Belial::laserBody,
					_hand[_laserDir].x + (30 + headWidth + laserInterval * i) * direction,
					_hand[_laserDir].y + 18
				);
			}

			// 오른쪽손은 레이저가 반대라 렉트 크기도 반대
			if (rc1.left > rc2.left) swapValue(rc1, rc2);

			_rcAttack.left = rc1.left;
			_rcAttack.top = rc1.top;
			_rcAttack.right = rc2.right;
			_rcAttack.bottom = rc2.bottom;
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
		// 레이저를 쏘고나면 반대쪽 손으로 변경
		_laserDir = _laserDir ? R : L;
		break;
	default:
		break;
	}

	_hand[_laserDir].rc = RectMakeCenter(_hand[_laserDir].x, _hand[_laserDir].y,
		_imgHand[_hand[_laserDir].state]->getFrameWidth(),
		_imgHand[_hand[_laserDir].state]->getFrameHeight());

	// 두손다 쐈으면 종료
	if (_hand[R].laserState == BELIAL_LASER_STATE::DONE &&
		_hand[L].laserState == BELIAL_LASER_STATE::DONE)
	{
		_skill = BELIAL_SKILL::NONE;
		_skillCooldown = TIMEMANAGER->getWorldTime();
		_hand[R].laserState = BELIAL_LASER_STATE::NONE;
		_hand[L].laserState = BELIAL_LASER_STATE::NONE;
	}
}
