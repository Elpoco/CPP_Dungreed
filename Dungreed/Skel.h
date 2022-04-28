#pragma once
#include "Enemy.h"

class Skel : public Enemy
{
private:
	enum SKEL_MOTION
	{
		IDLE,
		MOVE,
		ATTACK,
	};

private:
	ImageBase* _sword;

	float _attackTime;
	float _angleWeapon;
	float _anglePlayer;

	int _atkCnt;

public:
	Skel(float x, float y);
	virtual ~Skel();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void move();
	void initAnimation();

	void attack();
	virtual void frameUpdateEvent() override;

};

