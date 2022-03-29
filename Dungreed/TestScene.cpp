#include "stdafx.h"
#include "TestScene.h"

#include "Player.h"

HRESULT TestScene::init()
{
	_player = new Player;
	_player->init();

	TILEMANAGER->loadMap();

	return S_OK;
}

void TestScene::release()
{
}

void TestScene::update()
{
	_player->update();
}

void TestScene::render()
{
	TILEMANAGER->render(getMemDC());
	_player->render(getMemDC());
}
