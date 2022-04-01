#include "Stdafx.h"
#include "ImageManager.h"

#include "ImageLoader.h"

HRESULT ImageManager::init()
{
	_imageLoader = new ImageLoader;
	_imageLoader->init();

	return S_OK;
}

void ImageManager::release()
{
	this->deleteAll();
	SAFE_DELETE(_imageLoader);
}

Image* ImageManager::addImage(string strKey, int width, int height)
{
	Image* img = findImage(strKey);

	if (img) return img;

	img = new Image;
	if (FAILED(img->init(width, height))) {
		SAFE_DELETE(img);
		errorMsg(IM_ERROR_CODE::LOAD_FAILD, strKey);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image* ImageManager::addImage(string strKey, const char* fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	Image* img = findImage(strKey);

	if (img) return img;

	img = new Image;
	if (FAILED(img->init(fileName, width, height, isTrans, transColor))) {
		SAFE_DELETE(img);
		errorMsg(IM_ERROR_CODE::LOAD_FAILD, strKey);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image* ImageManager::addImage(string strKey, const char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	Image* img = findImage(strKey);

	if (img) return img;

	img = new Image;
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor))) {
		SAFE_DELETE(img);
		errorMsg(IM_ERROR_CODE::LOAD_FAILD, strKey);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image* ImageManager::addFrameImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	Image* img = findImage(strKey);

	if (img) return img;

	img = new Image;
	if (FAILED(img->init(fileName, width, height, maxFrameX, maxFrameY, isTrans, transColor))) {
		SAFE_DELETE(img);
		errorMsg(IM_ERROR_CODE::LOAD_FAILD, strKey);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image* ImageManager::findImage(string strKey)
{
	auto key = _mImageList.find(strKey);

	if (key != _mImageList.end()) {
		return key->second;
	}

	return nullptr;
}

bool ImageManager::deleteImage(string strKey)
{
	auto key = _mImageList.find(strKey);

	if (key != _mImageList.end()) {
		key->second->release();
		SAFE_DELETE(key->second);
		_mImageList.erase(key);

		return true;
	}

	return false;
}

bool ImageManager::deleteAll()
{
	auto iter = _mImageList.begin();

	for (; iter != _mImageList.end();) {
		if (iter->second != NULL) {
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else ++iter;
	}

	_mImageList.clear();

	return true;
}

// ==============
// ## �Ϲ� ���� ##
// ==============
void ImageManager::render(string strKey, HDC hdc)
{
	Image* img = findImage(strKey);
	if (img)
	{
		img->render(hdc);
	}
		
}

void ImageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	Image* img = findImage(strKey);
	if (img)
	{
		img->render(hdc, destX, destY);
	}
}

void ImageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	Image* img = findImage(strKey);
	if (img)
	{
		img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
	}
}

// ==============
// ## ���� ���� ##
// ==============
void ImageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	Image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, alpha);
}

void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	Image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	Image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}

// ================
// ## ������ ���� ##
// ================
void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	Image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY);
}

void ImageManager::frameRender(string strKey, HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY)
{
	Image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void ImageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	Image* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);
}

void ImageManager::loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	Image* img = findImage(strKey);
	if (img) img->loopAlphaRender(hdc, drawArea, offsetX, offsetY, alpha);
}

void ImageManager::errorMsg(IM_ERROR_CODE code, string str)
{
	switch (code)
	{
	case IM_ERROR_CODE::LOAD_FAILD:
		cout << "IMAGE LOAD FALED: " << str << endl;
		break;
	default:
		break;
	}
}
