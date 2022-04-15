#pragma once
namespace ImageName
{
	constexpr char* none = "IMG none";

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
		constexpr char* sapwn	 = "ENEMY_spawn";
		constexpr char* die		 = "ENEMY_die";
		constexpr char* dieSmall = "ENEMY_dieSmall";

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
		constexpr char* logo = "UI logo";
		constexpr char* bird = "UI bird";

		namespace Button
		{
			constexpr char* gameStart = "BUTTON gameStart";
			constexpr char* mapTool = "BUTTON mapTool";
			constexpr char* quit = "BUTTON quit";
		}

		namespace Cursor
		{
			constexpr char* cursor = "CURSOR Cursor";
			constexpr char* attack = "CURSOR attack";
		}

		namespace Font
		{	
			constexpr char* damage = "FontDamage";
			constexpr char* gold = "FontGold";
		}

		namespace Inventory
		{
			constexpr char* base = "INVENTORY base";
			constexpr char* btn = "INVENTORY btn";
			constexpr char* Cell = "INVENTORY Cell";
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
			constexpr char* basicShotSword = "WEAPON BasicShotSword";
			constexpr char* basicShotSwordInven = "WEAPON BasicShotSwordInven";
			constexpr char* colt = "WEAPON Colt";
			constexpr char* coltInven = "WEAPON ColtInven";
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
	constexpr char* title = "SOUND title";
	constexpr char* invenOpen = "SOUND invenOpen";

	namespace Item
	{
		constexpr char* getCoin = "SOUND getCoin";
		constexpr char* getItem = "SOUND getItem";

		namespace Weapon
		{
			constexpr char* swing2 = "SOUND swing0";
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
