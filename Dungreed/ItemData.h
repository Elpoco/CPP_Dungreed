#pragma once

class ItemData
{
private:
	ITEM_INFO _info[TO_INT(Code::ITEM::ITEM_CNT)];
	/*
	Code::ITEM_TYPE type; // 아이템 타입
	Code::ITEM code;	  // 아이템 코드
	string name;		  // 아이템 이름
	int minDmg;			  // 아이템 최소 공격력
	int maxDmg;			  // 아이템 최대 공격력
	float atkSpeed;		  // 공격속도
	int def;			  // 방어력
	int etc;			  // 기타 수치  ( 총이면 총알 )
	*/

public:
	ItemData()
	{
		// 무기
		_info[TO_INT(Code::ITEM::SHOT_SWORD)]	= { Code::ITEM_TYPE::WEAPON, Code::ITEM::SHOT_SWORD, "숏소드", 8, 10, 0.303f };
		_info[TO_INT(Code::ITEM::COLT)]			= { Code::ITEM_TYPE::WEAPON, Code::ITEM::COLT, "더 콜트", 3, 5, 0.833f, 1, 12 };
	}
	~ItemData() {}

	ITEM_INFO getInfo(Code::ITEM code) { return _info[(int)code]; }

};

