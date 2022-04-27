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
	loadImages();

	return S_OK;
}

void ImageLoader::release()
{
}

void ImageLoader::loadImages()
{
	IMAGEMANAGER->addImage(ImageName::none, PATH_IMAGE"None.bmp", 0, 0, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::ChangeScene, PATH_IMAGE"ScreenCover.bmp", WINSIZE_X, WINSIZE_Y);
	
	// ==========
	// # Player #
	// ==========
#pragma region Player
	IMAGEMANAGER->addFrameImage(ImageName::Player::idle, PATH_UNIT"Player/PlayerIdle.bmp", 0, 0, 5, 2, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Player::run, PATH_UNIT"Player/PlayerRun.bmp", 0, 0, 8, 2, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Player::jump, PATH_UNIT"Player/PlayerJump.bmp", 0, 0, 1, 2, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Player::runEffectR, PATH_UNIT"Player/RunEffectR.bmp", 0, 0, 5, 1, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Player::runEffectL, PATH_UNIT"Player/RunEffectL.bmp", 0, 0, 5, 1, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Player::jumpEffect, PATH_UNIT"Player/JumpFX.bmp", 225, 50, 5, 1, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Player::die, PATH_UNIT"Player/PlayerDie.bmp", 0, 0, true, ColorSet::MAGENTA);
#pragma endregion

	// =========
	// # Enemy #
	// =========
#pragma region Enemy
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::sapwn, PATH_UNIT"Enemy/EnemySpawn.bmp", 0, 0, 15, 1, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::die, PATH_UNIT"Enemy/EnemyDie.bmp", 0, 0, 11, 1, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::dieSmall, PATH_UNIT"Enemy/EnemyDie_small.bmp", 0, 0, 11, 1, true, ColorSet::MAGENTA);
	// 뼈 멍멍이
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::dogIdle, PATH_UNIT"Enemy/SkelDog/SkelDogIdle.bmp", 0, 0, 5, 2, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::dogRun, PATH_UNIT"Enemy/SkelDog/SkelDogRun.bmp", 0, 0, 7, 2, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::dogDie, PATH_UNIT"Enemy/SkelDog/SkelDogDie.bmp", 0, 0, 1, 2, true, ColorSet::MAGENTA);
	// 작은 유령
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::littleGhostIdle, PATH_UNIT"Enemy/LittleGhost/LittleGhost.bmp", 0, 0, 6, 2, true, ColorSet::MAGENTA);
	// 벨리알
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
	// 니플헤임
	IMAGEMANAGER->addImage(ImageName::Enemy::Niflheim::bullet, PATH_UNIT"Enemy/Niflheim/IceBullet.bmp", 0,0, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Niflheim::idle, PATH_UNIT"Enemy/Niflheim/Idle.bmp", 0, 0, 6, 2, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Niflheim::attack, PATH_UNIT"Enemy/Niflheim/Attack.bmp", 0, 0, 11, 2, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Niflheim::bulletFX, PATH_UNIT"Enemy/Niflheim/IceBulletFX.bmp", 0, 0, 3, 1, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Niflheim::pillar, PATH_UNIT"Enemy/Niflheim/Pillar.bmp", 0, 0, 20, 1, true, ColorSet::MAGENTA);
	//GPIMAGEMANAGER->addFrameImage(getMemDC(), ImageName::Enemy::Niflheim::pillar, PATH_UNIT"Enemy/Niflheim/Pillar.png", 20, 1);
#pragma endregion

	// ===========
	// # MapTool #
	// ===========
