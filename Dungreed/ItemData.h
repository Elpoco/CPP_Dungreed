#pragma once

class ItemData
{
private:
	ITEM_INFO _info[TO_INT(Code::ITEM::ITEM_CNT)];
	/*
	Code::ITEM_KIND  type;	// 타입
	Code::ITEM		 code;	// 코드
	Code::ITEM_GRADE grade;	// 등급
	string name;			// 아이템 이름
	string description;		// 아이템 설명
	int minDmg;				// 아이템 최소 공격력
	int maxDmg;				// 아이템 최대 공격력
	float atkSpeed;			// 공격속도
	int def;				// 방어력
	int bulletCnt;			// 총알 수		
	*/

public:
	ItemData()
	{
		// 무기
		_info[TO_INT(Code::ITEM::SHOT_SWORD)]	= { Code::ITEM_KIND::WEAPON, Code::ITEM::SHOT_SWORD, Code::ITEM_GRADE::COMMON, "숏소드", "\"가볍고 휘두르기 편한 검\"", 8, 10, 3.03f };
		_info[TO_INT(Code::ITEM::BAMBOO_SWORD)]	= { Code::ITEM_KIND::WEAPON, Code::ITEM::BAMBOO_SWORD, Code::ITEM_GRADE::COMMON, "죽도", "\"날 없이 검술 훈련을 할 때 사용되는 검\"", 5, 6, 6.06f };
		_info[TO_INT(Code::ITEM::LIGHTSABER)]	= { Code::ITEM_KIND::WEAPON, Code::ITEM::LIGHTSABER, Code::ITEM_GRADE::RARE, "라이트 세이버", "\"고온의 플라즈마를 칼날 삼아 모든 걸 베어버리는 광검\"", 12, 12, 3.28f };
		_info[TO_INT(Code::ITEM::COLT)]			= { Code::ITEM_KIND::WEAPON, Code::ITEM::COLT, Code::ITEM_GRADE::COMMON, "더 콜트", "\"그는 모두를 자유롭게 했고, 그녀는 모두를 평등하게 했다.\"", 3, 5, 8.33f, 1, 12 };
	}
	~ItemData() {}

	ITEM_INFO getInfo(Code::ITEM code) { return _info[TO_INT(code)]; }

};

