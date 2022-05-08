#pragma once

namespace TileSet
{
	constexpr int TILE_CNT_X = 120;
	constexpr int TILE_CNT_Y = 30;
	constexpr int TOTAL_TILE_CNT = TILE_CNT_X * TILE_CNT_Y;

	constexpr int TOTAL_TILE_X = TILE_CNT_X * TILE_SIZE;
	constexpr int TOTAL_TILE_Y = TILE_CNT_Y * TILE_SIZE;
}

namespace ColorSet
{
	constexpr DWORD BLACK	= RGB(0, 0, 0);
	constexpr DWORD RED		= RGB(255, 0, 0);
	constexpr DWORD GREEN	= RGB(0, 255, 0);
	constexpr DWORD BLUE	= RGB(0, 0, 255);
	constexpr DWORD MAGENTA = RGB(255, 0, 255);
	constexpr DWORD YELLOW	= RGB(255, 255, 0);
	constexpr DWORD WHITE	= RGB(255, 255, 255);

	constexpr DWORD ITEM_DSC  = RGB(202, 255, 255);
	constexpr DWORD UNCOMMON  = RGB(43, 123, 255);
	constexpr DWORD RARE	  = RGB(255, 210, 0);
	constexpr DWORD LEGEND	  = RGB(255, 0, 142);
	constexpr DWORD FOOD_NAME = RGB(255, 178 , 144);

	constexpr DWORD WRATH = RGB(204, 124 , 107);
	constexpr DWORD PATIENCE = RGB(169, 175 , 186);
	constexpr DWORD GREED = RGB(223, 175 , 75);
}

namespace UnitSet
{
	constexpr float MOVE_SPEED = 3.0f;
	constexpr float JUMP_SPEED = 7.0f;
	constexpr float GRAVITY = 0.1f;
	constexpr int MAX_SPAWN = 30;
}

namespace MapSet
{
	constexpr int MAX_SPAWN = 20;
}

namespace AbilitySet
{
	constexpr int ABILITY_CNT = 3;
	constexpr int POWER = 2;
	constexpr int DEFENSE = 1;
	constexpr int MAX_HP = 5;
}
