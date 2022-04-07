#pragma once
#include "GameNode.h"

class Object;

class TownScene : public GameNode
{
private:
	Image* _layer;
	Image* _background;

	Object* _camera;

public:
	TownScene();
	~TownScene();

	HRESULT init();
	void release();
	void update();
	void render();

};

