#pragma once
#include "Item.h"

class Gun : public Item
{
private:
	int _bulletCnt;

public:
	Gun(Code::ITEM code);
	virtual ~Gun();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual RECT attack() override;
};

