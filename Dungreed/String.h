#pragma once
namespace ImageName
{
	constexpr char* none = "IMG none";
	constexpr char* ChangeScene = "IMG ChangeScene";
	constexpr char* BossIntro = "IMG BossIntro";
	constexpr char* info = "IMG info";

	namespace Player
	{
		constexpr char* idle = "PLAYER idle";
		constexpr char* run  = "PLAYER run";
		constexpr char* jump = "PLAYER jump";
		constexpr char* die  = "PLAYER die";
		constexpr char* hand = "PLAYER hand";
		constexpr char* runFX = "PLAYER runFX";
		constexpr char* runEffectR = "PLAYER runEffectR";
		constexpr char* runEffectL = "PLAYER runEffectL";
		constexpr char* jumpEffect = "PLAYER jumpEffect";
		constexpr char* dashEffectR = "PLAYER dashEffectR";
		constexpr char* dashEffectL = "PLAYER dashEffectL";
	}

	namespace Enemy
	{
		constexpr char* sapwn	 = "ENEMY spawn";
		constexpr char* die		 = "ENEMY die";
		constexpr char* dieSmall = "ENEMY dieSmall";

		constexpr char* dogIdle = "ENEMY DogIdle";
		constexpr char* dogRun  = "ENEMY DogRun";
		constexpr char* dogDie  = "ENEMY DogDie";
		
		constexpr char* littleGhostIdle = "ENEMY littleGhostIdle";

		constexpr char* BansheeIdle = "ENEMY BansheeIdle";
		constexpr char* BansheeATK = "ENEMY BansheeATK";
		constexpr char* BansheeBullet = "ENEMY BansheeBullet";
		constexpr char* BansheeBulletFX = "ENEMY BansheeBulletFX";

		constexpr char* BatIdle = "ENEMY BatIdle";
		constexpr char* GiantBat = "ENEMY GiantBat";
		constexpr char* RedGiantBat = "ENEMY RedGiantBat";
		constexpr char* BatAttack = "ENEMY BatAttack";
		constexpr char* GiantBatAttack = "ENEMY GiantBatAttack";
		constexpr char* RedGiantBatAttack = "ENEMY RedGiantBatAttack";
		constexpr char* BatBullet = "ENEMY BatBullet";
		constexpr char* BatBulletHit = "ENEMY BatBulletHit";

		constexpr char* SkelIdle = "ENEMY SkelIdle";
		constexpr char* SkelWalk = "ENEMY SkelWalk";
		constexpr char* SkelSword = "ENEMY SkelSword";
		constexpr char* SkelBow = "ENEMY SkelBow";
		constexpr char* SkelArrow = "ENEMY SkelArrow";
		constexpr char* SkelArrowEffect = "ENEMY SkelArrowEffect";

		constexpr char* BigWhiteSkelIdle = "ENEMY BigWhiteSkelIdle";
		constexpr char* BigWhiteSkelMove = "ENEMY BigWhiteSkelMove";
		constexpr char* BigWhiteSkelAttack = "ENEMY BigWhiteSkelAttack";

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
			constexpr char* icicle = NIFLHEIM_NM"icicle";
			constexpr char* icicleFX = NIFLHEIM_NM"icicleFX";
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
			constexpr char* Exit = "BUTTON Exit";
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
			constexpr char* G = "FONT G";
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
			constexpr char* DashStart = "PLAYERHPBAR DashStart";
			constexpr char* DashEnd = "PLAYERHPBAR DashEnd";
			constexpr char* DashCount = "PLAYERHPBAR DashCount";
		}

		namespace MonsterHpBar
		{
			constexpr char* back = "MonsterHpBar back";
			constexpr char* gauge = "MonsterHpBar gauge";
			constexpr char* BossLifeBack = "MonsterHpBar BossLifeBack";
			constexpr char* BossLifeBase = "MonsterHpBar BossLifeBase";
			constexpr char* BossLifeGauge = "MonsterHpBar BossLifeGauge";
			constexpr char* BossSkellPortrait = "MonsterHpBar BossSkellPortrait";
		}

