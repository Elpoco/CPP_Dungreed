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
	~Item();

	HRESULT init();
	HRESULT init(string name);
	void release();
	void update();
	void render(HDC hdc);
	
};

