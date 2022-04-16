#pragma once

enum KEY
{
	LEFT  =	'A',
	UP	  =	'W',
	RIGHT = 'D',
	DOWN  =	'S',

	UP_ARROW = VK_UP,
	DOWN_ARROW = VK_DOWN,
	LEFT_ARROW = VK_LEFT,
	RIGHT_ARROW = VK_DOWN,

	SPACE = VK_SPACE,
	ESC	  = VK_ESCAPE,

	CLICK_L = VK_LBUTTON,
	CLICK_R = VK_RBUTTON,

	// 플레이어
	INVENTORY = 'V',
};

namespace MapToolEnum
{
	enum class TYPE
	{
		NONE,
		BLOCK,
		DIG_L,
		DIG_R,
		PLATFORM,
		WALLPAPER
	};

	enum class TERRAIN
	{
		TR_NONE,
		TR_WALL
	};

	enum class MAP_OBJECT
	{
		MO_NONE,
		MO_BLOCK,
		MO_DIG_L,
		MO_DIG_R,
		MO_PLATFORM
	};
}

namespace ColliderEnum
{
	enum DIRECTION
	{
		LEFT,
		TOP,
		RIGHT,
		BOTTOM,
		LT,
		RT,
		LB,
		RB,
		DIR_CNT,
		NONE
	};
}

namespace ObjectEnum
{
	enum class TYPE
	{
		// 밑으로 갈수록 랜더를 나중에 함
		EFFECT_BACK,
		NPC,
		ENEMY,
		ENEMY_OBJ,
		ITEM_DROP,
		PLAYER,
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
		SKEL_DOG,
		LITTLE_GHOST,
		BELIAL,
		NIFLEHEIM,
		NIFLEHEIM_PILLAR,

		UNIT_CNT
	};

	enum class ITEM_TYPE
	{
		GOLD,
		WEAPON,
		ARMOR,

		ITEM_TYPE_CNT
	};

	enum class ITEM
	{
		COIN,
		BULLION,

		// 무기
		SHOT_SWORD,
		GREAT_SWORD,
		COLT,

		ITEM_CNT
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