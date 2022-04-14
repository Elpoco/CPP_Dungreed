#pragma once
#include "SingletonBase.h"

class ItemManager : public SingletonBase<ItemManager>
{

public:
	ItemManager();
	~ItemManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	string findCodeImage(Code::Item code);

	void dropItem(Code::Item code, float x, float y);

};

