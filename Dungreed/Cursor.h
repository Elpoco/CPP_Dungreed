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

	enum CURSOR_CURRENT
	{
		NONE,
		TARGET
	};

private:
	vector<tagCursorInfo> _vCursor;
	CURSOR_CURRENT _cursorCurrent;

public:
	Cursor();
	virtual ~Cursor();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void setCursor(CURSOR_CURRENT cursorType) { _cursorCurrent = cursorType; }

};

