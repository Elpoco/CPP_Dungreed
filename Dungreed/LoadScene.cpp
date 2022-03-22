#include "Stdafx.h"
#include "LoadScene.h"

HRESULT LoadScene::init(void)
{
	loadImage();


	return S_OK;
}

void LoadScene::release(void)
{
}

void LoadScene::update(void)
{
	if(KEYMANAGER->isOnceKeyDown(VK_RETURN))
		SCENEMANAGER->changeScene("test");

	if(KEYMANAGER->isOnceKeyDown('M'))
		SCENEMANAGER->changeScene("MapTool");
}

void LoadScene::render(void)
{
}

void LoadScene::loadImage(void)
{
	// Player
	IMAGEMANAGER->addFrameImage("PlayerIdle", PATH_UNIT"Player/Idle.bmp", 390, 150, 5, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("PlayerRun", PATH_UNIT"Player/Run.bmp", 624, 150, 8, 2, true, MAGENTA);

	// Map
	IMAGEMANAGER->addImage("PixelTest", PATH_IMAGE"PixelTest.bmp", WINSIZE_X, WINSIZE_Y);

}
