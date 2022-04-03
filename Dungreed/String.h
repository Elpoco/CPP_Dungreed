#pragma once
namespace ImageName
{
	namespace Player
	{
		constexpr char* idle = "PlayerIdle";
		constexpr char* run = "PlayerRun";
		constexpr char* die = "PlayerDie";
		constexpr char* hand = "PlayerHand";
	}

	namespace Enemy
	{
		constexpr char* dogIdle = "dogIdle";
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
}

namespace SceneName
{
	constexpr char* testScene = "Test";
	constexpr char* startScene = "Start";
	constexpr char* mapToolScene = "MapTool";
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
