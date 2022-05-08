#pragma once

class ItemData
{
private:
	ITEM_INFO _info[TO_INT(Code::ITEM::ITEM_CNT)];
	/*
	Code::ITEM_KIND  type;	// Ÿ��
	Code::ITEM		 code;	// �ڵ�
	Code::ITEM_GRADE grade;	// ���
	string name;			// ������ �̸�
	string description;		// ������ ����
	int price;				// ������ ����
	int minDmg;				// ������ �ּ� ���ݷ�
	int maxDmg;				// ������ �ִ� ���ݷ�
	float atkSpeed;			// ���ݼӵ�
	int def;				// ����
	int bulletCnt;			// �Ѿ� ��		
	*/

public:
	ItemData()
	{
		// ����
		_info[TO_INT(Code::ITEM::SHOT_SWORD)]	= { Code::ITEM_KIND::WEAPON, Code::ITEM::SHOT_SWORD, Code::ITEM_GRADE::COMMON, "���ҵ�", "\"������ �ֵθ��� ���� ��\"", 10, 8, 10, 3.03f };
		_info[TO_INT(Code::ITEM::BAMBOO_SWORD)]	= { Code::ITEM_KIND::WEAPON, Code::ITEM::BAMBOO_SWORD, Code::ITEM_GRADE::UNCOMMON, "�׵�", "\"�� ���� �˼� �Ʒ��� �� �� ���Ǵ� ��\"", 300, 5, 6, 4.06f };
		_info[TO_INT(Code::ITEM::LIGHTSABER)]	= { Code::ITEM_KIND::WEAPON, Code::ITEM::LIGHTSABER, Code::ITEM_GRADE::RARE, "����Ʈ ���̹�", "\"����� �ö���� Į�� ��� ��� �� ��������� ����\"", 1000, 12, 12, 4.58f };
		_info[TO_INT(Code::ITEM::LIGHTSABER)].ability = "��� ����";
		_info[TO_INT(Code::ITEM::COSMOSSWORD)]	= { Code::ITEM_KIND::WEAPON, Code::ITEM::COSMOSSWORD, Code::ITEM_GRADE::LEGEND, "���ְ�", "\"�� ���� ���մ� ������ �ź��� ��.\"", 1700, 15, 25, 3.17f };
		_info[TO_INT(Code::ITEM::THREETIEREDBATON)]	= { Code::ITEM_KIND::WEAPON, Code::ITEM::THREETIEREDBATON, Code::ITEM_GRADE::UNCOMMON, "��ܺ�", "\"ȣ�ſ����� ���Ǵ�, 3������ ������ �ܺ�.\"", 500, 8, 9, 3.85f };
		_info[TO_INT(Code::ITEM::LALA)]			= { Code::ITEM_KIND::WEAPON, Code::ITEM::LALA, Code::ITEM_GRADE::LEGEND, "����� �����", "\"���� �ҳ� ��� �Ҿ���� ������̴�.\"", 2000, 13, 20, 2.0f, 0, 12 };
		_info[TO_INT(Code::ITEM::COLT)]			= { Code::ITEM_KIND::WEAPON, Code::ITEM::COLT, Code::ITEM_GRADE::COMMON, "�� ��Ʈ", "\"�״� ��θ� �����Ӱ� �߰�, �׳�� ��θ� ����ϰ� �ߴ�.\"", 500, 3, 5, 8.33f, 1, 12 };
		_info[TO_INT(Code::ITEM::GATLINGGUN)]	= { Code::ITEM_KIND::WEAPON, Code::ITEM::GATLINGGUN, Code::ITEM_GRADE::LEGEND, "N134 ��Ʋ�� �����", "\"������ ��Ʋ�� ����Ѻ��� �۾����� �̴ϰ��̴�.\"", 2000, 2, 6, 21.74f, 0, 100 };
		//_info[TO_INT(Code::ITEM::SPEAR)]		= { Code::ITEM_KIND::WEAPON, Code::ITEM::SPEAR, Code::ITEM_GRADE::LEGEND, "N134 ��Ʋ�� �����", "\"������ ��Ʋ�� ����Ѻ��� �۾����� �̴ϰ��̴�.\"", 2000, 2, 6, 21.74f, 0, 100 };
		// �Ǽ�
		_info[TO_INT(Code::ITEM::MULTI_BULLET)]	= { Code::ITEM_KIND::ACCESSORY, Code::ITEM::MULTI_BULLET, Code::ITEM_GRADE::RARE, "������ź", "\"ź�� �� ������ ������ �ѷ��ش�. ���ݷµ� �� ������ �ȴ�.\"", 1500, "�Ѿ��� 3������ �߻������, ������� ����" };
		_info[TO_INT(Code::ITEM::MAGNIFYINGGLASS)]	= { Code::ITEM_KIND::ACCESSORY, Code::ITEM::MAGNIFYINGGLASS, Code::ITEM_GRADE::UNCOMMON, "������ ������", "\"���� ����� ������ �� ũ�� ����� �ݴϴ�.\"", 800, "�Ѿ��� ũ�Ⱑ Ŀ���� ������� ����������, ���ݼӵ� 30% ����" };
		_info[TO_INT(Code::ITEM::WINGBOOTS)]	= { Code::ITEM_KIND::ACCESSORY, Code::ITEM::WINGBOOTS, Code::ITEM_GRADE::UNCOMMON, "�� ����", "\"�߰����� ���� ���������ϴ�.\"", 600, "���� ��������, �뽬 Ƚ�� 1 ����" };
		_info[TO_INT(Code::ITEM::BULLION2)]		= { Code::ITEM_KIND::ACCESSORY, Code::ITEM::BULLION2, Code::ITEM_GRADE::UNCOMMON, "��ݱ�", "\"������ �ȸ� ���� ������...?\"", 2380, "���� �Ǹ� �� 1666 ���" };
		_info[TO_INT(Code::ITEM::LEATHERARMOR)]	= { Code::ITEM_KIND::ACCESSORY, Code::ITEM::LEATHERARMOR, Code::ITEM_GRADE::COMMON, "���׿�", "\"�������� �� �� ������ ������� �ʴ´�.\"", 600, "" };
		_info[TO_INT(Code::ITEM::LEATHERARMOR)].def = 8;
		_info[TO_INT(Code::ITEM::CHAINARMOR)]	= { Code::ITEM_KIND::ACCESSORY, Code::ITEM::CHAINARMOR, Code::ITEM_GRADE::COMMON, "�罽����", "\"��������, �Ҹ��� Ŀ�� �߰����� ����Ǵ� ����\"", 1400, "" };
		_info[TO_INT(Code::ITEM::CHAINARMOR)].def = 11;
		_info[TO_INT(Code::ITEM::CharmOfAttack)]	= { Code::ITEM_KIND::ACCESSORY, Code::ITEM::CharmOfAttack, Code::ITEM_GRADE::COMMON, "������ ����", "\"���� ���� Ȯ���ϸ�, ������ ȿ���� ������ϴ�.\"", 400, "" };
		_info[TO_INT(Code::ITEM::CharmOfAttack)].power = 8;
		_info[TO_INT(Code::ITEM::CharmOfMadness)]	= { Code::ITEM_KIND::ACCESSORY, Code::ITEM::CharmOfMadness, Code::ITEM_GRADE::UNCOMMON, "������ ����", "\"�ŸӸ��� �پ� �ִ� �ұ��� ����� ��� ������ �Ѵ�.\"", 1800, "" };
		_info[TO_INT(Code::ITEM::CharmOfMadness)].power = 20;
		_info[TO_INT(Code::ITEM::CharmOfMadness)].hp = -20;
		_info[TO_INT(Code::ITEM::Jarngreipr)]	= { Code::ITEM_KIND::ACCESSORY, Code::ITEM::Jarngreipr, Code::ITEM_GRADE::RARE, "�߸��׷�������", "\"�߰ſ� ���⸦ ���� �� �ְ� �����ִ� �尩\"", 1600, "�Ѽչ��� ���� �� ���ݼӵ� 50% ����" };
		_info[TO_INT(Code::ITEM::Speedloader)]	= { Code::ITEM_KIND::ACCESSORY, Code::ITEM::Speedloader, Code::ITEM_GRADE::RARE, "���ǵ� ���δ�", "\"�ѱ���� �������� �����ִ� �ⱸ\"", 1600, "�������ӵ� 70% ����" };
		_info[TO_INT(Code::ITEM::DaisyRing)]	= { Code::ITEM_KIND::ACCESSORY, Code::ITEM::DaisyRing, Code::ITEM_GRADE::LEGEND, "������ ����", "\"����� �帮�ھ��.\"", 3000, "�뽬 Ƚ�� 2 ����, ��ų ��Ÿ�� 80% ����" };
		// ��
		_info[TO_INT(Code::ITEM::MagicShield)]	= { Code::ITEM_KIND::ARMOR, Code::ITEM::MagicShield, Code::ITEM_GRADE::UNCOMMON, "���� ����", "\"���и� �ٶ�� ��������� ���ܳ���.\"", 500, "" };
		_info[TO_INT(Code::ITEM::MagicShield)].def = 8;
	}
	~ItemData() {}

	ITEM_INFO getInfo(Code::ITEM code) { return _info[TO_INT(code)]; }

};

