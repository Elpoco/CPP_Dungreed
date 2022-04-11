#pragma once
#include "Enemy.h"

class Niflheim : public Enemy
{
private:

public:
	Niflheim(float x, float y);
	~Niflheim();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void deleteEffect() override;

	void move();
	void animation();
	void initAnimation();
};

