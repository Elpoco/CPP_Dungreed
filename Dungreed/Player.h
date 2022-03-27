#pragma once
#include "Unit.h"

#define KEY_INVENTORY		'V'
#define KEY_CHANGE_WEAPON	'~'
#define KEY_INTERACTION		'F'

#define MOVE_SPEED	2.0f

using namespace PlayerInfo;

class Player : public Unit
{
private:
	PLAYER_STATE _state;

public:
	Player();
	~Player();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void initAnimation();

	void move();
	void animation();

};

