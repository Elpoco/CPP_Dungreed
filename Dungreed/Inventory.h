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

	Item* _arrItems[InventorySet::CELL_CNT]; // �κ��丮�� ����ִ� ������
	Item* _arrEquipWeapon[2];	// ���� ����
	Item* _arrEquipArmor[2];	// ���� ��
	BOOL _equipIdx;				// ���� �ε��� 0 or 1

	// ������� (�����ϴ�)
	UI* _equipBase;
	UI* _equipBaseBack;
	RECT _rcEquipBase;
	BOOL _isSawp;  // TRUE�ϵ��� �ڽ� ������
	int _swapTick; // �����̴°� üũ

	// �κ��丮
	POINT _ptCell[InventorySet::CELL_CNT];
	RECT _rcCell[InventorySet::CELL_CNT];
	int _clickCell;

	// ������� (�κ��丮)
	UI* _equipSlot[2];
	POINT _ptEquipSlot[SLOT_CNT];
	RECT _rcEquipSlot[SLOT_CNT];

	POINT _ptAcc[InventorySet::ACC_CNT];
	RECT _rcAcc[InventorySet::ACC_CNT];

	// ���콺 ������ ������
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

