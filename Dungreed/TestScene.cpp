#include "stdafx.h"
#include "TestScene.h"

HRESULT TestScene::init()
{
	UIMANAGER->setCursorType(UIEnum::CURSOR_TYPE::TARGET);
	OBJECTMANAGER->addPlayer(CENTER_X, 500);
	TILEMANAGER->loadMap(FileName::testSave);
	SOUNDMANAGER->play(SoundName::TestScene, _sound);

	OBJECTMANAGER->addNPC(Code::NPC::DUNGEON_SHOP, 172, 383);
	OBJECTMANAGER->addTresure(220, 365, Code::TRESURE_TYPE::GOLD);
	OBJECTMANAGER->addTresure(300, 365);
	OBJECTMANAGER->addTresure(380, 365);
	OBJECTMANAGER->addTresure(460, 365);

	return S_OK;
}

void TestScene::release()
{
}

void TestScene::update()
{
	if (IsOnceKeyDown('Z'))
	{
		OBJECTMANAGER->addEnemy(Code::UNIT::SKEL_DOG, 500, 800);
	}
	if (IsStayKeyDown('B') && IsOnceKeyDown(VK_F1))
	{
		OBJECTMANAGER->addEnemy(Code::UNIT::BELIAL, 1000, 550);
	}
	if (IsStayKeyDown('B') && IsOnceKeyDown(VK_F2))
	{
		OBJECTMANAGER->addEnemy(Code::UNIT::NIFLEHEIM, 1000, 500);
	}
}

void TestScene::render()
{
	IMAGEMANAGER->render(ImageName::Background::bgSky, getMemDC());

	TILEMANAGER->render(getMemDC());
}
