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

		constexpr char* dogIdle = "DogIdle";
		constexpr char* dogRun = "DogRun";
		constexpr char* dogDie = "DogDie";
		
		constexpr char* littleGhostIdle = "littleGhostIdle";

		constexpr char* belialIdle = "BelialIdle";
		constexpr char* belialAttack = "BelialAttack";
		constexpr char* belialBack = "BelialBack";
		constexpr char* belialBullet = "BelialBullet";
		constexpr char* belialBulletEffect = "BelialBulletEffect";
		constexpr char* belialHandL = "BelialHandL";
		constexpr char* belialHandR = "BelialHandR";
		constexpr char* belialSword = "BelialSword";
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
