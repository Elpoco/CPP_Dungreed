#pragma once
#include "SingletonBase.h"

class Item;
class Inventory;

class ItemManager : public SingletonBase<ItemManager>
{
private:
	Inventory* _inventory;

public:
	ItemManager();
	~ItemManager();

	HRESULT init();
	void release();

	void setInventory(Inventory* inventory) { _inventory = inventory; }

	Item* getItem(Code::ITEM code);
	BOOL giveItem(Code::ITEM code);
	BOOL giveItem(Item* item);
	Item* getEquipItem();
	Code::ITEM getEquipAccCode(int idx);

	ImageBase* findImage(Code::ITEM code);

	void dropItem(Code::ITEM code, float x, float y, BOOL scatter = FALSE);

};

