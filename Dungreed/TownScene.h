#pragma once
#include "GameNode.h"
class TownScene : public GameNode
{
private:
	Image* _layer;

public:
	TownScene();
	~TownScene();

	HRESULT init();
	void release();
	void update();
	void render();

};

