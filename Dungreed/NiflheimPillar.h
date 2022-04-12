#pragma once
#include "Enemy.h"

#include "Niflheim.h"

namespace NiflheimPillarSet
{
	constexpr float IDLE_SPEED		= 0.009f;
	constexpr float AROUND_SPEED	= 0.02f;
}

class NiflheimPillar : public Enemy
{
private:
	enum PILLAR_ORDER
	{
		LT,
		RT,
		LB,
		RB,
		ORDER_CNT
	};

private:
	PILLAR_ORDER _order;

	Niflheim::NIFLHEIM_SKILL _skill;
	bool _isInit;
	float* _niflheimX;
	float* _niflheimY;
	float _bossAngle;
	float _bossDistance;
	float _spinSpeed;

	float _wideAngle;
	float _wideLeft;
	float _wideRight;
	float _wideTop;
	float _wideBottom;
	float _wideMoveX;
	float _wideMoveY;

	POINT _movePoint;

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

	void settingOrder();

	void setPosAddress(float* x, float* y) { _niflheimX = x; _niflheimY = y; }
	inline void setSkill(Niflheim::NIFLHEIM_SKILL skill) { _skill = skill; }
	inline float getAngle() { return _bossAngle; }
	inline int getImgAngle() { return _imgAngle; }

};