#pragma region MapTool
	IMAGEMANAGER->addFrameImage(ImageName::MapTool::mapTile, PATH_IMAGE"MapTool/MapTile.bmp", 512 * TILE_SCALE, 512 * TILE_SCALE, 32, 32, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::MapTool::mapToolTile, PATH_IMAGE"MapTool/MapTile.bmp", 512 * TOOL_TILE_SCALE, 512 * TOOL_TILE_SCALE, 4, 2, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::MapTool::mapObject, PATH_IMAGE"MapTool/Object.bmp", 128 * TILE_SCALE, 16 * TILE_SCALE, 8, 1, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::MapTool::mapToolObject, PATH_IMAGE"MapTool/Object.bmp", 128 * TOOL_TILE_SCALE, 16 * TOOL_TILE_SCALE, 8, 1, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::MapTool::button, PATH_IMAGE"MapTool/Button.bmp", 85, 100, 1, 2, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::MapTool::box, PATH_IMAGE"MapTool/RectBox.bmp", 85*3, 100, 1, 2, true, ColorSet::MAGENTA);
#pragma endregion

	// ==============
	// # Background #
	// ==============
#pragma region Background
	IMAGEMANAGER->addImage(ImageName::Background::startCloud1, PATH_IMAGE"Background/Cloud1.bmp", 0, WINSIZE_Y, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Background::startCloud2, PATH_IMAGE"Background/Cloud2.bmp", 0, WINSIZE_Y, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Background::bgSky, PATH_IMAGE"Background/Sky.bmp", WINSIZE_X, WINSIZE_Y, true, ColorSet::MAGENTA);
#pragma endregion

	// ======
	// # UI #
	// ======
