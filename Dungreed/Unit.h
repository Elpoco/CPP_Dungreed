#pragma once
#include "Object.h"
#include "PixelCollider.h"

#define UNIT_MOVE_SPEED		1.0f
#define UNIT_JUMP_SPEED		15.0f
#define UNIT_FALL_SPEED		0.0f
#define UNIT_GRAVITY		0.3f

class Unit : public Object, public PixelCollider
{
protected:
	bool _isLeft;
	bool _isJump;
	bool _isFall;

	float _moveSpeed;
	float _jumpSpeed;
	float _fallSpeed;
	float _gravity;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void move();
	void animation();

	virtual void jump();

	void setCollision(bool isCollision) { _isCollision = isCollision; }

	Unit();
	virtual ~Unit() {}
};

