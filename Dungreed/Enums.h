#pragma once

enum KEY
{
	LEFT  =	'A',
	UP	  =	'W',
	RIGHT = 'D',
	DOWN  =	'S'
};

namespace MapToolEnum
{
	enum class TYPE : unsigned char
	{
		NONE,
		BLOCK,
		DIG_L,
		DIG_R,
		PLATFORM,
		WALLPAPER
	};

	enum class TERRAIN : unsigned char
	{
		TR_NONE,
		TR_WALL
	};

	enum class MAP_OBJECT : unsigned char
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
		EFFECT_BACK,
		NPC,
		ENEMY,
		ENEMY_OBJ,
		ITEM_DROP,
		ITEM,
		PLAYER,
		PLAYER_OBJ,
		EFFECT,
		BUTTON,
		UI,
		UI_FRONT,
		TYPE_CNT
	};
}

namespace Code
{
	enum class Unit
	{
		PLAYER,
		SKEL_DOG,
		LITTLE_GHOST,
		BELIAL,
		NIFLEHEIM,

		UNIT_CNT
	};
}