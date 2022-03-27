#include "Stdafx.h"
#include "StartScene.h"

#include "UI.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

HRESULT StartScene::init(void)
{
	_loop1 = _loop2 = 0.0f;

	_logo = RectMakeCenter(CENTER_X, CENTER_Y, 468, 255);

	UI* ui = new UI;
	ui->init("Logo", RectMakeCenter(CENTER_X, CENTER_Y, 468, 255));
	//UIMANAGER->addUI(ui);

	return S_OK;
}

void StartScene::release(void)
{
}

void StartScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		SCENEMANAGER->changeScene("Test");

	if (KEYMANAGER->isOnceKeyDown('M'))
		SCENEMANAGER->changeScene("MapTool");

	_loop1 += 0.1f;
	_loop2 += 0.7f;
}

void StartScene::render(void)
{
	RECT rc = { 0, 0, WINSIZE_X, WINSIZE_Y };
	IMAGEMANAGER->render("Background", getMemDC());
	IMAGEMANAGER->loopRender("Cloud1", getMemDC(), &rc, _loop1, 0);
	IMAGEMANAGER->loopRender("Cloud2", getMemDC(), &rc, _loop2, 0);


	IMAGEMANAGER->render("Logo", getMemDC(), _logo.left, _logo.top - 100);
}
