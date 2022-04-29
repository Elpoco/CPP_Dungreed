#pragma once
#include "Enemy.h"

namespace BatSet
{
	constexpr float BULLET_SPEED = 3.5f;
}

class Bat : public Enemy
{
private:
	enum BAT_MOTION
	{
		IDLE,
		ATTACK
	};

	enum class BAT_TYPE
	{
		NORMAL,
		GIANT,
		RED,

		TYPE_CNT,
		NONE,
	};

private:
	BAT_TYPE _batType;
	float _attackTime;
	float _angle;
	float _shootTime;
	float _distance;

public:
	Bat(float x, float y, Code::UNIT code = Code::UNIT::BAT);
	virtual ~Bat();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void move();
	void initAnimation();

	void attack();
	virtual void frameUpdateEvent() override;

};
