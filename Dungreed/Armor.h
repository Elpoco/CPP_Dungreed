#pragma once
#include "Item.h"

class Armor : public Item
{
public:
	Armor(Code::ITEM code);
	virtual ~Armor();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void equip();
	virtual void unequip();
};

