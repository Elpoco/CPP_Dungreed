#pragma once
#include "UI.h"

class Item;
class Button;

namespace InventorySet
{
	constexpr int CELL_CNT = 15;
}

class Inventory : public UI
{
private:
	Item* _vItems[InventorySet::CELL_CNT];
	vector<UI*> _vUI;
	BOOL _isOpen;

	RECT _rcClose;
	RECT _rcCell[InventorySet::CELL_CNT];

public:
	Inventory();
	~Inventory();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void settingUI();

	void toggleInventory();

};

