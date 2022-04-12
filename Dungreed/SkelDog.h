#pragma once
#include "Enemy.h"

class SkelDog : public Enemy
{
private:
	enum SKELDOG_MOTION
	{
		IDLE,
		RUN,
		DIE
	};

private:
	float _overMove;
	int _atkCnt;

public:
	SkelDog(float x, float y);
	~SkelDog();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void move();
	void animation();
	void initAnimation();

	void attack();


};