#pragma region UI
	IMAGEMANAGER->addImage(ImageName::UI::logo, PATH_IMAGE"UI/Logo.bmp", 0, 0, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::UI::bird, PATH_IMAGE"UI/Bird.bmp", 0, 0, 8, 1, true, ColorSet::MAGENTA);
	// 버튼
	IMAGEMANAGER->addFrameImage(ImageName::UI::Button::gameStart, PATH_IMAGE"UI/Buttons/GameStart.bmp", 0, 0, 1, 2, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::UI::Button::mapTool, PATH_IMAGE"UI/Buttons/MapTool.bmp", 0, 0, 1, 2, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::UI::Button::quit, PATH_IMAGE"UI/Buttons/Quit.bmp", 0, 0, 1, 2, true, ColorSet::MAGENTA);
	// 커서
	IMAGEMANAGER->addImage(ImageName::UI::Cursor::cursor, PATH_IMAGE"UI/Cursor/BasicCursor.bmp", 0, 0, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::Cursor::attack, PATH_IMAGE"UI/Cursor/ShootingCursor.bmp", 0, 0, true, ColorSet::MAGENTA);
	// 이미지 폰트
	IMAGEMANAGER->addFrameImage(ImageName::UI::Font::Normal_s, PATH_IMAGE"UI/Font/NormalFont.bmp", 182 * 2, 56 * 2, 26, 4, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::UI::Font::Normal, PATH_IMAGE"UI/Font/NormalFont.bmp", 182 * 3, 56 * 3, 26, 4, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::UI::Font::Damage, PATH_IMAGE"UI/Font/DamageFont.bmp", 0, 0, 10, 1, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::UI::Font::Gold, PATH_IMAGE"UI/Font/GoldFont.bmp", 165, 26, 11, 1, true, ColorSet::MAGENTA);
	// 인벤토리
	IMAGEMANAGER->addImage(ImageName::UI::Inventory::on, PATH_IMAGE"UI/Inventory/on.bmp", 0, 0, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::Inventory::Base, PATH_IMAGE"UI/Inventory/InventoryBase.bmp");
	IMAGEMANAGER->addImage(ImageName::UI::Inventory::Cell, PATH_IMAGE"UI/Inventory/Cell.bmp", 0, 0, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::Inventory::Cell_On, PATH_IMAGE"UI/Inventory/Cell_On.bmp", 0, 0, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::Inventory::equipBase, PATH_IMAGE"UI/Inventory/EquippedWeaponBase.bmp", 0, 0, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::Inventory::Accessory, PATH_IMAGE"UI/Inventory/Accessory.bmp", 0, 0, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::Inventory::EquipSlot1On, PATH_IMAGE"UI/Inventory/EquipSlot1On.bmp", 0, 0, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::Inventory::EquipSlot2On, PATH_IMAGE"UI/Inventory/EquipSlot2On.bmp", 0, 0, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::UI::Inventory::exitBtn, PATH_IMAGE"UI/Inventory/InventoryExit.bmp", 0, 0, 1, 2, true, ColorSet::MAGENTA);
	// 몬스터 HP Bar
	IMAGEMANAGER->addImage(ImageName::UI::MonsterHpBar::back, PATH_IMAGE"UI/MonsterHp/MonsterHpBar.bmp", 0, 0, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::MonsterHpBar::gauge, PATH_IMAGE"UI/MonsterHp/MonsterLifeGauge.bmp", 0, 0, true, ColorSet::MAGENTA);
	// 플레이어 HP Bar
	IMAGEMANAGER->addImage(ImageName::UI::PlayerHpBar::Back, PATH_IMAGE"UI/PlayerHP/PlayerLifeBack.bmp", 0, 0, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::PlayerHpBar::Base, PATH_IMAGE"UI/PlayerHP/PlayerLifeBase.bmp", 0, 0, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::PlayerHpBar::LifeBar, PATH_IMAGE"UI/PlayerHP/LifeBar.bmp", 0, 0, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::PlayerHpBar::DashStart, PATH_IMAGE"UI/PlayerHP/DashStart.bmp", 0, 0, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::PlayerHpBar::DashEnd, PATH_IMAGE"UI/PlayerHP/DashEnd.bmp", 0, 0, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::PlayerHpBar::DashCount, PATH_IMAGE"UI/PlayerHP/DashCount.bmp", 0, 0, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::UI::PlayerHpBar::LifeWave, PATH_IMAGE"UI/PlayerHP/LifeWave.bmp", 0, 0, 7, 1, true, ColorSet::MAGENTA);
	// 미니맵
	IMAGEMANAGER->addImage(ImageName::UI::MiniMap::MapPixel, PATH_IMAGE"UI/MiniMap/MiniMapPixel.bmp");
	IMAGEMANAGER->addImage(ImageName::UI::MiniMap::PlayerPixel, PATH_IMAGE"UI/MiniMap/MiniMapPlayer.bmp");
	IMAGEMANAGER->addImage(ImageName::UI::MiniMap::EnemyPixel, PATH_IMAGE"UI/MiniMap/MiniMapEnemy.bmp");
	IMAGEMANAGER->addImage(ImageName::UI::MiniMap::DoorPixel, PATH_IMAGE"UI/MiniMap/MiniMapDoor.bmp");
	// 키보드
	IMAGEMANAGER->addImage(ImageName::UI::Keyboard::F, PATH_IMAGE"UI/KeyBoard/Keyboard_F.bmp", 23, 25, true, ColorSet::MAGENTA);
	// 재장전
	IMAGEMANAGER->addImage(ImageName::UI::Item::reloadBar, PATH_IMAGE"UI/Item/ReloadBar.bmp", 0, 0, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::Item::reloadBase, PATH_IMAGE"UI/Item/ReloadBase.bmp", 0, 0, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::UI::Item::reloadBase, PATH_IMAGE"UI/Item/ReloadEffect.bmp", 0, 0, 4, 1, true, ColorSet::MAGENTA);

