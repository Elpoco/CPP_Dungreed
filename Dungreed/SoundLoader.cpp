#include "Stdafx.h"
#include "SoundLoader.h"

SoundLoader::SoundLoader()
{
}

SoundLoader::~SoundLoader()
{
}

HRESULT SoundLoader::init()
{
	loadSounds();

	return S_OK;
}

void SoundLoader::release()
{
}

void SoundLoader::loadSounds()
{
	// =============
	// # Backgound #
	// =============
	SOUNDMANAGER->addSound(SoundName::title, PATH_SOUND"Title.wav", true, true);
	SOUNDMANAGER->addSound(SoundName::town, PATH_SOUND"BGM_Town.wav", true, true);
	SOUNDMANAGER->addSound(SoundName::dungeon, PATH_SOUND"JailField.wav", true, true);
	SOUNDMANAGER->addSound(SoundName::belialBG, PATH_SOUND"JailBoss.wav", true, true);
	SOUNDMANAGER->addSound(SoundName::IceDungeon, PATH_SOUND"2.IceField.wav", true, true);
	SOUNDMANAGER->addSound(SoundName::niflheimBG, PATH_SOUND"2.IceBoss.wav", true, true);

	SOUNDMANAGER->addSound(SoundName::dungeonEat, PATH_SOUND"DungeonEat.wav", false, false);
	SOUNDMANAGER->addSound(SoundName::dungeonEat2, PATH_SOUND"DungeonEat2.wav", false, false);

	// ==========
	// # Player #
	// ==========
	SOUNDMANAGER->addSound(SoundName::Player::dash, PATH_SOUND"Dash.wav", false, false);
	SOUNDMANAGER->addSound(SoundName::Player::hit, PATH_SOUND"Hit_Player.wav", false, false);
	SOUNDMANAGER->addSound(SoundName::Player::Jumping, PATH_SOUND"Jumping.wav", false, false);

	// =========
	// # Enemy #
	// =========
	SOUNDMANAGER->addSound(SoundName::Enemy::hit, PATH_SOUND"Hit_Monster.wav", false, false);
	SOUNDMANAGER->addSound(SoundName::Enemy::SpawnEnemy, PATH_SOUND"SpawnMonster.wav", false, false);
	SOUNDMANAGER->addSound(SoundName::Enemy::MonsterDie, PATH_SOUND"MonsterDie.wav", false, false);
	// 몬스터
	SOUNDMANAGER->addSound(SoundName::Enemy::BansheeATK, PATH_SOUND"Banshee_ATK.wav", false, false);

	// 보스
	SOUNDMANAGER->addSound(SoundName::Enemy::Skeletonking, PATH_SOUND"Skeletonking.wav", false, false);
	SOUNDMANAGER->addSound(SoundName::Enemy::BelialBullet, PATH_SOUND"BelialBullet.wav", false, false);
	SOUNDMANAGER->addSound(SoundName::Enemy::BelialLazer, PATH_SOUND"Belial_lazer.wav", false, false);
	SOUNDMANAGER->addSound(SoundName::Enemy::BelialSword, PATH_SOUND"Belial_sword.wav", false, false);
	SOUNDMANAGER->addSound(SoundName::Enemy::BelialSwordShoot, PATH_SOUND"Belial_sword_shoot.wav", false, false);
	SOUNDMANAGER->addSound(SoundName::Enemy::niflheim_start, PATH_SOUND"niflheim_start.wav", false, false);
	SOUNDMANAGER->addSound(SoundName::Enemy::NiflheimBullet, PATH_SOUND"NiflheimBullet.wav", false, false);

	// ========
	// # Item #
	// ========
	SOUNDMANAGER->addSound(SoundName::invenOpen, PATH_SOUND"Inventory_open.wav", false, false);
	SOUNDMANAGER->addSound(SoundName::swapEquip, PATH_SOUND"Swap_weapon.wav", false, false);

	SOUNDMANAGER->addSound(SoundName::Item::coin, PATH_SOUND"coin.wav", false, false);
	SOUNDMANAGER->addSound(SoundName::Item::Equip, PATH_SOUND"Equip.wav", false, false);
	SOUNDMANAGER->addSound(SoundName::Item::getCoin, PATH_SOUND"Get_Coin.wav", false, false);
	SOUNDMANAGER->addSound(SoundName::Item::getItem, PATH_SOUND"Get_Item.wav", false, false);
	SOUNDMANAGER->addSound(SoundName::Item::PickUpItem, PATH_SOUND"PickUpItem.wav", false, false);

	// ==========
	// # Weapon #
	// ==========
	SOUNDMANAGER->addSound(SoundName::Item::Weapon::swing2, PATH_SOUND"swing2.wav", false, false);
	SOUNDMANAGER->addSound(SoundName::Item::Weapon::Gun, PATH_SOUND"Gun.wav", false, false);
	SOUNDMANAGER->addSound(SoundName::Item::Reload2, PATH_SOUND"Reload2.wav", false, false);

	// ===========
	// # Dungeon #
	// ===========
	SOUNDMANAGER->addSound(SoundName::Dungeon::DoorMove, PATH_SOUND"Door_move.wav", false, false);
	SOUNDMANAGER->addSound(SoundName::Dungeon::OpenTresure, PATH_SOUND"open_tresure.wav", false, false);

}
