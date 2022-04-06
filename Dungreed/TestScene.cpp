#include "stdafx.h"
#include "TestScene.h"

#include "Player.h"
#include "SkelDog.h"
#include "LittleGhost.h"

HRESULT TestScene::init()
{
	OBJECTMANAGER->addObject(ObjectEnum::TYPE::PLAYER, new Player);
	//OBJECTMANAGER->addObject(ObjectEnum::TYPE::ENEMY, new SkelDog(100,200));
	//OBJECTMANAGER->addObject(ObjectEnum::TYPE::ENEMY, new LittleGhost(100, 200));

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
