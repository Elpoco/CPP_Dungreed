#pragma once
#include "Object.h"
class Item : public Object
{
private:
	string _name;

public:
	Item();
	~Item();

	HRESULT init();
	HRESULT init(string name);
	void release();
	void update();
	void render(HDC hdc);
	
};

