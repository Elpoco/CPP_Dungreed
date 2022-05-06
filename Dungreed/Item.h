#pragma once
#include "Object.h"

class Skill;

class Item : public Object
{
protected:
	ITEM_INFO	_itemInfo;
	ImageBase*	_img;
	FRAME_INFO	_frameInfo;

	BOOL _isEquip;
	float _handleX;
	float _handleY;

	float	_angle;
	int		_degree;

	float _lastAttack;

	Skill* _skill;

public:
	Item(Code::ITEM itemCode);
	virtual ~Item();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual RECT attack() { return { 0,0,0,0 }; }
	void skill();

	virtual BULLET_INFO getBulletInfo() { return { 0,0 }; }

	void updateDegree();

	void itemHover();

	virtual void equip() { _isEquip = TRUE; }
	virtual void unequip() { _isEquip = FALSE; }

	inline ImageBase* getImage() { return _img; }
	inline FRAME_INFO getFrameInfo() { return _frameInfo; }
	inline virtual int getDmg() override { return RND->getFromIntTo(_itemInfo.minDmg, _itemInfo.maxDmg); }
	inline Code::ITEM_KIND getItemType() { return _itemInfo.type; }
	inline ITEM_INFO getInfo() { return _itemInfo; }

	inline BOOL isSkill() { return _skill != nullptr; }
	string getSkillIconName();
	float getSkillCooltime();
	float getSkillRunTime();
	BOOL isSkillUing();

};
