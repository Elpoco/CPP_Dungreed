#pragma once
#include "UI.h"

class Item;
class Button;

class Inventory : public UI
{
private:
	vector<Item*> _vItems;
	bool _isOpen;
	UI* _invenBase;
	Button* _btnClose;
	vector<UI*> _vUI;

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

