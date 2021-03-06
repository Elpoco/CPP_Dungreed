#include "Stdafx.h"
#include "ImageGpManager.h"

ImageGpManager::ImageGpManager()
{
}

ImageGpManager::~ImageGpManager()
{
}

HRESULT ImageGpManager::init()
{
	return S_OK;
}

void ImageGpManager::release()
{
	this->deleteAll();
}

ImageGp* ImageGpManager::findImage(string strKey)
{
	auto key = _mImageList.find(strKey);

	if (key != _mImageList.end()) {
		return key->second;
	}

	return nullptr;
}

bool ImageGpManager::deleteAll()
{
	auto iter = _mImageList.begin();

	for (; iter != _mImageList.end();)
	{
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else ++iter;
	}

	_mImageList.clear();
	
	return false;
}

ImageGp* ImageGpManager::addImage(HDC hdc, string strKey, string fileName, float scaleW, float scaleH)
{
	ImageGp* img = findImage(strKey);

	if (img) return img;

	img = new ImageGp;

	wstring name = wstring(fileName.begin(), fileName.end());

	if (FAILED(img->init(hdc, name.c_str(), scaleW, scaleH)))
	{
		SAFE_DELETE(img);
		ImageManager::errorMsg(ImageManager::IM_ERROR_CODE::LOAD_FAILD, strKey);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

ImageGp* ImageGpManager::addFrameImage(HDC memDc, string strKey, string fileName, int maxFrameX, int maxFrameY)
{
	ImageGp* img = findImage(strKey);

	if (img) return img;

	img = new ImageGp;

	wstring name = wstring(fileName.begin(), fileName.end());

	if (FAILED(img->init(memDc, name.c_str(), maxFrameX, maxFrameY)))
	{
		SAFE_DELETE(img);
		ImageManager::errorMsg(ImageManager::IM_ERROR_CODE::LOAD_FAILD, strKey);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

void ImageGpManager::render(string strKey, HDC hdc, float x, float y, int angle, POINT rotateCenter)
{
	ImageGp* img = findImage(strKey);
	if (img)
	{
		img->render(hdc, x, y, angle, rotateCenter);
	}
}

void ImageGpManager::frameRender(string strKey, HDC hdc, float x, float y, int frameX, int frameY, int angle, POINT rotateCenter)
{
	ImageGp* img = findImage(strKey);
	if (img)
	{
		img->frameRender(hdc, x, y, frameX, frameY, angle, rotateCenter);
	}
}

POINT ImageGpManager::getImageSize(string fileName)
{
	wstring name = wstring(fileName.begin(), fileName.end());
	ImageGp img(name.c_str());

	POINT size = { img.getWidth(), img.getHeight() };
	img.release();

	return size;
}
