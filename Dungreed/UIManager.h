#pragma once
#include "SingletonBase.h"

class UI;
class Cursor;
class Inventory;
class MiniMap;
class ImageFont;
class ItemInfo;
class DropItemInfo;

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

	BOOL _isUI; // 켜진 UI가 있는지

	Inventory* _inventory;	
	MiniMap* _miniMap;

	map<KEY, tagKeyboard> _mKey; // 키 이미지 보여줄때

	BOOL _isShowReload;
	UI* _uiReloadBar;
	UI* _uiReloadBase;
	float _reloadX;
	float _reloadY;
	float _reloadTick;
	float _reloadStartTime;

	// 아이템 정보
	ItemInfo*   _uiItemInfo;
	DropItemInfo* _uiDropItemInfo;
	ITEM_INFO	_itemInfo;
	BOOL _isShowItemInfo;
	float _itemInfoTime;

	UI* _bossIntro;
	ImageFont* _bossInfo;
	BOOL _showBossInfo;
	float _showStartTime;
	float _showInfoTime;

	ImageFont* _mapInfo;
	BOOL _showMapInfo;
	BOOL _isIn;
	float _infoSpeed;
	
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
	void updateKeyboard();
	void showKeyboard(KEY key, float x, float top);

	void initReload();
	void updateReload();
	void showReloadBar(float reloadTick);

	// ==============
	// # 아이템 정보 #
	// ==============
	void initItemInfo();
	void showItemInfo(ITEM_INFO itemInfo);
	void showDropItemInfo(ITEM_INFO itemInfo);
	void updateDropItemInfo();

	BOOL isUI() { return _isUI; }
	void onUI() { _isUI = TRUE; }
	void offUI() { _isUI = FALSE; }

	void initBossInfo();
	void showBossInfo(char* bossName);
	void updateBossInfo();

	void initMapInfo();
	void showMapInfo(char* mapName);
	void updateMapInfo();

};

