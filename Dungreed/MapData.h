#pragma once

class MapData
{
private:
	MAP_INFO _info[TO_INT(Code::MAP::MAP_CNT)];

public:
	MapData()
	{
		_info[TO_INT(Code::MAP::DUNGEON_01)].arrSpawnInfo[0].ptSpawn = PointMake(900, 500);
		_info[TO_INT(Code::MAP::DUNGEON_01)].arrSpawnInfo[0].unit = Code::UNIT::SKEL_DOG;
		_info[TO_INT(Code::MAP::DUNGEON_01)].ptTresure = { 770, 455 };

		_info[TO_INT(Code::MAP::BELIAL)].arrSpawnInfo[0].ptSpawn = PointMake(760, 526);
		_info[TO_INT(Code::MAP::BELIAL)].arrSpawnInfo[0].unit = Code::UNIT::BELIAL;
		_info[TO_INT(Code::MAP::BELIAL)].ptTresure = { 781, 733 };

		_info[TO_INT(Code::MAP::NIFLHEIM)].arrSpawnInfo[0].ptSpawn = PointMake(740, 405);
		_info[TO_INT(Code::MAP::NIFLHEIM)].arrSpawnInfo[0].unit = Code::UNIT::NIFLEHEIM;
	}
	~MapData() {}

	MAP_INFO getInfo(Code::MAP code) { return _info[TO_INT(code)]; }

};

