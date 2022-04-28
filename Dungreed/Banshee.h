#pragma once
#include "Enemy.h"

class Banshee : public Enemy
{
private:
	enum BANSHEE_MOTION
	{
		IDLE,
		ATTACK
	};

private:
	float _attackTime;

public:
	Banshee(float x, float y);
	virtual ~Banshee();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void move();
	void animation();
	void initAnimation();

	void attack();
	virtual void frameUpdateEvent() override;

};

