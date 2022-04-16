#pragma once

class ItemData
{
private:
	ITEM_INFO _info[TO_INT(Code::ITEM::ITEM_CNT)];
	/*
	Code::ITEM_TYPE type; // ������ Ÿ��
	Code::ITEM code;	  // ������ �ڵ�
	string name;		  // ������ �̸�
	int minDmg;			  // ������ �ּ� ���ݷ�
	int maxDmg;			  // ������ �ִ� ���ݷ�
	float atkSpeed;		  // ���ݼӵ�
	int def;			  // ����
	int etc;			  // ��Ÿ ��ġ  ( ���̸� �Ѿ� )
	*/

public:
	ItemData()
	{
		// ����
		_info[TO_INT(Code::ITEM::SHOT_SWORD)]	= { Code::ITEM_TYPE::WEAPON, Code::ITEM::SHOT_SWORD, "���ҵ�", 8, 10, 0.303f };
		_info[TO_INT(Code::ITEM::COLT)]			= { Code::ITEM_TYPE::WEAPON, Code::ITEM::COLT, "�� ��Ʈ", 3, 5, 0.833f, 1, 12 };
	}
	~ItemData() {}

	ITEM_INFO getInfo(Code::ITEM code) { return _info[(int)code]; }

};

