#include "stdafx.h"
#include "TestScene.h"

HRESULT TestScene::init()
{
	OBJECTMANAGER->addUnit(Code::Unit::PLAYER, CENTER_X, 500);
	TILEMANAGER->loadMap();


	return S_OK;
}

void TestScene::release()
{
}

void TestScene::update()
{
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		OBJECTMANAGER->addUnit(Code::Unit::SKEL_DOG, 100, 800);
	}
	if (KEYMANAGER->isStayKeyDown('B') && KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		OBJECTMANAGER->addUnit(Code::Unit::BELIAL, 1000, 550);
	}
	if (KEYMANAGER->isStayKeyDown('B') && KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		OBJECTMANAGER->addUnit(Code::Unit::NIFLEHEIM, 1000, 500);

	}
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		OBJECTMANAGER->addDropItem(
			Code::Item::BULLION,
			CAMERAMANAGER->calAbsX(_ptMouse.x),
			CAMERAMANAGER->calAbsY(_ptMouse.y)
		);
	}
}

void TestScene::render()
{
	IMAGEMANAGER->render(ImageName::Background::bgSky, getMemDC());

	TILEMANAGER->render(getMemDC());
}
