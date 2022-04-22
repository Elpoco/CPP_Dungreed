#include "Stdafx.h"
#include "PlayerHpBar.h"

using namespace PlayerHpBarSet;

PlayerHpBar::PlayerHpBar()
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
}

void PlayerHpBar::render(HDC hdc)
{
	_back->render(hdc, _rc.left, _rc.top);
	//_hpBar->render(hdc, _rc.left + hpStartX - 3, _rc.top + hpStartY);
	_hpWave->frameRender(hdc, _rc.left + hpStartX + 189, _rc.top + hpStartY, _waveFrame.x, _waveFrame.y);
	_base->render(hdc, _rc.left, _rc.top);
}

void PlayerHpBar::settingUI()
{
	_base = FindImage(ImageName::UI::PlayerHpBar::Base);
	_back = FindImage(ImageName::UI::PlayerHpBar::Back);
	_hpBar = FindImage(ImageName::UI::PlayerHpBar::LifeBar);
	_hpWave = FindImage(ImageName::UI::PlayerHpBar::LifeWave);
	_rc = RectMake(baseX, baseY, _base->getWidth(), _base->getHeight());

	_waveFrame.maxFrameX = _hpWave->getMaxFrameX();
	_waveFrame.width = _hpWave->getFrameWidth();
	_waveFrame.height = _hpWave->getFrameHeight();
}

void PlayerHpBar::animation()
{
	if (++_waveFrame.cnt > _waveFrame.tick)
	{
		_waveFrame.cnt = 0;
		_waveFrame.x++;

		if (_waveFrame.x > _waveFrame.maxFrameX) _waveFrame.x = 0;
	}
}
