#pragma once

class ItemData
{
private:
	ITEM_INFO _info[(int)Code::ITEM::ITEM_CNT];

public:
	ItemData()
	{
		_info[Code::ITEM::COIN] = { "����", Code::ITEM_TYPE::GOLD, 10 };
		_info[Code::ITEM::BULLION] = { "�ݵ��", Code::ITEM_TYPE::GOLD, 100 };
	}
	~ItemData() {}

	ITEM_INFO getInfo(Code::ITEM code) { return _info[(int)code]; }

};

