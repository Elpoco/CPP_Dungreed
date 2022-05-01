#pragma once
#include "UI.h"

class Ability : public UI
{
private:
	ImageBase* _imgBack;
	ImageBase* _imgButton;
	UI* _uiLabel;
	UI* _uiEsc;

	RECT _rcExitBtn;

public:
	Ability();
	virtual ~Ability();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void show();
	virtual void hide();

	void initUI();
	void animation();

};

