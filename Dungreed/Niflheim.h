#pragma once
#include "Enemy.h"

class NiflheimPillar;

namespace NifleheimSet
{
	constexpr float SKILL_TIME  = 2.0f;
	constexpr int PILLAR_CNT	= 4;
	constexpr int BULLET_CNT	= 30;
	constexpr int BULLET_CNT_L	= 19;
}

class Niflheim : public Enemy
{
private:
	enum NIFLHEIM_MOTION
	{
		IDLE,
		ATTACK,
		DIE
	};

	enum class NIFLHEIM_SKILL
	{
		NONE,
		AROUND,		   // 주변에 모여서 나선형태
		WIDE,   // 네방향으로 가서 나선형태
		WIDE_LINE, // 네방향으로 가서 플레이어한테 직선형태
		LINE_UP,	   // 중앙에 직선으로 모여서 나선형태
		FULL_ATTACK,   // 모든기둥이 플레이어한테 연사
		SKILL_CNT
	};

	friend class NiflheimPillar;

private:
	NiflheimPillar* _pillar[NifleheimSet::PILLAR_CNT];
	bool _onInitPillar;

	NIFLHEIM_SKILL  _skill;
	NIFLHEIM_SKILL	_lastSkill;
	int				_skillTick;
	int 			_skillActCnt;
	bool			_skillAuto;
	float			_skillCooldown;

	int _skillFirstTick;
	POINT _ptLastPlayer;

public:
	Niflheim(float x, float y);
	virtual ~Niflheim();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void deleteEffect() override;
	virtual void hitAttack(int dmg) override;

	void move();
	void animation();
	void initAnimation();

	void initPillar();
	void attackAnimation();
	void shootBullet(float x, float y, float angle);
	void turnAround();
	void moveAndFire();
};