		namespace MiniMap
		{
			constexpr char* MapPixel = "MINIMAP MapPixel";
			constexpr char* PlayerPixel = "MINIMAP PlayerPixel";
			constexpr char* EnemyPixel = "MINIMAP EnemyPixel";
			constexpr char* DoorPixel = "MINIMAP DoorPixel";
			constexpr char* BorderPixel = "MINIMAP BorderPixel";
		}

		namespace Keyboard
		{
			constexpr char* F = "Keyboard F";
			constexpr char* Q = "Keyboard Q";
			constexpr char* ESC = "Keyboard ESC";
		}

		namespace Item
		{
			constexpr char* ItemInfo = "UI ITEM ItemInfo";
			constexpr char* Skill = "UI ITEM Skill";
			constexpr char* reloadBar = "UI ITEM reloadBar";
			constexpr char* reloadBase = "UI ITEM reloadBase";
			constexpr char* reloadEffect = "UI ITEM reloadEffect";
		}

		namespace NPC
		{
			constexpr char* ShopBase = "UI NPC ShopBase";
			constexpr char* DungeonShopBase = "UI NPC DungeonShopBase";
			constexpr char* ShopItem = "UI NPC ShopItem";
			constexpr char* ShopItem_Selected = "UI NPC ShopItem_Selected";

			constexpr char* FoodShopLabel = "UI NPC FoodShopLabel";
			constexpr char* Base_0 = "UI NPC Base_0";
			constexpr char* Base_3 = "UI NPC Base_3";
			constexpr char* RestaurantTable = "UI NPC RestaurantTable";
			constexpr char* RestaurantMenu = "UI NPC RestaurantMenu";
			constexpr char* RestaurantMenuSelected = "UI NPC RestaurantMenuSelected";
			constexpr char* RestaurantMenuSell = "UI NPC RestaurantMenuSell";
			constexpr char* RestaurantRect = "UI NPC RestaurantRect";
			constexpr char* GoldCoin = "UI NPC GoldCoin";
		}

		namespace FOOD
		{
			constexpr char* Bread = "FOOD 01_Bread";
			constexpr char* FriedEgg = "FOOD 02_FriedEgg";
			constexpr char* GrilledMushroom = "FOOD 03_GrilledMushroom";
			constexpr char* TamatoSoup = "FOOD 04_TamatoSoup";
			constexpr char* OnionSoup = "FOOD 05_OnionSoup";
			constexpr char* PeaSoup = "FOOD 06_PeaSoup";
			constexpr char* VegetableSalsaSoup = "FOOD 07_VegetableSalsaSoup";
			constexpr char* Lemonade = "FOOD 08_Lemonade";
			constexpr char* DeluxeBurger = "FOOD 09_DeluxeBurger";
			constexpr char* ChocolateCookie = "FOOD 10_ChocolateCookie";
		}

