#pragma once
#include "UI.h"

typedef void(*CALLBACK_FUNC)();

class Button : public UI
{
private:
	ImageBase* _imgOn;
	BOOL _isHoverImg;
	BOOL _isOn;

	CALLBACK_FUNC _callback;

public:
	Button(string imgName, int x, int y, BOOL fixed = TRUE, CALLBACK_FUNC cb = nullptr, string imgNameOn = "");
	virtual ~Button();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	inline void setOn() { _isOn = TRUE; }
	inline void setOff() { _isOn = FALSE; }

	inline void setCallback(CALLBACK_FUNC cb) { _callback = cb; }
	inline void onClick() { if (_callback) _callback(); }

};