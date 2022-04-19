#include "Stdafx.h"
#include "Niflheim.h"

#include "NiflheimPillar.h"

using namespace NiflheimSet;

Niflheim::Niflheim(float x, float y)
	: _onInitPillar(false)
	, _skill(NIFLHEIM_SKILL::NONE)
	, _lastSkill(NIFLHEIM_SKILL::NONE)
	, _skillTick(0)
	, _skillActCnt(0)
	, _skillAuto(TRUE)
	, _skillCooldown(TIMEMANAGER->getWorldTime())
{
	_startSpawn = TRUE;
	_isSpawn = TRUE;

	_x = x;
	_y = y;
}

Niflheim::~Niflheim()
{
}

HRESULT Niflheim::init()
{
	Enemy::init();
	this->initAnimation();
	Unit::updateRect();

	_info = DBMANAGER->getInfo(Code::UNIT::NIFLEHEIM);
	_isFlying = true;
	_scanScale = { 10,10 };

	settingHp(_info.hp);

	this->initPillar();

	SOUNDMANAGER->stop(SoundName::dungeon);
	SOUNDMANAGER->stop(SoundName::belialBG);
	SOUNDMANAGER->play(SoundName::Enemy::niflheim_start, _sound);
	SOUNDMANAGER->play(SoundName::niflheimBG, _sound);

	return S_OK;
}

void Niflheim::release()
{
	Enemy::release();
	for (int i = 0; i < PILLAR_CNT; i++)
	{
		if (_pillar[i])
		{
			_pillar[i]->deleteObject();
		}
	}
}

void Niflheim::update()
{
	Enemy::update();
	this->move();
	Unit::updateRect();
	this->animation();

	if (IsStayKeyDown('B') && IsOnceKeyDown('0')) _skillAuto = !_skillAuto;
	if (IsStayKeyDown('B') && IsOnceKeyDown('1')) _skill = NIFLHEIM_SKILL::AROUND;
	if (IsStayKeyDown('B') && IsOnceKeyDown('2')) _skill = NIFLHEIM_SKILL::WIDE;
	if (IsStayKeyDown('B') && IsOnceKeyDown('3')) _skill = NIFLHEIM_SKILL::WIDE_LINE;
	if (IsStayKeyDown('B') && IsOnceKeyDown('4')) _skill = NIFLHEIM_SKILL::LINE_UP;
	if (IsStayKeyDown('B') && IsOnceKeyDown('5')) _skill = NIFLHEIM_SKILL::FULL_ATTACK;
	if (IsStayKeyDown('B') && IsOnceKeyDown('6')) _onInitPillar = true;
	if (IsStayKeyDown('B') && IsOnceKeyDown('9')) _isLive = FALSE;

	switch (_skill)
	{
	case Niflheim::NIFLHEIM_SKILL::NONE:
		for (int i = 0; i < PILLAR_CNT; i++)
		{
			if (!_pillar[i]) continue;

			_pillar[i]->setSkill(_skill);
		}

		if (_skillAuto && _skillCooldown + SKILL_TIME < TIMEMANAGER->getWorldTime())
		{
			while (_skill == NIFLHEIM_SKILL::NONE || _lastSkill == _skill)
			{
				_skill = (NIFLHEIM_SKILL)RND->getInt((int)NIFLHEIM_SKILL::SKILL_CNT);
			}
			_lastSkill = _skill;
		}
		break;
	case Niflheim::NIFLHEIM_SKILL::AROUND:
		this->turnAround();
		break;
	case Niflheim::NIFLHEIM_SKILL::WIDE:
	case Niflheim::NIFLHEIM_SKILL::WIDE_LINE:
	case Niflheim::NIFLHEIM_SKILL::LINE_UP:
	case Niflheim::NIFLHEIM_SKILL::FULL_ATTACK:
		this->moveAndFire();
		break;
	case Niflheim::NIFLHEIM_SKILL::SKILL_CNT:
		break;
	default:
		break;
	}

	for (int i = 0; i < PILLAR_CNT; i++)
	{
		if (_pillar[i] && _pillar[i]->isDestroy())
		{
			_pillar[i]->deleteObject();
			_pillar[i] = nullptr;
		}
	}
}

void Niflheim::render(HDC hdc)
{
	Enemy::render(hdc);
	
	// 업데이트에서 하면 벡터 돌아가는중 에러남
	if (_onInitPillar)
	{
		_onInitPillar = false;
		this->initPillar();
	}
}

void Niflheim::deleteEffect()
{
	OBJECTMANAGER->addEffect(ImageName::Enemy::die, _x, _y);
}

void Niflheim::hitAttack(int dmg, int dir)
{
	for (int i = 0; i < PILLAR_CNT; i++)
	{
		if (_pillar[i]) return;
	}
	_hp -= dmg;
	OBJECTMANAGER->addDynamicImageFont(_x, _rc.top, dmg, dir);
	if (_hp < 1)
	{
		_isLive = FALSE;
	}
}

