#pragma once
#include "Unit.h"

namespace PlayerSet
{
	constexpr float HIT_TIME	= 2.0f;
	constexpr BYTE  HIT_ALPHA	= 150;

	constexpr float DASH_DISTANCE	= 300;
	constexpr float DASH_SPEED		= 8.0f;

	constexpr int	DEFAULT_HP = 50;
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
	BOOL _isStop;

	POINT	_body;
	POINT	_hand;
	int		_mainHandX;

	int		_dashMove;
	float	_dashAngle;

	int _maxHp;
	int _curHp;

	BOOL _isDust;

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
	virtual void frameUpdateEvent();

	void moveLeft();
	void moveRight();
	void setIdle();
	void attack();
	void dash();
	void jump();

	void getItem(Code::ITEM code);

};

