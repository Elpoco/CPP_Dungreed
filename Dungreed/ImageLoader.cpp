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
	IMAGEMANAGER->addImage(ImageName::none, PATH_IMAGE"None.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::ChangeScene, PATH_IMAGE"ScreenCover.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage(ImageName::info, PATH_IMAGE"ScreenCover.bmp", 350, 90);
	IMAGEMANAGER->addImage(ImageName::skill, PATH_IMAGE"ScreenCover.bmp", 50, 50);
	IMAGEMANAGER->addImage(ImageName::BossIntro, PATH_IMAGE"BossIntro.bmp", WINSIZE_X, WINSIZE_Y, TRUE, ColorSet::MAGENTA);
	
	// ==========
	// # Player #
	// ==========
#pragma region Player
	IMAGEMANAGER->addFrameImage(ImageName::Player::idle, PATH_UNIT"Player/PlayerIdle.bmp", 0, 0, 5, 2, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Player::run, PATH_UNIT"Player/PlayerRun.bmp", 0, 0, 8, 2, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Player::jump, PATH_UNIT"Player/PlayerJump.bmp", 0, 0, 1, 2, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Player::runEffectR, PATH_UNIT"Player/RunEffectR.bmp", 0, 0, 5, 1, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Player::runEffectL, PATH_UNIT"Player/RunEffectL.bmp", 0, 0, 5, 1, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Player::jumpEffect, PATH_UNIT"Player/JumpFX.bmp", 180, 40, 5, 1, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Player::die, PATH_UNIT"Player/PlayerDie.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Player::dashEffectR, PATH_UNIT"Player/PlayerDashR.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Player::dashEffectL, PATH_UNIT"Player/PlayerDashL.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
#pragma endregion

	// =========
	// # Enemy #
	// =========
#pragma region Enemy
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::sapwn, PATH_UNIT"Enemy/EnemySpawn.bmp", 0, 0, 15, 1, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::die, PATH_UNIT"Enemy/EnemyDie.bmp", 0, 0, 11, 1, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::dieSmall, PATH_UNIT"Enemy/EnemyDie_small.bmp", 0, 0, 11, 1, TRUE, ColorSet::MAGENTA);

	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Scarecrow, PATH_UNIT"Enemy/Scarecrow/criminalldle.bmp", 0, 0, 5, 2, TRUE, ColorSet::MAGENTA);
	// 뼈 멍멍이
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::dogIdle, PATH_UNIT"Enemy/SkelDog/SkelDogIdle.bmp", 0, 0, 5, 2, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::dogRun, PATH_UNIT"Enemy/SkelDog/SkelDogRun.bmp", 0, 0, 7, 2, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::dogDie, PATH_UNIT"Enemy/SkelDog/SkelDogDie.bmp", 0, 0, 1, 2, TRUE, ColorSet::MAGENTA);
	// 작은 유령
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::littleGhostIdle, PATH_UNIT"Enemy/LittleGhost/LittleGhost.bmp", 0, 0, 6, 2, TRUE, ColorSet::MAGENTA);
	// 밴시
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::BansheeIdle, PATH_UNIT"Enemy/Banshee/BansheeIdle.bmp", 0, 0, 6, 2, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::BansheeATK, PATH_UNIT"Enemy/Banshee/BansheeAttack.bmp", 0, 0, 6, 2, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::BansheeBullet, PATH_UNIT"Enemy/Banshee/BansheeBulletSprite.bmp", 0, 0, 4, 1, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::BansheeBulletFX, PATH_UNIT"Enemy/Banshee/BansheeBulletBoomSprite.bmp", 0, 0, 6, 1, TRUE, ColorSet::MAGENTA, 3.0f);
	// 큰 박쥐
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::BatIdle, PATH_UNIT"Enemy/Bat/BatIdle.bmp", 0, 0, 6, 2, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::GiantBat, PATH_UNIT"Enemy/Bat/GiantBat.bmp", 0, 0, 7, 2, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::RedGiantBat, PATH_UNIT"Enemy/Bat/RedGiantBat.bmp", 0, 0, 7, 2, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::BatAttack, PATH_UNIT"Enemy/Bat/BatAttack.bmp", 0, 0, 10, 2, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::GiantBatAttack, PATH_UNIT"Enemy/Bat/GiantBatAttack.bmp", 0, 0, 10, 2, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::RedGiantBatAttack, PATH_UNIT"Enemy/Bat/RedGiantBatAttack.bmp", 0, 0, 10, 2, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::BatBullet, PATH_UNIT"Enemy/Bat/BatBullet.bmp", 0, 0, 5, 1, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::BatBulletHit, PATH_UNIT"Enemy/Bat/BatBulletHit.bmp", 0, 0, 7, 1, TRUE, ColorSet::MAGENTA);
	// 스켈레톤
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::SkelIdle, PATH_UNIT"Enemy/Skel/SkelIdle.bmp", 0, 0, 1, 2, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::SkelWalk, PATH_UNIT"Enemy/Skel/SkelWalk.bmp", 0, 0, 6, 2, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::SkelBow, PATH_UNIT"Enemy/Skel/SkelBow.bmp", 0, 0, 6, 1, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::SkelArrowEffect, PATH_UNIT"Enemy/Skel/ArrowFX.bmp", 0, 0, 6, 1, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Enemy::SkelSword, PATH_UNIT"Enemy/Skel/SkelSword.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Enemy::SkelArrow, PATH_UNIT"Enemy/Skel/SkelArrow.bmp", 0, 0, TRUE, ColorSet::MAGENTA);

	// 벨리알
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Belial::idle, PATH_UNIT"Enemy/Belial/SkellBossIdle.bmp", 0, 0, 10, 1, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Belial::back, PATH_UNIT"Enemy/Belial/SkellBossBack.bmp", 0, 0, 10, 1, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Belial::attack, PATH_UNIT"Enemy/Belial/SkellBossAttack.bmp", 0, 0, 10, 1, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Belial::particle, PATH_UNIT"Enemy/Belial/SkellBossParticle.bmp", 0, 0, 8, 1, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Belial::bullet, PATH_UNIT"Enemy/Belial/BossBullet.bmp", 0, 0, 2, 1, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Belial::bulletEffect, PATH_UNIT"Enemy/Belial/BossBulletEffect.bmp", 0, 0, 8, 1, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Belial::hand, PATH_UNIT"Enemy/Belial/SkellBossHandIdle.bmp", 0, 0, 10, 2, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Belial::handAttack, PATH_UNIT"Enemy/Belial/SkellBossHandAttack.bmp", 0, 0, 18, 2, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Belial::laserHeadL, PATH_UNIT"Enemy/Belial/LaserHeadL.bmp", 0, 0, 7, 1, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Belial::laserHeadR, PATH_UNIT"Enemy/Belial/LaserHeadR.bmp", 0, 0, 7, 1, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Belial::laserBody, PATH_UNIT"Enemy/Belial/LaserBody.bmp", 0, 0, 7, 1, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Belial::swordEffect, PATH_UNIT"Enemy/Belial/SwordEffect.bmp", 0, 0, 3, 1, TRUE, ColorSet::MAGENTA);
	GPIMAGEMANAGER->addImage(getMemDC(), ImageName::Enemy::Belial::sword, PATH_UNIT"Enemy/Belial/SkellBossSword.png");
	// 니플헤임
	IMAGEMANAGER->addImage(ImageName::Enemy::Niflheim::bullet, PATH_UNIT"Enemy/Niflheim/IceBullet.bmp", 0,0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Enemy::Niflheim::icicle, PATH_UNIT"Enemy/Niflheim/icicle.bmp", 0,0, TRUE, ColorSet::MAGENTA, 2.0f);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Niflheim::idle, PATH_UNIT"Enemy/Niflheim/Idle.bmp", 0, 0, 6, 2, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Niflheim::attack, PATH_UNIT"Enemy/Niflheim/Attack.bmp", 0, 0, 11, 2, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Niflheim::bulletFX, PATH_UNIT"Enemy/Niflheim/IceBulletFX.bmp", 0, 0, 3, 1, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Niflheim::pillar, PATH_UNIT"Enemy/Niflheim/Pillar.bmp", 0, 0, 20, 1, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Enemy::Niflheim::icicleFX, PATH_UNIT"Enemy/Niflheim/icicle_init.bmp", 0, 0, 10, 1, TRUE, ColorSet::MAGENTA, 2.0f);
