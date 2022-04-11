#pragma once
#include "Enemy.h"
class NiflheimPillar : public Enemy
{
private:
	enum class PILLAR_STATE
	{
		IDLE,
		MUSTER,		   // 주변에 모여서 나선형태
		DISSOLUTION,   // 네방향으로 가서 나선형태
		DISSOLUTION_L, // 네방향으로 가서 플레이어한테 직선형태
		LINE_UP,	   // 중앙에 직선으로 모여서 나선형태
		FULL_ATTACK	   // 모든기둥이 플레이어한테 연사
	};

private:
	float* _niflheimX;
	float* _niflheimY;
	float _bossAngle;
	float _bossDistance;
	float _shootAngle;

public:
	NiflheimPillar(float x, float y);
	~NiflheimPillar();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void move();
	void animation();
	void initAnimation();

	void setPosAddress(float* x, float* y) { _niflheimX = x; _niflheimY = y; }

};

