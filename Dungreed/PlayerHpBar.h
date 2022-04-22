#pragma once
#include "UI.h"

namespace PlayerHpBarSet
{
	constexpr int baseX = 10;
	constexpr int baseY = 10;
	constexpr int hpStartX = 88;
	constexpr int hpStartY = 12;
}

class PlayerHpBar : public UI
{
private:
	ImageBase* _base;
	ImageBase* _back;
	ImageBase* _hpBar;
	ImageBase* _hpWave;

	FRAME_INFO _waveFrame;

public:
	PlayerHpBar();
	virtual ~PlayerHpBar();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void settingUI();

	void animation();

};
