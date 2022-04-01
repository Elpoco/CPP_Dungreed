#include "stdafx.h"
#include "TestScene.h"

#include "Player.h"

HRESULT TestScene::init()
{
	OBJECTMANAGER->addObject(new Player);

	TILEMANAGER->loadMap();

	return S_OK;
}

void TestScene::release()
{
}

void TestScene::update()
{
}

void TestScene::render()
{
	IMAGEMANAGER->render(ImageName::background, getMemDC());
	TILEMANAGER->render(getMemDC());
}
