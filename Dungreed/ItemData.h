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
		_info[TO_INT(Code::ITEM::SHOT_SWORD)]	= { Code::ITEM_KIND::WEAPON, Code::ITEM::SHOT_SWORD, Code::ITEM_GRADE::COMMON, "���ҵ�", "\"������ �ֵθ��� ���� ��\"", 8, 10, 3.03f };
		_info[TO_INT(Code::ITEM::BAMBOO_SWORD)]	= { Code::ITEM_KIND::WEAPON, Code::ITEM::BAMBOO_SWORD, Code::ITEM_GRADE::COMMON, "�׵�", "\"�� ���� �˼� �Ʒ��� �� �� ���Ǵ� ��\"", 5, 6, 6.06f };
		_info[TO_INT(Code::ITEM::LIGHTSABER)]	= { Code::ITEM_KIND::WEAPON, Code::ITEM::LIGHTSABER, Code::ITEM_GRADE::RARE, "����Ʈ ���̹�", "\"����� �ö���� Į�� ��� ��� �� ��������� ����\"", 12, 12, 3.28f };
		_info[TO_INT(Code::ITEM::COLT)]			= { Code::ITEM_KIND::WEAPON, Code::ITEM::COLT, Code::ITEM_GRADE::COMMON, "�� ��Ʈ", "\"�״� ��θ� �����Ӱ� �߰�, �׳�� ��θ� ����ϰ� �ߴ�.\"", 3, 5, 8.33f, 1, 12 };
	}
	~ItemData() {}

	ITEM_INFO getInfo(Code::ITEM code) { return _info[TO_INT(code)]; }

};

