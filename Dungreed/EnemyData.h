#pragma once

class EnemyData
{
private:
	ENEMY_INFO _info[TO_INT(Code::UNIT::UNIT_CNT)];

public:
	EnemyData()
	{
		_info[TO_INT(Code::UNIT::SKEL_DOG)]		= { Code::UNIT::SKEL_DOG, "스켈리독", 10 };
		_info[TO_INT(Code::UNIT::LITTLE_GHOST)]	= { Code::UNIT::LITTLE_GHOST, "꼬마유령", 2 };

		// 보스
		_info[TO_INT(Code::UNIT::BELIAL)]				= { Code::UNIT::BELIAL, "벨리알", 50 };
		_info[TO_INT(Code::UNIT::NIFLEHEIM)]			= { Code::UNIT::NIFLEHEIM, "니플헤임", 50 };
		_info[TO_INT(Code::UNIT::NIFLEHEIM_PILLAR)]		= { Code::UNIT::NIFLEHEIM_PILLAR, "얼음 기둥", 10 };
	}
	~EnemyData() {}

	ENEMY_INFO getInfo(Code::UNIT code) { return _info[(int)code]; }

};

