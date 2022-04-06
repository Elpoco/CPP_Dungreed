#pragma once
#include "Unit.h"

#define KEY_INVENTORY		'V'
#define KEY_CHANGE_WEAPON	'~'
#define KEY_INTERACTION		'F'

class Player : public Unit
{
private:
	typedef struct tagPlayerHand
	{
		Image* image;
		RECT rc;
	} PlayerHand;

	enum PLAYER_MOTION
	{
		IDLE,
		RUN,
		JUMP,
	};

private:
	PLAYER_MOTION _state;
	PlayerHand hand;

	int mainHandX;
	int mainWeaponX;
	int tempAngle;

	ImageGp* _weapon;
	int angle;
	int attackAngle;

public:
	Player();
	~Player();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void move();
	void animation();

	void initAnimation();

};

