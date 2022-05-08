#include "stdafx.h"
#include "TestScene.h"

HRESULT TestScene::init()
{
	UIMANAGER->setCursorType(UIEnum::CURSOR_TYPE::TARGET);
	OBJECTMANAGER->addPlayer(CENTER_X, 500);
	TILEMANAGER->loadMap(FileName::testSave);
	SOUNDMANAGER->play(SoundName::TestScene, _sound);
	UIMANAGER->showMapInfo("Test Map");

	OBJECTMANAGER->addNPC(Code::NPC::DUNGEON_SHOP, 172, 386);
	OBJECTMANAGER->addNPC(Code::NPC::INN, 408, 383);
	OBJECTMANAGER->addNPC(Code::NPC::COMMANDER, 308, 383);

	OBJECTMANAGER->addTresure(85, 825, Code::TRESURE_TYPE::GOLD);
	OBJECTMANAGER->addTresure(170, 825, Code::TRESURE_TYPE::GOLD);
	OBJECTMANAGER->addTresure(250, 825, Code::TRESURE_TYPE::GOLD);
	OBJECTMANAGER->addTresure(330, 825);
	OBJECTMANAGER->addTresure(410, 825);
	OBJECTMANAGER->addTresure(490, 825);
	OBJECTMANAGER->addTresure(570, 820, Code::TRESURE_TYPE::BOSS);

	return S_OK;
}

void TestScene::release()
{
}

void TestScene::update()
{
	if (IsStayKeyDown('B') && IsOnceKeyDown(VK_F1))
	{
		OBJECTMANAGER->addEnemy(Code::UNIT::BELIAL, 1000, 550);
	}
	if (IsStayKeyDown('B') && IsOnceKeyDown(VK_F2))
	{
		OBJECTMANAGER->addEnemy(Code::UNIT::NIFLEHEIM, 1000, 500);
	}

	if (IsOnceKeyDown('M'))
	{
		OBJECTMANAGER->addEnemy(Code::UNIT::SCARECROW, 1000, 550);
	}
}

void TestScene::render()
{
	IMAGEMANAGER->render(ImageName::Background::bgSky, getMemDC());

	TILEMANAGER->render(getMemDC());
}
