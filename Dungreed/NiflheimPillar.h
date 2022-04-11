#pragma once
#include "Enemy.h"
class NiflheimPillar : public Enemy
{
private:
	ImageGp* _img;
	float _angle;

public:
	NiflheimPillar(float x, float y);
	~NiflheimPillar();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void move();
	void animation();
	void initAnimation();

};

