#pragma once
namespace ImageName
{
	constexpr char* none = "IMG none";

	namespace Player
	{
		constexpr char* idle = "PLAYER idle";
		constexpr char* run  = "PLAYER run";
		constexpr char* jump = "PLAYER jump";
		constexpr char* die  = "PLAYER die";
		constexpr char* hand = "PLAYER hand";
		constexpr char* runFX = "PLAYER runFX";
	}

	namespace Enemy
	{
		constexpr char* sapwn	 = "ENEMY spawn";
		constexpr char* die		 = "ENEMY die";
		constexpr char* dieSmall = "ENEMY dieSmall";

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
			constexpr char* Damage = "FontDamage";
			constexpr char* Gold = "FontGold";
		}

		namespace Inventory
		{
			constexpr char* Base = "INVENTORY Base";
			constexpr char* on = "INVENTORY on";
			constexpr char* equipBase = "INVENTORY equipBase";
			constexpr char* exitBtn = "INVENTORY exitBtn";
			constexpr char* Cell = "INVENTORY Cell";
			constexpr char* Accessory = "INVENTORY Accessory";
			constexpr char* EquipSlot1On = "INVENTORY EquipSlot1On";
			constexpr char* EquipSlot2On = "INVENTORY EquipSlot2On";
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
			constexpr char* colt = "WEAPON Colt";
			constexpr char* bullet02 = "WEAPON bullet02";
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
			constexpr char* basicSwing = "EFFECT BasicSwing";
			constexpr char* shooting = "EFFECT Shooting";
			constexpr char* shootingHit = "EFFECT ShootingHit";
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
	constexpr char* swapEquip = "SOUND swapEquip";

	namespace Item
	{
		constexpr char* getCoin = "SOUND getCoin";
		constexpr char* getItem = "SOUND getItem";
		constexpr char* Equip = "SOUND Equip";
		constexpr char* PickUpItem = "SOUND PickUpItem";

		namespace Weapon
		{
			constexpr char* swing2 = "SOUND swing0";
			constexpr char* Gun = "SOUND Gun";
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
