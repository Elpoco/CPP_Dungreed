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
	ImageBase* _imgBase;
	ImageBase* _imgBack;
	ImageBase* _imgHpBar;
	ImageBase* _imgHpWave;
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

	// 대시
	ImageBase* _imgDashStart;
	ImageBase* _imgDashEnd;
	ImageBase* _imgDashCnt;
	RECT _rcDash;
	int _dashEndWidth;
	int _dashCnt;
	int _dashMaxCnt;

public:
	PlayerHpBar(int* maxHp, int* curHp);
	virtual ~PlayerHpBar();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void settingUI();
	void settingDashUI();

	void animation();
	void updateHpUI();

	void renderHpBar(HDC hdc);
	void renderDashBar(HDC hdc);

};
