#include "stdafx.h"
#include "MainGame.h"

#include "ImageLoader.h"

#include "TestScene.h"
#include "StartScene.h"
#include "MapToolScene.h"
#include "TownScene.h"

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
	SCENEMANAGER->addScene(SceneName::townScene, new TownScene);
	// ===================================================

	SCENEMANAGER->changeScene(SceneName::startScene);

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

	COLLISIONMANAGER->render(getMemDC());

	OBJECTMANAGER->render(getMemDC());

	TIMEMANAGER->render(getMemDC());

	// 현재 씬 이름
	if (_isDebug)
	{
		TextOut(getMemDC(),
			0, WINSIZE_Y-20, 
			SCENEMANAGER->getCurrentSceneName().c_str(),
			SCENEMANAGER->getCurrentSceneName().length()
		);
		char str[128];
		wsprintf(str, "F1 디버그 모드");
		TextOut(getMemDC(), 0, WINSIZE_Y - 40, str, strlen(str));
	}
		
	this->getBackBuffer()->render(getHDC());
}
