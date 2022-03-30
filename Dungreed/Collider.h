#pragma once

using namespace ColliderEnum;

class Collider
{
private:
	PointF _prove[DIRECTION::DIR_CNT];

public:
	Collider();
	~Collider();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void settingProve();

	void tileCollision(); 

};

