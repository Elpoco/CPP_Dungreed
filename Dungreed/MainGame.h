#pragma once
#include "GameNode.h"

class ImageLoader;

class MainGame : public GameNode
{
public:
	MainGame();
	~MainGame();
	
	HRESULT init();
	void release();
	void update();
	void render();

private:
	ImageLoader* _imageLoader;

};
