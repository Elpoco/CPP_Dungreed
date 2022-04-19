#pragma once
#include "Unit.h"

namespace PlayerSet
{
	constexpr float HIT_TIME = 2.0f;
	constexpr BYTE HIT_ALPHA = 150;
	constexpr float DASH_DISTANCE = 300;
	constexpr int DASH_SPEED = 10;
}

class Player : public Unit
{
private:
	enum PLAYER_MOTION
	{
		IDLE,
		RUN,
		JUMP,
		DASH = 2,
	};

private:
	POINT _body;
	POINT _hand;
	BOOL _isDash;
	int _mainHandX;
	int _dashMove;
	float _dashAngle;

	BOOL _isStop;

public:
	Player();
	Player(float x, float y);
	virtual ~Player();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void hitAttack(int dmg, int dir) override;
	virtual int getDmg() override;

	virtual void stopObject() override { _isStop = TRUE; }
	virtual void resumeObject() override { _isStop = FALSE; }

	void move();
	void animation();
	void initAnimation();

	void moveLeft();
	void moveRight();
	void setIdle();
	void attack();
	void dash();

	void getItem(Code::ITEM code);

};

