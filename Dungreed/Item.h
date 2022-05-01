#pragma once
#include "Object.h"

class Item : public Object
{
protected:
	ITEM_INFO _info;
	ImageBase* _img;
	FRAME_INFO _frameInfo;
	float _handleX;
	float _handleY;

	BOOL _isEquip;
	int _degree;

	float _lastAttack;

	BOOL _isHover;

public:
	Item(Code::ITEM itemCode);
	virtual ~Item();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual RECT attack() { return { 0,0,0,0 }; }

	virtual BULLET_INFO getBulletInfo() { return { 0,0 }; }

	void updateDegree();

	void itemHover();

	virtual void equip() { _isEquip = TRUE; }
	virtual void unequip() { _isEquip = FALSE; }

	inline ImageBase* getImage() { return _img; }
	inline virtual int getDmg() override { return RND->getFromIntTo(_info.minDmg, _info.maxDmg); }
	inline Code::ITEM_KIND getItemType() { return _info.type; }
	inline ITEM_INFO getInfo() { return _info; }

};
