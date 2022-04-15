#pragma once

class ItemData
{
private:
	ITEM_INFO _info[(int)Code::ITEM::ITEM_CNT];

public:
	ItemData()
	{
		_info[Code::ITEM::COIN] = { "동전", Code::ITEM_TYPE::GOLD, 10 };
		_info[Code::ITEM::BULLION] = { "금덩어리", Code::ITEM_TYPE::GOLD, 100 };
	}
	~ItemData() {}

	ITEM_INFO getInfo(Code::ITEM code) { return _info[(int)code]; }

};

