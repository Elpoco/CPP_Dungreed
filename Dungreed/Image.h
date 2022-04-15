#pragma once
#include "ImageBase.h"

class Animation;

class Image : public ImageBase
{
public:

	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,
		LOAD_FILE,
		LOAD_EMPTY,
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD		resID;
		HDC			hMemDC;
		HBITMAP		hBit;
		HBITMAP		hOBit;
		float		x;
		float		y;
		int			width;
		int			height;
		int			currentFrameX;
		int			currentFrameY;
		int			maxFrameX;
		int			maxFrameY;
		int			frameWidth;
		int			frameHeight;
		BYTE		loadType;

		tagImage()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
	} IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;
	CHAR*			_fileName;
	BOOL			_isTrans;		// 배경색 유무
	COLORREF		_transColor;	// 배경색을 없앨 RGB값   RGB(각각 1바이트 0~255 농도 표현 가능)

	BLENDFUNCTION	_blendFunc;
	LPIMAGE_INFO	_blendImage;

	void setSize(string fileName, int& width, int& height);

public:
	HRESULT init(int width, int height);
	HRESULT init(const DWORD resID, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0), float scale = 1.0f);

	HRESULT init(const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	HRESULT initForAlphaBlend();

	void setTransColor(BOOL isTrans, COLORREF transColopr);

	void release();

	void render(HDC hdc);
	virtual void render(HDC hdc, float destX, float destY) override;
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	void frameRender(HDC hdc, int destX, int destY);
	virtual void frameRender(HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY) override;
	virtual void frameAlphaRender(HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, BYTE alpha) override;

	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	void aniRender(HDC hdc, int destX, int destY, Animation* ani);

	// ==============
	// # 인라인 함수 #
	// ==============
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	inline float getX(void) { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }
	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }

	inline void setCenter(float x, float y) {
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	virtual inline int getWidth(void) override { return _imageInfo->width; }
	virtual inline int getHeight(void) override { return _imageInfo->height; }

	inline RECT boundingBox(void) {
		RECT rc = {
			(int)_imageInfo->x,
			(int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->width,
			(int)_imageInfo->y + _imageInfo->height
		};
		return rc;
	}

	inline RECT boundingBoxWithFrame(void) {
		RECT rc = {
			(int)_imageInfo->x,
			(int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->frameWidth,
			(int)_imageInfo->y + _imageInfo->frameHeight
		};
		return rc;
	}

	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX) {
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX) {
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY) {
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY) {
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	virtual inline int getFrameWidth(void) override { return _imageInfo->frameWidth; }
	virtual inline int getFrameHeight(void) override { return _imageInfo->frameHeight; }

	virtual inline int getMaxFrameX(void) override { return _imageInfo->maxFrameX; }
	virtual inline int getMaxFrameY(void) override { return _imageInfo->maxFrameY; }

	Image();
	~Image() {}
};

