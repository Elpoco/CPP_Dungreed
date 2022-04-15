#pragma once
#include "Object.h"

namespace BelialSwordSet
{
	constexpr float SWORD_SPEED		= 12.0f;
	constexpr float SWORD_LIFE_TIME = 8.0f;
	constexpr int	SWORD_DAMAGE	= 4;
}

class BelialSword : public Object
{
private:
	ImageBase* _img;
	float _startX;
	float _startY;
	float _angle;
	int	  _degree;

	POINT* _ptPlayer;
	float _initTime;
	bool _isShoot;
	bool _isMoving;
	bool _isCollision;

	RECT _rcRender;

public:
	BelialSword(float x, float y, POINT* ptPlayer);
	virtual ~BelialSword();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void deleteEffect() override;
	virtual void collisionObject() override;
	virtual void stopObject() override { _isMoving = false; }

	virtual int getDmg() override { return BelialSwordSet::SWORD_DAMAGE; }

	void move();
};

