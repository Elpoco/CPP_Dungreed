#include "Stdafx.h"
#include "ImageGp.h"

using namespace Gdiplus;

ImageGp::ImageGp()
{
}

ImageGp::ImageGp(const WCHAR* fileName)
{
	// 이미지 사이즈만 얻는 기능
	_img = new Bitmap(fileName);
	_imageInfo = new GP_IMAGE_INFO;
	_imageInfo->width = _img->GetWidth();
	_imageInfo->height = _img->GetHeight();
}

ImageGp::~ImageGp()
{
}

HRESULT ImageGp::init(HDC memDc, const WCHAR* fileName, float scaleW, float scaleH)
{
	if (_imageInfo != NULL) this->release();

	_img = new Bitmap(fileName);

	if (_img->GetLastStatus() != Ok) return E_FAIL;

	_graphics = new Graphics(memDc);

	_imageInfo = new GP_IMAGE_INFO;
	_imageInfo->width = _img->GetWidth();
	_imageInfo->height = _img->GetHeight();
	_imageInfo->scaleW = scaleW;
	_imageInfo->scaleH = scaleH;

	return S_OK;
}

HRESULT ImageGp::init(HDC memDc, const WCHAR* fileName, int maxFrameX, int maxFrameY)
{
	if (_imageInfo != NULL) this->release();

	_img = new Bitmap(fileName);

	if (_img->GetLastStatus() != Ok) return E_FAIL;

	_graphics = new Graphics(memDc);

	_imageInfo = new GP_IMAGE_INFO;
	_imageInfo->width = _img->GetWidth();
	_imageInfo->height = _img->GetHeight();
	_imageInfo->maxFrameX = maxFrameX;
	_imageInfo->maxFrameY = maxFrameY;
	_imageInfo->frameWidth = _imageInfo->width / maxFrameX;
	_imageInfo->frameHeight = _imageInfo->height / maxFrameY;

	return S_OK;
}

void ImageGp::release()
{
	SAFE_DELETE(_imageInfo);
	SAFE_DELETE(_graphics);
	SAFE_DELETE(_img);
}

void ImageGp::render(HDC hdc, float destX, float destY, int angle, POINT rotateCenter)
{
	if (rotateCenter.x == 0) rotateCenter.x = destX;
	if (rotateCenter.y == 0) rotateCenter.y = destY;

	Matrix matrix;
	matrix.RotateAt(-angle, PointToPointF(rotateCenter));
	_graphics->SetTransform(&matrix);

	_graphics->DrawImage(_img, destX, destY);
}

void ImageGp::frameRender(float destX, float destY, int frameX, int frameY, int angle, POINT rotateCenter)
{
	if (rotateCenter.x == 0) rotateCenter.x = destX;
	if (rotateCenter.y == 0) rotateCenter.y = destY;

	Matrix matrix;
	matrix.RotateAt(-angle, PointToPointF(rotateCenter));
	_graphics->SetTransform(&matrix);

	_graphics->DrawImage(
		_img,
		(int)destX, (int)destY,
		frameX * _imageInfo->frameWidth, 
		frameY * _imageInfo->frameHeight, 
		_imageInfo->frameWidth,
		_imageInfo->frameHeight,
		Unit::UnitPixel);
}
