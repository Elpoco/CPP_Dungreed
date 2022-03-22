#include "stdafx.h"
#include "TestScene.h"

#include "Player.h"

HRESULT TestScene::init(void)
{
	_player = new Player;
	_player->init();

	return S_OK;
}

void TestScene::release(void)
{
}

void TestScene::update(void)
{
	_player->update();
}

void TestScene::render(void)
{
	IMAGEMANAGER->render("PixelTest", getMemDC());
	_player->render(getMemDC());
}