		namespace Ability
		{
			constexpr char* Label = "ABILITY Label";
		}
	}

	namespace NPC
	{
		constexpr char* Merchant = "NPC Merchant";
		constexpr char* Giant = "NPC Giant";
		constexpr char* BlackSmith = "NPC BlackSmith";
		constexpr char* Commander = "NPC Commander";
		constexpr char* Inn = "NPC Inn";
	}

	namespace Background
	{
		constexpr char* startCloud1 = "BgStartCloud1";
		constexpr char* startCloud2 = "BgStartCloud2";
		constexpr char* bgSky = "BgSky";
	}

	namespace Town
	{
		constexpr char* cloud = "TOWN Cloud";
		constexpr char* townBgDay = "TOWN BgDay";
		constexpr char* townLayerDay = "TOWN LayerDay";
		constexpr char* dungeonEat = "TOWN dungeonEat";
		constexpr char* BrokenTemple = "TOWN BrokenTemple";
		constexpr char* DogHouse = "TOWN DogHouse";
		constexpr char* DungeonSignL = "TOWN DungeonSignL";
		constexpr char* DungeonSignR = "TOWN DungeonSignR";
		constexpr char* Tree0 = "TOWN Tree0";
		constexpr char* Tree1 = "TOWN Tree1";
		constexpr char* Grass0 = "TOWN Grass0";
		constexpr char* Grass1 = "TOWN Grass1";
		constexpr char* Grass2 = "TOWN Grass2";
		constexpr char* Shop = "TOWN Shop";
		constexpr char* BrokenHouse0 = "TOWN BrokenHouse0";
		constexpr char* BrokenHouse1 = "TOWN BrokenHouse1";
		constexpr char* TrainingSchool = "TOWN TrainingSchool";
		constexpr char* BlackSmith = "TOWN BlackSmith";
		constexpr char* StreetLight_0 = "TOWN StreetLight_0";
		constexpr char* StreetLight_1 = "TOWN StreetLight_1";
		constexpr char* StreetLight_2 = "TOWN StreetLight_2";
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
			constexpr char* BambooSword = "WEAPON BambooSword";
			constexpr char* LightSaber = "WEAPON LightSaber";
			constexpr char* CosmosSword = "WEAPON CosmosSword";

			constexpr char* colt = "WEAPON Colt";
			constexpr char* GatlingGun = "WEAPON GatlingGun";
			constexpr char* Bullet02 = "WEAPON Bullet02";
			constexpr char* Bullet02_big = "WEAPON Bullet02_big";
			constexpr char* Bullet03 = "WEAPON Bullet03";
			constexpr char* Bullet03_big = "WEAPON Bullet03_big";
		}

		namespace Accessory
		{
			constexpr char* MultiBullet = "ACCESSORY MultiBullet";
			constexpr char* MagnifyingGlass = "ACCESSORY MagnifyingGlass";
			constexpr char* Wingboots = "ACCESSORY Wingboots";
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
			constexpr char* BambooSwing = "EFFECT BambooSwing";
			constexpr char* SwingFX = "EFFECT SwingFX";
			constexpr char* CosmosSwingFX = "EFFECT CosmosSwingFX";
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
		constexpr char* StartDoor = "DUNGEON StartDoor";
		constexpr char* Door = "DUNGEON Door";
		constexpr char* DoorLeft = "DUNGEON DoorLeft";
		constexpr char* DoorRight = "DUNGEON DoorRight";

		constexpr char* bgLayer0 = "DUNGEON bgLayer0";
		constexpr char* bgLayer1 = "DUNGEON bgLayer1";
		constexpr char* Snow = "DUNGEON Snow";
		constexpr char* subBg = "DUNGEON subBg";

		constexpr char* BasicTresure = "DUNGEON BasicTresure";
		constexpr char* GoldTresure = "DUNGEON GoldTresure";
		constexpr char* BlueTresure = "DUNGEON BlueTresure";
		constexpr char* BossTresure = "DUNGEON BossTresure";

		constexpr char* DungeonInn = "DUNGEON DungeonInn";
		constexpr char* InDungeonShop = "DUNGEON InDungeonShop";
	}

}

namespace SoundName
{
	constexpr char* title = "SOUND title";
	constexpr char* town = "SOUND town";
	constexpr char* dungeon = "SOUND dungeon";
	constexpr char* belialBG = "SOUND belialBG";
	constexpr char* IceDungeon = "SOUND IceDungeon";
	constexpr char* niflheimBG = "SOUND 2.IceBoss";
	constexpr char* dungeonEat = "SOUND dungeonEat";
	constexpr char* dungeonEat2 = "SOUND dungeonEat2";
	constexpr char* invenOpen = "SOUND invenOpen";
	constexpr char* swapEquip = "SOUND swapEquip";
	constexpr char* FireBall = "SOUND FireBall";
	constexpr char* TestScene = "SOUND TestScene";
	constexpr char* MapTool = "SOUND MapTool";
	constexpr char* Foodshop = "SOUND Foodshop";
	constexpr char* BuyFood = "SOUND BuyFood";

