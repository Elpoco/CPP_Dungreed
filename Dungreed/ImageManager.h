#pragma once
#include "SingletonBase.h"
#include "Image.h"

class ImageLoader;

class ImageManager : public SingletonBase<ImageManager>
{
private:
	typedef map<string, Image*> mapImageList;
	typedef map<string, Image*>::iterator mapImageIter;

	enum class IM_ERROR_CODE
	{
		LOAD_FAILD
	};

private:
	mapImageList _mImageList;
	HDC _memDc;

	ImageLoader* _imageLoader;

public:
	HRESULT init();
	void release();

	void setMemDc(HDC hdc) { _memDc = hdc; }

	Image* addImage(string strKey, int width, int height);
	Image* addImage(string strKey, const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	Image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	Image* addFrameImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	// gdi+
	Image* addImage(string strKey, const WCHAR* fileName);
	Image* addFrameImage(string strKey, const WCHAR* fileName, int maxFrameX, int maxFrameY);

	Image* findImage(string strKey);
	bool deleteImage(string strKey);
	bool deleteAll();

	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY);

	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	void errorMsg(IM_ERROR_CODE code, string str);

	ImageManager() {}
	~ImageManager() {}
};

