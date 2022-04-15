#pragma once
#include "Item.h"
class Sword : public Item
{
private:
	BOOL _isFirst;

public:
	Sword(Code::ITEM code);
	virtual ~Sword();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual RECT attack() override;

};

