#pragma once

class MapData
{
private:
	MAP_INFO _info[TO_INT(Code::MAP::MAP_CNT)];

public:
	MapData()
	{
		_info[TO_INT(Code::MAP::DUNGEON_START)].arrSpawnInfo[0].ptSpawn = PointMake(900,500);
		_info[TO_INT(Code::MAP::DUNGEON_START)].arrSpawnInfo[0].unit = Code::UNIT::SKEL_DOG;
	}
	~MapData() {}

	MAP_INFO getInfo(Code::MAP code) { return _info[TO_INT(code)]; }

};

