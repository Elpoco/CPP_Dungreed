#pragma once
#include "Item.h"
class Spear : public Item
{
public:
	Spear(Code::ITEM code);
	virtual ~Spear();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual RECT attack() override;

	virtual void equip();
	virtual void unequip();
};

