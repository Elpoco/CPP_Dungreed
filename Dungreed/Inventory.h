#pragma once
#include "UI.h"

class Item;
class Button;

namespace InventorySet
{
	constexpr int CLICK_NONE = -1;
	constexpr int CELL_CNT = 15;
	constexpr int ACC_CNT = 4;
}

class Inventory : public UI
{
private:
	enum SLOT_POINT
	{
		WEAPON_0,
		ARMOR_0,
		WEAPON_1,
		ARMOR_1,

		SLOT_CNT
	};

private:
	vector<UI*> _vUI;
	BOOL _isOpen;
	RECT _rcClose;

	Item* _arrItems[InventorySet::CELL_CNT]; // 인벤토리에 들고있는 아이템
	Item* _arrEquipWeapon[2];	// 착용 무기
	Item* _arrEquipArmor[2];	// 착용 방어구
	BOOL _equipIdx;				// 착용 인덱스 0 or 1

	// 착용장비 (우측하단)
	UI* _equipBase;
	UI* _equipBaseBack;
	RECT _rcEquipBase;
	BOOL _isSawp;  // TRUE일동안 박스 움직임
	int _swapTick; // 움직이는거 체크

	// 인벤토리
	POINT _ptCell[InventorySet::CELL_CNT];
	RECT _rcCell[InventorySet::CELL_CNT];
	int _clickCell;

	// 착용장비 (인벤토리)
	UI* _equipSlot[2];
	POINT _ptEquipSlot[SLOT_CNT];
	RECT _rcEquipSlot[SLOT_CNT];

	POINT _ptAcc[InventorySet::ACC_CNT];
	RECT _rcAcc[InventorySet::ACC_CNT];

	// 마우스 오버시 테투리
	ImageBase* _imgHover;
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
	Item* getEquipItem() { return _arrEquipWeapon[_equipIdx]; }

};

