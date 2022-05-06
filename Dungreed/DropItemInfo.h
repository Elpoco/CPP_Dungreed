#pragma once
#include "UI.h"

class DropItemInfo : public UI
{
private:
	ImageBase* _imgInfo;
	ImageBase* _imgItem;
	ITEM_INFO _itemInfo;
	RECT _rcInfo;

	RECT _rcItem;
	DWORD _itemColor;
	float _itemInfoX;
	float _itemInfoY;

public:
	DropItemInfo();
	virtual ~DropItemInfo();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void setInfo(ITEM_INFO info);

};

