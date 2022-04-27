#pragma once
#include "SingletonBase.h"

class UI;
class Cursor;
class Inventory;
class MiniMap;

class UIManager : public SingletonBase<UIManager>
{
private:
	struct tagKeyboard
	{
		UI* key;
		BOOL isShow;

		tagKeyboard() {}
		tagKeyboard(UI* key)
		{
			this->key = key;
			isShow = FALSE;
		}
	};

private:
	Cursor* _cursor;
	Inventory* _inventory;	
	MiniMap* _miniMap;
	map<KEY, tagKeyboard> _mKey;

public:
	UIManager();
	~UIManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void setCursorType(UIEnum::CURSOR_TYPE cursorType);
	void reloadUI(float reloadTime);

	void initInventory();
	BOOL onInventory();
	void toggleInventory();

	void initPlayerHpBar(int* maxHp, int* curHp);

	void initMiniMap();
	void updateMiniMap();
	void enterDungeon();

	void initKeyboard();
	void showKeyboard(KEY key, float x, float top);
	void updateKeyboard();

};

