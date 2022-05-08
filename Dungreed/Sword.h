#pragma once
#include "Item.h"

class Sword : public Item
{
private:
	string _effectName;
	string _soundName;
	BOOL _isFirst;

public:
	Sword(Code::ITEM code);
	virtual ~Sword();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual RECT attack() override;

	virtual void equip();
	virtual void unequip();

};

