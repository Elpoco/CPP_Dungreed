#pragma once

namespace MapToolSet
{
	constexpr int TILE_CNT_X = 100;
	constexpr int TILE_CNT_Y = 100;

	constexpr int TOOL_TILE_SCALE = 2;
	constexpr int TOOL_TILE_SIZE = TILE_RES_SIZE * TOOL_TILE_SCALE;

	constexpr int TOOL_SIZE_X = TOOL_TILE_SIZE * 10;
	constexpr int TOOL_START_X = WINSIZE_X - TOOL_SIZE_X;

	constexpr float CAMERA_SPPED = 10;
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

	namespace Enemy
	{
		namespace SkelDog
		{
			constexpr int HP = 10;
			constexpr float JUMP_SPEED = 4.0f;
		}

		namespace LittleGhost
		{
			constexpr float MOVE_SPEED = 2.0f;
		}

		namespace Belial
		{
			constexpr int HP = 50;
		}
	}
}
