#include "Stdafx.h"
#include "StartScene.h"

#include "UI.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

HRESULT StartScene::init()
{
	_loop1 = _loop2 = 0.0f;

	_logo = RectMakeCenter(CENTER_X, CENTER_Y, 468, 255);

	OBJECTMANAGER->addObject(ObjectEnum::TYPE::FIXED_UI, new UI(ImageName::logo, CENTER_X, CENTER_Y, true));

	return S_OK;
}

void StartScene::release()
{
}

void StartScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		SCENEMANAGER->changeScene(SceneName::testScene);

	if (KEYMANAGER->isOnceKeyDown('M'))
		SCENEMANAGER->changeScene(SceneName::mapToolScene);

	if (KEYMANAGER->isOnceKeyDown('T'))
		SCENEMANAGER->changeScene(SceneName::townScene);

	_loop1 += 0.1f;
	_loop2 += 0.7f;
}

void StartScene::render()
{
	RECT rc = { 0, 0, WINSIZE_X, WINSIZE_Y };
	IMAGEMANAGER->render("Background", getMemDC());
	IMAGEMANAGER->loopRender("Cloud1", getMemDC(), &rc, _loop1, 0);
	IMAGEMANAGER->loopRender("Cloud2", getMemDC(), &rc, _loop2, 0);

	IMAGEMANAGER->render("Logo", getMemDC(), _logo.left, _logo.top - 100);
}
