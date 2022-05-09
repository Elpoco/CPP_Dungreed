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
	enum INVENTORY_ENUM
	{
		WEAPON_0, WEAPON_1,
		SUB_WEAPON_0, SUB_WEAPON_1,
		WEAPON_CNT = 2,

		ACC_0 = 4,
		ACC_1, ACC_2, ACC_3,
		ACC_CNT,
		EQUIP_CNT = 8,

		INVEN_0 = 8,
		INVEN_1, INVEN_2, INVEN_3,
		INVEN_4, INVEN_5, INVEN_6, 
		INVEN_7, INVEN_8, INVEN_9,
		INVEN_10, INVEN_11, INVEN_12,
		INVEN_13, INVEN_14,
		INVEN_CNT
	};

	typedef struct tagSlotInfo
	{
		Item* item;
		RECT rc;
		POINT pt;
	} SLOT_INFO;

private:
	vector<UI*> _vUI;
	BOOL _isOpen;
	RECT _rcClose;

	// ������� (�����ϴ�)
	UI* _equipBase;
	UI* _equipBaseBack;
	RECT _rcEquipBase;
	BOOL _isSawp;  // TRUE�ϵ��� �ڽ� ������
	int _swapTick; // �����̴°� üũ

	// ������� (�κ��丮)
	UI* _equipSlot[2];

	// �κ��丮
	SLOT_INFO _arrSlot[INVEN_CNT];
	RECT _rcBase;
	BOOL _equipIdx;				// ���� �ε��� 0 or 1
	int _clickCell;

	// ���콺 ������ ������
	ImageBase* _imgHover;
	ImageBase* _imgInvenHover;
	BOOL _isHover;
	RECT _rcHover;

	// ��ų
	UI* _uiSkill;

	Code::ITEM _lastItemCode;

public:
	Inventory();
	virtual ~Inventory();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void settingUI();
	void open();
	void close();
	// ���콺 ���� ���
	void clickEvent();
	int checkCell();
	void onClick();
	void offClick();
	void hoverSlot();
	void equipClick();
	void sellItem();
	// ������ Ÿ�� ��
	BOOL checkType(int cellIdx, Item* item);

	void swapEquipSlot();
	void changeEquipSlot(int idx);
	void renderEquipBase(HDC hdc); // ���� �ϴ� ����
	void renderInventoryItem(HDC hdc);

	BOOL addItem(Item* item);

	BOOL isOpen() { return _isOpen; }
	Item* getEquipItem() { return _arrSlot[_equipIdx].item; }
	Code::ITEM getEquipAccCode(int idx);

	void clearInventory();

};

