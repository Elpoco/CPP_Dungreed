#include "stdafx.h"
#include "TestScene.h"

#include "Player.h"
#include "SkelDog.h"

HRESULT TestScene::init()
{
	OBJECTMANAGER->addObject(ObjectEnum::TYPE::PLAYER, new Player);
	OBJECTMANAGER->addObject(ObjectEnum::TYPE::ENEMY, new SkelDog);

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
