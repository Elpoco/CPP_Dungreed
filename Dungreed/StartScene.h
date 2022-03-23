#pragma once
#include "GameNode.h"
class StartScene : public GameNode
{
private:
	float _loop1, _loop2;
	RECT _logo;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void loadImage(void);

	StartScene() {}
	~StartScene() {}
};

