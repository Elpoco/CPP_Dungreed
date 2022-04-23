#pragma once
#include "UI.h"

class ImageFont;

namespace PlayerHpBarSet
{
	constexpr int baseX = 10;
	constexpr int baseY = 10;
	constexpr int hpSourX = 88;
	constexpr int hpSourY = 12;
	constexpr int levelX = 46;
}

class PlayerHpBar : public UI
{
private:
	// 체력바
	ImageBase* _base;
	ImageBase* _back;
	ImageBase* _hpBar;
	ImageBase* _hpWave;
	FRAME_INFO _waveFrame;

	int _imgBaseWidth;
	int _imgBaseHeight;

	int _hpMaxWidth;
	int _hpWidth;
	int _hpStartX;
	int _hpStartY;

	int* _maxHp;
	int* _curHp;

	// 폰트
	ImageFont* _uiLevel;
	ImageFont* _uiMaxHp;
	ImageFont* _uiCurHp;
	ImageFont* _uiSlash;

public:
	PlayerHpBar(int* maxHp, int* curHp);
	virtual ~PlayerHpBar();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void settingUI();

	void animation();
	void updateHpUi();

};
