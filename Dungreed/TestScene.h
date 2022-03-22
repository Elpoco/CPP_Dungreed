#pragma once
#include "GameNode.h"

class Player;

class TestScene : public GameNode
{
private:
	Player* _player;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	TestScene() {}
	~TestScene() {}
};

