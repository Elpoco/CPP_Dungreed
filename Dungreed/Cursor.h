#pragma once
#include "UI.h"

class Cursor : public UI
{
private:
	typedef struct tagCursorInfo
	{
		ImageBase* img;
		bool isCenter;
	} CURSOR_INFO;

private:
	vector<tagCursorInfo> _vCursor;
	UIEnum::CURSOR_TYPE _cursorCurrent;

public:
	Cursor();
	virtual ~Cursor();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void setCursor(UIEnum::CURSOR_TYPE cursorType) { _cursorCurrent = cursorType; }

};

