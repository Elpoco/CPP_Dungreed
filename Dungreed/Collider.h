#pragma once
#include "GameNode.h"

class Object;

using namespace ColliderInfo;

class Collider : public GameNode
{
private:
	Object* _object;
	POINT _prove[DIRECTION::DIR_CNT];

public:
	HRESULT init();
	HRESULT init(Object* object);
	void release();
	void update();
	void render();

	void settingProve();

};

