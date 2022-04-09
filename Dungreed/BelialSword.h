#pragma once
#include "Object.h"

class BelialSword : public Object
{
private:
	ImageGp* _img;
	float _startX;
	float _startY;
	float _angle;
	int	  _degree;

	POINT* _ptPlayer;
	float _initTime;
	bool _isShoot;
	bool _isMoving;

public:
	BelialSword(float x, float y, POINT* ptPlayer);
	~BelialSword();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void deleteEffect() override;
	virtual void collisionObject() override;
	virtual void stopObject() override { _isMoving = false; }

	void move();
};

