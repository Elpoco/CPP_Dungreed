#pragma once
#include "GameNode.h"


class StartScene : public GameNode
{
public:
	StartScene();
	~StartScene();

	HRESULT init();
	void release();
	void update();
	void render();

private:
	float _loop1, _loop2;
	RECT _logo;

};

