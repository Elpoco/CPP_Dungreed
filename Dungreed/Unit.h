#pragma once
#include "Object.h"

/*
»óÅÂ°ª
*/

class Unit : public Object
{
protected:
	bool _isJump;
	bool _isFall;
	bool _isFlying;

	float _moveSpeed;
	float _jumpSpeed;
	float _fallSpeed;
	float _gravity;

public:
	Unit();
	virtual ~Unit();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void move();

	virtual void jump();

};

