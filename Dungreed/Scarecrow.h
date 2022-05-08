#pragma once
#include "Enemy.h"

class Scarecrow : public Enemy
{
private:
	enum SCARECROW_MOTION
	{
		IDLE,
		ATTACK
	};

public:
	Scarecrow(float x, float y);
	virtual ~Scarecrow();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void move();
	void initAnimation();

};

