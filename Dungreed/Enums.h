#pragma once

enum class KEY
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
		BLOCK
	};
}

namespace PlayerEnum
{
	enum PLAYER_STATE
	{
		IDLE,
		RUN,
		JUMP
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
		DIR_CNT
	};
}