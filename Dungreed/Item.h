#pragma once
#include "Object.h"

class Item : public Object
{
protected:
	ITEM_INFO _info;
	ImageBase* _img;
	FRAME_INFO _frameInfo;

	BOOL _isEquip;
	int _angle;

	POINT* _ptHand;
	BOOL* _isLeft;

public:
	Item(Code::ITEM itemCode);
	virtual ~Item();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual RECT attack() { return { 0,0,0,0 }; }

	void equip() { _isEquip = TRUE; }
	void unequip() { _isEquip = FALSE; }

	void setPos(POINT* pt) { _ptHand = pt; }
	void setIsLeft(BOOL* isLeft) { _isLeft = isLeft; }
	
};