#pragma endregion

	// ===========
	// # MapTool #
	// ===========
#pragma region MapTool
	IMAGEMANAGER->addFrameImage(ImageName::MapTool::mapTile, PATH_IMAGE"MapTool/MapTile.bmp", 512 * TILE_SCALE, 512 * TILE_SCALE, 32, 32, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::MapTool::mapToolTile, PATH_IMAGE"MapTool/MapTile.bmp", 512 * TOOL_TILE_SCALE, 512 * TOOL_TILE_SCALE, 4, 2, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::MapTool::mapObject, PATH_IMAGE"MapTool/Object.bmp", 128 * TILE_SCALE, 16 * TILE_SCALE, 8, 1, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::MapTool::mapToolObject, PATH_IMAGE"MapTool/Object.bmp", 128 * TOOL_TILE_SCALE, 16 * TOOL_TILE_SCALE, 8, 1, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::MapTool::button, PATH_IMAGE"MapTool/Button.bmp", 85, 100, 1, 2, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::MapTool::box, PATH_IMAGE"MapTool/RectBox.bmp", 85*3, 100, 1, 2, TRUE, ColorSet::MAGENTA);
#pragma endregion

	// ==============
	// # Background #
	// ==============
#pragma region Background
	IMAGEMANAGER->addImage(ImageName::Background::startCloud1, PATH_IMAGE"Background/Cloud1.bmp", 0, WINSIZE_Y, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Background::startCloud2, PATH_IMAGE"Background/Cloud2.bmp", 0, WINSIZE_Y, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Background::bgSky, PATH_IMAGE"Background/Sky.bmp", WINSIZE_X, WINSIZE_Y, TRUE, ColorSet::MAGENTA);