	namespace Player
	{
		constexpr char* dash = "SOUND PLAYER dash";
		constexpr char* hit = "SOUND PLAYER hit";
		constexpr char* Jumping = "SOUND PLAYER Jumping";
		constexpr char* step_lth1 = "SOUND PLAYER step_lth1";
	}

	namespace Enemy
	{
		constexpr char* hit = "SOUND ENEMY hit";
		constexpr char* SpawnEnemy = "SOUND ENEMY SpawnEnemy";
		constexpr char* MonsterDie = "SOUND ENEMY MonsterDie";
		// 몬스터
		constexpr char* BansheeATK = "SOUND ENEMY Banshee_ATK";
		constexpr char* Bat = "SOUND ENEMY Bat";
		constexpr char* Bat_giant = "SOUND ENEMY Bat_giant";
		constexpr char* Bat_red = "SOUND ENEMY Bat_red";
		constexpr char* arrow_load = "SOUND ENEMY arrow_load";
		constexpr char* arrow_shoot = "SOUND ENEMY arrow_shoot";

		// 보스
		constexpr char* Skeletonking = "SOUND ENEMY Skeletonking";
		constexpr char* BelialBullet = "SOUND ENEMY BelialBullet";
		constexpr char* BelialLazer = "SOUND ENEMY BelialLazer";
		constexpr char* BelialSword = "SOUND ENEMY BelialSword";
		constexpr char* BelialSwordShoot = "SOUND ENEMY BelialSwordShoot";
		constexpr char* niflheim_start = "SOUND ENEMY niflheim_start";
		constexpr char* NiflheimBullet = "SOUND ENEMY NiflheimBullet";
	}

	namespace Item
	{
		constexpr char* coin		= "SOUND ITEM coin";
		constexpr char* getCoin		= "SOUND ITEM getCoin";
		constexpr char* getItem		= "SOUND ITEM getItem";
		constexpr char* Equip		= "SOUND ITEM Equip";
		constexpr char* PickUpItem	= "SOUND ITEM PickUpItem";
		constexpr char* Reload = "SOUND Reload";
		constexpr char* Reload2		= "SOUND Reload2";

		namespace Weapon
		{
			constexpr char* swing0 = "SOUND swing0";
			constexpr char* swing1 = "SOUND swing1";
			constexpr char* swing2 = "SOUND swing2";
			constexpr char* swing5 = "SOUND swing5";
			constexpr char* LightSaver = "SOUND LightSaver";
			constexpr char* Gun = "SOUND Gun";
			constexpr char* GatlingGun = "SOUND GatlingGun";
		}
	}

	namespace Dungeon
	{
		constexpr char* DoorMove = "SOUND DUNGEON DoorMove";
		constexpr char* OpenTresure = "SOUND DUNGEON OpenTresure";
		constexpr char* CloseSteelDoor = "SOUND DUNGEON CloseSteelDoor";
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
	constexpr char* DungeonShop = "DungeonShop";
	constexpr char* DungeonFood = "DungeonFood";
	constexpr char* Dungeon01 = "Dungeon01";
	constexpr char* Dungeon02 = "Dungeon02";
	constexpr char* Dungeon03 = "Dungeon03";
	constexpr char* Dungeon04 = "Dungeon04";
	constexpr char* Dungeon05 = "Dungeon05";
	constexpr char* Dungeon06 = "Dungeon06";
	constexpr char* Dungeon07 = "Dungeon07";
	constexpr char* Dungeon08 = "Dungeon08";
	constexpr char* Dungeon09 = "Dungeon09";
	constexpr char* Dungeon10 = "Dungeon10";
	constexpr char* Dungeon11 = "Dungeon11";

	constexpr char* Belial = "Belial";
	constexpr char* Niflheim = "Niflheim";
}

namespace FontName
{
	constexpr char* num = "neo둥근모";
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
