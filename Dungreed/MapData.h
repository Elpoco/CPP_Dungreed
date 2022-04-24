#pragma once

class MapData
{
private:
	MAP_INFO _info[TO_INT(Code::MAP::MAP_CNT)];

public:
	MapData()
	{
		_info[TO_INT(Code::MAP::DUNGEON_START)].door[DIR::TOP].isOn = TRUE;
		_info[TO_INT(Code::MAP::DUNGEON_START)].door[DIR::TOP].tileX = 16;
		_info[TO_INT(Code::MAP::DUNGEON_START)].door[DIR::TOP].tileY = 0;
		_info[TO_INT(Code::MAP::DUNGEON_START)].door[DIR::RIGHT].isOn = TRUE;
		_info[TO_INT(Code::MAP::DUNGEON_START)].door[DIR::RIGHT].tileX = 25;
		_info[TO_INT(Code::MAP::DUNGEON_START)].door[DIR::RIGHT].tileY = 8;
		_info[TO_INT(Code::MAP::DUNGEON_START)].door[DIR::BOTTOM].isOn = TRUE;
		_info[TO_INT(Code::MAP::DUNGEON_START)].door[DIR::BOTTOM].tileX = 16;
		_info[TO_INT(Code::MAP::DUNGEON_START)].door[DIR::BOTTOM].tileY = 14;
		_info[TO_INT(Code::MAP::DUNGEON_START)].arrSpawnInfo[0].ptSpawn = PointMake(900,500);
		_info[TO_INT(Code::MAP::DUNGEON_START)].arrSpawnInfo[0].unit = Code::UNIT::SKEL_DOG;
	}
	~MapData() {}

	MAP_INFO getInfo(Code::MAP code) { return _info[TO_INT(code)]; }

};

