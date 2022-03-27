#pragma once
class ImageLoader
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

