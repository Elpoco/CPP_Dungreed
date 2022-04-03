#include "stdafx.h"
#include "MainGame.h"

#include "ImageLoader.h"

#include "TestScene.h"
#include "StartScene.h"
#include "MapToolScene.h"

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}

HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);

	// ===================================================
	SCENEMANAGER->addScene(SceneName::testScene, new TestScene);
	SCENEMANAGER->addScene(SceneName::startScene, new StartScene);
	SCENEMANAGER->addScene(SceneName::mapToolScene, new MapToolScene);
	// ===================================================

	SCENEMANAGER->changeScene(SceneName::startScene);

	COLLISIONMANAGER->onTileCollision();

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
}

void MainGame::update(void)
{
	GameNode::update();
	SCENEMANAGER->update();

	OBJECTMANAGER->update();

	COLLISIONMANAGER->update();

	CAMERAMANAGER->update();

	if (KEYMANAGER->isOnceKeyDown(VK_F1)) _isDebug = !_isDebug;
}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), ColorSet::BLACK);

	SCENEMANAGER->render();

	OBJECTMANAGER->render(getMemDC());

	COLLISIONMANAGER->render(getMemDC());

	TIMEMANAGER->render(getMemDC());

	// ÇöÀç ¾À ÀÌ¸§
	if(_isDebug)
		TextOut(getMemDC(), 0, WINSIZE_Y-20, 
			SCENEMANAGER->getCurrentSceneName().c_str(), SCENEMANAGER->getCurrentSceneName().length());

	this->getBackBuffer()->render(getHDC());

}
