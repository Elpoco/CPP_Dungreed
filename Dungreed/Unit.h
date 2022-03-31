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
	float _gravity;

public:
	Unit();
	virtual ~Unit();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void move();

	virtual void jump();

};

