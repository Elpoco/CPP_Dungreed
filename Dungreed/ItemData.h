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
		_info[TO_INT(Code::ITEM::LIGHTSABER)]	= { Code::ITEM_KIND::WEAPON, Code::ITEM::LIGHTSABER, Code::ITEM_GRADE::RARE, "����Ʈ ���̹�", "\"����� �ö���� Į�� ��� ��� �� ��������� ����\"", 1000, 12, 12, 6.28f };
		_info[TO_INT(Code::ITEM::LIGHTSABER)].ability = "��� ����";
		_info[TO_INT(Code::ITEM::COSMOSSWORD)]	= { Code::ITEM_KIND::WEAPON, Code::ITEM::COSMOSSWORD, Code::ITEM_GRADE::LEGEND, "���ְ�", "\"�� ���� ���մ� ������ �ź��� ��.\"", 2500, 30, 45, 3.17f };
		_info[TO_INT(Code::ITEM::COLT)]			= { Code::ITEM_KIND::WEAPON, Code::ITEM::COLT, Code::ITEM_GRADE::COMMON, "�� ��Ʈ", "\"�״� ��θ� �����Ӱ� �߰�, �׳�� ��θ� ����ϰ� �ߴ�.\"", 500, 3, 5, 8.33f, 1, 12 };
		_info[TO_INT(Code::ITEM::GATLINGGUN)]	= { Code::ITEM_KIND::WEAPON, Code::ITEM::GATLINGGUN, Code::ITEM_GRADE::LEGEND, "N134 ��Ʋ�� �����", "\"������ ��Ʋ�� ����Ѻ��� �۾����� �̴ϰ��̴�.\"", 3000, 2, 6, 21.74f, 0, 100 };
		// �Ǽ�
		_info[TO_INT(Code::ITEM::MULTI_BULLET)]	= { Code::ITEM_KIND::ACCESSORY, Code::ITEM::MULTI_BULLET, Code::ITEM_GRADE::RARE, "������ź", "\"ź�� �� ������ ������ �ѷ��ش�. ���ݷµ� �� ������ �ȴ�.\"", 1500, "�Ѿ��� 3������ �߻������, ������� ����" };
		_info[TO_INT(Code::ITEM::MAGNIFYINGGLASS)]	= { Code::ITEM_KIND::ACCESSORY, Code::ITEM::MAGNIFYINGGLASS, Code::ITEM_GRADE::UNCOMMON, "������ ������", "\"���� ����� ������ �� ũ�� ����� �ݴϴ�.\"", 800, "�Ѿ��� ũ�Ⱑ Ŀ���� ������� ����������, ���ݼӵ� 30% ����" };
		_info[TO_INT(Code::ITEM::WINGBOOTS)]	= { Code::ITEM_KIND::ACCESSORY, Code::ITEM::WINGBOOTS, Code::ITEM_GRADE::UNCOMMON, "�� ����", "\"�߰����� ���� ���������ϴ�.\"", 600, "���� ��������, ��� Ƚ�� 1 ����" };
	}
	~ItemData() {}

	ITEM_INFO getInfo(Code::ITEM code) { return _info[TO_INT(code)]; }

};

