#pragma once

enum KEY
{
	LEFT = 'A',
	UP = 'W',
	RIGHT = 'D',
	DOWN = 'S',

	UP_ARROW = VK_UP,
	DOWN_ARROW = VK_DOWN,
	LEFT_ARROW = VK_LEFT,
	RIGHT_ARROW = VK_RIGHT,

	SPACE = VK_SPACE,
	ESC = VK_ESCAPE,

	CLICK_L = VK_LBUTTON,
	CLICK_R = VK_RBUTTON,

	// 키보드
	F1 = VK_F1, F2 = VK_F2, F3 = VK_F3, F4 = VK_F4,
	F5 = VK_F5, F6 = VK_F6, F7 = VK_F7, F8 = VK_F8,
	F9 = VK_F9, F10 = VK_F10, F11 = VK_F11, F12 = VK_F12,
	F = 'F', 

	// 플레이어
	INVENTORY = 'V',
	CHANGE_EQUIP = 192,
};

namespace MapToolEnum
{
	enum MAP_OBJ
	{
		NONE,
		BLOCK,
		BLOCK_R, // 올라가는 방향
		BLOCK_L,
		DOWN,
		DOWN_R,
		DOWN_L,
		OBJECT_CNT
	};
}

namespace Direction
{
	enum DIR
	{
		LEFT,
		TOP,
		RIGHT,
		BOTTOM,
		DIR_CNT,
		NONE
	};
}

namespace ObjectEnum
{
	enum class OBJ_TYPE
	{
		EFFECT_BACK,
		NPC,
		DUNGEON_OBJ,
		DUNGEON,
		ENEMY,
		ENEMY_OBJ,
		PLAYER,
		ITEM_DROP,
		ITEM,
		PLAYER_OBJ,
		EFFECT,
		UI,
		BUTTON,
		ITEM_FRONT,
		UI_FRONT,

		TYPE_CNT
	};
}

namespace Code
{
	enum class UNIT
	{
		PLAYER,

		// 몬스터
		SKEL_DOG,
		LITTLE_GHOST,
		BANSHEE,

		// 보스
		BELIAL,
		NIFLEHEIM,
		NIFLEHEIM_PILLAR,

		UNIT_CNT,
		NONE
	};

	enum class ITEM_TYPE
	{
		GOLD,
		WEAPON,
		ARMOR,
		ACCESSORY,

		ITEM_TYPE_CNT
	};

	enum class ITEM
	{
		COIN,
		BULLION,

		ITEM,
		// 무기
		SHOT_SWORD,
		GREAT_SWORD,
		COLT,

		ITEM_CNT
	};

	enum class MAP
	{
		// ┌ ┬ ┐
		// ├ ┼ ┤
		// └ ┴ ┘
		// │ ─

		// ┌┬─┐
		DUNGEON_04, // ┌
		DUNGEON_05, // ┬
		DUNGEON_SHOP, // ─
		DUNGEON_06, // ┐

		// ├┴┬┘
		DUNGEON_START, // ├
		DUNGEON_01, // ┴
		DUNGEON_02, // ┬
		DUNGEON_07, // ┘

		// └┬┴─
		DUNGEON_03, // └
		DUNGEON_08, // ┬
		DUNGEON_09, // ┴
		BELIAL, // ─

		// ─┴──
		DUNGEON_10, // ─
		DUNGEON_11, // ┴
		DUNGEON_FOOD, // ─
		NIFLHEIM, // ─

		// ┌┬─┐
		// ├┴┬┘
		// └┬┴─
		// ─┴──
		MAP_CNT,
	};
}

namespace ImageFontEnum
{
	enum class FONT_TYPE
	{
		NORMAL,
		DAMAGE,
		GOLD,

		FONT_CNT
	};

	enum FONT_KIND
	{
		NUM,
		ENG_SM,
		ENG,
		SPC_CHAR,

		KIND_CNT
	};

	enum class FONT_SIZE
	{
		SMALL,
		MIDDLE,
		LARGE
	};
}

namespace UIEnum
{
	enum CURSOR_TYPE
	{
		NONE,
		NORMAL,
		TARGET
	};
}

namespace LocationEnum
{
	enum class LOCATION
	{
		TOWN,
		DUNGEON
	};
}
