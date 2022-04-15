#pragma once
#include "GameNode.h"

class UI;

namespace StartSceneSet
{
	constexpr int BIRD_CNT = 5;
}

class StartScene : public GameNode
{
private:
	float _loop1, _loop2;
	UI* _bird[StartSceneSet::BIRD_CNT];

public:
	StartScene();
	~StartScene();

	HRESULT init();
	void release();
	void update();
	void render();

};

