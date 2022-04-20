#pragma once
#include "SingletonBase.h"

class Item;
class Inventory;

class ItemManager : public SingletonBase<ItemManager>
{
private:
	Inventory* _inventory;

	POINT* _ptPlayerBody;
	POINT* _ptPlayerHand;
	BOOL* _isPlayerLeft;

public:
	ItemManager();
	~ItemManager();

	HRESULT init();
	void release();

	void inventoryInit();

	void getItem(Code::ITEM code);
	Item* getEquipItem();

	ImageBase* findImage(Code::ITEM code);

	void dropItem(Code::ITEM code, float x, float y);
	void playItemEffect(Code::ITEM code, int x, int y, R_L dir);

	void setPlayerBody(POINT* pt) { _ptPlayerBody = pt; }
	void setPlayerHand(POINT* pt) { _ptPlayerHand = pt; }
	void setPlayerLeft(BOOL* isLeft) { _isPlayerLeft = isLeft; }
	POINT getPlayerBody() { return *_ptPlayerBody; }
	POINT getPlayerHand() { return *_ptPlayerHand; }
	BOOL getPlayerIsLeft() { return *_isPlayerLeft; }

};

