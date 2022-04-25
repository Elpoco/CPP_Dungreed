#pragma once
#include "SingletonBase.h"

class UI;
class Cursor;
class Inventory;
class MiniMap;

class UIManager : public SingletonBase<UIManager>
{
private:
	Cursor* _cursor;
	Inventory* _inventory;	
	MiniMap* _miniMap;

public:
	UIManager();
	~UIManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void setCursorType(UIEnum::CURSOR_TYPE cursorType);

	void initInventory();
	BOOL onInventory();
	void toggleInventory();

	void initPlayerHpBar(int* maxHp, int* curHp);

	void initMiniMap();
	void updateMiniMap();

};

