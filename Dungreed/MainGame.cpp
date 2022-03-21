#include "stdafx.h"
#include "MainGame.h"

#include "TestScene.h"

HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);
	SCENEMANAGER->addScene("test", new TestScene);

	// ===================================================

	SCENEMANAGER->changeScene("test");
	
	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();

	SCENEMANAGER->release();
}

void MainGame::update(void)
{
	GameNode::update();
	SCENEMANAGER->update();
}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);

	SCENEMANAGER->render();

	TIMEMANAGER->render(getMemDC());

	this->getBackBuffer()->render(getHDC());
}
