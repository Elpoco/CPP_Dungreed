#pragma once

class ImageGp
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
		}
	} GP_IMAGE_INFO, *LPGP_IMAGE_INFO;

private:
	LPGP_IMAGE_INFO _imageInfo;

	Graphics* _graphics;
	Gdiplus::Bitmap* _img;

public:
	ImageGp();
	~ImageGp();
	
	HRESULT init(const WCHAR* fileName, float scaleW = 1, float scaleH = 1);

	void release();

	void render(HDC hdc, float destX, float destY, int angle = 0, PointF rotateCenter = {0, 0});

	inline int getWidth() { return _imageInfo->width; }
	inline int getHeight() { return _imageInfo->height; }

};

