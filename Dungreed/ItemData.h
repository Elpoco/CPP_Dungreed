#pragma once

class ItemData
{
private:
	ITEM_INFO _info[TO_INT(Code::ITEM::ITEM_CNT)];
	/*
	Code::ITEM_TYPE type; // 아이템 타입
	Code::ITEM code;	  // 아이템 코드
	string name;		  // 아이템 이름
	int point;			  // 아이템 관련 수치
	int maxPoint;		  // 아이템 관련 최대치	(기본값 0)
	*/

public:
	ItemData()
	{
		_info[TO_INT(Code::ITEM::COIN)]		= { Code::ITEM_TYPE::GOLD, Code::ITEM::COIN, "동전",  10 };
		_info[TO_INT(Code::ITEM::BULLION)]	= { Code::ITEM_TYPE::GOLD, Code::ITEM::BULLION, "금덩어리", 100 };

		// 무기
		_info[TO_INT(Code::ITEM::SHOT_SWORD)] = { Code::ITEM_TYPE::WEAPON, Code::ITEM::SHOT_SWORD, "숏소드", 8, 10 };
	}
	~ItemData() {}

	ITEM_INFO getInfo(Code::ITEM code) { return _info[(int)code]; }

};

