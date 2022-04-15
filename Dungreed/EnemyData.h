#pragma once

class EnemyData
{
private:
	ENEMY_INFO _info[(int)Code::UNIT::UNIT_CNT];

public:
	EnemyData()
	{
		_info[Code::UNIT::SKEL_DOG] = { "스켈리독", 10 };
		_info[Code::UNIT::LITTLE_GHOST] = { "꼬마유령", 2 };
		_info[Code::UNIT::BELIAL] = { "벨리알", 50 };
		_info[Code::UNIT::NIFLEHEIM] = { "니플헤임", 50 };
		_info[Code::UNIT::NIFLEHEIM_PILLAR] = { "얼음 기둥", 10 };
	}
	~EnemyData() {}

	ENEMY_INFO getInfo(Code::UNIT code) { return _info[(int)code]; }

};

