#pragma once
#include "GameNode.h"

class MainGame : public GameNode
{
public:
	MainGame();
	~MainGame();
	
	HRESULT init();
	void release();
	void update();
	void render();

};
