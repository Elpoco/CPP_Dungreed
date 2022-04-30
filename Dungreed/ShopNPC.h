#pragma once
#include "NPC.h"

namespace ShopNPCSet
{
	constexpr int MAX_ITEM_CNT = 6;
}

class ShopNPC : public NPC
{
private:
	UI* _uiBase;
	UI* _uiSelect;
	UI* _arrUI[ShopNPCSet::MAX_ITEM_CNT];
	RECT _arrRcUI[ShopNPCSet::MAX_ITEM_CNT];

	int _itemCnt;

public:
	ShopNPC(float x, float y);
	virtual ~ShopNPC();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void initAnimation();
	void initUI();

	void hoverImg();

	virtual void openNpc() override;
	virtual void closeNpc() override;

};

