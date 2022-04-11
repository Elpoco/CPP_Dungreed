#include "stdafx.h"
#include "TestScene.h"

#include "Player.h"
#include "SkelDog.h"
#include "LittleGhost.h"
#include "Belial.h"
#include "Niflheim.h"

HRESULT TestScene::init()
{
	OBJECTMANAGER->addObject(ObjectEnum::TYPE::PLAYER, new Player(CENTER_X, 500));
	OBJECTMANAGER->addObject(ObjectEnum::TYPE::ENEMY, new Belial(1000,550));
	OBJECTMANAGER->addObject(ObjectEnum::TYPE::ENEMY, new Niflheim(1000,800));
	OBJECTMANAGER->addObject(ObjectEnum::TYPE::ENEMY, new SkelDog(100,800));
	OBJECTMANAGER->addObject(ObjectEnum::TYPE::ENEMY, new LittleGhost(100, 200));

	TILEMANAGER->loadMap();

	return S_OK;
}

void TestScene::release()
{
}

void TestScene::update()
{
	OBJECTMANAGER->update();

	COLLISIONMANAGER->update();

	CAMERAMANAGER->update();
}

void TestScene::render()
{
	IMAGEMANAGER->render(ImageName::background, getMemDC());

	TILEMANAGER->render(getMemDC());

	OBJECTMANAGER->render(getMemDC());

	COLLISIONMANAGER->render(getMemDC());
}