#pragma endregion

	// Town
	IMAGEMANAGER->addImage(ImageName::Town::cloud, PATH_IMAGE"Town/Cloud.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage(ImageName::Town::townBgDay, PATH_IMAGE"Town/TownBG_Day.bmp", 0, 0, true, ColorSet::MAGENTA, 4.0f);
	IMAGEMANAGER->addImage(ImageName::Town::townLayerDay, PATH_IMAGE"Town/TownLayer_Day.bmp", 0, 0, true, ColorSet::MAGENTA, 4.0f);
	IMAGEMANAGER->addFrameImage(ImageName::Town::dungeonEat, PATH_IMAGE"Town/DungeonEat.bmp", 0, 0, 28, 1, true, ColorSet::MAGENTA);

	// ========
	// # Item #
	// ========
#pragma region Item
	// 골드
	IMAGEMANAGER->addFrameImage(ImageName::Item::Gold::coin, PATH_ITEM"Gold/Coin.bmp", 0, 0, 8, 1, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Item::Gold::bullion, PATH_ITEM"Gold/Bullion.bmp", 0, 0, 7, 1, true, ColorSet::MAGENTA);
	// 숏소드
	GPIMAGEMANAGER->addImage(getMemDC(), ImageName::Item::Weapon::basicShotSword, PATH_ITEM"Weapon/BasicShortSword.png");
	// 더 콜트
	GPIMAGEMANAGER->addFrameImage(getMemDC(), ImageName::Item::Weapon::colt, PATH_ITEM"Weapon/Colt.png", 1, 2);
	// 총알
	GPIMAGEMANAGER->addImage(getMemDC(), ImageName::Item::Weapon::bullet02, PATH_ITEM"Bullet/Bullet02.png");
#pragma endregion

	// ==========
	// # Effect #
	// ==========
#pragma region Effect
	// 검 이펙트
	GPIMAGEMANAGER->addFrameImage(getMemDC(), ImageName::Effect::Weapon::basicSwing, PATH_ITEM"Effect/BasicShortSwordEffect.png", 3, 1);
	// 총 이펙트
	GPIMAGEMANAGER->addFrameImage(getMemDC(), ImageName::Effect::Weapon::shooting, PATH_ITEM"Effect/Shooting.png", 6, 1);
	GPIMAGEMANAGER->addFrameImage(getMemDC(), ImageName::Effect::Weapon::shootingHit, PATH_ITEM"Effect/Shooting_hit.png", 6, 1);
#pragma endregion

	// ===========
	// # Dungeon #
	// ===========
	IMAGEMANAGER->addImage(ImageName::Dungeon::sqaure1, PATH_IMAGE"Dungeon/Particle/SqaureParticle_1.bmp", 0, 0, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Dungeon::sqaure2, PATH_IMAGE"Dungeon/Particle/SqaureParticle_2.bmp", 0, 0, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Dungeon::sqaure3, PATH_IMAGE"Dungeon/Particle/SqaureParticle_3.bmp", 0, 0, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Dungeon::sqaure4, PATH_IMAGE"Dungeon/Particle/SqaureParticle_4.bmp", 0, 0, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Dungeon::sqaure5, PATH_IMAGE"Dungeon/Particle/SqaureParticle_5.bmp", 0, 0, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Dungeon::bgLayer0, PATH_IMAGE"Background/BGLayer_0.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage(ImageName::Dungeon::bgLayer1, PATH_IMAGE"Background/BGLayer_1.bmp", WINSIZE_X, WINSIZE_Y, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Dungeon::Door, PATH_IMAGE"Dungeon/Door/Door.bmp", 0, 0, 23, 1, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Dungeon::DoorLeft, PATH_IMAGE"Dungeon/Door/Door_Left.bmp", 0, 0, 23, 1, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Dungeon::DoorRight, PATH_IMAGE"Dungeon/Door/Door_Right.bmp", 0, 0, 23, 1, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Dungeon::tresureNormal, PATH_IMAGE"Dungeon/Tresure/Stash.bmp", 0, 0, 1, 2, true, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Dungeon::tresureBoss, PATH_IMAGE"Dungeon/Tresure/YellowTresure.bmp", 0, 0, 1, 2, true, ColorSet::MAGENTA);

	// ==========
	// # Object #
	// ==========
	IMAGEMANAGER->addImage(ImageName::Object::box, PATH_IMAGE"Object/Box.bmp", 0, 0, true, ColorSet::MAGENTA);

}
