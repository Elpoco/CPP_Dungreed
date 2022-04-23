#include "Stdafx.h"
#include "PlayerHpBar.h"

#include "ImageFont.h"

using namespace PlayerHpBarSet;

PlayerHpBar::PlayerHpBar(int* maxHp, int* curHp)
	: _maxHp(maxHp)
	, _curHp(curHp)
{
}

PlayerHpBar::~PlayerHpBar()
{
}

HRESULT PlayerHpBar::init()
{
	settingUI();

	return S_OK;
}

void PlayerHpBar::release()
{
}

void PlayerHpBar::update()
{
	animation();
	updateHpUi();
}

void PlayerHpBar::render(HDC hdc)
{
	_back->render(hdc, _rc.left, _rc.top);
	_hpBar->render(hdc, _hpStartX, _hpStartY, 0, 0, _hpWidth, 40);
	if(*_curHp > 0)
	_hpWave->frameRender(hdc, _hpStartX + _hpWidth - 4, _hpStartY, _waveFrame.x, _waveFrame.y);
	_base->render(hdc, _rc.left, _rc.top);
	_uiLevel->render(hdc);
	_uiSlash->render(hdc);
	_uiMaxHp->render(hdc);
	_uiCurHp->render(hdc);
}

void PlayerHpBar::settingUI()
{
	// 체력바 UI 설정
	_base = FindImage(ImageName::UI::PlayerHpBar::Base);
	_back = FindImage(ImageName::UI::PlayerHpBar::Back);
	_hpBar = FindImage(ImageName::UI::PlayerHpBar::LifeBar);
	_hpWave = FindImage(ImageName::UI::PlayerHpBar::LifeWave);
	_rc = RectMake(baseX, baseY, _base->getWidth(), _base->getHeight());

	_imgBaseWidth = _base->getWidth();
	_imgBaseHeight = _base->getHeight();

	_waveFrame.maxFrameX = _hpWave->getMaxFrameX();
	_waveFrame.width = _hpWave->getFrameWidth();
	_waveFrame.height = _hpWave->getFrameHeight();

	_hpMaxWidth = _hpWidth = _hpBar->getWidth();
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

void PlayerHpBar::updateHpUi()
{
	_uiMaxHp->setNumber(*_maxHp);
	_uiCurHp->setNumber(*_curHp);
}
