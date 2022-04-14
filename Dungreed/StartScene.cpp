#include "Stdafx.h"
#include "StartScene.h"

#include "Cursor.h"

void clickStart();
void clickMapTool();
void clickQuit();

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

HRESULT StartScene::init()
{
	_loop1 = _loop2 = 0.0f;

	OBJECTMANAGER->addUI(ImageName::UI::logo, CENTER_X, CENTER_Y - 150, TRUE);
	OBJECTMANAGER->addButton(ImageName::UI::Button::gameStart, CENTER_X, CENTER_Y + 100, TRUE, clickStart);
	OBJECTMANAGER->addButton(ImageName::UI::Button::mapTool, CENTER_X, CENTER_Y + 170, TRUE, clickMapTool);
	OBJECTMANAGER->addButton(ImageName::UI::Button::quit, CENTER_X, CENTER_Y + 240, TRUE, clickQuit);

	OBJECTMANAGER->addObject(ObjectEnum::TYPE::UI_FRONT, new Cursor());
	ShowCursor(false);

	SOUNDMANAGER->play(SoundName::title, _sound);

	return S_OK;
}

void StartScene::release()
{
	SOUNDMANAGER->stop(SoundName::title);
}

void StartScene::update()
{
	_loop1 += 0.1f;
	_loop2 += 0.7f;
}

void StartScene::render()
{
	RECT rc = { 0, 0, WINSIZE_X, WINSIZE_Y };
	IMAGEMANAGER->render(ImageName::Background::bgSky, getMemDC());
	IMAGEMANAGER->loopRender(ImageName::Background::startCloud1, getMemDC(), &rc, _loop1, 0);
	IMAGEMANAGER->loopRender(ImageName::Background::startCloud2, getMemDC(), &rc, _loop2, 0);
}

void clickStart()
{
	SCENEMANAGER->changeScene(SceneName::testScene);
}

void clickMapTool()
{
	SCENEMANAGER->changeScene(SceneName::mapToolScene);
}

void clickQuit()
{
	PostMessage(_hWnd, WM_DESTROY, 0, 0);
}