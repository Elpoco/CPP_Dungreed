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

void ImageGp::release()
{
	SAFE_DELETE(_imageInfo);
	SAFE_DELETE(_graphics);
	SAFE_DELETE(_img);
}

void ImageGp::render(HDC hdc, float destX, float destY, int angle, POINT rotateCenter)
{
	Graphics graphics(hdc);
	// rotate
	if (rotateCenter.x == 0) rotateCenter.x = destX;
	if (rotateCenter.y == 0) rotateCenter.y = destY;
	Matrix matrix;
	//matrix.SetElements(cosf(PI / 2), -sinf(PI / 2), cosf(PI / 2), sinf(PI / 2), destX, destY);
	matrix.Scale(_imageInfo->scaleW, _imageInfo->scaleH);
	_graphics->SetTransform(&matrix);
	//matrix.RotateAt(-angle, rotateCenter);
	//_graphics->SetTransform(&matrix);
	// rotate
	//_graphics->TranslateTransform(_imageInfo->width, _imageInfo->height);
	//_graphics->ScaleTransform(_imageInfo->scaleW, _imageInfo->scaleH);
	//_graphics->ScaleTransform(_imageInfo->scaleW, _imageInfo->scaleH);
	//_graphics->RotateTransform(30);
	//_graphics->DrawImage(_img, (int)destX, (int)destY, _imageInfo->width, _imageInfo->height);
	_graphics->DrawImage(_img, (int)destX, (int)destY);
}
