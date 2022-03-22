#pragma once
#include "GameNode.h"
class LoadScene : public GameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void loadImage(void);

	LoadScene() {}
	~LoadScene() {}
};

