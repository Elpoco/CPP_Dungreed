#pragma once
namespace ImageName
{
	namespace Player
	{
		constexpr char* idle = "PlayerIdle";
		constexpr char* run  = "PlayerRun";
		constexpr char* jump = "PlayerJump";
		constexpr char* die  = "PlayerDie";
		constexpr char* hand = "PlayerHand";
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
#define BELIAL "Belial"
			constexpr char* idle		 = BELIAL"Idle";
			constexpr char* attack		 = BELIAL"Attack";
			constexpr char* back		 = BELIAL"Back";
			constexpr char* particle	 = BELIAL"Particle";
			constexpr char* bullet		 = BELIAL"Bullet";
			constexpr char* bulletEffect = BELIAL"BulletEffect";
			constexpr char* hand		 = BELIAL"Hand";
			constexpr char* handAttack   = BELIAL"HandAttack";
			constexpr char* sword		 = BELIAL"Sword";
			constexpr char* swordEffect  = BELIAL"SwordEffect";
			constexpr char* laserHeadL	 = BELIAL"LaserHeadL";
			constexpr char* laserHeadR	 = BELIAL"LaserHeadR";
			constexpr char* laserBody	 = BELIAL"LaserBody";
		}

		namespace Niflheim
		{
#define NIFLHEIM "Niflheim"
			constexpr char* idle	 = NIFLHEIM"Idle";
			constexpr char* attack   = NIFLHEIM"Attack";
			constexpr char* pillar   = NIFLHEIM"Pillar";
			constexpr char* bullet   = NIFLHEIM"Bullet";
			constexpr char* bulletFX = NIFLHEIM"BulletFX";
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
	
	constexpr char* pixelTest = "PixelTest";
	constexpr char* testTile = "TestTile";

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
	}

	namespace Effect
	{
		namespace Weapon
		{
			constexpr char* effectBasic = "EffectBasic";
		}
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
