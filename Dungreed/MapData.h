#pragma once

class MapData
{
private:
	MAP_INFO _info[TO_INT(Code::MAP::MAP_CNT)];

public:
	MapData()
	{
		_info[TO_INT(Code::MAP::DUNGEON_01)].arrSpawnInfo[0].ptSpawn = PointMake(483, 792);
		_info[TO_INT(Code::MAP::DUNGEON_01)].arrSpawnInfo[0].unit = Code::UNIT::SKEL_DOG;
		_info[TO_INT(Code::MAP::DUNGEON_01)].arrSpawnInfo[1].ptSpawn = PointMake(1002, 792);
		_info[TO_INT(Code::MAP::DUNGEON_01)].arrSpawnInfo[1].unit = Code::UNIT::SKEL_DOG;
		_info[TO_INT(Code::MAP::DUNGEON_01)].arrSpawnInfo[2].ptSpawn = PointMake(432, 435);
		_info[TO_INT(Code::MAP::DUNGEON_01)].arrSpawnInfo[2].unit = Code::UNIT::SKEL_BOW;
		_info[TO_INT(Code::MAP::DUNGEON_01)].arrSpawnInfo[3].ptSpawn = PointMake(770, 435);
		_info[TO_INT(Code::MAP::DUNGEON_01)].arrSpawnInfo[3].unit = Code::UNIT::SKEL_BOW;
		_info[TO_INT(Code::MAP::DUNGEON_01)].arrSpawnInfo[4].ptSpawn = PointMake(1105, 435);
		_info[TO_INT(Code::MAP::DUNGEON_01)].arrSpawnInfo[4].unit = Code::UNIT::SKEL_BOW;
		_info[TO_INT(Code::MAP::DUNGEON_01)].ptTresure = { 770, 455 };
		_info[TO_INT(Code::MAP::DUNGEON_01)].door[DIR::LEFT] = TRUE;
		_info[TO_INT(Code::MAP::DUNGEON_01)].door[DIR::TOP] = TRUE;
		_info[TO_INT(Code::MAP::DUNGEON_01)].door[DIR::RIGHT] = TRUE;

		_info[TO_INT(Code::MAP::DUNGEON_02)].arrSpawnInfo[0].ptSpawn = PointMake(335, 419);
		_info[TO_INT(Code::MAP::DUNGEON_02)].arrSpawnInfo[0].unit = Code::UNIT::BAT;
		_info[TO_INT(Code::MAP::DUNGEON_02)].arrSpawnInfo[1].ptSpawn = PointMake(653, 505);
		_info[TO_INT(Code::MAP::DUNGEON_02)].arrSpawnInfo[1].unit = Code::UNIT::BAT;
		_info[TO_INT(Code::MAP::DUNGEON_02)].arrSpawnInfo[2].ptSpawn = PointMake(929, 559);
		_info[TO_INT(Code::MAP::DUNGEON_02)].arrSpawnInfo[2].unit = Code::UNIT::BANSHEE;
		_info[TO_INT(Code::MAP::DUNGEON_02)].arrSpawnInfo[3].ptSpawn = PointMake(1318, 614);
		_info[TO_INT(Code::MAP::DUNGEON_02)].arrSpawnInfo[3].unit = Code::UNIT::BAT;
		_info[TO_INT(Code::MAP::DUNGEON_02)].arrSpawnInfo[4].ptSpawn = PointMake(1655, 619);
		_info[TO_INT(Code::MAP::DUNGEON_02)].arrSpawnInfo[4].unit = Code::UNIT::GIANT_BAT;
		_info[TO_INT(Code::MAP::DUNGEON_02)].ptTresure = { 1419, 791 };
		_info[TO_INT(Code::MAP::DUNGEON_02)].door[DIR::LEFT] = TRUE;
		_info[TO_INT(Code::MAP::DUNGEON_02)].door[DIR::RIGHT] = TRUE;
		_info[TO_INT(Code::MAP::DUNGEON_02)].door[DIR::BOTTOM] = TRUE;

		_info[TO_INT(Code::MAP::DUNGEON_03)].arrSpawnInfo[0].ptSpawn = PointMake(548, 419);
		_info[TO_INT(Code::MAP::DUNGEON_03)].arrSpawnInfo[0].unit = Code::UNIT::BANSHEE;
		_info[TO_INT(Code::MAP::DUNGEON_03)].arrSpawnInfo[1].ptSpawn = PointMake(376, 686);
		_info[TO_INT(Code::MAP::DUNGEON_03)].arrSpawnInfo[1].unit = Code::UNIT::SKEL;
		_info[TO_INT(Code::MAP::DUNGEON_03)].arrSpawnInfo[2].ptSpawn = PointMake(893, 688);
		_info[TO_INT(Code::MAP::DUNGEON_03)].arrSpawnInfo[2].unit = Code::UNIT::SKEL;
		_info[TO_INT(Code::MAP::DUNGEON_03)].arrSpawnInfo[3].ptSpawn = PointMake(385, 205);
		_info[TO_INT(Code::MAP::DUNGEON_03)].arrSpawnInfo[3].unit = Code::UNIT::SKEL_DOG;
		_info[TO_INT(Code::MAP::DUNGEON_03)].ptTresure = { 540, 551 };
		_info[TO_INT(Code::MAP::DUNGEON_03)].door[DIR::TOP] = TRUE;
		_info[TO_INT(Code::MAP::DUNGEON_03)].door[DIR::RIGHT] = TRUE;

		_info[TO_INT(Code::MAP::DUNGEON_04)].arrSpawnInfo[0].ptSpawn = PointMake(217, 470);
		_info[TO_INT(Code::MAP::DUNGEON_04)].arrSpawnInfo[0].unit = Code::UNIT::GIANT_BAT;
		_info[TO_INT(Code::MAP::DUNGEON_04)].arrSpawnInfo[1].ptSpawn = PointMake(1112, 221);
		_info[TO_INT(Code::MAP::DUNGEON_04)].arrSpawnInfo[1].unit = Code::UNIT::BANSHEE;
		_info[TO_INT(Code::MAP::DUNGEON_04)].arrSpawnInfo[2].ptSpawn = PointMake(704, 563);
		_info[TO_INT(Code::MAP::DUNGEON_04)].arrSpawnInfo[2].unit = Code::UNIT::SKEL_DOG;
		_info[TO_INT(Code::MAP::DUNGEON_04)].arrSpawnInfo[3].ptSpawn = PointMake(526, 269);
		_info[TO_INT(Code::MAP::DUNGEON_04)].arrSpawnInfo[3].unit = Code::UNIT::BAT;
		_info[TO_INT(Code::MAP::DUNGEON_04)].ptTresure = { 700, 551 };
		_info[TO_INT(Code::MAP::DUNGEON_04)].door[DIR::RIGHT] = TRUE;
		_info[TO_INT(Code::MAP::DUNGEON_04)].door[DIR::BOTTOM] = TRUE;

		_info[TO_INT(Code::MAP::DUNGEON_05)].arrSpawnInfo[0].ptSpawn = PointMake(900, 500);
		_info[TO_INT(Code::MAP::DUNGEON_05)].arrSpawnInfo[0].unit = Code::UNIT::LITTLE_GHOST;
		_info[TO_INT(Code::MAP::DUNGEON_05)].arrSpawnInfo[1].ptSpawn = PointMake(835, 438);
		_info[TO_INT(Code::MAP::DUNGEON_05)].arrSpawnInfo[1].unit = Code::UNIT::LITTLE_GHOST;
		_info[TO_INT(Code::MAP::DUNGEON_05)].arrSpawnInfo[2].ptSpawn = PointMake(962, 438);
		_info[TO_INT(Code::MAP::DUNGEON_05)].arrSpawnInfo[2].unit = Code::UNIT::LITTLE_GHOST;
		_info[TO_INT(Code::MAP::DUNGEON_05)].arrSpawnInfo[3].ptSpawn = PointMake(962, 561);
		_info[TO_INT(Code::MAP::DUNGEON_05)].arrSpawnInfo[3].unit = Code::UNIT::LITTLE_GHOST;
		_info[TO_INT(Code::MAP::DUNGEON_05)].arrSpawnInfo[4].ptSpawn = PointMake(835, 561);
		_info[TO_INT(Code::MAP::DUNGEON_05)].arrSpawnInfo[4].unit = Code::UNIT::LITTLE_GHOST;
		_info[TO_INT(Code::MAP::DUNGEON_05)].arrSpawnInfo[5].ptSpawn = PointMake(760, 367);
		_info[TO_INT(Code::MAP::DUNGEON_05)].arrSpawnInfo[5].unit = Code::UNIT::LITTLE_GHOST;
		_info[TO_INT(Code::MAP::DUNGEON_05)].arrSpawnInfo[6].ptSpawn = PointMake(1027, 367);
		_info[TO_INT(Code::MAP::DUNGEON_05)].arrSpawnInfo[6].unit = Code::UNIT::LITTLE_GHOST;
		_info[TO_INT(Code::MAP::DUNGEON_05)].arrSpawnInfo[7].ptSpawn = PointMake(1027, 623);
		_info[TO_INT(Code::MAP::DUNGEON_05)].arrSpawnInfo[7].unit = Code::UNIT::LITTLE_GHOST;
		_info[TO_INT(Code::MAP::DUNGEON_05)].arrSpawnInfo[8].ptSpawn = PointMake(760, 623);
		_info[TO_INT(Code::MAP::DUNGEON_05)].arrSpawnInfo[8].unit = Code::UNIT::LITTLE_GHOST;
		_info[TO_INT(Code::MAP::DUNGEON_05)].arrSpawnInfo[9].ptSpawn = PointMake(456, 529);
		_info[TO_INT(Code::MAP::DUNGEON_05)].arrSpawnInfo[9].unit = Code::UNIT::SKEL_BOW;
		_info[TO_INT(Code::MAP::DUNGEON_05)].arrSpawnInfo[10].ptSpawn = PointMake(459, 242);
		_info[TO_INT(Code::MAP::DUNGEON_05)].arrSpawnInfo[10].unit = Code::UNIT::SKEL_BOW;
		_info[TO_INT(Code::MAP::DUNGEON_05)].arrSpawnInfo[11].ptSpawn = PointMake(1368, 247);
		_info[TO_INT(Code::MAP::DUNGEON_05)].arrSpawnInfo[11].unit = Code::UNIT::SKEL_BOW;
		_info[TO_INT(Code::MAP::DUNGEON_05)].arrSpawnInfo[12].ptSpawn = PointMake(1371, 535);
		_info[TO_INT(Code::MAP::DUNGEON_05)].arrSpawnInfo[12].unit = Code::UNIT::SKEL_BOW;
		_info[TO_INT(Code::MAP::DUNGEON_05)].ptTresure = { 907, 743 };
		_info[TO_INT(Code::MAP::DUNGEON_05)].door[DIR::LEFT] = TRUE;
		_info[TO_INT(Code::MAP::DUNGEON_05)].door[DIR::RIGHT] = TRUE;
		_info[TO_INT(Code::MAP::DUNGEON_05)].door[DIR::BOTTOM] = TRUE;

		_info[TO_INT(Code::MAP::DUNGEON_06)].arrSpawnInfo[0].ptSpawn = PointMake(1530, 784);
		_info[TO_INT(Code::MAP::DUNGEON_06)].arrSpawnInfo[0].unit = Code::UNIT::SKEL;
		_info[TO_INT(Code::MAP::DUNGEON_06)].arrSpawnInfo[1].ptSpawn = PointMake(1527, 543);
		_info[TO_INT(Code::MAP::DUNGEON_06)].arrSpawnInfo[1].unit = Code::UNIT::SKEL;
		_info[TO_INT(Code::MAP::DUNGEON_06)].arrSpawnInfo[2].ptSpawn = PointMake(1413, 259);
		_info[TO_INT(Code::MAP::DUNGEON_06)].arrSpawnInfo[2].unit = Code::UNIT::SKEL_BOW;
		_info[TO_INT(Code::MAP::DUNGEON_06)].arrSpawnInfo[3].ptSpawn = PointMake(1623, 253);
		_info[TO_INT(Code::MAP::DUNGEON_06)].arrSpawnInfo[3].unit = Code::UNIT::SKEL_BOW;
		_info[TO_INT(Code::MAP::DUNGEON_06)].arrSpawnInfo[4].ptSpawn = PointMake(364, 296);
		_info[TO_INT(Code::MAP::DUNGEON_06)].arrSpawnInfo[4].unit = Code::UNIT::SKEL_BOW;
		_info[TO_INT(Code::MAP::DUNGEON_06)].arrSpawnInfo[5].ptSpawn = PointMake(355, 725);
		_info[TO_INT(Code::MAP::DUNGEON_06)].arrSpawnInfo[5].unit = Code::UNIT::SKEL_BOW;
		_info[TO_INT(Code::MAP::DUNGEON_06)].arrSpawnInfo[6].ptSpawn = PointMake(925, 393);
		_info[TO_INT(Code::MAP::DUNGEON_06)].arrSpawnInfo[6].unit = Code::UNIT::BANSHEE;
		_info[TO_INT(Code::MAP::DUNGEON_06)].arrSpawnInfo[7].ptSpawn = PointMake(376, 1021);
		_info[TO_INT(Code::MAP::DUNGEON_06)].arrSpawnInfo[7].unit = Code::UNIT::SKEL_DOG;
		_info[TO_INT(Code::MAP::DUNGEON_06)].ptTresure = { 922, 457 };
		_info[TO_INT(Code::MAP::DUNGEON_06)].door[DIR::LEFT] = TRUE;
		_info[TO_INT(Code::MAP::DUNGEON_06)].door[DIR::BOTTOM] = TRUE;

		_info[TO_INT(Code::MAP::DUNGEON_07)].arrSpawnInfo[0].ptSpawn = PointMake(900, 500);
		_info[TO_INT(Code::MAP::DUNGEON_07)].arrSpawnInfo[0].unit = Code::UNIT::SKEL;
		_info[TO_INT(Code::MAP::DUNGEON_07)].arrSpawnInfo[1].ptSpawn = PointMake(793, 238);
		_info[TO_INT(Code::MAP::DUNGEON_07)].arrSpawnInfo[1].unit = Code::UNIT::RED_GIANT_BAT;
		_info[TO_INT(Code::MAP::DUNGEON_07)].arrSpawnInfo[2].ptSpawn = PointMake(1482, 198);
		_info[TO_INT(Code::MAP::DUNGEON_07)].arrSpawnInfo[2].unit = Code::UNIT::BAT;
		_info[TO_INT(Code::MAP::DUNGEON_07)].arrSpawnInfo[3].ptSpawn = PointMake(1503, 718);
		_info[TO_INT(Code::MAP::DUNGEON_07)].arrSpawnInfo[3].unit = Code::UNIT::SKEL;
		_info[TO_INT(Code::MAP::DUNGEON_07)].arrSpawnInfo[4].ptSpawn = PointMake(1422, 967);
		_info[TO_INT(Code::MAP::DUNGEON_07)].arrSpawnInfo[4].unit = Code::UNIT::SKEL_DOG;
		_info[TO_INT(Code::MAP::DUNGEON_07)].arrSpawnInfo[5].ptSpawn = PointMake(1165, 964);
		_info[TO_INT(Code::MAP::DUNGEON_07)].arrSpawnInfo[5].unit = Code::UNIT::SKEL_DOG;
		_info[TO_INT(Code::MAP::DUNGEON_07)].arrSpawnInfo[6].ptSpawn = PointMake(882, 962);
		_info[TO_INT(Code::MAP::DUNGEON_07)].arrSpawnInfo[6].unit = Code::UNIT::SKEL_DOG;
		_info[TO_INT(Code::MAP::DUNGEON_07)].arrSpawnInfo[7].ptSpawn = PointMake(654, 859);
		_info[TO_INT(Code::MAP::DUNGEON_07)].arrSpawnInfo[7].unit = Code::UNIT::BAT;
		_info[TO_INT(Code::MAP::DUNGEON_07)].ptTresure = { 772, 552 };
		_info[TO_INT(Code::MAP::DUNGEON_07)].door[DIR::LEFT] = TRUE;
		_info[TO_INT(Code::MAP::DUNGEON_07)].door[DIR::TOP] = TRUE;
		_info[TO_INT(Code::MAP::DUNGEON_07)].ptWorm = PointMake(1248, 381);

		_info[TO_INT(Code::MAP::DUNGEON_08)].arrSpawnInfo[0].ptSpawn = PointMake(286, 587);
		_info[TO_INT(Code::MAP::DUNGEON_08)].arrSpawnInfo[0].unit = Code::UNIT::SKEL_BOW;
		_info[TO_INT(Code::MAP::DUNGEON_08)].arrSpawnInfo[1].ptSpawn = PointMake(379, 539);
		_info[TO_INT(Code::MAP::DUNGEON_08)].arrSpawnInfo[1].unit = Code::UNIT::SKEL_BOW;
		_info[TO_INT(Code::MAP::DUNGEON_08)].arrSpawnInfo[2].ptSpawn = PointMake(477, 490);
		_info[TO_INT(Code::MAP::DUNGEON_08)].arrSpawnInfo[2].unit = Code::UNIT::SKEL_BOW;
		_info[TO_INT(Code::MAP::DUNGEON_08)].arrSpawnInfo[3].ptSpawn = PointMake(574, 443);
		_info[TO_INT(Code::MAP::DUNGEON_08)].arrSpawnInfo[3].unit = Code::UNIT::SKEL_BOW;
		_info[TO_INT(Code::MAP::DUNGEON_08)].arrSpawnInfo[4].ptSpawn = PointMake(697, 389);
		_info[TO_INT(Code::MAP::DUNGEON_08)].arrSpawnInfo[4].unit = Code::UNIT::SKEL_BOW;
		_info[TO_INT(Code::MAP::DUNGEON_08)].arrSpawnInfo[5].ptSpawn = PointMake(1131, 394);
		_info[TO_INT(Code::MAP::DUNGEON_08)].arrSpawnInfo[5].unit = Code::UNIT::SKEL_BOW;
		_info[TO_INT(Code::MAP::DUNGEON_08)].arrSpawnInfo[6].ptSpawn = PointMake(1245, 442);
		_info[TO_INT(Code::MAP::DUNGEON_08)].arrSpawnInfo[6].unit = Code::UNIT::SKEL_BOW;
		_info[TO_INT(Code::MAP::DUNGEON_08)].arrSpawnInfo[7].ptSpawn = PointMake(1344, 490);
		_info[TO_INT(Code::MAP::DUNGEON_08)].arrSpawnInfo[7].unit = Code::UNIT::SKEL_BOW;
		_info[TO_INT(Code::MAP::DUNGEON_08)].arrSpawnInfo[8].ptSpawn = PointMake(1437, 541);
		_info[TO_INT(Code::MAP::DUNGEON_08)].arrSpawnInfo[8].unit = Code::UNIT::SKEL_BOW;
		_info[TO_INT(Code::MAP::DUNGEON_08)].arrSpawnInfo[9].ptSpawn = PointMake(1536, 590);
		_info[TO_INT(Code::MAP::DUNGEON_08)].arrSpawnInfo[9].unit = Code::UNIT::SKEL_BOW;
		_info[TO_INT(Code::MAP::DUNGEON_08)].arrSpawnInfo[10].ptSpawn = PointMake(913, 256);
		_info[TO_INT(Code::MAP::DUNGEON_08)].arrSpawnInfo[10].unit = Code::UNIT::SKEL_BOW;
		_info[TO_INT(Code::MAP::DUNGEON_08)].arrSpawnInfo[11].ptSpawn = PointMake(919, 610);
		_info[TO_INT(Code::MAP::DUNGEON_08)].arrSpawnInfo[11].unit = Code::UNIT::BANSHEE;
		_info[TO_INT(Code::MAP::DUNGEON_08)].arrSpawnInfo[12].ptSpawn = PointMake(525, 779);
		_info[TO_INT(Code::MAP::DUNGEON_08)].arrSpawnInfo[12].unit = Code::UNIT::SKEL_DOG;
		_info[TO_INT(Code::MAP::DUNGEON_08)].arrSpawnInfo[13].ptSpawn = PointMake(1260, 782);
		_info[TO_INT(Code::MAP::DUNGEON_08)].arrSpawnInfo[13].unit = Code::UNIT::SKEL_DOG;
		_info[TO_INT(Code::MAP::DUNGEON_08)].ptTresure = { 910, 263 };
		_info[TO_INT(Code::MAP::DUNGEON_08)].door[DIR::LEFT] = TRUE;
		_info[TO_INT(Code::MAP::DUNGEON_08)].door[DIR::RIGHT] = TRUE;
		_info[TO_INT(Code::MAP::DUNGEON_08)].door[DIR::BOTTOM] = TRUE;

		_info[TO_INT(Code::MAP::DUNGEON_09)].arrSpawnInfo[0].ptSpawn = PointMake(166, 154);
		_info[TO_INT(Code::MAP::DUNGEON_09)].arrSpawnInfo[0].unit = Code::UNIT::SKEL_DOG;
		_info[TO_INT(Code::MAP::DUNGEON_09)].arrSpawnInfo[1].ptSpawn = PointMake(459, 394);
		_info[TO_INT(Code::MAP::DUNGEON_09)].arrSpawnInfo[1].unit = Code::UNIT::SKEL_DOG;
		_info[TO_INT(Code::MAP::DUNGEON_09)].arrSpawnInfo[2].ptSpawn = PointMake(229, 673);
		_info[TO_INT(Code::MAP::DUNGEON_09)].arrSpawnInfo[2].unit = Code::UNIT::SKEL;
		_info[TO_INT(Code::MAP::DUNGEON_09)].arrSpawnInfo[3].ptSpawn = PointMake(648, 882);
		_info[TO_INT(Code::MAP::DUNGEON_09)].arrSpawnInfo[3].unit = Code::UNIT::BAT;
		_info[TO_INT(Code::MAP::DUNGEON_09)].arrSpawnInfo[4].ptSpawn = PointMake(1224, 883);
		_info[TO_INT(Code::MAP::DUNGEON_09)].arrSpawnInfo[4].unit = Code::UNIT::BAT;
		_info[TO_INT(Code::MAP::DUNGEON_09)].arrSpawnInfo[5].ptSpawn = PointMake(1224, 883);
		_info[TO_INT(Code::MAP::DUNGEON_09)].arrSpawnInfo[5].unit = Code::UNIT::BAT;
		_info[TO_INT(Code::MAP::DUNGEON_09)].arrSpawnInfo[6].ptSpawn = PointMake(915, 481);
		_info[TO_INT(Code::MAP::DUNGEON_09)].arrSpawnInfo[6].unit = Code::UNIT::SKEL;
		_info[TO_INT(Code::MAP::DUNGEON_09)].arrSpawnInfo[7].ptSpawn = PointMake(911, 240);
		_info[TO_INT(Code::MAP::DUNGEON_09)].arrSpawnInfo[7].unit = Code::UNIT::SKEL;
		_info[TO_INT(Code::MAP::DUNGEON_09)].arrSpawnInfo[8].ptSpawn = PointMake(800, 681);
		_info[TO_INT(Code::MAP::DUNGEON_09)].arrSpawnInfo[8].unit = Code::UNIT::SKEL;
		_info[TO_INT(Code::MAP::DUNGEON_09)].arrSpawnInfo[9].ptSpawn = PointMake(1452, 632);
		_info[TO_INT(Code::MAP::DUNGEON_09)].arrSpawnInfo[9].unit = Code::UNIT::SKEL;
		_info[TO_INT(Code::MAP::DUNGEON_09)].arrSpawnInfo[10].ptSpawn = PointMake(1461, 249);
		_info[TO_INT(Code::MAP::DUNGEON_09)].arrSpawnInfo[10].unit = Code::UNIT::SKEL;
		_info[TO_INT(Code::MAP::DUNGEON_09)].ptTresure = { 910, 984 };
		_info[TO_INT(Code::MAP::DUNGEON_09)].door[DIR::LEFT] = TRUE;
		_info[TO_INT(Code::MAP::DUNGEON_09)].door[DIR::TOP] = TRUE;
		_info[TO_INT(Code::MAP::DUNGEON_09)].door[DIR::RIGHT] = TRUE;
		_info[TO_INT(Code::MAP::DUNGEON_09)].ptWorm = PointMake(1250, 1006);

		_info[TO_INT(Code::MAP::DUNGEON_10)].arrSpawnInfo[0].ptSpawn = PointMake(1651, 829);
		_info[TO_INT(Code::MAP::DUNGEON_10)].arrSpawnInfo[0].unit = Code::UNIT::RED_GIANT_BAT;
		_info[TO_INT(Code::MAP::DUNGEON_10)].arrSpawnInfo[1].ptSpawn = PointMake(1683, 524);
		_info[TO_INT(Code::MAP::DUNGEON_10)].arrSpawnInfo[1].unit = Code::UNIT::SKEL;
		_info[TO_INT(Code::MAP::DUNGEON_10)].arrSpawnInfo[2].ptSpawn = PointMake(1491, 1018);
		_info[TO_INT(Code::MAP::DUNGEON_10)].arrSpawnInfo[2].unit = Code::UNIT::SKEL_DOG;
		_info[TO_INT(Code::MAP::DUNGEON_10)].arrSpawnInfo[3].ptSpawn = PointMake(1174, 443);
		_info[TO_INT(Code::MAP::DUNGEON_10)].arrSpawnInfo[3].unit = Code::UNIT::SKEL_BOW;
		_info[TO_INT(Code::MAP::DUNGEON_10)].arrSpawnInfo[4].ptSpawn = PointMake(967, 779);
		_info[TO_INT(Code::MAP::DUNGEON_10)].arrSpawnInfo[4].unit = Code::UNIT::SKEL;
		_info[TO_INT(Code::MAP::DUNGEON_10)].arrSpawnInfo[5].ptSpawn = PointMake(772, 478);
		_info[TO_INT(Code::MAP::DUNGEON_10)].arrSpawnInfo[5].unit = Code::UNIT::BANSHEE;
		_info[TO_INT(Code::MAP::DUNGEON_10)].arrSpawnInfo[6].ptSpawn = PointMake(436, 271);
		_info[TO_INT(Code::MAP::DUNGEON_10)].arrSpawnInfo[6].unit = Code::UNIT::GIANT_BAT;
		_info[TO_INT(Code::MAP::DUNGEON_10)].arrSpawnInfo[7].ptSpawn = PointMake(432, 520);
		_info[TO_INT(Code::MAP::DUNGEON_10)].arrSpawnInfo[7].unit = Code::UNIT::GIANT_BAT;
		_info[TO_INT(Code::MAP::DUNGEON_10)].arrSpawnInfo[8].ptSpawn = PointMake(403, 1016);
		_info[TO_INT(Code::MAP::DUNGEON_10)].arrSpawnInfo[8].unit = Code::UNIT::SKEL;
		_info[TO_INT(Code::MAP::DUNGEON_10)].ptTresure = { 1591, 552 };
		_info[TO_INT(Code::MAP::DUNGEON_10)].door[DIR::RIGHT] = TRUE;
		_info[TO_INT(Code::MAP::DUNGEON_10)].ptWorm = PointMake(954, 814);

		_info[TO_INT(Code::MAP::DUNGEON_11)].arrSpawnInfo[0].ptSpawn = PointMake(1072, 333);
		_info[TO_INT(Code::MAP::DUNGEON_11)].arrSpawnInfo[0].unit = Code::UNIT::RED_GIANT_BAT;
		_info[TO_INT(Code::MAP::DUNGEON_11)].arrSpawnInfo[1].ptSpawn = PointMake(353, 374);
		_info[TO_INT(Code::MAP::DUNGEON_11)].arrSpawnInfo[1].unit = Code::UNIT::RED_GIANT_BAT;
		_info[TO_INT(Code::MAP::DUNGEON_11)].arrSpawnInfo[2].ptSpawn = PointMake(1166, 671);
		_info[TO_INT(Code::MAP::DUNGEON_11)].arrSpawnInfo[2].unit = Code::UNIT::GIANT_BAT;
		_info[TO_INT(Code::MAP::DUNGEON_11)].arrSpawnInfo[3].ptSpawn = PointMake(347, 677);
		_info[TO_INT(Code::MAP::DUNGEON_11)].arrSpawnInfo[3].unit = Code::UNIT::GIANT_BAT;
		_info[TO_INT(Code::MAP::DUNGEON_11)].arrSpawnInfo[4].ptSpawn = PointMake(592, 638);
		_info[TO_INT(Code::MAP::DUNGEON_11)].arrSpawnInfo[4].unit = Code::UNIT::SKEL;
		_info[TO_INT(Code::MAP::DUNGEON_11)].arrSpawnInfo[5].ptSpawn = PointMake(879, 496);
		_info[TO_INT(Code::MAP::DUNGEON_11)].arrSpawnInfo[5].unit = Code::UNIT::SKEL_BOW;
		_info[TO_INT(Code::MAP::DUNGEON_11)].arrSpawnInfo[6].ptSpawn = PointMake(1066, 782);
		_info[TO_INT(Code::MAP::DUNGEON_11)].arrSpawnInfo[6].unit = Code::UNIT::SKEL_DOG;
		_info[TO_INT(Code::MAP::DUNGEON_11)].arrSpawnInfo[7].ptSpawn = PointMake(390, 1021);
		_info[TO_INT(Code::MAP::DUNGEON_11)].arrSpawnInfo[7].unit = Code::UNIT::SKEL_DOG;
		_info[TO_INT(Code::MAP::DUNGEON_11)].ptTresure = { 1087, 1027 };
		_info[TO_INT(Code::MAP::DUNGEON_11)].door[DIR::LEFT] = TRUE;
		_info[TO_INT(Code::MAP::DUNGEON_11)].door[DIR::TOP] = TRUE;
		_info[TO_INT(Code::MAP::DUNGEON_11)].door[DIR::RIGHT] = TRUE;

		_info[TO_INT(Code::MAP::BELIAL)].arrSpawnInfo[0].ptSpawn = PointMake(750, 526);
		_info[TO_INT(Code::MAP::BELIAL)].arrSpawnInfo[0].unit = Code::UNIT::BELIAL;
		_info[TO_INT(Code::MAP::BELIAL)].ptTresure = { 780, 727 };
		_info[TO_INT(Code::MAP::BELIAL)].door[DIR::LEFT] = TRUE;

		_info[TO_INT(Code::MAP::NIFLHEIM)].arrSpawnInfo[0].ptSpawn = PointMake(740, 405);
		_info[TO_INT(Code::MAP::NIFLHEIM)].arrSpawnInfo[0].unit = Code::UNIT::NIFLEHEIM;
		_info[TO_INT(Code::MAP::NIFLHEIM)].ptTresure = { 746, 490 };
		_info[TO_INT(Code::MAP::NIFLHEIM)].door[DIR::LEFT] = TRUE;

		_info[TO_INT(Code::MAP::DUNGEON_START)].door[DIR::TOP] = TRUE;
		_info[TO_INT(Code::MAP::DUNGEON_START)].door[DIR::RIGHT] = TRUE;
		_info[TO_INT(Code::MAP::DUNGEON_START)].door[DIR::BOTTOM] = TRUE;
		_info[TO_INT(Code::MAP::DUNGEON_START)].ptWorm = PointMake(565, 622);
		_info[TO_INT(Code::MAP::DUNGEON_SHOP)].door[DIR::LEFT] = TRUE;
		_info[TO_INT(Code::MAP::DUNGEON_SHOP)].door[DIR::RIGHT] = TRUE;
		_info[TO_INT(Code::MAP::DUNGEON_SHOP)].ptWorm = PointMake(441, 286);
		_info[TO_INT(Code::MAP::DUNGEON_FOOD)].door[DIR::LEFT] = TRUE;
		_info[TO_INT(Code::MAP::DUNGEON_FOOD)].door[DIR::RIGHT] = TRUE;
		_info[TO_INT(Code::MAP::DUNGEON_FOOD)].ptWorm = PointMake(975, 622);
	}
	~MapData() {}

	MAP_INFO getInfo(Code::MAP code) { return _info[TO_INT(code)]; }

};

