#pragma once
#include "Unit.h"

class Item;
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
	Inventory* _inventory;

	POINT _hand;
	Item* _item;
	int _mainHandX;

public:
	Player();
	Player(float x, float y);
	virtual ~Player();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void hitAttack(int dmg, int dir) override;
	virtual int getDmg() override { return 3; }

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

