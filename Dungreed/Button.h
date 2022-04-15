#pragma once
#include "UI.h"

class Button : public UI
{
private:
	CALLBACK_FUNC _callback;
	BOOL _isHoverImg;
	BOOL _isOn;

public:
	Button(string imgName, int x = 0, int y = 0, BOOL fixed = TRUE, CALLBACK_FUNC cb = nullptr);
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
