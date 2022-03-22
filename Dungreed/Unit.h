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
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void move(void);
	void animation(void);

	virtual void jump(void);

	Unit();
	virtual ~Unit() {}
};

