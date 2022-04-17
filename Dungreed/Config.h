#pragma once

namespace MapToolSet
{
	constexpr int TILE_CNT_X = 120;
	constexpr int TILE_CNT_Y = 30;

	constexpr int TOOL_TILE_SCALE = 2;
	constexpr int TOOL_TILE_SIZE = TILE_RES_SIZE * TOOL_TILE_SCALE;

	constexpr int TOOL_SIZE_X = TOOL_TILE_SIZE * 8;
	constexpr int TOOL_START_X = WINSIZE_X - TOOL_SIZE_X;

	constexpr int TOTAL_TILE_X = TILE_CNT_X * TILE_SIZE;
	constexpr int TOTAL_TILE_Y = TILE_CNT_Y * TILE_SIZE;

	constexpr float CAMERA_SPPED = 10.0f;
}

namespace ColorSet
{
	constexpr DWORD BLACK	= RGB(0, 0, 0);
	constexpr DWORD RED		= RGB(255, 0, 0);
	constexpr DWORD GREEN	= RGB(0, 255, 0);
	constexpr DWORD BLUE	= RGB(0, 0, 255);
	constexpr DWORD MAGENTA = RGB(255, 0, 255);
	constexpr DWORD WHITE	= RGB(255, 255, 255);
}

namespace UnitSet
{
	constexpr float MOVE_SPEED = 3.0f;
	constexpr float JUMP_SPEED = 8.0f;
	constexpr float GRAVITY = 0.1f;
}
