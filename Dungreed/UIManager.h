#pragma once
#include "SingletonBase.h"

class Cursor;

class UIManager : public SingletonBase<UIManager>
{
private:
	Cursor* _cursor;

public:
	UIManager();
	~UIManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void setCursor(UIEnum::CURSOR_TYPE cursorType);

};

