#pragma once
#include "Object.h"

class Item : public Object
{
protected:
	enum class ITEM_TYPE
	{
		NONE,
		SWORD
	};

private:
	string _name;
	ITEM_TYPE _type;

	ImageGp* _img;

	int _isEquit;

public:
	Item();
	Item(string name);
	virtual ~Item();

	virtual HRESULT init() override;
	HRESULT init(string name);
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	
};

