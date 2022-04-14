#pragma once
#include "Object.h"

class Item : public Object
{
protected:
	enum class ITEM_TYPE
	{
		NONE,
		WEAPON,
		ARMOR,
	};

private:
	string _name;
	ITEM_TYPE _type;
	ImageBase* _img;
	Code::Item _itemCode;

public:
	Item();
	virtual ~Item();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual RECT attack() { return { 0,0,0,0 }; }
	
};

