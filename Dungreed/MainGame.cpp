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
	SCENEMANAGER->addScene(SceneName::startScene, new StartScene);
	SCENEMANAGER->addScene(SceneName::mapToolScene, new MapToolScene);
	SCENEMANAGER->addScene(SceneName::testScene, new TestScene);

	// ===================================================

	SCENEMANAGER->changeScene(SceneName::startScene);

	//for (int i = 0; i < 2; i++)
	//{
	//	for (int j = 0; j < 2; j++)
	//	{
	//		cout << (i + j) * 2 + i * -4 << ", " << -2 + (i + j) * 2 << endl;
	//	}
	//}

	
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
	TIMEMANAGER->render(getMemDC());


	if(_isDebug)
		TextOut(getMemDC(), 0, WINSIZE_Y-20, SCENEMANAGER->getCurrentSceneName().c_str(), SCENEMANAGER->getCurrentSceneName().length());

	this->getBackBuffer()->render(getHDC());
}
