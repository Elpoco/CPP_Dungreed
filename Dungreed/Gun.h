#pragma once
#include "Item.h"

class Gun : public Item
{
private:
	float _shootingX;
	float _shootingY;
	float _angle;
	float _reloadTime;
	int _bulletCnt;

public:
	Gun(Code::ITEM code);
	virtual ~Gun();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual RECT attack() override;

	void settingShootingPoint();
};

