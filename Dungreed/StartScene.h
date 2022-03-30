#pragma once
#include "GameNode.h"


class StartScene : public GameNode
{
private:
	float _loop1, _loop2;
	RectF _logo;

public:
	StartScene();
	~StartScene();

	HRESULT init();
	void release();
	void update();
	void render();

};

