#include "Stdafx.h"
#include "ImageLoader.h"

ImageLoader::ImageLoader()
{
}

ImageLoader::~ImageLoader()
{
}

HRESULT ImageLoader::init()
{
	this->loadImages();

	return S_OK;
}

void ImageLoader::release()
{
}

void ImageLoader::update()
{
}

void ImageLoader::render()
{
}

void ImageLoader::loadImages()
{
	// Player
	IMAGEMANAGER->addFrameImage(ImageName::playerIdle, PATH_UNIT"Player/Idle.bmp", 390, 150, 5, 2, true, Color::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::playerRun, PATH_UNIT"Player/Run.bmp", 624, 150, 8, 2, true, Color::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::playerDie, PATH_UNIT"Player/Die.bmp", 78, 75, true, Color::MAGENTA);

	// Map
	IMAGEMANAGER->addImage(ImageName::pixelTest, PATH_IMAGE"PixelTest.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage(ImageName::testTile, PATH_IMAGE"TestTile.bmp", 48, 48);

	// MapTool
	IMAGEMANAGER->addFrameImage(ImageName::mapTile, PATH_IMAGE"MapTool/MapTile.bmp", 1024 * TILE_SCALE, 512 * TILE_SCALE, 64, 32, true, Color::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::mapToolTile, PATH_IMAGE"MapTool/MapTile.bmp", 1024 * MapTool::TOOL_TILE_SCALE, 512 * MapTool::TOOL_TILE_SCALE, 64, 32, true, Color::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::mapPixel, PATH_IMAGE"MapTool/MapPixel.bmp", 48 * TILE_SCALE, 32 * TILE_SCALE, true, Color::MAGENTA);
	//IMAGEMANAGER->addImage("MapTileGp", L"Resources/Images/MapTool/MapTile.png");

	// Loading
	IMAGEMANAGER->addImage(ImageName::logo, PATH_IMAGE"StartScene/Logo.bmp", 468, 225, true, Color::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::cloud1, PATH_IMAGE"StartScene/Cloud1.bmp", 2564, WINSIZE_Y, true, Color::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::cloud2, PATH_IMAGE"StartScene/Cloud2.bmp", 2304, WINSIZE_Y, true, Color::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::background, PATH_IMAGE"StartScene/Background.bmp", WINSIZE_X, WINSIZE_Y, true, Color::MAGENTA);

	// Town
	IMAGEMANAGER->addImage(ImageName::floor, PATH_IMAGE"Town/Floor.bmp", 2752, 448, true, Color::MAGENTA);
}
