#include "stdafx.h"
#include "TestScene.h"

#include "Player.h"
#include "SkelDog.h"
#include "LittleGhost.h"
#include "Belial.h"

HRESULT TestScene::init()
{
	OBJECTMANAGER->addObject(ObjectEnum::TYPE::PLAYER, new Player);
	OBJECTMANAGER->addObject(ObjectEnum::TYPE::ENEMY, new Belial(1000,550));
	//OBJECTMANAGER->addObject(ObjectEnum::TYPE::ENEMY, new SkelDog(100,700));
	//OBJECTMANAGER->addObject(ObjectEnum::TYPE::ENEMY, new SkelDog(1200,700));
	//OBJECTMANAGER->addObject(ObjectEnum::TYPE::ENEMY, new SkelDog(1400,700));
	//OBJECTMANAGER->addObject(ObjectEnum::TYPE::ENEMY, new SkelDog(1600,700));
	//OBJECTMANAGER->addObject(ObjectEnum::TYPE::ENEMY, new SkelDog(1800,700));
	//OBJECTMANAGER->addObject(ObjectEnum::TYPE::ENEMY, new LittleGhost(100, 200));
	//OBJECTMANAGER->addObject(ObjectEnum::TYPE::ENEMY, new LittleGhost(1200, 400));
	//OBJECTMANAGER->addObject(ObjectEnum::TYPE::ENEMY, new LittleGhost(1600, 300));

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
