#pragma once
#include "Unit.h"

class Inventory;

namespace PlayerSet
{
	constexpr float HIT_TIME = 2.0f;
	constexpr BYTE HIT_ALPHA = 150;
}

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

	Inventory* _inventory;

public:
	Player();
	Player(float x, float y);
	virtual ~Player();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void hitAttack(int dmg, int dir) override;

	void move();
	void animation();
	void initAnimation();

	void moveLeft();
	void moveRight();

	void settingWeapon();

};

