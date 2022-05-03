#pragma once

class EnemyData
{
private:
	ENEMY_INFO _info[TO_INT(Code::UNIT::UNIT_CNT)];

public:
	EnemyData()
	{
		_info[TO_INT(Code::UNIT::SKEL_DOG)]		= { Code::UNIT::SKEL_DOG, "���̸���", 20, 3, 1 };
		_info[TO_INT(Code::UNIT::LITTLE_GHOST)]	= { Code::UNIT::LITTLE_GHOST, "��������", 6, 3 };
		_info[TO_INT(Code::UNIT::BANSHEE)]		= { Code::UNIT::BANSHEE, "���", 40, 6, 1, 3.0f };
		_info[TO_INT(Code::UNIT::BAT)]			= { Code::UNIT::BAT, "����", 16, 3, 1, 2.5f };
		_info[TO_INT(Code::UNIT::GIANT_BAT)]	= { Code::UNIT::GIANT_BAT, "ū ����", 46, 8, 1, 3.5f };
		_info[TO_INT(Code::UNIT::RED_GIANT_BAT)]= { Code::UNIT::RED_GIANT_BAT, "ū ���� ����", 44, 7, 1, 3.5f };
		_info[TO_INT(Code::UNIT::SKEL)]			= { Code::UNIT::SKEL, "���̷���", 37, 10, 1, 2.5f };
		_info[TO_INT(Code::UNIT::SKEL_BOW)]		= { Code::UNIT::SKEL_BOW, "���̷��� �ü�", 30, 5, 0, 2.5f };

		// ����
		_info[TO_INT(Code::UNIT::BELIAL)]				= { Code::UNIT::BELIAL, "������", 300, 8, 2 };
		_info[TO_INT(Code::UNIT::NIFLEHEIM)]			= { Code::UNIT::NIFLEHEIM, "��������", 200, 10, 2 };
		_info[TO_INT(Code::UNIT::NIFLEHEIM_PILLAR)]		= { Code::UNIT::NIFLEHEIM_PILLAR, "���� ���", 50, 1, 1 };
	}
	~EnemyData() {}

	ENEMY_INFO getInfo(Code::UNIT code) { return _info[TO_INT(code)]; }

};

