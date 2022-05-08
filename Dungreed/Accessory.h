#pragma once
#include "Item.h"

class Accessory : public Item
{
public:
	Accessory(Code::ITEM code);
	virtual ~Accessory();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void equip(); 
	virtual void unequip();

};

