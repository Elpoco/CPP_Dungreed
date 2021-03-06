#pragma once
#include "Enemy.h"

class NiflheimPillar;

namespace NiflheimSet
{
	constexpr float SKILL_TIME   = 2.0f;
	constexpr float BULLET_SPEED = 4.0f;
	constexpr int PILLAR_CNT	 = 4;
	constexpr int BULLET_CNT	 = 32;
	constexpr int BULLET_DMG	 = 20;
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
		AROUND,			// 주변에 모여서 나선형태
		WIDE,			// 네방향으로 가서 나선형태
		WIDE_LINE,		// 네방향으로 가서 플레이어한테 직선형태
		LINE_UP,	    // 중앙에 직선으로 모여서 나선형태
		FULL_ATTACK,    // 모든기둥이 플레이어한테 연사
		TELEPORT,
		ICICLE,
		SKILL_CNT,
		STUN,
	};

	friend class NiflheimPillar;

private:
	NiflheimPillar* _pillar[NiflheimSet::PILLAR_CNT];
	bool _onInitPillar;
	bool _checkPillar;
	float _stunTime;

	NIFLHEIM_SKILL  _skill;
	NIFLHEIM_SKILL	_lastSkill;
	int				_skillTick;
	int				_skillCnt;	  // 스킬 횟수
	int 			_skillActCnt; // 스킬 실행 횟수
	bool			_skillAuto;
	float			_skillCooldown;

	int _skillFirstTick;
	POINT _ptLastPlayer;

	float _bulletSound;

public:
	Niflheim(float x, float y);
	virtual ~Niflheim();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void deleteEffect() override;
	virtual void hitAttack(int dmg, int dir) override;

	void move();
	void animation();
	void initAnimation();

	void initPillar();
	void attackAnimation();
	void shootBullet(float x, float y, float angle);
	void turnAround();
	void moveAndFire();
	void teleport();
	void icicle();
};

