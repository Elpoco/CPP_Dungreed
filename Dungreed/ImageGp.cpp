#include "Stdafx.h"
#include "ImageGp.h"

using namespace Gdiplus;

ImageGp::ImageGp()
{
}

ImageGp::~ImageGp()
{
}

HRESULT ImageGp::init(const WCHAR* fileName, float scaleW, float scaleH)
{
	if (_imageInfo != NULL) this->release();

	_img = new Bitmap(fileName);
	if (_img->GetLastStatus() != Ok) return E_FAIL;

	HDC hdc = GetDC(_hWnd);
	_imageInfo = new GP_IMAGE_INFO;
	_imageInfo->width = _img->GetWidth() * scaleW;
	_imageInfo->height = _img->GetHeight() * scaleH;

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void ImageGp::release()
{
	SAFE_DELETE(_imageInfo);
	SAFE_DELETE(_graphics);
	SAFE_DELETE(_img);
}

void ImageGp::render(HDC hdc, float destX, float destY, int angle, PointF rotateCenter)
{
	Graphics graphics(hdc);

	// rotate
	if (rotateCenter.X == 0) rotateCenter.X = destX;
	if (rotateCenter.Y == 0) rotateCenter.Y = destY;
	Matrix matrix;
	matrix.RotateAt(-angle, rotateCenter);
	graphics.SetTransform(&matrix);
	// rotate
	
	graphics.DrawImage(_img, (int)destX, (int)destY, _imageInfo->width, _imageInfo->height);
}
