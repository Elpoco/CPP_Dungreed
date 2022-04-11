#pragma once
namespace ImageName
{
	namespace Player
	{
		constexpr char* idle = "PlayerIdle";
		constexpr char* run = "PlayerRun";
		constexpr char* jump = "PlayerJump";
		constexpr char* die = "PlayerDie";
		constexpr char* hand = "PlayerHand";
	}

	namespace Enemy
	{
		constexpr char* enemySpawn = "EnemySpawn";
		constexpr char* enemyDie = "EnemyDie";
		constexpr char* enemyDieSmall = "EnemyDieSmall";

		constexpr char* dogIdle = "DogIdle";
		constexpr char* dogRun = "DogRun";
		constexpr char* dogDie = "DogDie";
		
		constexpr char* littleGhostIdle = "littleGhostIdle";

		namespace Belial
		{
			constexpr char* idle		 = "BelialIdle";
			constexpr char* attack		 = "BelialAttack";
			constexpr char* back		 = "BelialBack";
			constexpr char* particle	 = "BelialParticle";
			constexpr char* bullet		 = "BelialBullet";
			constexpr char* bulletEffect = "BelialBulletEffect";
			constexpr char* hand		 = "BelialHand";
			constexpr char* handAttack   = "BelialHandAttack";
			constexpr char* sword		 = "BelialSword";
			constexpr char* swordEffect  = "BelialSwordEffect";
			constexpr char* laserHeadL	 = "BelialLaserHeadL";
			constexpr char* laserHeadR	 = "BelialLaserHeadR";
			constexpr char* laserBody	 = "BelialLaserBody";
		}

		namespace Niflheim
		{
			constexpr char* idle = "NiflheimIdle";
		}
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

	constexpr char* logo = "Logo";
	constexpr char* cloud1 = "Cloud1";
	constexpr char* cloud2 = "Cloud2";
	constexpr char* background = "Background";

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
