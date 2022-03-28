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

	_imageLoader = new ImageLoader;
	_imageLoader->init();

	// ===================================================
	SCENEMANAGER->addScene("Loading", new StartScene);
	SCENEMANAGER->addScene("MapTool", new MapToolScene);
	SCENEMANAGER->addScene("Test", new TestScene);

	// ===================================================

	SCENEMANAGER->changeScene("Loading");
	
	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();

	SAFE_DELETE(_imageLoader);
}

void MainGame::update(void)
{
	GameNode::update();
	SCENEMANAGER->update();
	CAMERAMANAGER->update();
	UIMANAGER->update();

	COLLISIONMANAGER->update();

	if (KEYMANAGER->isOnceKeyDown(VK_F1)) _isDebug = !_isDebug;
}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), Color::BLACK);

	SCENEMANAGER->render();

	COLLISIONMANAGER->render();

	UIMANAGER->render();
	TIMEMANAGER->render(getMemDC());

	if(_isDebug)
		TextOut(getMemDC(), 0, WINSIZE_Y-20, SCENEMANAGER->getCurrentSceneName().c_str(), SCENEMANAGER->getCurrentSceneName().length());

	this->getBackBuffer()->render(getHDC());
}
