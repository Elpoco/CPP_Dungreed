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
	// ==========
	// # Player #
	// ==========
	IMAGEMANAGER->addFrameImage(ImageName::Player::idle, PATH_UNIT"Player/PlayerIdle.bmp", 0, 0, 5, 2, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Player::run, PATH_UNIT"Player/PlayerRun.bmp", 0, 0, 8, 2, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Player::jump, PATH_UNIT"Player/PlayerJump.bmp", 0, 0, 1, 2, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Player::die, PATH_UNIT"Player/PlayerDie.bmp", 0, 0, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Player::hand, PATH_UNIT"Player/Hand.bmp");

	// =========
	// # Enemy #
	// =========
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::enemySpawn, PATH_UNIT"Enemy/EnemySpawn.bmp", 0, 0, 15, 1, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::enemyDie, PATH_UNIT"Enemy/EnemyDie.bmp", 0, 0, 11, 1, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::enemyDieSmall, PATH_UNIT"Enemy/EnemyDie_small.bmp", 0, 0, 11, 1, true, ColorSet::MAGENTA);
	// »À ¸Û¸ÛÀÌ
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::dogIdle, PATH_UNIT"Enemy/SkelDog/SkelDogIdle.bmp", 0, 0, 5, 2, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::dogRun, PATH_UNIT"Enemy/SkelDog/SkelDogRun.bmp", 0, 0, 7, 2, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::dogDie, PATH_UNIT"Enemy/SkelDog/SkelDogDie.bmp", 0, 0, 1, 2, true, ColorSet::MAGENTA);
	// ÀÛÀº À¯·É
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::littleGhostIdle, PATH_UNIT"Enemy/LittleGhost/LittleGhost.bmp", 0, 0, 6, 2, true, ColorSet::MAGENTA);
	// º§¸®¾Ë
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Belial::idle, PATH_UNIT"Enemy/Belial/SkellBossIdle.bmp", 0, 0, 10, 1, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Belial::back, PATH_UNIT"Enemy/Belial/SkellBossBack.bmp", 0, 0, 10, 1, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Belial::attack, PATH_UNIT"Enemy/Belial/SkellBossAttack.bmp", 0, 0, 10, 1, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Belial::particle, PATH_UNIT"Enemy/Belial/SkellBossParticle.bmp", 0, 0, 8, 1, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Belial::bullet, PATH_UNIT"Enemy/Belial/BossBullet.bmp", 0, 0, 2, 1, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Belial::bulletEffect, PATH_UNIT"Enemy/Belial/BossBulletEffect.bmp", 0, 0, 8, 1, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Belial::hand, PATH_UNIT"Enemy/Belial/SkellBossHandIdle.bmp", 0, 0, 10, 2, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Belial::handAttack, PATH_UNIT"Enemy/Belial/SkellBossHandAttack.bmp", 0, 0, 18, 2, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Belial::laserHeadL, PATH_UNIT"Enemy/Belial/LaserHeadL.bmp", 0, 0, 7, 1, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Belial::laserHeadR, PATH_UNIT"Enemy/Belial/LaserHeadR.bmp", 0, 0, 7, 1, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Belial::laserBody, PATH_UNIT"Enemy/Belial/LaserBody.bmp", 0, 0, 7, 1, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Belial::swordEffect, PATH_UNIT"Enemy/Belial/SwordEffect.bmp", 0, 0, 3, 1, true, ColorSet::MAGENTA);
	GPIMAGEMANAGER->addImage(getMemDC(), ImageName::Enemy::Belial::sword, PATH_UNIT"Enemy/Belial/SkellBossSword.png");
	// ´ÏÇÃÇìÀÓ
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Niflheim::idle, PATH_UNIT"Enemy/Niflheim/Idle.bmp", 0, 0, 6, 2, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Niflheim::attack, PATH_UNIT"Enemy/Niflheim/Attack.bmp", 0, 0, 11, 2, true, ColorSet::MAGENTA);
	GPIMAGEMANAGER->addFrameImage(getMemDC(), ImageName::Enemy::Niflheim::pillar, PATH_UNIT"Enemy/Niflheim/Pillar.png", 20, 1);

	// Map
	IMAGEMANAGER->addImage(ImageName::pixelTest, PATH_IMAGE"PixelTest.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage(ImageName::testTile, PATH_IMAGE"TestTile.bmp", 48, 48);

	// MapTool
	IMAGEMANAGER->addFrameImage(ImageName::mapTile, PATH_IMAGE"MapTool/MapTile.bmp", 1024 * TILE_SCALE, 512 * TILE_SCALE, 64, 32, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::mapToolTile, PATH_IMAGE"MapTool/MapTile.bmp", 1024 * MapToolSet::TOOL_TILE_SCALE, 512 * MapToolSet::TOOL_TILE_SCALE, 64, 32, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::mapPixel, PATH_IMAGE"MapTool/MapPixel.bmp", 48 * TILE_SCALE, 32 * TILE_SCALE, true, ColorSet::MAGENTA);
	//IMAGEMANAGER->addImage("MapTileGp", L"Resources/Images/MapTool/MapTile.png");

	// Loading
	IMAGEMANAGER->addImage(ImageName::logo, PATH_IMAGE"StartScene/Logo.bmp", 0, 0, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::cloud1, PATH_IMAGE"StartScene/Cloud1.bmp", 0, WINSIZE_Y, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::cloud2, PATH_IMAGE"StartScene/Cloud2.bmp", 0, WINSIZE_Y, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::background, PATH_IMAGE"StartScene/Background.bmp", WINSIZE_X, WINSIZE_Y, true, ColorSet::MAGENTA);

	// Town
	IMAGEMANAGER->addImage(ImageName::floor, PATH_IMAGE"Town/Floor.bmp", 0, 0, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Town::cloud, PATH_IMAGE"Town/Cloud.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage(ImageName::Town::townBgDay, PATH_IMAGE"Town/TownBG_Day.bmp", 0, 0, true, ColorSet::MAGENTA, 4.0f);
	IMAGEMANAGER->addImage(ImageName::Town::townLayerDay, PATH_IMAGE"Town/TownLayer_Day.bmp", 0, 0, true, ColorSet::MAGENTA, 4.0f);

	// Item
	GPIMAGEMANAGER->addImage(getMemDC(), ImageName::Item::Weapon::basicShotSword, PATH_ITEM"Weapon/BasicShortSword_rotate.png");

	// Effect
	GPIMAGEMANAGER->addFrameImage(getMemDC(), ImageName::Effect::Weapon::effectBasic, PATH_ITEM"Effect/BasicShortSwordEffect.png", 3, 1);
}
