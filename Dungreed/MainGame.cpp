#include "stdafx.h"
#include "MainGame.h"

#include "ImageLoader.h"

#include "TestScene.h"
#include "StartScene.h"
#include "MapToolScene.h"
#include "GameScene.h"

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
	SCENEMANAGER->addScene(SceneName::gameScene, new GameScene);
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

	SOUNDMANAGER->update();

	TILEMANAGER->update();

	OBJECTMANAGER->update();

	UIMANAGER->update();
	COLLISIONMANAGER->update();

	CAMERAMANAGER->update();

	if (IsOnceKeyDown(KEY::F1)) _isDebug = !_isDebug;

	if (IsOnceKeyDown(VK_MBUTTON))
	{
		cout << __FUNCTION__ << "_ABS_" << _ptMouse.x << ", " << _ptMouse.y << endl;
		cout << __FUNCTION__ << "_REL_" << CAMERAMANAGER->calAbsX(_ptMouse.x) << ", " << CAMERAMANAGER->calAbsY(_ptMouse.y) << endl;
	}
}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);

	SetTextColor(getMemDC(), ColorSet::BLACK);


	if (SCENEMANAGER->getChangeScene())
	{
		IMAGEMANAGER->render(ImageName::ChangeScene, getMemDC());
		RECT rc = RectMakeCenter(CENTER_X, CENTER_Y, 200, 50);
		Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
		char str[128];
		wsprintf(str, "던전에 빨려 들어가는중...");
		TextOut(getMemDC(), rc.left + 10, rc.top + 17, str, strlen(str));
	}
	else
	{
		SCENEMANAGER->render();

		OBJECTMANAGER->render(getMemDC());

		COLLISIONMANAGER->render(getMemDC());
	}

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
