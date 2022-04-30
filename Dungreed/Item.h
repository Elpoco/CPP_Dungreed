#pragma once
#include "Object.h"

class Item : public Object
{
protected:
	ITEM_INFO _info;
	ImageBase* _img;
	FRAME_INFO _frameInfo;
	float _handle;

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

	void updateDegree();

	void itemHover();

	void equip() { _isEquip = TRUE; }
	void unequip() { _isEquip = FALSE; }

	ImageBase* getImage() { return _img; }
	inline virtual int getDmg() override { return RND->getFromIntTo(_info.minDmg, _info.maxDmg); }
	inline Code::ITEM_KIND getItemType() { return _info.type; }

};
