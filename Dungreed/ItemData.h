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
	int price;				// 아이템 가격
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
		_info[TO_INT(Code::ITEM::SHOT_SWORD)]	= { Code::ITEM_KIND::WEAPON, Code::ITEM::SHOT_SWORD, Code::ITEM_GRADE::COMMON, "숏소드", "\"가볍고 휘두르기 편한 검\"", 10, 8, 10, 3.03f };
		_info[TO_INT(Code::ITEM::BAMBOO_SWORD)]	= { Code::ITEM_KIND::WEAPON, Code::ITEM::BAMBOO_SWORD, Code::ITEM_GRADE::UNCOMMON, "죽도", "\"날 없이 검술 훈련을 할 때 사용되는 검\"", 300, 5, 6, 4.06f };
		_info[TO_INT(Code::ITEM::LIGHTSABER)]	= { Code::ITEM_KIND::WEAPON, Code::ITEM::LIGHTSABER, Code::ITEM_GRADE::RARE, "라이트 세이버", "\"고온의 플라즈마를 칼날 삼아 모든 걸 베어버리는 광검\"", 1000, 12, 12, 6.28f };
		_info[TO_INT(Code::ITEM::LIGHTSABER)].ability = "방어 무시";
		_info[TO_INT(Code::ITEM::COSMOSSWORD)]	= { Code::ITEM_KIND::WEAPON, Code::ITEM::COSMOSSWORD, Code::ITEM_GRADE::LEGEND, "우주검", "\"이 검이 내뿜는 우주의 신비한 빛.\"", 2500, 30, 45, 3.17f };
		_info[TO_INT(Code::ITEM::COLT)]			= { Code::ITEM_KIND::WEAPON, Code::ITEM::COLT, Code::ITEM_GRADE::COMMON, "더 콜트", "\"그는 모두를 자유롭게 했고, 그녀는 모두를 평등하게 했다.\"", 500, 3, 5, 8.33f, 1, 12 };
		_info[TO_INT(Code::ITEM::GATLINGGUN)]	= { Code::ITEM_KIND::WEAPON, Code::ITEM::GATLINGGUN, Code::ITEM_GRADE::LEGEND, "N134 개틀링 기관총", "\"원본인 개틀링 기관총보다 작아져서 미니건이다.\"", 3000, 2, 6, 21.74f, 0, 100 };
		// 악세
		_info[TO_INT(Code::ITEM::MULTI_BULLET)]	= { Code::ITEM_KIND::ACCESSORY, Code::ITEM::MULTI_BULLET, Code::ITEM_GRADE::RARE, "갈래총탄", "\"탄을 세 갈래로 나누어 뿌려준다. 공격력도 세 갈래가 된다.\"", 1500, "총알이 3갈래로 발사되지만, 대미지가 감소" };
		_info[TO_INT(Code::ITEM::MAGNIFYINGGLASS)]	= { Code::ITEM_KIND::ACCESSORY, Code::ITEM::MAGNIFYINGGLASS, Code::ITEM_GRADE::UNCOMMON, "마법의 돋보기", "\"보는 대상을 실제로 더 크게 만들어 줍니다.\"", 800, "총알의 크기가 커지고 대미지가 증가하지만, 공격속도 30% 감소" };
		_info[TO_INT(Code::ITEM::WINGBOOTS)]	= { Code::ITEM_KIND::ACCESSORY, Code::ITEM::WINGBOOTS, Code::ITEM_GRADE::UNCOMMON, "윙 부츠", "\"발걸음이 아주 가벼워집니다.\"", 600, "몸이 가벼워짐, 대시 횟수 1 증가" };
	}
	~ItemData() {}

	ITEM_INFO getInfo(Code::ITEM code) { return _info[TO_INT(code)]; }

};

