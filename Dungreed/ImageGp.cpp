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

HRESULT ImageGp::init(HDC hdc, const WCHAR* fileName, float scaleW, float scaleH)
{
	if (_imageInfo != NULL) this->release();

	_img = new Bitmap(fileName);

	if (_img->GetLastStatus() != Ok) return E_FAIL;

	_graphics = new Graphics(hdc);

	_imageInfo = new GP_IMAGE_INFO;
	_imageInfo->width = _img->GetWidth();
	_imageInfo->height = _img->GetHeight();
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;
	_imageInfo->frameWidth = _imageInfo->width;
	_imageInfo->frameHeight = _imageInfo->height;

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
	_imageInfo->maxFrameX = maxFrameX - 1;
	_imageInfo->maxFrameY = maxFrameY - 1;
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

void ImageGp::render(HDC hdc, float x, float y)
{
	_graphics->DrawImage(_img, x, y);
}

void ImageGp::render(HDC hdc, float x, float y, int angle, POINT rotateCenter)
{
	if (rotateCenter.x == 0) rotateCenter.x = x + _imageInfo->width * 0.5f;
	if (rotateCenter.y == 0) rotateCenter.y = y + _imageInfo->height * 0.5f;

	Matrix matrix;
	matrix.RotateAt(-angle, PointToPointF(rotateCenter));
	_graphics->SetTransform(&matrix);

	_graphics->DrawImage(_img, x, y);

	Matrix release;
	_graphics->SetTransform(&release);
}

void ImageGp::frameRender(HDC hdc, float x, float y, int frameX, int frameY)
{
	_graphics->DrawImage(
		_img,
		(int)x, (int)y,
		frameX * _imageInfo->frameWidth,
		frameY * _imageInfo->frameHeight,
		_imageInfo->frameWidth,
		_imageInfo->frameHeight,
		Unit::UnitPixel
	);
}

void ImageGp::frameRender(HDC hdc, float x, float y, int frameX, int frameY, int angle, POINT rotateCenter)
{
	if (rotateCenter.x == 0) rotateCenter.x = x;
	if (rotateCenter.y == 0) rotateCenter.y = y;

	Matrix matrix;
	matrix.RotateAt(-angle, PointToPointF(rotateCenter));
	_graphics->SetTransform(&matrix);

	_graphics->DrawImage(
		_img,
		(int)x, (int)y,
		frameX * _imageInfo->frameWidth, 
		frameY * _imageInfo->frameHeight, 
		_imageInfo->frameWidth,
		_imageInfo->frameHeight,
		Unit::UnitPixel
	);

	Matrix release;
	_graphics->SetTransform(&release);
}
