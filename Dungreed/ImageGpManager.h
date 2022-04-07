#pragma once
#include "SingletonBase.h"

#include "ImageGp.h"

class ImageGpManager : public SingletonBase<ImageGpManager>
{
private:
	typedef map<string, ImageGp*> mapImageList;
	typedef map<string, ImageGp*>::iterator mapImageIter;

private:
	mapImageList _mImageList;

public:
	ImageGpManager();
	~ImageGpManager();

	HRESULT init();
	void release();

	ImageGp* findImage(string strKey);
	bool deleteAll();

	ImageGp* addImage(HDC memDc, string strKey, string fileName, float scaleW = 1, float scaleH = 1);
	ImageGp* addFrameImage(HDC hdc, string strKey, string fileName, int maxFrameX, int maxFrameY);

	void render(string strKey, HDC hdc, int destX, int destY, int angle = 0, POINT rotateCenter = { 0,0 });
	void frameRender(string strKey, HDC hdc, int destX, int destY, int frameX, int frameY, int angle = 0, POINT rotateCenter = { 0,0 });

	POINT getImageSize(string fileName);
};

