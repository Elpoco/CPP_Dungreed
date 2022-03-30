#pragma once
#include "GameNode.h"

class TestScene : public GameNode
{
private:

public:
	HRESULT init();
	void release();
	void update();
	void render();

	TestScene() {}
	~TestScene() {}
};

