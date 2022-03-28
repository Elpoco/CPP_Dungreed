#pragma once
#include "GameNode.h"

class Object;

class Collider : public GameNode
{
private:
	Object* _object;
	POINT _prove[ColliderInfo::DIRECTION::DIR_CNT];

public:
	Collider(Object* object);
	~Collider();

	HRESULT init();
	void release();
	void update();
	void render();

	void settingProve();

	void tileCollision();

};

