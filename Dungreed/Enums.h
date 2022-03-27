#pragma once

enum class KEY
{
	LEFT  =	'A',
	UP	  =	'W',
	RIGHT = 'D',
	DOWN  =	'S'
};

namespace MapTool
{
	enum class TILE_TYPE
	{
		NONE,
		BLOCK
	};
}

namespace PlayerInfo
{
	enum PLAYER_STATE
	{
		IDLE,
		RUN
	};
}

namespace ColliderInfo
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