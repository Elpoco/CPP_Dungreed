#pragma once
#include "SingletonBase.h"

class Item;

class ItemManager : public SingletonBase<ItemManager>
{

public:
	ItemManager();
	~ItemManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	Item* getItem(Code::ITEM code);

	ImageBase* findCodeImage(Code::ITEM code);

	void dropItem(Code::ITEM code, float x, float y);

};

