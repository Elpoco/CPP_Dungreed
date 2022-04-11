#pragma once
#include "ImageBase.h"

class ImageGp : public ImageBase
{
public:
	typedef struct tagImageGp
	{
		int width;
		int height;
		int currentFrameX;
		int currentFrameY;
		int maxFrameX;
		int maxFrameY;
		int frameWidth;
		int frameHeight;

		float scaleW;
		float scaleH;

		tagImageGp()
		{
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;

			scaleW = 1.0f;
			scaleH = 1.0f;
		}
	} GP_IMAGE_INFO, *LPGP_IMAGE_INFO;

private:
	LPGP_IMAGE_INFO _imageInfo;

	Gdiplus::Graphics* _graphics;
	Gdiplus::Bitmap* _img;

	HDC hdc;

public:
	ImageGp();
	ImageGp(const WCHAR* fileName);
	~ImageGp();
	
	HRESULT init(HDC hdc, const WCHAR* fileName, float scaleW = 1, float scaleH = 1);
	HRESULT init(HDC hdc, const WCHAR* fileName, int maxFrameX, int maxFrameY);

	void release();

	virtual void render(HDC hdc, float x, float y) override;
	virtual void render(HDC hdc, float x, float y, int angle, POINT rotateCenter) override;
	virtual void frameRender(HDC hdc, float x, float y, int frameX, int frameY) override;
	virtual void frameRender(HDC hdc, float x, float y, int frameX, int frameY, int angle, POINT rotateCenter) override;

	virtual inline int getWidth() override { return _imageInfo->width; }
	virtual inline int getHeight() override { return _imageInfo->height; }
	virtual inline int getFrameWidth() override { return _imageInfo->frameWidth; }
	virtual inline int getFrameHeight() override { return _imageInfo->frameHeight; }
	virtual inline int getMaxFrameX() override { return _imageInfo->maxFrameX; }
	virtual inline int getMaxFrameY() override { return _imageInfo->maxFrameY; }

};

