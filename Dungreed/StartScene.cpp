#include "Stdafx.h"
#include "StartScene.h"

#include "UI.h"

using namespace StartSceneSet;

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

	for (int i = 0; i < BIRD_CNT; i++)
	{
		_bird[i] = new UI(ImageName::UI::bird, -50 - i * 70, 100 + i * 20);

		OBJECTMANAGER->addUI(_bird[i]);
	}

	OBJECTMANAGER->addUI(ImageName::UI::logo, CENTER_X, CENTER_Y - 150);
	OBJECTMANAGER->addButton(ImageName::UI::Button::gameStart, CENTER_X, CENTER_Y + 100, TRUE, clickStart);
	OBJECTMANAGER->addButton(ImageName::UI::Button::mapTool, CENTER_X, CENTER_Y + 170, TRUE, clickMapTool);
	OBJECTMANAGER->addButton(ImageName::UI::Button::quit, CENTER_X, CENTER_Y + 240, TRUE, clickQuit);
	
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

	for (int i = 0; i < BIRD_CNT; i++)
	{
		_bird[i]->setX(_bird[i]->getX() + 1);

		if (_bird[i]->getX() > WINSIZE_X + 50)
		{
			_bird[i]->setX(-150);
		}
	}

	if(IsOnceKeyDown(KEY::ESC)) exitGame();
	if (IsOnceKeyDown(KEY::SPACE)) UIMANAGER->showMapInfo("TETEST");
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
	if(_isDebug) SCENEMANAGER->changeScene(SceneName::testScene);
	else SCENEMANAGER->changeScene(SceneName::gameScene);
}

void clickMapTool()
{
	SCENEMANAGER->changeScene(SceneName::mapToolScene);
}

void clickQuit()
{
	exitGame();
}