#include "Stdafx.h"
#include "CameraManager.h"

#include "Camera.h"
#include "UI.h"
#include "Object.h"

CameraManager::CameraManager()
{
}

CameraManager::~CameraManager()
{
}

HRESULT CameraManager::init()
{
	_camera = new Camera;

	return S_OK;
}

void CameraManager::release()
{
}

void CameraManager::update()
{
}

void CameraManager::render()
{
}

void CameraManager::renderObject()
{
	viObjects iter = _vObjects.begin();
	for (; iter != _vObjects.end(); ++iter)
	{
		_camera->render();
	}
}

void CameraManager::addRender(Object* object, bool isFront)
{
	if (isFront)
	{
		_vFrontObject.push_back(object);
	}
	else
	{
		_vObjects.push_back(object);
	}
}

float CameraManager::getRelX(float x)
{
	return x - _camera->getX();
}

float CameraManager::getRelY(float y)
{
	return y - _camera->getY();
}

float CameraManager::getAbsX()
{
	return _camera->getX();
}

float CameraManager::getAbsY()
{
	return _camera->getY();
}

void CameraManager::moveX(float x)
{
	_camera->moveX(x);
}

void CameraManager::moveY(float y)
{
	_camera->moveY(y);
}

void CameraManager::setCameraPos(float x, float y)
{
	_camera->setCameraPos(x, y);
}
