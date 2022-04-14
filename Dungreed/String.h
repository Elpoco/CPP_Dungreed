#pragma once
namespace ImageName
{
	namespace Player
	{
		constexpr char* idle = "PLAYER_idle";
		constexpr char* run  = "PLAYER_run";
		constexpr char* jump = "PLAYER_jump";
		constexpr char* die  = "PLAYER_die";
		constexpr char* hand = "PLAYER_hand";
	}

	namespace Enemy
	{
		constexpr char* enemySpawn	  = "EnemySpawn";
		constexpr char* enemyDie	  = "EnemyDie";
		constexpr char* enemyDieSmall = "EnemyDieSmall";

		constexpr char* dogIdle = "DogIdle";
		constexpr char* dogRun  = "DogRun";
		constexpr char* dogDie  = "DogDie";
		
		constexpr char* littleGhostIdle = "littleGhostIdle";

		namespace Belial
		{
#define BELIAL_NM "Belial"
			constexpr char* idle		 = BELIAL_NM"Idle";
			constexpr char* attack		 = BELIAL_NM"Attack";
			constexpr char* back		 = BELIAL_NM"Back";
			constexpr char* particle	 = BELIAL_NM"Particle";
			constexpr char* bullet		 = BELIAL_NM"Bullet";
			constexpr char* bulletEffect = BELIAL_NM"BulletEffect";
			constexpr char* hand		 = BELIAL_NM"Hand";
			constexpr char* handAttack   = BELIAL_NM"HandAttack";
			constexpr char* sword		 = BELIAL_NM"Sword";
			constexpr char* swordEffect  = BELIAL_NM"SwordEffect";
			constexpr char* laserHeadL	 = BELIAL_NM"LaserHeadL";
			constexpr char* laserHeadR	 = BELIAL_NM"LaserHeadR";
			constexpr char* laserBody	 = BELIAL_NM"LaserBody";
		}

		namespace Niflheim
		{
#define NIFLHEIM_NM "Niflheim"
			constexpr char* idle	 = NIFLHEIM_NM"Idle";
			constexpr char* attack   = NIFLHEIM_NM"Attack";
			constexpr char* pillar   = NIFLHEIM_NM"Pillar";
			constexpr char* bullet   = NIFLHEIM_NM"Bullet";
			constexpr char* bulletFX = NIFLHEIM_NM"BulletFX";
		}
	}

	namespace UI
	{
		constexpr char* logo = "StartSceneLogo";

		namespace Button
		{
			constexpr char* startOff = "BtnGameStartOff";
			constexpr char* startOn = "BtnGameStartOn";
			constexpr char* mapToolOff = "BtnMapToolOff";
			constexpr char* mapToolOn = "BtnMapToolOn";
			constexpr char* quitOff = "BtnQuitOff";
			constexpr char* quitOn = "BtnQuitOn";
		}

		namespace Cursor
		{
			constexpr char* cursor = "Cursor";
		}

		namespace Font
		{
			constexpr char* damage = "FontDamage";
			constexpr char* gold = "FontGold";
		}
	}

	namespace Background
	{
		constexpr char* startCloud1 = "BgStartCloud1";
		constexpr char* startCloud2 = "BgStartCloud2";
		constexpr char* bgSky = "BgSky";
	}

	namespace Town
	{
		constexpr char* cloud = "TownCloud";
		constexpr char* townBgDay = "TownBgDay";
		constexpr char* townLayerDay = "TownLayerDay";
	}

	constexpr char* mapTile = "MapTile";
	constexpr char* mapToolTile = "MapToolTile";
	constexpr char* mapPixel = "MapPixel";

	constexpr char* floor = "Floor";

	namespace Item
	{
		namespace Weapon
		{
			constexpr char* basicShotSword = "BasicShotSword";
		}

		namespace Gold
		{
			constexpr char* coin = "GoldCoin";
			constexpr char* bullion = "Bullion";
		}
	}

	namespace Effect
	{
		namespace Weapon
		{
			constexpr char* effectBasic = "EffectBasic";
		}
	}

	namespace Object
	{
		constexpr char* box = "OBJECT_box";
	}
}

namespace SoundName
{
	constexpr char* title = "SOUND_title";

	namespace Item
	{
		constexpr char* collecting = "SOUND_collecting";
	}
}

namespace SceneName
{
	constexpr char* testScene = "Test";
	constexpr char* startScene = "Start";
	constexpr char* mapToolScene = "MapTool";
	constexpr char* townScene = "Town";
}

namespace String
{
	constexpr char* tagImage = "IMAGE: ";

	constexpr char* btnSave = "SAVE";
	constexpr char* btnLoad = "LOAD";
	constexpr char* msgSaveSuccess = "Save success";
	constexpr char* msgSaveFail = "Save failed";
	constexpr char* msgLoadSuccess = "Load success";
	constexpr char* msgLoadFail = "Load failed";

	constexpr char* tempSaveFile = "testSave.dat";
}
