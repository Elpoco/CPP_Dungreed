#pragma once
namespace ImageName
{
	constexpr char* none = "IMG none";
	constexpr char* ChangeScene = "IMG ChangeScene";

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
			constexpr char* Normal_s = "FONT Normal_s";
			constexpr char* Normal = "FONT Normal";
			constexpr char* Damage = "FONT Damage";
			constexpr char* Gold = "FONT Gold";
		}

		namespace Inventory
		{
			constexpr char* Base = "INVENTORY Base";
			constexpr char* on = "INVENTORY on";
			constexpr char* equipBase = "INVENTORY equipBase";
			constexpr char* exitBtn = "INVENTORY exitBtn";
			constexpr char* Cell = "INVENTORY Cell";
			constexpr char* Cell_On = "INVENTORY Cell_On";
			constexpr char* Accessory = "INVENTORY Accessory";
			constexpr char* EquipSlot1On = "INVENTORY EquipSlot1On";
			constexpr char* EquipSlot2On = "INVENTORY EquipSlot2On";
		}

		namespace PlayerHpBar
		{
			constexpr char* Base = "PLAYERHPBAR Base";
			constexpr char* Back = "PLAYERHPBAR Back";
			constexpr char* LifeBar = "PLAYERHPBAR LifeBar";
			constexpr char* LifeWave = "PLAYERHPBAR LifeWave";
		}

		namespace MonsterHpBar
		{
			constexpr char* back = "MonsterHpBar back";
			constexpr char* gauge = "MonsterHpBar gauge";
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
		constexpr char* dungeonEat = "TOWN dungeonEat";
	}

	namespace MapTool
	{
		constexpr char* mapTile = "MAPTOOL MapTile";
		constexpr char* mapObject = "MAPTOOL Object";
		constexpr char* mapToolObject = "MAPTOOL ToolObject";
		constexpr char* mapToolTile = "MAPTOOL MapToolTile";
		constexpr char* button = "MAPTOOL button";
		constexpr char* box = "MAPTOOL box";
	}
	
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

	namespace Dungeon
	{
		constexpr char* sqaure1 = "DUNGEON sqaure1";
		constexpr char* sqaure2 = "DUNGEON sqaure2";
		constexpr char* sqaure3 = "DUNGEON sqaure3";
		constexpr char* sqaure4 = "DUNGEON sqaure4";
		constexpr char* sqaure5 = "DUNGEON sqaure5";
		constexpr char* doorUp = "DUNGEON doorUp";
		constexpr char* Door = "DUNGEON Door";
		constexpr char* DoorLeft = "DUNGEON DoorLeft";
		constexpr char* DoorRight = "DUNGEON DoorRight";
	}
}

namespace SoundName
{
	constexpr char* title = "SOUND title";
	constexpr char* town = "SOUND town";
	constexpr char* dungeon = "SOUND dungeon";
	constexpr char* belialBG = "SOUND belialBG";
	constexpr char* niflheimBG = "SOUND 2.IceBoss";
	constexpr char* dungeonEat = "SOUND dungeonEat";
	constexpr char* dungeonEat2 = "SOUND dungeonEat2";
	constexpr char* invenOpen = "SOUND invenOpen";
	constexpr char* swapEquip = "SOUND swapEquip";

	namespace Player
	{
		constexpr char* dash = "SOUND PLAYER dash";
		constexpr char* hit = "SOUND PLAYER hit";
	}

	namespace Enemy
	{
		constexpr char* hit = "SOUND ENEMY hit";
		constexpr char* SpawnEnemy = "SOUND ENEMY SpawnEnemy";
		constexpr char* MonsterDie = "SOUND ENEMY MonsterDie";
		constexpr char* Skeletonking = "SOUND ENEMY Skeletonking";
		constexpr char* BelialBullet = "SOUND ENEMY BelialBullet";
		constexpr char* niflheim_start = "SOUND ENEMY niflheim_start";
		constexpr char* NiflheimBullet = "SOUND ENEMY NiflheimBullet";
	}

	namespace Item
	{
		constexpr char* getCoin		= "SOUND ITEM getCoin";
		constexpr char* getItem		= "SOUND ITEM getItem";
		constexpr char* Equip		= "SOUND ITEM Equip";
		constexpr char* PickUpItem	= "SOUND ITEM PickUpItem";
		constexpr char* Reload2		= "SOUND Reload2";

		namespace Weapon
		{
			constexpr char* swing2 = "SOUND swing0";
			constexpr char* Gun = "SOUND Gun";
		}
	}

	namespace Dungeon
	{
		constexpr char* DoorMove = "SOUND DUNGEON DoorMove";
	}
}

namespace SceneName
{
	constexpr char* testScene = "Test";
	constexpr char* startScene = "Start";
	constexpr char* mapToolScene = "MapTool";
	constexpr char* gameScene = "Game";
}

namespace FileName
{
	constexpr char* testSave = "testSave";
	constexpr char* Town = "Town";
	constexpr char* DungeonStart = "DungeonStart";
	constexpr char* Dungeon01 = "Dungeon01";
	constexpr char* Dungeon02 = "Dungeon02";
	constexpr char* Belial = "Belial";
}

namespace FontName
{
	constexpr char* num = "neoµÕ±Ù¸ð";
	constexpr char* text = "AaCassiopeia";
}

namespace String
{
	constexpr char* tagImage = "IMAGE: ";

	constexpr char* btnSave = "SAVE";
	constexpr char* btnLoad = "LOAD";
	constexpr char* btnQuit = "QUIT";
	constexpr char* msgSaveSuccess = "Save success";
	constexpr char* msgSaveFail = "Save failed";
	constexpr char* msgLoadSuccess = "Load success";
	constexpr char* msgLoadFail = "Load failed";
}
