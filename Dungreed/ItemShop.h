#pragma once
#include "UI.h"

namespace ItemShopSet
{
	constexpr int MAX_ITEM_CNT = 6;
}

class ItemShop : public UI
{
private:
	Code::NPC _code;
	UI* _uiBase;
	UI* _uiSelect;
	UI* _arrUI[ItemShopSet::MAX_ITEM_CNT];
	RECT _rcSlots[ItemShopSet::MAX_ITEM_CNT];
	
	vector<Item*> _vItems;

	int _itemCnt;

public:
	ItemShop();
	ItemShop(Code::NPC code);
	virtual ~ItemShop();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void show();

	void initUI();

	void renderItemSlot(HDC hdc);
	void hoverImg();

	void clickEvent();
	void clickItem();

};

