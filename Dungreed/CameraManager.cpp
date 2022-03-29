#include "Stdafx.h"
#include "CameraManager.h"

#include "Object.h"

CameraManager::CameraManager() :
	_x(0.f),
	_y(0.f),
	_object(nullptr),
	_isFollow(false)
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
		_x = _object->getX() - CENTER_X;
		_y = _object->getY() - CENTER_Y;
	}
}

void CameraManager::render(HDC hdc)
{
}

void CameraManager::printPoint(HDC hdc, float x, float y, int ptX, int ptY, char* format)
{
	MY_UTIL::printPoint(hdc, x - _x, y - _y, ptX, ptY, format);
}

void CameraManager::printRectangle(HDC hdc, float x, float y, float width, float height)
{
	RectangleMake(hdc, x - _x, y - _y, width, height);
}

int CameraManager::checkObjectInCamera(Image * img, float x, float y)
{
	int posX = x - _x;
	int posY = y - _y;
	int frameWidth = img->getFrameWidth();
	int frameHeight = img->getFrameHeight();

	return posX < -frameWidth || posY < -frameHeight || frameWidth > WINSIZE_X || frameHeight > WINSIZE_Y;
}

void CameraManager::render(HDC hdc, Image * img, float x, float y)
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
