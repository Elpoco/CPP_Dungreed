#pragma once

class ItemData
{
private:
	ITEM_INFO _info[TO_INT(Code::ITEM::ITEM_CNT)];
	/*
	Code::ITEM_TYPE type; // ������ Ÿ��
	Code::ITEM code;	  // ������ �ڵ�
	string name;		  // ������ �̸�
	int point;			  // ������ ���� ��ġ
	int maxPoint;		  // ������ ���� �ִ�ġ	(�⺻�� 0)
	*/

public:
	ItemData()
	{
		_info[TO_INT(Code::ITEM::COIN)]		= { Code::ITEM_TYPE::GOLD, Code::ITEM::COIN, "����",  10 };
		_info[TO_INT(Code::ITEM::BULLION)]	= { Code::ITEM_TYPE::GOLD, Code::ITEM::BULLION, "�ݵ��", 100 };

		// ����
		_info[TO_INT(Code::ITEM::SHOT_SWORD)] = { Code::ITEM_TYPE::WEAPON, Code::ITEM::SHOT_SWORD, "���ҵ�", 8, 10 };
	}
	~ItemData() {}

	ITEM_INFO getInfo(Code::ITEM code) { return _info[(int)code]; }

};