#pragma endregion

	// ======
	// # UI #
	// ======
#pragma region UI
	IMAGEMANAGER->addImage(ImageName::UI::logo, PATH_IMAGE"UI/Logo.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::UI::bird, PATH_IMAGE"UI/Bird.bmp", 0, 0, 8, 1, TRUE, ColorSet::MAGENTA);
	// 버튼
	IMAGEMANAGER->addFrameImage(ImageName::UI::Button::gameStart, PATH_IMAGE"UI/Buttons/GameStart.bmp", 0, 0, 1, 2, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::UI::Button::mapTool, PATH_IMAGE"UI/Buttons/MapTool.bmp", 0, 0, 1, 2, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::UI::Button::quit, PATH_IMAGE"UI/Buttons/Quit.bmp", 0, 0, 1, 2, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::UI::Button::Exit, PATH_IMAGE"UI/Buttons/FullWindowExitButton.bmp", 0, 0, 1, 2, TRUE, ColorSet::MAGENTA, 3.0f);
	// 커서
	IMAGEMANAGER->addImage(ImageName::UI::Cursor::cursor, PATH_IMAGE"UI/Cursor/BasicCursor.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::Cursor::attack, PATH_IMAGE"UI/Cursor/ShootingCursor.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	// 이미지 폰트
	IMAGEMANAGER->addFrameImage(ImageName::UI::Font::Normal_s, PATH_IMAGE"UI/Font/NormalFont.bmp", 182 * 2, 56 * 2, 26, 4, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::UI::Font::Normal, PATH_IMAGE"UI/Font/NormalFont.bmp", 182 * 3, 56 * 3, 26, 4, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::UI::Font::Damage, PATH_IMAGE"UI/Font/DamageFont.bmp", 0, 0, 10, 1, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addFrameImage(ImageName::UI::Font::Gold, PATH_IMAGE"UI/Font/GoldFont.bmp", 0, 0, 10, 1, TRUE, ColorSet::MAGENTA, 2.5f);
	IMAGEMANAGER->addImage(ImageName::UI::Font::G, PATH_IMAGE"UI/Font/G.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 2.5f);
	// 인벤토리
	IMAGEMANAGER->addImage(ImageName::UI::Inventory::on, PATH_IMAGE"UI/Inventory/on.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::Inventory::Base, PATH_IMAGE"UI/Inventory/InventoryBase.bmp");
	IMAGEMANAGER->addImage(ImageName::UI::Inventory::Cell, PATH_IMAGE"UI/Inventory/Cell.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::Inventory::Cell_On, PATH_IMAGE"UI/Inventory/Cell_On.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::Inventory::equipBase, PATH_IMAGE"UI/Inventory/EquippedWeaponBase.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::Inventory::Accessory, PATH_IMAGE"UI/Inventory/Accessory.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::Inventory::EquipSlot1On, PATH_IMAGE"UI/Inventory/EquipSlot1On.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::Inventory::EquipSlot2On, PATH_IMAGE"UI/Inventory/EquipSlot2On.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::Inventory::hp, PATH_IMAGE"UI/Inventory/hp.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 2.0f);
	IMAGEMANAGER->addImage(ImageName::UI::Inventory::power, PATH_IMAGE"UI/Inventory/power.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 2.0f);
	IMAGEMANAGER->addImage(ImageName::UI::Inventory::defense, PATH_IMAGE"UI/Inventory/defense.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 2.0f);
	IMAGEMANAGER->addFrameImage(ImageName::UI::Inventory::exitBtn, PATH_IMAGE"UI/Inventory/InventoryExit.bmp", 0, 0, 1, 2, TRUE, ColorSet::MAGENTA);
	// 몬스터 HP Bar
	IMAGEMANAGER->addImage(ImageName::UI::MonsterHpBar::back, PATH_IMAGE"UI/MonsterHp/MonsterHpBar.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::MonsterHpBar::gauge, PATH_IMAGE"UI/MonsterHp/MonsterLifeGauge.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	// 보스 HP Bar
	IMAGEMANAGER->addImage(ImageName::UI::MonsterHpBar::BossLifeBack, PATH_IMAGE"UI/MonsterHp/BossLifeBack.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::UI::MonsterHpBar::BossLifeBase, PATH_IMAGE"UI/MonsterHp/BossLifeBase.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::UI::MonsterHpBar::BossLifeGauge, PATH_IMAGE"UI/MonsterHp/BossLifeGauge.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::UI::MonsterHpBar::BossSkellPortrait, PATH_IMAGE"UI/MonsterHp/BossSkellPortrait.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	// 플레이어 HP Bar
	IMAGEMANAGER->addImage(ImageName::UI::PlayerHpBar::Back, PATH_IMAGE"UI/PlayerHP/PlayerLifeBack.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::PlayerHpBar::Base, PATH_IMAGE"UI/PlayerHP/PlayerLifeBase.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::PlayerHpBar::LifeBar, PATH_IMAGE"UI/PlayerHP/LifeBar.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::PlayerHpBar::DashStart, PATH_IMAGE"UI/PlayerHP/DashStart.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::PlayerHpBar::DashEnd, PATH_IMAGE"UI/PlayerHP/DashEnd.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::PlayerHpBar::DashCount, PATH_IMAGE"UI/PlayerHP/DashCount.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::UI::PlayerHpBar::LifeWave, PATH_IMAGE"UI/PlayerHP/LifeWave.bmp", 0, 0, 7, 1, TRUE, ColorSet::MAGENTA);
	// 미니맵
	IMAGEMANAGER->addImage(ImageName::UI::MiniMap::MapPixel, PATH_IMAGE"UI/MiniMap/MiniMapPixel.bmp");
	IMAGEMANAGER->addImage(ImageName::UI::MiniMap::PlayerPixel, PATH_IMAGE"UI/MiniMap/MiniMapPlayer.bmp");
	IMAGEMANAGER->addImage(ImageName::UI::MiniMap::EnemyPixel, PATH_IMAGE"UI/MiniMap/MiniMapEnemy.bmp");
	IMAGEMANAGER->addImage(ImageName::UI::MiniMap::DoorPixel, PATH_IMAGE"UI/MiniMap/MiniMapDoor.bmp");
	IMAGEMANAGER->addImage(ImageName::UI::MiniMap::BorderPixel, PATH_IMAGE"UI/MiniMap/MiniMapBorder.bmp");
	IMAGEMANAGER->addImage(ImageName::UI::MiniMap::NPCPixel, PATH_IMAGE"UI/MiniMap/MiniMapNPC.bmp");
	IMAGEMANAGER->addImage(ImageName::UI::MiniMap::MiniMapTresure, PATH_IMAGE"UI/MiniMap/MiniMapTresure.bmp");
	IMAGEMANAGER->addImage(ImageName::UI::MiniMap::MiniMapDungeon, PATH_IMAGE"UI/MiniMap/MiniMapDungeon.bmp");
	IMAGEMANAGER->addImage(ImageName::UI::MiniMap::MiniMapWorm, PATH_IMAGE"UI/MiniMap/MiniMapWorm.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	// 월드맵
	IMAGEMANAGER->addImage(ImageName::UI::WorldMap::MapBaseTitle, PATH_IMAGE"UI/WorldMap/MapBaseTitle.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::UI::WorldMap::MapBase, PATH_IMAGE"UI/WorldMap/MapBase.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::UI::WorldMap::Room, PATH_IMAGE"UI/WorldMap/Room.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 2.0f);
	IMAGEMANAGER->addImage(ImageName::UI::WorldMap::CurrentRoom, PATH_IMAGE"UI/WorldMap/CurrentRoom.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 2.0f);
	IMAGEMANAGER->addImage(ImageName::UI::WorldMap::line_h, PATH_IMAGE"UI/WorldMap/line_h.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 2.0f);
	IMAGEMANAGER->addImage(ImageName::UI::WorldMap::line_v, PATH_IMAGE"UI/WorldMap/line_v.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 2.0f);
	IMAGEMANAGER->addImage(ImageName::UI::WorldMap::ShopIcon, PATH_IMAGE"UI/WorldMap/ShopIcon.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 2.0f);
	IMAGEMANAGER->addImage(ImageName::UI::WorldMap::Food, PATH_IMAGE"UI/WorldMap/Food.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 2.0f);
	IMAGEMANAGER->addImage(ImageName::UI::WorldMap::Worm, PATH_IMAGE"UI/WorldMap/Worm.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 2.0f);
	IMAGEMANAGER->addImage(ImageName::UI::WorldMap::Worm_Selected, PATH_IMAGE"UI/WorldMap/Worm_Selected.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 2.0f);
	// 키보드
	IMAGEMANAGER->addImage(ImageName::UI::Keyboard::F, PATH_IMAGE"UI/KeyBoard/Keyboard_F.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::UI::Keyboard::Q, PATH_IMAGE"UI/KeyBoard/Keyboard_Q.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 1.5f);
	IMAGEMANAGER->addImage(ImageName::UI::Keyboard::R, PATH_IMAGE"UI/KeyBoard/Keyboard_R.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 1.5f);
	IMAGEMANAGER->addImage(ImageName::UI::Keyboard::ESC, PATH_IMAGE"UI/KeyBoard/Keyboard_esc.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	// 아이템
	IMAGEMANAGER->addImage(ImageName::UI::Item::ItemInfo, PATH_IMAGE"UI/Item/ItemInfo.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::UI::Item::Skill, PATH_IMAGE"UI/Item/Skill.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::Item::reloadBar, PATH_IMAGE"UI/Item/ReloadBar.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::Item::reloadBase, PATH_IMAGE"UI/Item/ReloadBase.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::UI::Item::reloadEffect, PATH_IMAGE"UI/Item/ReloadEffect.bmp", 0, 0, 4, 1, TRUE, ColorSet::MAGENTA);
	// 상점
	IMAGEMANAGER->addImage(ImageName::UI::NPC::ShopBase, PATH_IMAGE"UI/Shop/ShopBase.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::UI::NPC::DungeonShopBase, PATH_IMAGE"UI/Shop/DungeonShopBase.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::UI::NPC::ShopItem, PATH_IMAGE"UI/Shop/ShopItem.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::UI::NPC::ShopItem_Selected, PATH_IMAGE"UI/Shop/ShopItem_Selected.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	// 음식점
	IMAGEMANAGER->addImage(ImageName::UI::NPC::FoodShopLabel, PATH_IMAGE"UI/FoodShop/Label.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::UI::NPC::Base_0, PATH_IMAGE"UI/FoodShop/Base_0.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::UI::NPC::Base_3, PATH_IMAGE"UI/FoodShop/Base_3.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::UI::NPC::RestaurantMenu, PATH_IMAGE"UI/FoodShop/RestaurantMenu.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::UI::NPC::RestaurantMenuSelected, PATH_IMAGE"UI/FoodShop/RestaurantMenuSelected.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::UI::NPC::RestaurantMenuSell, PATH_IMAGE"UI/FoodShop/RestaurantMenuSell.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::UI::NPC::RestaurantRect, PATH_IMAGE"UI/FoodShop/RestaurantRect.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::UI::NPC::GoldCoin, PATH_IMAGE"UI/FoodShop/GoldCoin.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addFrameImage(ImageName::UI::NPC::RestaurantTable, PATH_IMAGE"UI/FoodShop/RestaurantTable.bmp", 0, 0, 3, 1, TRUE, ColorSet::MAGENTA, 3.0f);
	// 음식
	IMAGEMANAGER->addImage(ImageName::UI::FOOD::Bread, PATH_IMAGE"UI/FoodShop/Food/01_Bread.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::FOOD::FriedEgg, PATH_IMAGE"UI/FoodShop/Food/02_FriedEgg.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::FOOD::GrilledMushroom, PATH_IMAGE"UI/FoodShop/Food/03_GrilledMushroom.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::FOOD::TamatoSoup, PATH_IMAGE"UI/FoodShop/Food/04_TamatoSoup.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::FOOD::OnionSoup, PATH_IMAGE"UI/FoodShop/Food/05_OnionSoup.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::FOOD::PeaSoup, PATH_IMAGE"UI/FoodShop/Food/06_PeaSoup.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::FOOD::VegetableSalsaSoup, PATH_IMAGE"UI/FoodShop/Food/07_VegetableSalsaSoup.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::FOOD::Lemonade, PATH_IMAGE"UI/FoodShop/Food/08_Lemonade.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::FOOD::DeluxeBurger, PATH_IMAGE"UI/FoodShop/Food/09_DeluxeBurger.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::UI::FOOD::ChocolateCookie, PATH_IMAGE"UI/FoodShop/Food/10_ChocolateCookie.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	// 어빌리티
	IMAGEMANAGER->addImage(ImageName::UI::Ability::Label, PATH_IMAGE"UI/Ability/AbilityTItle.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::UI::Ability::Wrath, PATH_IMAGE"UI/Ability/AbilityBackground_Wrath.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::UI::Ability::Patience, PATH_IMAGE"UI/Ability/AbilityBackground_Patience.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::UI::Ability::Greed, PATH_IMAGE"UI/Ability/AbilityBackground_Greed.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addFrameImage(ImageName::UI::Ability::btnWrath, PATH_IMAGE"UI/Ability/AbilityBackgroundButton_Wrath.bmp", 0, 0, 1, 2, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addFrameImage(ImageName::UI::Ability::btnPatience, PATH_IMAGE"UI/Ability/AbilityBackgroundButton_Patience.bmp", 0, 0, 1, 2, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addFrameImage(ImageName::UI::Ability::btnGreed, PATH_IMAGE"UI/Ability/AbilityBackgroundButton_Greed.bmp", 0, 0, 1, 2, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addFrameImage(ImageName::UI::Ability::AbilityFX, PATH_IMAGE"UI/Ability/AbilityFX.bmp", 0, 0, 6, 1, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addFrameImage(ImageName::UI::Ability::AbilityTextBar, PATH_IMAGE"UI/Ability/AbilityTextBar.bmp", 0, 0, 3, 1, TRUE, ColorSet::MAGENTA, 3.0f);
	// 탐험 종료
	IMAGEMANAGER->addImage(ImageName::UI::ExplorationFailureKor, PATH_IMAGE"UI/ExplorationFailureKor.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::UI::ExplorationSuccessKor, PATH_IMAGE"UI/ExplorationSuccessKor.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::UI::LevelUp, PATH_IMAGE"UI/LevelUp.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);

#pragma endregion

	// =======
	// # NPC #
	// =======
#pragma region NPC
	IMAGEMANAGER->addFrameImage(ImageName::NPC::Merchant, PATH_UNIT"NPC/NPC_Merchant.bmp", 0, 0, 6, 1, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addFrameImage(ImageName::NPC::Giant, PATH_UNIT"NPC/NPC_Giant.bmp", 0, 0, 4, 1, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addFrameImage(ImageName::NPC::BlackSmith, PATH_UNIT"NPC/NPC_BlackSmith.bmp", 0, 0, 6, 1, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addFrameImage(ImageName::NPC::Commander, PATH_UNIT"NPC/NPC_Commander.bmp", 0, 0, 6, 1, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addFrameImage(ImageName::NPC::Inn, PATH_UNIT"NPC/NPC_Inn.bmp", 0, 0, 6, 1, TRUE, ColorSet::MAGENTA, 3.0f);
#pragma endregion

	// ========
	// # Town #
	// ========
#pragma region Town
	IMAGEMANAGER->addImage(ImageName::Town::cloud, PATH_IMAGE"Town/Cloud.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage(ImageName::Town::townBgDay, PATH_IMAGE"Town/TownBG_Day.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 4.0f);
	IMAGEMANAGER->addImage(ImageName::Town::townLayerDay, PATH_IMAGE"Town/TownLayer_Day.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 4.0f);
	IMAGEMANAGER->addImage(ImageName::Town::BrokenTemple, PATH_IMAGE"Town/BrokenTemple.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::Town::DogHouse, PATH_IMAGE"Town/DogHouse.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::Town::DungeonSignL, PATH_IMAGE"Town/DungeonSignL.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::Town::DungeonSignR, PATH_IMAGE"Town/DungeonSignR.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::Town::Tree0, PATH_IMAGE"Town/Tree0.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::Town::Tree1, PATH_IMAGE"Town/Tree1.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::Town::Grass0, PATH_IMAGE"Town/Grass0.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::Town::Grass1, PATH_IMAGE"Town/Grass1.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::Town::Grass2, PATH_IMAGE"Town/Grass2.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::Town::Shop, PATH_IMAGE"Town/Shop.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Town::BrokenHouse0, PATH_IMAGE"Town/BrokenHouse0.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::Town::BrokenHouse1, PATH_IMAGE"Town/BrokenHouse1.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::Town::TrainingSchool, PATH_IMAGE"Town/TrainingSchool.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::Town::BlackSmith, PATH_IMAGE"Town/BlackSmith.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::Town::StreetLight_0, PATH_IMAGE"Town/StreetLight_0.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::Town::StreetLight_1, PATH_IMAGE"Town/StreetLight_1.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::Town::StreetLight_2, PATH_IMAGE"Town/StreetLight_2.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addFrameImage(ImageName::Town::dungeonEat, PATH_IMAGE"Town/DungeonEat.bmp", 0, 0, 28, 1, TRUE, ColorSet::MAGENTA);
#pragma endregion

	// ========
	// # Item #
	// ========
#pragma region Item
	// 골드
	IMAGEMANAGER->addFrameImage(ImageName::Item::Gold::coin, PATH_ITEM"Gold/Coin.bmp", 0, 0, 8, 1, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Item::Gold::bullion, PATH_ITEM"Gold/Bullion.bmp", 0, 0, 7, 1, TRUE, ColorSet::MAGENTA);
	// 검
	GPIMAGEMANAGER->addImage(getMemDC(), ImageName::Item::Weapon::basicShotSword, PATH_ITEM"Weapon/BasicShortSword.png");
	GPIMAGEMANAGER->addImage(getMemDC(), ImageName::Item::Weapon::BambooSword, PATH_ITEM"Weapon/BambooSword.png");
	GPIMAGEMANAGER->addImage(getMemDC(), ImageName::Item::Weapon::LightSaber, PATH_ITEM"Weapon/LightSaber.png");
	GPIMAGEMANAGER->addImage(getMemDC(), ImageName::Item::Weapon::ThreeTieredBaton, PATH_ITEM"Weapon/Three-TieredBaton.png");
	GPIMAGEMANAGER->addFrameImage(getMemDC(), ImageName::Item::Weapon::CosmosSword, PATH_ITEM"Weapon/CosmosSword.png", 12, 1);

	GPIMAGEMANAGER->addImage(getMemDC(), ImageName::Item::Weapon::Lala, PATH_ITEM"Weapon/Lala.png");
	// 총
	GPIMAGEMANAGER->addFrameImage(getMemDC(), ImageName::Item::Weapon::colt, PATH_ITEM"Weapon/Colt.png", 1, 2);
	GPIMAGEMANAGER->addFrameImage(getMemDC(), ImageName::Item::Weapon::GatlingGun, PATH_ITEM"Weapon/GatlingGun.png", 1, 2);
	// 총알
	IMAGEMANAGER->addImage(ImageName::Item::Weapon::Bullet02, PATH_ITEM"Bullet/Bullet02.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Item::Weapon::Bullet03, PATH_ITEM"Bullet/Bullet03.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Item::Weapon::Bullet07, PATH_ITEM"Bullet/Bullet07.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 2.0f);
	IMAGEMANAGER->addImage(ImageName::Item::Weapon::Bullet08, PATH_ITEM"Bullet/Bullet08.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Item::Weapon::StarBullet, PATH_ITEM"Bullet/StarBullet.bmp", 0, 0, 4, 1, TRUE, ColorSet::MAGENTA, 3.0f);
	// 창
	GPIMAGEMANAGER->addImage(getMemDC(), ImageName::Item::Weapon::Spear, PATH_ITEM"Weapon/Spear.png");
	// 방어구
	IMAGEMANAGER->addImage(ImageName::Item::Weapon::MagicShield, PATH_ITEM"Weapon/MagicShield.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);

	// 악세
	IMAGEMANAGER->addImage(ImageName::Item::Accessory::MultiBullet, PATH_ITEM"Accessory/MultiBullet.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Item::Accessory::MagnifyingGlass, PATH_ITEM"Accessory/MagnifyingGlass.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Item::Accessory::Wingboots, PATH_ITEM"Accessory/Wingboots.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::Item::Accessory::Bullion, PATH_ITEM"Accessory/Bullion.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::Item::Accessory::LeatherArmor, PATH_ITEM"Accessory/LeatherArmor.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::Item::Accessory::ChainArmor, PATH_ITEM"Accessory/ChainArmor.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::Item::Accessory::CharmOfAttack, PATH_ITEM"Accessory/CharmOfAttack.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::Item::Accessory::CharmOfMadness, PATH_ITEM"Accessory/CharmOfMadness.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::Item::Accessory::Jarngreipr, PATH_ITEM"Accessory/Jarngreipr.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::Item::Accessory::Speedloader, PATH_ITEM"Accessory/Speedloader.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::Item::Accessory::DaisyRing, PATH_ITEM"Accessory/DaisyRing.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	// 스킬
	IMAGEMANAGER->addFrameImage(ImageName::Item::Weapon::CosmosSwordAura, PATH_ITEM"Bullet/CosmosAuror.bmp", 0, 0, 5, 1, TRUE, ColorSet::MAGENTA, 3.0f);
	// 스킬 아이콘
	IMAGEMANAGER->addImage(ImageName::Item::Weapon::CosmosSkill, PATH_ITEM"Skill/Skill_CosmosSwordAuror.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::Item::Weapon::LalaSkill, PATH_ITEM"Skill/Skill_ShootingStars.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
#pragma endregion

	// ==========
	// # Effect #
	// ==========
#pragma region Effect
	// 검 이펙트
	GPIMAGEMANAGER->addFrameImage(getMemDC(), ImageName::Effect::Weapon::basicSwing, PATH_ITEM"Effect/BasicShortSwordEffect.png", 3, 1);
	GPIMAGEMANAGER->addFrameImage(getMemDC(), ImageName::Effect::Weapon::BambooSwing, PATH_ITEM"Effect/BambooSword_Effect.png", 3, 1);
	GPIMAGEMANAGER->addFrameImage(getMemDC(), ImageName::Effect::Weapon::SwingFX, PATH_ITEM"Effect/SwingFX.png", 3, 1);
	GPIMAGEMANAGER->addFrameImage(getMemDC(), ImageName::Effect::Weapon::CosmosSwingFX, PATH_ITEM"Effect/CosmosSwingFX.png", 8, 1);
	// 총 이펙트
	IMAGEMANAGER->addFrameImage(ImageName::Effect::Weapon::StarBulletFX, PATH_ITEM"Effect/StarBulletFX.bmp", 0, 0, 7, 1, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addImage(ImageName::Effect::Weapon::StarParticle, PATH_ITEM"Effect/StarParticle.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	GPIMAGEMANAGER->addFrameImage(getMemDC(), ImageName::Effect::Weapon::shooting, PATH_ITEM"Effect/Shooting.png", 6, 1);
	GPIMAGEMANAGER->addFrameImage(getMemDC(), ImageName::Effect::Weapon::shootingHit, PATH_ITEM"Effect/Shooting_hit.png", 6, 1);
	GPIMAGEMANAGER->addFrameImage(getMemDC(), ImageName::Effect::Weapon::ShootEffect, PATH_ITEM"Effect/ShootEffect.png", 3, 1);
#pragma endregion

	// ===========
	// # Dungeon #
	// ===========
#pragma region Dungeon
	IMAGEMANAGER->addImage(ImageName::Dungeon::sqaure1, PATH_IMAGE"Dungeon/Particle/SqaureParticle_1.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Dungeon::sqaure2, PATH_IMAGE"Dungeon/Particle/SqaureParticle_2.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Dungeon::sqaure3, PATH_IMAGE"Dungeon/Particle/SqaureParticle_3.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Dungeon::sqaure4, PATH_IMAGE"Dungeon/Particle/SqaureParticle_4.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Dungeon::sqaure5, PATH_IMAGE"Dungeon/Particle/SqaureParticle_5.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Dungeon::bgLayer0, PATH_IMAGE"Background/BGLayer_0.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage(ImageName::Dungeon::bgLayer1, PATH_IMAGE"Background/BGLayer_1.bmp", WINSIZE_X, WINSIZE_Y, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Dungeon::Snow, PATH_IMAGE"Background/Snow.bmp", WINSIZE_X, WINSIZE_Y, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Dungeon::subBg, PATH_IMAGE"Background/SubBG.bmp", WINSIZE_X, WINSIZE_Y, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Dungeon::DungeonInn, PATH_IMAGE"Dungeon/NPC/DungeonInn.bmp", 0, 0, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addImage(ImageName::Dungeon::InDungeonShop, PATH_IMAGE"Dungeon/NPC/InDungeonShop.bmp", 0, 0, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addFrameImage(ImageName::Dungeon::StartDoor, PATH_IMAGE"Dungeon/Door/StartDoor.bmp", 0, 0, 10, 1, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addFrameImage(ImageName::Dungeon::Door, PATH_IMAGE"Dungeon/Door/Door.bmp", 0, 0, 23, 1, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Dungeon::DoorLeft, PATH_IMAGE"Dungeon/Door/Door_Left.bmp", 0, 0, 23, 1, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Dungeon::DoorRight, PATH_IMAGE"Dungeon/Door/Door_Right.bmp", 0, 0, 23, 1, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Dungeon::BasicTresure, PATH_IMAGE"Dungeon/Tresure/BasicTresure.bmp", 0, 0, 2, 1, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Dungeon::GoldTresure, PATH_IMAGE"Dungeon/Tresure/GoldTresure.bmp", 0, 0, 2, 1, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Dungeon::BlueTresure, PATH_IMAGE"Dungeon/Tresure/BlueTresure.bmp", 0, 0, 2, 1, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Dungeon::BossTresure, PATH_IMAGE"Dungeon/Tresure/BossTresure.bmp", 0, 0, 2, 1, TRUE, ColorSet::MAGENTA);
	IMAGEMANAGER->addFrameImage(ImageName::Dungeon::WormPassageIdle, PATH_IMAGE"Dungeon/Worm/WormPassageIdle.bmp", 0, 0, 9, 1, TRUE, ColorSet::MAGENTA, 3.0f);
	IMAGEMANAGER->addFrameImage(ImageName::Dungeon::WormPassageEat, PATH_IMAGE"Dungeon/Worm/WormPassageEat.bmp", 0, 0, 4, 1, TRUE, ColorSet::MAGENTA, 3.0f);
#pragma endregion

}
