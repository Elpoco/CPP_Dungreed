#pragma once
#include "UI.h"

namespace FoodShopSet
{
	constexpr int FOOD_CNT = 5;
	constexpr int TOTAL_FOOD = 10;
}

class FoodShop : public UI
{
private:
	struct tagFood
	{
		ImageBase* img;
		string name;
		int price;
		int recovery;

		BOOL isSell;
		tagFood()
		{
			isSell = FALSE;
		}
	};

private:
	ImageBase* _imgBack;
	ImageBase* _imgTable;
	ImageBase* _imgButton;
	UI* _uiLabel;
	UI* _uiBase0;
	UI* _uiBase3;
	UI* _uiMenu[FoodShopSet::FOOD_CNT];
	UI* _uiMenuSelect;
	UI* _uiRect;
	UI* _uiCoin;
	UI* _uiEsc;

	FRAME_INFO _tableFrame;
	RECT _rcExitBtn;
	tagFood _food[FoodShopSet::TOTAL_FOOD];
	

public:
	FoodShop();
	virtual ~FoodShop();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void show();
	virtual void hide();

	void initUI();
	void animation();

	void clickEvent();

};

