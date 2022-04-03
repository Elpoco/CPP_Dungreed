#pragma once
#include "Enemy.h"
class SkelDog : public Enemy
{
public:
	SkelDog();
	~SkelDog();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void initAnimation();

};

