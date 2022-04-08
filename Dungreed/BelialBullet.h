#pragma once
#include "Bullet.h"
class BelialBullet : public Bullet
{
public:
	BelialBullet(string imgName, float x, float y, float moveX, float moveY, float speed, float distance = 1500);
	~BelialBullet();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void move();
	void animation();

};

