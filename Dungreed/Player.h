#pragma once
#include "Unit.h"

namespace PlayerSet
{
	constexpr float HIT_TIME	= 1.5f;
	constexpr BYTE  HIT_ALPHA	= 150;

	constexpr float DASH_DISTANCE	= 250;
	constexpr float DASH_SPEED		= 8.0f;
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

	string	_dashImgName;
	int		_dashMove;
	float	_dashAngle;

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
	void skill();
	void dash();
	void jump();

	BOOL getItem(Code::ITEM code);

};

