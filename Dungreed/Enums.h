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
	enum class TILE_TYPE
	{
		NONE,
		BLOCK,
		DIG_L,
		DIG_R
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
		LBOTTOM,
		RBOTTOM,
		DIR_CNT
	};
}

namespace ObjectEnum
{
	enum class TYPE
	{
		PLAYER,
		ITEM,
		ENEMY,
		NPC,
	};
}