#pragma once
#include "Unit.h"

#define KEY_INVENTORY		'V'
#define KEY_CHANGE_WEAPON	'~'
#define KEY_INTERACTION		'F'

class Player : public Unit
{
private:
	enum PLAYER_MOTION
	{
		IDLE,
		RUN,
		JUMP,
	};

private:
	ImageGp* _weapon;
	int _mainHandX;
	RECT _rcWeapon;
	int _angleWeapon;
	int _atkCnt;		// 첫번째 공격인지 두번째 공격인지

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

	void moveLeft();
	void moveRight();

	void settingWeapon();

};

