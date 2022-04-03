#pragma once
#include "GameNode.h"

class ImageLoader : public GameNode
{
public:
	ImageLoader();
	~ImageLoader();

	HRESULT init();
	void release();
	void update();
	void render();

	void loadImages();
};

