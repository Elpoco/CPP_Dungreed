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
		_info[TO_INT(Code::ITEM::LIGHTSABER)]	= { Code::ITEM_KIND::WEAPON, Code::ITEM::LIGHTSABER, Code::ITEM_GRADE::RARE, "라이트 세이버", "\"고온의 플라즈마를 칼날 삼아 모든 걸 베어버리는 광검\"", 1000, 12, 12, 4.58f };
		_info[TO_INT(Code::ITEM::LIGHTSABER)].ability = "방어 무시";
		_info[TO_INT(Code::ITEM::COSMOSSWORD)]	= { Code::ITEM_KIND::WEAPON, Code::ITEM::COSMOSSWORD, Code::ITEM_GRADE::LEGEND, "우주검", "\"이 검이 내뿜는 우주의 신비한 빛.\"", 1700, 15, 25, 3.17f };
		_info[TO_INT(Code::ITEM::THREETIEREDBATON)]	= { Code::ITEM_KIND::WEAPON, Code::ITEM::THREETIEREDBATON, Code::ITEM_GRADE::UNCOMMON, "삼단봉", "\"호신용으로 사용되는, 3단으로 접히는 단봉.\"", 500, 8, 9, 3.85f };
		_info[TO_INT(Code::ITEM::LALA)]			= { Code::ITEM_KIND::WEAPON, Code::ITEM::LALA, Code::ITEM_GRADE::LEGEND, "라라의 요술봉", "\"마법 소녀 라라가 잃어버린 요술봉이다.\"", 2000, 13, 20, 2.0f, 0, 12 };
		_info[TO_INT(Code::ITEM::COLT)]			= { Code::ITEM_KIND::WEAPON, Code::ITEM::COLT, Code::ITEM_GRADE::COMMON, "더 콜트", "\"그는 모두를 자유롭게 했고, 그녀는 모두를 평등하게 했다.\"", 500, 3, 5, 8.33f, 1, 12 };
		_info[TO_INT(Code::ITEM::GATLINGGUN)]	= { Code::ITEM_KIND::WEAPON, Code::ITEM::GATLINGGUN, Code::ITEM_GRADE::LEGEND, "N134 개틀링 기관총", "\"원본인 개틀링 기관총보다 작아져서 미니건이다.\"", 2000, 2, 6, 21.74f, 0, 100 };
		//_info[TO_INT(Code::ITEM::SPEAR)]		= { Code::ITEM_KIND::WEAPON, Code::ITEM::SPEAR, Code::ITEM_GRADE::LEGEND, "N134 개틀링 기관총", "\"원본인 개틀링 기관총보다 작아져서 미니건이다.\"", 2000, 2, 6, 21.74f, 0, 100 };
		// 악세
		_info[TO_INT(Code::ITEM::MULTI_BULLET)]	= { Code::ITEM_KIND::ACCESSORY, Code::ITEM::MULTI_BULLET, Code::ITEM_GRADE::RARE, "갈래총탄", "\"탄을 세 갈래로 나누어 뿌려준다. 공격력도 세 갈래가 된다.\"", 1500, "총알이 3갈래로 발사되지만, 대미지가 감소" };
		_info[TO_INT(Code::ITEM::MAGNIFYINGGLASS)]	= { Code::ITEM_KIND::ACCESSORY, Code::ITEM::MAGNIFYINGGLASS, Code::ITEM_GRADE::UNCOMMON, "마법의 돋보기", "\"보는 대상을 실제로 더 크게 만들어 줍니다.\"", 800, "총알의 크기가 커지고 대미지가 증가하지만, 공격속도 30% 감소" };
		_info[TO_INT(Code::ITEM::WINGBOOTS)]	= { Code::ITEM_KIND::ACCESSORY, Code::ITEM::WINGBOOTS, Code::ITEM_GRADE::UNCOMMON, "윙 부츠", "\"발걸음이 아주 가벼워집니다.\"", 600, "몸이 가벼워짐, 대쉬 횟수 1 증가" };
		_info[TO_INT(Code::ITEM::BULLION2)]		= { Code::ITEM_KIND::ACCESSORY, Code::ITEM::BULLION2, Code::ITEM_GRADE::UNCOMMON, "백금괴", "\"상점에 팔면 돈이 될지도...?\"", 2380, "상점 판매 시 1666 골드" };
		_info[TO_INT(Code::ITEM::LEATHERARMOR)]	= { Code::ITEM_KIND::ACCESSORY, Code::ITEM::LEATHERARMOR, Code::ITEM_GRADE::COMMON, "가죽옷", "\"무두질이 잘 된 가죽은 배신하지 않는다.\"", 600, "" };
		_info[TO_INT(Code::ITEM::LEATHERARMOR)].def = 8;
		_info[TO_INT(Code::ITEM::CHAINARMOR)]	= { Code::ITEM_KIND::ACCESSORY, Code::ITEM::CHAINARMOR, Code::ITEM_GRADE::COMMON, "사슬갑옷", "\"가볍지만, 소리가 커서 발걸음이 위축되는 갑옷\"", 1400, "" };
		_info[TO_INT(Code::ITEM::CHAINARMOR)].def = 11;
		_info[TO_INT(Code::ITEM::CharmOfAttack)]	= { Code::ITEM_KIND::ACCESSORY, Code::ITEM::CharmOfAttack, Code::ITEM_GRADE::COMMON, "위력의 부적", "\"부적 안을 확인하면, 부적의 효력은 사라집니다.\"", 400, "" };
		_info[TO_INT(Code::ITEM::CharmOfAttack)].power = 8;
		_info[TO_INT(Code::ITEM::CharmOfMadness)]	= { Code::ITEM_KIND::ACCESSORY, Code::ITEM::CharmOfMadness, Code::ITEM_GRADE::UNCOMMON, "광기의 부적", "\"거머리가 붙어 있는 불길한 기분을 계속 느껴야 한다.\"", 1800, "" };
		_info[TO_INT(Code::ITEM::CharmOfMadness)].power = 20;
		_info[TO_INT(Code::ITEM::CharmOfMadness)].hp = -20;
		_info[TO_INT(Code::ITEM::Jarngreipr)]	= { Code::ITEM_KIND::ACCESSORY, Code::ITEM::Jarngreipr, Code::ITEM_GRADE::RARE, "야른그레이프르", "\"뜨거운 무기를 잡을 수 있게 도와주는 장갑\"", 1600, "한손무기 장착 시 공격속도 50% 증가" };
		_info[TO_INT(Code::ITEM::Speedloader)]	= { Code::ITEM_KIND::ACCESSORY, Code::ITEM::Speedloader, Code::ITEM_GRADE::RARE, "스피드 리로더", "\"총기류의 재장전을 도와주는 기구\"", 1600, "재장전속도 70% 증가" };
		_info[TO_INT(Code::ITEM::DaisyRing)]	= { Code::ITEM_KIND::ACCESSORY, Code::ITEM::DaisyRing, Code::ITEM_GRADE::LEGEND, "데이지 반지", "\"희망을 드리겠어요.\"", 3000, "대쉬 횟수 2 증가, 스킬 쿨타임 80% 감소" };
		// 방어구
		_info[TO_INT(Code::ITEM::MagicShield)]	= { Code::ITEM_KIND::ARMOR, Code::ITEM::MagicShield, Code::ITEM_GRADE::UNCOMMON, "마법 방패", "\"방패를 바라면 팔찌에서부터 생겨난다.\"", 500, "" };
		_info[TO_INT(Code::ITEM::MagicShield)].def = 8;
	}
	~ItemData() {}

	ITEM_INFO getInfo(Code::ITEM code) { return _info[TO_INT(code)]; }

};

