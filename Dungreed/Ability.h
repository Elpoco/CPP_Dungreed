#pragma once
#include "UI.h"

class Ability : public UI
{
private:
	ImageBase* _imgButton;
	UI* _uiLabel;
	UI* _uiR;

	RECT _rcExitBtn;

	UI* _uiWrath;
	UI* _uiPatience;
	UI* _uiGreed;
	ImageBase* _imgAblityBtn[AbilitySet::ABILITY_CNT];
	RECT _rcBtn[AbilitySet::ABILITY_CNT];
	BOOL _isHover[AbilitySet::ABILITY_CNT];

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

	void clickBtn(int idx);

};