void Niflheim::move()
{

}

void Niflheim::animation()
{
	if (_state == ATTACK)
	{
		if (_frameInfo.x >=_vImages[ATTACK]->getMaxFrameX())
		{
			_state = IDLE;
		}
	}
}

void Niflheim::initAnimation()
{
	_vImages.push_back(FindImage(ImageName::Enemy::Niflheim::idle));
	_vImages.push_back(FindImage(ImageName::Enemy::Niflheim::attack));

	_imgWidth = _vImages[0]->getFrameWidth();
	_imgHeight = _vImages[0]->getFrameHeight();
}

void Niflheim::initPillar()
{
	for (int i = 0; i < PILLAR_CNT; i++)
	{
		if (_pillar[i]) continue;
		int intervalX = i % 2;
		int intervalY = i / 2;
		_pillar[i] = new NiflheimPillar(_x + 115 - 250 * intervalX, _y + 115 - 250 * intervalY);
		_pillar[i]->setPosAddress(&_x, &_y);
		OBJECTMANAGER->addObject(ObjectEnum::OBJ_TYPE::ENEMY, _pillar[i]);
	}
}

void Niflheim::attackAnimation()
{
	_frameInfo.x = 0;
	_state = ATTACK;
}

void Niflheim::shootBullet(float x, float y, float angle)
{
	OBJECTMANAGER->addEffect(ImageName::Enemy::Niflheim::bulletFX, x, y);
	
	OBJECTMANAGER->addBullet(
		ObjectEnum::OBJ_TYPE::ENEMY_OBJ,
		ImageName::Enemy::Niflheim::bullet,
		x,
		y,
		angle,
		BULLET_SPEED,
		BULLET_DMG,
		ImageName::Enemy::Niflheim::bulletFX
	);

	SOUNDMANAGER->play(SoundName::Enemy::NiflheimBullet, _sound);
}

void Niflheim::turnAround()
{
	if (_skillActCnt == 0 && _skillTick == 0)
	{
		this->attackAnimation();
		_skillFirstTick = 50;
	}

	if (_skillTick++ < _skillFirstTick) return;
	_skillTick = 0;
	_skillFirstTick = 15;


	for (int i = 0; i < PILLAR_CNT; i++)
	{
		if (!_pillar[i]) continue;

		_pillar[i]->setSkill(_skill);
		float x = _pillar[i]->getX();
		float y = _pillar[i]->getY();
		float angle = GetAngle(_x, _y, x, y);

		this->shootBullet(x, y, angle);
	}

	if (++_skillActCnt > BULLET_CNT)
	{
		_skillTick = 0;
		_skillActCnt = 0;
		_skill = NIFLHEIM_SKILL::NONE;
		_skillCooldown = TIMEMANAGER->getWorldTime();

		_state = IDLE;
	}
}

void Niflheim::moveAndFire()
{
	int bulletCnt = BULLET_CNT;

	if (_skillActCnt == 0 && _skillTick == 0)
	{
		this->attackAnimation();
		_skillFirstTick = 150;
	}

	// 기둥 이동
	if (_skillTick == 50) 
	{
		for (int i = 0; i < PILLAR_CNT; i++)
		{
			if (!_pillar[i]) continue;
			_pillar[i]->setSkill(_skill);
		}
	}

	if (_skillTick == 150)
	{
		_ptLastPlayer = _ptPlayer;
	}

	if (_skillTick++ < _skillFirstTick) return;
	_skillTick = 0;
	_skillFirstTick = 10;
	
	for (int i = 0; i < PILLAR_CNT; i++)
	{
		if (!_pillar[i]) continue;
		
		if (_skill == NIFLHEIM_SKILL::WIDE_LINE)
		{
			bulletCnt = BULLET_CNT_L;
			int idx = _skillActCnt / 5;
			if (!_pillar[idx])
			{
				_skillTick = _skillFirstTick;
				continue;
			}
			float x = _pillar[idx]->getX();
			float y = _pillar[idx]->getY();
			this->shootBullet(x, y, GetAngle(x, y, _ptLastPlayer.x, _ptLastPlayer.y));
		}
		else if (_skill == NIFLHEIM_SKILL::FULL_ATTACK)
		{
			float x = _pillar[i]->getX();
			float y = _pillar[i]->getY();
			x += 40 - RND->getInt(80);
			y += 40 - RND->getInt(80);
			this->shootBullet(x, y, GetAngle(x, y, _ptLastPlayer.x, _ptLastPlayer.y));
		}
		else
		{
			float x = _pillar[i]->getX();
			float y = _pillar[i]->getY();
			int angle = _pillar[i]->getImgAngle();
			this->shootBullet(x, y, DegToRad(angle));
		}
	}

	if (++_skillActCnt >= bulletCnt)
	{
		_skillTick = 0;
		_skillActCnt = 0;
		_skill = NIFLHEIM_SKILL::NONE;
		_skillCooldown = TIMEMANAGER->getWorldTime();

		_state = IDLE;
	}
}
