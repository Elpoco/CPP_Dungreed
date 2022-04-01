#include "Stdafx.h"
#include "CameraManager.h"

#include "Object.h"

CameraManager::CameraManager() :
	_x(0.f),
	_y(0.f),
	_object(nullptr),
	_isFollow(false),
	_isLock(true)
{
}

CameraManager::~CameraManager()
{
}

HRESULT CameraManager::init()
{
	return S_OK;
}

void CameraManager::release()
{
}

void CameraManager::update()
{
	if (_object != nullptr && _isFollow)
	{
		float x = _object->getX();
		float y = _object->getY();

		if (_isLock)
		{
			if (x >= CENTER_X && MapToolSet::TILE_CNT_X * TILE_SIZE - CENTER_X > x) _x = x - CENTER_X;
			if (y >= CENTER_Y && MapToolSet::TILE_CNT_Y * TILE_SIZE - CENTER_Y > y) _y = y - CENTER_Y;
		}
		else
		{
			_x = x - CENTER_X;
			_y = y - CENTER_Y;
		}
	}
}

void CameraManager::printPoint(HDC hdc, float x, float y, int ptX, int ptY, char* format)
{
	MY_UTIL::printPoint(hdc, x - _x, y - _y, ptX, ptY, format);
}

void CameraManager::printRectangle(HDC hdc, float x, float y, float width, float height)
{
	RectangleMake(hdc, x - _x, y - _y, width, height);
}

void CameraManager::printRectangle(HDC hdc, RectF rc, Color penColor, bool isFill, Color fillColor)
{
	RectangleMake(hdc, { rc.GetLeft() - _x, rc.GetTop() - _y, rc.Width, rc.Height }, penColor, isFill, fillColor);
}

void CameraManager::printRectanglePoint(HDC hdc, PointF point, float width, float height, Color color)
{
	RectangleMakePoint(hdc, {point.X -_x, point.Y - _y}, width, height, color);
}

void CameraManager::printRectangleCenter(HDC hdc, float x, float y, float width, float height)
{
	RectangleMakeCenter(hdc, x - _x, y - _y, width, height);
}

int CameraManager::checkObjectInCamera(float x, float y, float width, float height)
{
	int posX = x - _x;
	int posY = y - _y;

	return posX < -width || posY < -height || width > WINSIZE_X || height > WINSIZE_Y;
}

void CameraManager::render(HDC hdc, Image* img, float x, float y)
{
	if (this->checkObjectInCamera(x, y, img->getWidth(), img->getHeight())) return;

	img->render(hdc, x - _x, y - _y);
}

void CameraManager::render(HDC hdc, ImageGp* img, float x, float y, int angle, PointF rotateCenter)
{
	if (this->checkObjectInCamera(x, y, img->getWidth(), img->getHeight())) return;

	if (rotateCenter.X != 0) rotateCenter.X -= _x;
	if (rotateCenter.Y != 0) rotateCenter.Y -= _y;

	img->render(hdc, x - _x, y - _y, angle, rotateCenter);
}

void CameraManager::frameRender(HDC hdc, Image* img, float x, float y, int frameX, int frameY)
{
	if (this->checkObjectInCamera(x, y, img->getFrameWidth(), img->getFrameHeight())) return;
	
	img->frameRender(hdc, x - _x, y - _y, frameX, frameY);
}

void CameraManager::followCamera(Object* object)
{
	_object = object;
	_isFollow = true;
}
