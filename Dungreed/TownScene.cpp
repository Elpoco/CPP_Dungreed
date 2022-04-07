#include "Stdafx.h"
#include "TownScene.h"

#include "Object.h"

TownScene::TownScene()
{
}

TownScene::~TownScene()
{
}

HRESULT TownScene::init()
{
	TILEMANAGER->loadMap("Town");

	_layer = IMAGEMANAGER->findImage(ImageName::Town::townLayerDay);
	_background = IMAGEMANAGER->findImage(ImageName::Town::townBgDay);

	_camera = new Object;

	CAMERAMANAGER->followCamera(_camera);

	return S_OK;
}

void TownScene::release()
{
}

void TownScene::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_camera->setX(_camera->getX() + 5);
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_camera->setX(_camera->getX() - 5);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_camera->setY(_camera->getY() - 5);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_camera->setY(_camera->getY() + 5);
	}
}

void TownScene::render()
{
	IMAGEMANAGER->render(ImageName::Town::cloud, getMemDC());
	RECT rc = { 0,WINSIZE_Y - _background->getHeight(),WINSIZE_X, WINSIZE_Y };
	_background->loopRender(getMemDC(), &rc, CAMERAMANAGER->getAbsX() / 3, 0);
	rc = { 0, WINSIZE_Y - _layer->getHeight() , WINSIZE_X, WINSIZE_Y };
	_layer->loopRender(getMemDC(), &rc, CAMERAMANAGER->getAbsX(), 0);

	TILEMANAGER->render(getMemDC());
}
