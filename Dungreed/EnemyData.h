#pragma once

class EnemyData
{
private:
	ENEMY_INFO _info[TO_INT(Code::UNIT::UNIT_CNT)];

public:
	EnemyData()
	{
		_info[TO_INT(Code::UNIT::SKEL_DOG)]		= { Code::UNIT::SKEL_DOG, "½ºÄÌ¸®µ¶", 20, 3, 1 };
		_info[TO_INT(Code::UNIT::LITTLE_GHOST)]	= { Code::UNIT::LITTLE_GHOST, "²¿¸¶À¯·É", 6, 3 };
		_info[TO_INT(Code::UNIT::BANSHEE)]		= { Code::UNIT::BANSHEE, "¹ê½Ã", 40, 2, 1, 3.0f };
		_info[TO_INT(Code::UNIT::BAT)]			= { Code::UNIT::BAT, "¹ÚÁã", 16, 3, 1, 2.5f };
		_info[TO_INT(Code::UNIT::GIANT_BAT)]	= { Code::UNIT::GIANT_BAT, "Å« ¹ÚÁã", 46, 6, 1, 3.5f };
		_info[TO_INT(Code::UNIT::RED_GIANT_BAT)]= { Code::UNIT::RED_GIANT_BAT, "Å« ºÓÀº ¹ÚÁã", 44, 6, 1, 3.5f };
		_info[TO_INT(Code::UNIT::SKEL)]			= { Code::UNIT::SKEL, "½ºÄÌ·¹Åæ", 37, 5, 1, 2.5f };
		_info[TO_INT(Code::UNIT::SKEL_BOW)]		= { Code::UNIT::SKEL_BOW, "½ºÄÌ·¹Åæ ±Ã¼ö", 30, 3, 0, 2.5f };

		// º¸½º
		_info[TO_INT(Code::UNIT::BELIAL)]				= { Code::UNIT::BELIAL, "º§¸®¾Ë", 150, 8, 2 };
		_info[TO_INT(Code::UNIT::NIFLEHEIM)]			= { Code::UNIT::NIFLEHEIM, "´ÏÇÃÇìÀÓ", 100, 10, 2 };
		_info[TO_INT(Code::UNIT::NIFLEHEIM_PILLAR)]		= { Code::UNIT::NIFLEHEIM_PILLAR, "¾óÀ½ ±âµÕ", 20, 1, 1 };
	}
	~EnemyData() {}

	ENEMY_INFO getInfo(Code::UNIT code) { return _info[TO_INT(code)]; }

};

