#pragma once

#define TILE_RES_SIZE		16
#define TILE_SCALE			3
#define TILE_SIZE			(TILE_RES_SIZE * TILE_SCALE)

namespace MapTool
{
	constexpr int TILE_CNT_X = 100;
	constexpr int TILE_CNT_Y = 100;
	constexpr int TOOL_START_X = 896;
	constexpr int CAMERA_SPPED = 10;
	constexpr int TOOL_TILE_SCALE = 2;
	constexpr int TOOL_TILE_SIZE = TILE_RES_SIZE * TOOL_TILE_SCALE;
}

namespace Color
{
	constexpr DWORD BLACK	= RGB(0, 0, 0);
	constexpr DWORD RED		= RGB(255, 0, 0);
	constexpr DWORD MAGENTA = RGB(255, 0, 255);
}

namespace UnitSet
{
	constexpr float MOVE_SPEED = 1.0f;
	constexpr float JUMP_SPEED = 15.0f;
	constexpr float FALL_SPEED = 0.0f;
	constexpr float GRAVITY = 0.3f;
}