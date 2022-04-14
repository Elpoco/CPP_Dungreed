#pragma once
#include "GameNode.h"

class ImageLoader : public GameNode
{
public:
	ImageLoader();
	~ImageLoader();

	HRESULT init();
	void release();

	void loadImages();
};

