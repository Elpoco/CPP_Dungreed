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
	IMAGEMANAGER->addFrameImage(ImageName::Player::idle, PATH_UNIT"Player/Idle.bmp", 390, 150, 5, 2, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Player::run, PATH_UNIT"Player/Run.bmp", 624, 150, 8, 2, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Player::die, PATH_UNIT"Player/Die.bmp", 78, 75, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Player::hand, PATH_UNIT"Player/Hand.bmp", 8, 8);

	// Enemy
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::dogIdle, PATH_UNIT"Enemy/SkelDogIdle.bmp", 300, 108, 5, 2, true, ColorSet::MAGENTA);

	// Map
	IMAGEMANAGER->addImage(ImageName::pixelTest, PATH_IMAGE"PixelTest.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage(ImageName::testTile, PATH_IMAGE"TestTile.bmp", 48, 48);

	// MapTool
	IMAGEMANAGER->addFrameImage(ImageName::mapTile, PATH_IMAGE"MapTool/MapTile.bmp", 1024 * TILE_SCALE, 512 * TILE_SCALE, 64, 32, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::mapToolTile, PATH_IMAGE"MapTool/MapTile.bmp", 1024 * MapToolSet::TOOL_TILE_SCALE, 512 * MapToolSet::TOOL_TILE_SCALE, 64, 32, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::mapPixel, PATH_IMAGE"MapTool/MapPixel.bmp", 48 * TILE_SCALE, 32 * TILE_SCALE, true, ColorSet::MAGENTA);
	//IMAGEMANAGER->addImage("MapTileGp", L"Resources/Images/MapTool/MapTile.png");

	// Loading
	IMAGEMANAGER->addImage(ImageName::logo, PATH_IMAGE"StartScene/Logo.bmp", 468, 225, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::cloud1, PATH_IMAGE"StartScene/Cloud1.bmp", 2564, WINSIZE_Y, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::cloud2, PATH_IMAGE"StartScene/Cloud2.bmp", 2304, WINSIZE_Y, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::background, PATH_IMAGE"StartScene/Background.bmp", WINSIZE_X, WINSIZE_Y, true, ColorSet::MAGENTA);

	// Town
	IMAGEMANAGER->addImage(ImageName::floor, PATH_IMAGE"Town/Floor.bmp", 2752, 448, true, ColorSet::MAGENTA);

	// Item
	GPIMAGEMANAGER->addImage(getMemDC(), ImageName::Item::Weapon::basicShotSword, 
		PATH_ITEM"Weapon/BasicShortSword_New.png", 3.0f, 3.0f);
}
