#pragma once
#include "SingletonBase.h"

class ItemManager : public SingletonBase<ItemManager>
{

public:
	ItemManager();
	~ItemManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	string findCodeImage(Code::ITEM code);

	void dropItem(Code::ITEM code, float x, float y);

};

