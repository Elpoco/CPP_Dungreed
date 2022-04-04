#pragma once
#include "Enemy.h"
class LittleGhost : public Enemy
{
private:
	enum LITTLEGHOST_MOTION
	{
		IDLE
	};

public:
	LittleGhost();
	~LittleGhost();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void move();
	void animation();

	void initAnimation();

};

