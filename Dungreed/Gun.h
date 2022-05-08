#pragma once
#include "Item.h"

namespace GunSet
{
	constexpr float DEFAULT_BULLET_SPEED = 7.0f;
	constexpr float DEFAULT_RELOAD_TICK = 1.2f;
}

class Gun : public Item
{
private:
	float _bulletSpeed;
	float _shootingX;
	float _shootingY;
	int _bulletCnt;

	BOOL	_isReload;
	float	_reloadStartTime;
	float	_reloadTick;
	
	string _bulletImgName;
	string _shootingImgName;
	string _hitImgName;
	BOOL _isPenetrate;
	BOOL _isAuto;
	BOOL _isSuper;

public:
	Gun(Code::ITEM code);
	virtual ~Gun();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual RECT attack() override;

	virtual BULLET_INFO getBulletInfo() { return { _bulletCnt, _itemInfo.bulletCnt }; }

	void settingShootingPoint();
};

