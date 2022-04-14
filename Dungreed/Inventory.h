#pragma once

class Item;
class UI;

class Inventory
{
private:
	vector<Item*> _vItems;
	BOOL _isOpen;
	UI* _inven;

public:
	Inventory();
	~Inventory();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

};

