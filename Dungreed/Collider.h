#pragma once

class Object;

class Collider
{
private:
	Object* _object;
	POINT _prove[ColliderEnum::DIRECTION::DIR_CNT];

public:
	Collider(Object* object);
	~Collider();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void settingProve();

	void tileCollision();

};

