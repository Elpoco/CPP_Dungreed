#pragma once
#include "GameNode.h"

class Player;

class TestScene : public GameNode
{
private:
	Player* _player;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	TestScene() {}
	~TestScene() {}
};

