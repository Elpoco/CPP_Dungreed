#pragma once

class EnemyData
{
private:
	ENEMY_INFO _info[TO_INT(Code::UNIT::UNIT_CNT)];
	/*
	Code::UNIT code;
	string name;
	int hp;
	int dmg;
	int def;
	float atkTime;
	*/

public:
	EnemyData()
	{
		_info[TO_INT(Code::UNIT::SCARECROW)]	= { Code::UNIT::SCARECROW, "Çã¼ö¾Æºñ", 99999, 10, 10 };
		_info[TO_INT(Code::UNIT::SKEL_DOG)]		= { Code::UNIT::SKEL_DOG, "½ºÄÌ¸®µ¶", 20, 3, 1 };
		_info[TO_INT(Code::UNIT::LITTLE_GHOST)]	= { Code::UNIT::LITTLE_GHOST, "²¿¸¶À¯·É", 6, 3 };
		_info[TO_INT(Code::UNIT::BANSHEE)]		= { Code::UNIT::BANSHEE, "¹ê½Ã", 40, 8, 1, 3.0f };
		_info[TO_INT(Code::UNIT::BAT)]			= { Code::UNIT::BAT, "¹ÚÁã", 16, 5, 1, 2.5f };
		_info[TO_INT(Code::UNIT::GIANT_BAT)]	= { Code::UNIT::GIANT_BAT, "Å« ¹ÚÁã", 46, 12, 1, 3.5f };
		_info[TO_INT(Code::UNIT::RED_GIANT_BAT)]= { Code::UNIT::RED_GIANT_BAT, "Å« ºÓÀº ¹ÚÁã", 44, 16, 1, 3.5f };
		_info[TO_INT(Code::UNIT::SKEL)]			= { Code::UNIT::SKEL, "½ºÄÌ·¹Åæ", 37, 15, 1, 2.5f };
		_info[TO_INT(Code::UNIT::SKEL_BOW)]		= { Code::UNIT::SKEL_BOW, "½ºÄÌ·¹Åæ ±Ã¼ö", 30, 10, 0, 2.5f };

		// º¸½º
		_info[TO_INT(Code::UNIT::BELIAL)]				= { Code::UNIT::BELIAL, "º§¸®¾Ë", 300, 15, 15 };
		_info[TO_INT(Code::UNIT::NIFLEHEIM)]			= { Code::UNIT::NIFLEHEIM, "´ÏÇÃÇìÀÓ", 200, 10, 20 };
		_info[TO_INT(Code::UNIT::NIFLEHEIM_PILLAR)]		= { Code::UNIT::NIFLEHEIM_PILLAR, "¾óÀ½ ±âµÕ", 50, 5, 10 };
	}
	~EnemyData() {}

	ENEMY_INFO getInfo(Code::UNIT code) { return _info[TO_INT(code)]; }

};

