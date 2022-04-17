#pragma once
#include "UI.h"

class Item;
class Button;

namespace InventorySet
{
	constexpr int CLICK_NONE = -1;
}

class Inventory : public UI
{
private:
	enum SLOT_POINT
	{
		WEAPON_0, WEAPON_1,
		ARMOR_0, ARMOR_1,
		EQUIP_CNT,

		ACC_0 = 4,
		ACC_1, ACC_2, ACC_3,
		ACC_CNT,

		INVEN_0 = 8,
		INVEN_1, INVEN_2, INVEN_3,
		INVEN_4, INVEN_5, INVEN_6, 
		INVEN_7, INVEN_8, INVEN_9,
		INVEN_10, INVEN_11, INVEN_12,
		INVEN_13, INVEN_14,
		INVEN_CNT
	};

private:
	vector<UI*> _vUI;
	BOOL _isOpen;
	RECT _rcClose;


	// 착용장비 (우측하단)
	UI* _equipBase;
	UI* _equipBaseBack;
	RECT _rcEquipBase;
	BOOL _isSawp;  // TRUE일동안 박스 움직임
	int _swapTick; // 움직이는거 체크

	// 착용장비 (인벤토리)
	UI* _equipSlot[2];

	// 인벤토리
	Item* _arrItems[INVEN_CNT];  // 인벤토리 아이템
	POINT _ptInven[INVEN_CNT];   // UI 중심
	RECT _rcInven[INVEN_CNT];    // UI RECT
	BOOL _equipIdx;				// 착용 인덱스 0 or 1
	int _clickCell;

	// 마우스 오버시 테투리
	ImageBase* _imgHover;
	ImageBase* _imgInvenHover;
	BOOL _isHover;
	RECT _rcHover;

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
	void hoverSlot();

	void swapEquip();
	void renderEquipBase(HDC hdc);
	void renderInventoryItem(HDC hdc);

	BOOL isOpen() { return _isOpen; }
	Item* getEquipItem() { return _arrItems[_equipIdx]; }
	BOOL pickUpItem(Code::ITEM code);

};

