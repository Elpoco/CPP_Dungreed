#pragma once

class EnemyData
{
private:
	ENEMY_INFO _info[(int)Code::UNIT::UNIT_CNT];

public:
	EnemyData()
	{
		_info[Code::UNIT::SKEL_DOG] = { "���̸���", 10 };
		_info[Code::UNIT::LITTLE_GHOST] = { "��������", 2 };
		_info[Code::UNIT::BELIAL] = { "������", 50 };
		_info[Code::UNIT::NIFLEHEIM] = { "��������", 50 };
		_info[Code::UNIT::NIFLEHEIM_PILLAR] = { "���� ���", 10 };
	}
	~EnemyData() {}

	ENEMY_INFO getInfo(Code::UNIT code) { return _info[(int)code]; }

};

