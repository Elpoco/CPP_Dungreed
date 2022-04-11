#pragma once
#include "Enemy.h"

class NiflheimPillar;

constexpr int PILLAR_CNT = 4;

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
		MUSTER,		   // 주변에 모여서 나선형태
		DISSOLUTION,   // 네방향으로 가서 나선형태
		DISSOLUTION_L, // 네방향으로 가서 플레이어한테 직선형태
		LINE_UP,	   // 중앙에 직선으로 모여서 나선형태
		FULL_ATTACK,   // 모든기둥이 플레이어한테 연사
		SKILL_CNT
	};

private:
	NiflheimPillar* _pillar[PILLAR_CNT];
	NIFLHEIM_SKILL _skill;

public:
	Niflheim(float x, float y);
	~Niflheim();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void deleteEffect() override;

	void move();
	void animation();
	void initAnimation();
};

