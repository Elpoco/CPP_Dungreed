#pragma once
#include "UI.h"

class Item;
class Button;

namespace InventorySet
{
	constexpr int CELL_CNT = 15;
	constexpr int CLICK_NONE = -1;
}

class Inventory : public UI
{
private:
	Item* _arrEquipWeapon[2];
	Item* _arrEquipArmor[2];
	Item* _arrItems[InventorySet::CELL_CNT];
	vector<UI*> _vUI;
	BOOL _isOpen;

	RECT _rcClose;
	POINT _ptCell[InventorySet::CELL_CNT];
	RECT _rcCell[InventorySet::CELL_CNT];

	BOOL _equipIdx;
	int _clickCell;

public:
	Inventory();
	~Inventory();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void settingUI();
	void toggleInventory();
	void sortItem();
	void onClick();
	void offClick();
	void dragItem();

	void changeEquip();

	BOOL isOpen() { return _isOpen; }
	Item* getEquipItem() { return _arrEquipWeapon[_equipIdx]; }

};

