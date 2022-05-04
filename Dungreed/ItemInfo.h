#pragma once
#include "UI.h"
class ItemInfo : public UI
{
private:
	ImageBase* _imgInfo;
	ImageBase* _imgItem;
	ITEM_INFO _itemInfo;

	RECT _rcItem;
	DWORD _itemColor;
	float _itemInfoX;
	float _itemInfoY;

	int _line;

public:
	ItemInfo();
	virtual ~ItemInfo();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void setInfo(ITEM_INFO info);

};

