#pragma once
#include "SingletonBase.h"

class UI;
class Cursor;
class Inventory;

class UIManager : public SingletonBase<UIManager>
{
private:
	Cursor* _cursor;
	Inventory* _inventory;

public:
	UIManager();
	~UIManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void setCursorType(UIEnum::CURSOR_TYPE cursorType);

	void setInventory(Inventory* inventory) { _inventory = inventory; }
	BOOL onInventory();

};

