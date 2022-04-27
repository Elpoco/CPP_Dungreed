#include "Stdafx.h"
#include "CameraManager.h"

#include "Object.h"

CameraManager::CameraManager()
	: _x(0.f)
	, _y(0.f)
	, _object(nullptr)
	, _isFollow(false)
	, _isLock(true)
	, _mapWidth(WINSIZE_X)
	, _mapHeight(WINSIZE_Y)
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

		_x = x - CENTER_X;
		_y = y - CENTER_Y;

		if (_isLock)
		{
			if (_x < 0) _x = 0;
			if (_y < 0) _y = 0;
			if (_x > _mapWidth - WINSIZE_X) _x = _mapWidth - WINSIZE_X;
			if (_y > _mapHeight - WINSIZE_Y) _y = _mapHeight - WINSIZE_Y;
		}
	}
}

void CameraManager::printPoint(HDC hdc, float x, float y, int ptX, int ptY, char* format)
{
	PrintPoint(hdc, x - _x, y - _y, ptX, ptY, format);
}

void CameraManager::printRectangle(HDC hdc, float x, float y, int width, int height)
{
	PrintRectangle(hdc, x - _x, y - _y, width, height);
}

void CameraManager::printRectangle(HDC hdc, RECT rc, Color penColor, bool isFill, Color fillColor)
{
	PrintRectangleColor(hdc, calRelRc(rc), penColor, isFill, fillColor);
}

void CameraManager::printRectanglePoint(HDC hdc, POINT point, int width, int height, Color color)
{
	PrintRectangleByPoint(hdc, PointMake(point.x -_x, point.y - _y), width, height, color);
}

void CameraManager::printRectangleCenter(HDC hdc, float x, float y, int width, int height)
{
	PrintRectangle(hdc, x, y, width, height);
}

int CameraManager::checkObjectInCamera(float x, float y, int width, int height)
{
	int posX = x - _x;
	int posY = y - _y;

	return posX < -width || posY < -height || width > WINSIZE_X || height > WINSIZE_Y;
}

void CameraManager::render(HDC hdc, ImageBase* img, float x, float y)
{
	if (this->checkObjectInCamera(x, y, img->getWidth(), img->getHeight())) return;

	img->render(hdc, x - _x, y - _y);
}

void CameraManager::render(HDC hdc, ImageBase* img, float x, float y, BYTE alpha)
{
	if (this->checkObjectInCamera(x, y, img->getWidth(), img->getHeight())) return;

	img->alphaRender(hdc, x - _x, y - _y, alpha);
}

void CameraManager::render(HDC hdc, ImageBase* img, float x, float y, int angle, POINT rotateCenter)
{
	if (this->checkObjectInCamera(x, y, img->getWidth(), img->getHeight())) return;

	if (rotateCenter.x != 0) rotateCenter.x -= _x;
	if (rotateCenter.y != 0) rotateCenter.y -= _y;

	img->render(hdc, x - _x, y - _y, angle, rotateCenter);
}

void CameraManager::render(HDC hdc, ImageBase * img, float x, float y, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (this->checkObjectInCamera(x, y, img->getWidth(), img->getHeight())) return;

	img->render(hdc, x - _x, y - _y, sourX, sourY, sourWidth, sourHeight);
}

void CameraManager::frameRender(HDC hdc, ImageBase* img, float x, float y, int frameX, int frameY)
{
	if (this->checkObjectInCamera(x, y, img->getFrameWidth(), img->getFrameHeight())) return;

	img->frameRender(hdc, x - _x, y - _y, frameX, frameY);
}

void CameraManager::frameRender(HDC hdc, ImageBase* img, float x, float y, int frameX, int frameY, BYTE alpha)
{
	if (this->checkObjectInCamera(x, y, img->getFrameWidth(), img->getFrameHeight())) return;

	img->frameAlphaRender(hdc, x - _x, y - _y, frameX, frameY, alpha);
}

void CameraManager::frameRender(HDC hdc, ImageBase* img, float x, float y, int frameX, int frameY, float angle)
{
	img->rotateRender(hdc, x - _x, y - _y, frameX, frameY, angle);
}

void CameraManager::frameRender(HDC hdc, ImageBase* img, float x, float y, int frameX, int frameY, int angle, POINT rotateCenter)
{
	if (this->checkObjectInCamera(x, y, img->getFrameWidth(), img->getFrameHeight())) return;

	if (rotateCenter.x != 0) rotateCenter.x -= _x;
	if (rotateCenter.y != 0) rotateCenter.y -= _y;

	img->frameRender(hdc, x - _x, y - _y, frameX, frameY, angle, rotateCenter);
}

void CameraManager::followCamera(Object* object)
{
	_object = object;
	_isFollow = true;
}

void CameraManager::cameraInitPos()
{
	_x = 0;
	_y = 0;
}

void CameraManager::updateMapSize()
{
	_mapWidth = TILEMANAGER->getCurrentMapTileWidth() + TILE_SIZE;
	_mapHeight = TILEMANAGER->getCurrentMapTileHeight() + TILE_SIZE;
}

POINT CameraManager::calRelPt(POINT pt)
{
	return PointMake(pt.x - _x, pt.y - _y);
}

POINT CameraManager::calAbsPt(POINT pt)
{
	return PointMake(pt.x + _x, pt.y + _y);
}
