#include "Stdafx.h"
#include "StartScene.h"

HRESULT StartScene::init(void)
{
	loadImage();

	_loop1 = _loop2 = 0.0f;

	_logo = RectMakeCenter(CENTER_X, CENTER_Y, 468, 255);

	return S_OK;
}

void StartScene::release(void)
{
}

void StartScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		SCENEMANAGER->changeScene("test");

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

void StartScene::loadImage(void)
{
	// Player
	IMAGEMANAGER->addFrameImage("PlayerIdle", PATH_UNIT"Player/Idle.bmp", 390, 150, 5, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("PlayerRun", PATH_UNIT"Player/Run.bmp", 624, 150, 8, 2, true, MAGENTA);
	IMAGEMANAGER->addImage("PlayerDie", PATH_UNIT"Player/Die.bmp", 78, 75, true, MAGENTA);

	// Map
	IMAGEMANAGER->addImage("PixelTest", PATH_IMAGE"PixelTest.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("TestTile", PATH_IMAGE"TestTile.bmp", 48, 48);
	
	// MapTool
	IMAGEMANAGER->addImage("MapTile", PATH_IMAGE"MapTool/MapTile.bmp", 1024 * TILE_SCALE, 512 * TILE_SCALE, true, MAGENTA);
	IMAGEMANAGER->addImage("MapTileGP", L"Resources/Images/MapTool/MapTile.png");
	IMAGEMANAGER->addImage("MapPixel", PATH_IMAGE"MapTool/MapPixel.bmp", 48 * TILE_SCALE, 32 * TILE_SCALE, true, MAGENTA);

	// Loading
	IMAGEMANAGER->addImage("Logo", PATH_IMAGE"StartScene/Logo.bmp", 468, 225, true, MAGENTA);
	IMAGEMANAGER->addImage("Cloud1", PATH_IMAGE"StartScene/Cloud1.bmp", 2564, WINSIZE_Y, true, MAGENTA);
	IMAGEMANAGER->addImage("Cloud2", PATH_IMAGE"StartScene/Cloud2.bmp", 2304, WINSIZE_Y, true, MAGENTA);
	IMAGEMANAGER->addImage("Background", PATH_IMAGE"StartScene/Background.bmp", WINSIZE_X, WINSIZE_Y, true, MAGENTA);

	// Town
	IMAGEMANAGER->addImage("Floor", PATH_IMAGE"Town/Floor.bmp", 2752, 448, true, MAGENTA);


}
