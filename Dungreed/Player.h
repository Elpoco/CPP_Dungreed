#pragma once
#include "Unit.h"

#define KEY_LEFT			'A'
#define KEY_UP				'W'
#define KEY_RIGHT			'D'
#define KEY_DOWN			'S'
#define KEY_INVENTORY		'V'
#define KEY_CHANGE_WEAPON	'~'
#define KEY_INTERACTION		'F'

#define MOVE_SPEED	2.0f

class Player : public Unit
{
private:
	enum class PLAYER_STATE
	{
		IDLE,
		RUN
	};

private:
	PLAYER_STATE _state;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void initAnimation(void);

	void move(void);
	void animation(void);

	Player();
	~Player();
};

