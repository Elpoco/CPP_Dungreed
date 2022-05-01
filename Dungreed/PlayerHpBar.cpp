#include "Stdafx.h"
#include "PlayerHpBar.h"

#include "ImageFont.h"

using namespace PlayerHpBarSet;

PlayerHpBar::PlayerHpBar(int* maxHp, int* curHp)
	: _maxHp(maxHp)
	, _curHp(curHp)
{
	_isFixed = TRUE;
}

PlayerHpBar::~PlayerHpBar()
{
}

HRESULT PlayerHpBar::init()
{
	settingUI();
	settingDashUI();

	return S_OK;
}

void PlayerHpBar::release()
{
}

void PlayerHpBar::update()
{
	animation();
	updateHpUI();

	_uiLevel->setNumber(PLAYERMANAGER->getLevel());
}

void PlayerHpBar::render(HDC hdc)
{
	renderHpBar(hdc);
	renderDashBar(hdc);
}

void PlayerHpBar::settingUI()
{
	// 체력바 UI 설정
	_imgBase = FindImage(ImageName::UI::PlayerHpBar::Base);
	_imgBack = FindImage(ImageName::UI::PlayerHpBar::Back);
	_imgHpBar = FindImage(ImageName::UI::PlayerHpBar::LifeBar);
	_imgHpWave = FindImage(ImageName::UI::PlayerHpBar::LifeWave);
	_rc = RectMake(baseX, baseY, _imgBase->getWidth(), _imgBase->getHeight());

	_imgBaseWidth = _imgBase->getWidth();
	_imgBaseHeight = _imgBase->getHeight();

	_waveFrame.maxFrameX = _imgHpWave->getMaxFrameX();
	_waveFrame.width = _imgHpWave->getFrameWidth();
	_waveFrame.height = _imgHpWave->getFrameHeight();

	_hpMaxWidth = _hpWidth = _imgHpBar->getWidth();
	_hpStartX = _rc.left + hpSourX;
	_hpStartY = _rc.top + hpSourY;

	// 폰트설정
	_uiLevel = new ImageFont(_rc.left + levelX, _rc.top + _imgBaseHeight * 0.5f, 1);
	_uiLevel->init();

	_uiMaxHp = new ImageFont(
		_hpStartX + _hpMaxWidth * 0.5f + 50,
		_rc.top + _imgBaseHeight * 0.5f + 2,
		*_maxHp
	);
	_uiMaxHp->init();

	_uiCurHp = new ImageFont(
		_hpStartX + _hpMaxWidth * 0.5f - 50,
		_rc.top + _imgBaseHeight * 0.5f + 2,
		*_curHp
	);
	_uiCurHp->init();

	_uiSlash = new ImageFont(
		_hpStartX + _hpMaxWidth * 0.5f,
		_rc.top + _imgBaseHeight * 0.5f + 2,
		"/"
	);
	_uiSlash->init();
}

void PlayerHpBar::settingDashUI()
{
	_imgDashStart = FindImage(ImageName::UI::PlayerHpBar::DashStart);
	_imgDashEnd = FindImage(ImageName::UI::PlayerHpBar::DashEnd);
	_imgDashCnt = FindImage(ImageName::UI::PlayerHpBar::DashCount);

	_rcDash = RectMake(_rc.left, _rc.bottom + 5, _imgDashStart->getWidth(), _imgDashStart->getHeight());
	_dashEndWidth = _imgDashEnd->getWidth() - 8;
}

void PlayerHpBar::animation()
{
	if (_waveFrame.cnt++ > _waveFrame.tick)
	{
		_waveFrame.cnt = 0;
		_waveFrame.x++;

		if (_waveFrame.x > _waveFrame.maxFrameX) _waveFrame.x = 0;
	}

	_hpWidth = _hpMaxWidth * (*_curHp / (float)*_maxHp);
}

void PlayerHpBar::updateHpUI()
{
	_uiMaxHp->setNumber(*_maxHp);
	_uiCurHp->setNumber(*_curHp);
}

void PlayerHpBar::renderHpBar(HDC hdc)
{
	_imgBack->render(hdc, _rc.left, _rc.top);
	_imgHpBar->render(hdc, _hpStartX, _hpStartY, 0, 0, _hpWidth, 40);
	if (*_curHp > 0)
		_imgHpWave->frameRender(hdc, _hpStartX + _hpWidth - 4, _hpStartY, _waveFrame.x, _waveFrame.y);
	_imgBase->render(hdc, _rc.left, _rc.top);

	_uiLevel->render(hdc);
	_uiSlash->render(hdc);
	_uiMaxHp->render(hdc);
	_uiCurHp->render(hdc);
}

void PlayerHpBar::renderDashBar(HDC hdc)
{
	_imgDashStart->render(hdc, _rcDash.left, _rcDash.top);
	_dashMaxCnt = PLAYERMANAGER->getDashMaxCnt() - 1;
	_dashCnt = PLAYERMANAGER->getDashCnt();

	for (int i = 0; i < _dashMaxCnt; i++)
	{
		_imgDashEnd->render(hdc, _rcDash.right + _dashEndWidth * i, _rcDash.top);
	}
	for (int i = 0; i < _dashCnt; i++)
	{
		_imgDashCnt->render(hdc, _rcDash.left + 8 + _dashEndWidth * i, _rcDash.top + 8);
	}
}
