#pragma once

class MapData
{
private:
	MAP_INFO _info[TO_INT(Code::MAP::MAP_CNT)];

public:
	MapData()
	{
#pragma region start
#pragma endregion
#pragma region dungeon01
		_info[TO_INT(Code::MAP::DUNGEON_01)].arrSpawnInfo[0].ptSpawn = PointMake(900, 500);
		_info[TO_INT(Code::MAP::DUNGEON_01)].arrSpawnInfo[0].unit = Code::UNIT::SKEL_DOG;
#pragma endregion
		_info[TO_INT(Code::MAP::BELIAL)].arrSpawnInfo[0].ptSpawn = PointMake(760, 526);
		_info[TO_INT(Code::MAP::BELIAL)].arrSpawnInfo[0].unit = Code::UNIT::BELIAL;

		
	}
	~MapData() {}

	MAP_INFO getInfo(Code::MAP code) { return _info[TO_INT(code)]; }

};

