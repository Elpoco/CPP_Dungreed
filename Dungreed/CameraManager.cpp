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

void CameraManager::printRectangle(HDC hdc, RectF rc, bool isFill, Color color, Color fillColor)
{
	RectangleMake(hdc, { rc.GetLeft() - _x, rc.GetTop() - _y, rc.Width, rc.Height }, isFill, color, fillColor);
}

void CameraManager::printRectanglePoint(HDC hdc, PointF point, float width, float height, Color color)
{
	RectangleMakePoint(hdc, {point.X -_x, point.Y - _y}, width, height, color);
}

void CameraManager::printRectangleCenter(HDC hdc, float x, float y, float width, float height)
{
	RectangleMakeCenter(hdc, x - _x, y - _y, width, height);
}

int CameraManager::checkObjectInCamera(Image * img, float x, float y)
{
	int posX = x - _x;
	int posY = y - _y;
	int frameWidth = img->getFrameWidth();
	int frameHeight = img->getFrameHeight();

	return posX < -frameWidth || posY < -frameHeight || frameWidth > WINSIZE_X || frameHeight > WINSIZE_Y;
}

void CameraManager::render(HDC hdc, Image* img, float x, float y)
{
	if (this->checkObjectInCamera(img, x, y)) return;

	img->render(hdc, x - _x, y - _y);
}

void CameraManager::frameRender(HDC hdc, Image* img, float x, float y, int frameX, int frameY)
{
	if (this->checkObjectInCamera(img, x, y)) return;
	
	img->frameRender(hdc, x - _x, y - _y, frameX, frameY);
}

void CameraManager::followCamera(Object* object)
{
	_object = object;
	_isFollow = true;
}
