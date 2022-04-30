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

	BOOL _isUI; // ���� UI�� �ִ���

	Inventory* _inventory;	
	MiniMap* _miniMap;

	map<KEY, tagKeyboard> _mKey; // Ű �̹��� �����ٶ�

	BOOL _isShowReload;
	UI* _uiReloadBar;
	UI* _uiReloadBase;
	float _reloadX;
	float _reloadY;
	float _reloadTime;
	float _reloadStartTime;

	// ������ ����
	UI*			_uiItemInfo;
	ITEM_INFO	_itemInfo;
	ImageBase*	_imgItem;
	RECT		_rcItem;
	int			_uiCneterX;

	BOOL	_isShowItemInfo;
	float	_itemInfoX;
	float	_itemInfoY;


public:
	UIManager();
	~UIManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void setCursorType(UIEnum::CURSOR_TYPE cursorType);

	void initInventory();
	void toggleInventory();

	void initPlayerHpBar(int* maxHp, int* curHp);

	void initMiniMap();
	void updateMiniMap();
	void enterDungeon();

	void initKeyboard();
	void showKeyboard(KEY key, float x, float top);
	void updateKeyboard();

	void initReload();
	void updateReload();
	void showReloadBar(float reloadTime);

	void initItemInfo();
	void showItemInfo(ITEM_INFO itemInfo);
	void hideItemInfo();

	BOOL isUI() { return _isUI; }
	void onUI() { _isUI = TRUE; }
	void offUI() { _isUI = FALSE; }

};

