#include "stdafx.h"
#include "MainGame.h"

#include "LoadScene.h"
#include "MapToolScene.h"

#include "TestScene.h"

HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);

	// ===================================================
	SCENEMANAGER->addScene("Loading", new LoadScene);
	SCENEMANAGER->addScene("MapTool", new MapToolScene);
	SCENEMANAGER->addScene("test", new TestScene);

	// ===================================================

	SCENEMANAGER->changeScene("Loading");
	
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

	TextOut(getMemDC(), 0, 0, SCENEMANAGER->getCurrentSceneName().c_str(), SCENEMANAGER->getCurrentSceneName().length());

	//TIMEMANAGER->render(getMemDC());

	this->getBackBuffer()->render(getHDC());
}
