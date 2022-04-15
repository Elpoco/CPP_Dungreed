#include "stdafx.h"
#include "TestScene.h"

HRESULT TestScene::init()
{
	UIMANAGER->setCursorType(UIEnum::CURSOR_TYPE::TARGET);
	OBJECTMANAGER->addUnit(Code::UNIT::PLAYER, CENTER_X, 500);
	TILEMANAGER->loadMap();

	return S_OK;
}

void TestScene::release()
{
}

void TestScene::update()
{
	if (IsOnceKeyDown('Z'))
	{
		OBJECTMANAGER->addUnit(Code::UNIT::SKEL_DOG, 100, 800);
	}
	if (IsStayKeyDown('B') && IsOnceKeyDown(VK_F1))
	{
		OBJECTMANAGER->addUnit(Code::UNIT::BELIAL, 1000, 550);
	}
	if (IsStayKeyDown('B') && IsOnceKeyDown(VK_F2))
	{
		OBJECTMANAGER->addUnit(Code::UNIT::NIFLEHEIM, 1000, 500);

	}
	if (IsOnceKeyDown(VK_RBUTTON))
	{
		ITEMMANAGER->dropItem(
			(Code::ITEM)RND->getInt(3),
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
