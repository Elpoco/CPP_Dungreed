#include "Stdafx.h"
#include "EnemyHpBar.h"

using namespace EnemyHpBarSet;

EnemyHpBar::EnemyHpBar(float* x, float* y, int* maxHp, int* curHp)
	: _x(x)
	, _y(y)
	, _maxHp(maxHp)
	, _curHp(curHp)
	, _isBoss(FALSE)
{
}

EnemyHpBar::~EnemyHpBar()
{
}

HRESULT EnemyHpBar::init()
{
	_imgBack = FindImage(ImageName::UI::MonsterHpBar::back);
	_imgGauge = FindImage(ImageName::UI::MonsterHpBar::gauge);

	_rc = RectMakeCenter(*_x, *_y + _moveY, _imgBack->getWidth(), _imgBack->getHeight());
	_rcGauge = RectMakeCenter(*_x, *_y + _moveY, _imgGauge->getWidth(), _imgGauge->getHeight());

	_hpMaxWidth = _hpWidth = _imgGauge->getWidth();

	return S_OK;
}

void EnemyHpBar::release()
{
}

void EnemyHpBar::update()
{
	if (!_isBoss)
	{
		_rc = RectMakeCenter(
			*_x,
			*_y + _moveY + 20,
			_imgBack->getWidth(),
			_imgBack->getHeight()
		);
		_rcGauge = RectMakeCenter(
			*_x,
			*_y + _moveY + 20,
			_imgGauge->getWidth(),
			_imgGauge->getHeight()
		);
	}

	if (*_curHp <= 0) Object::deleteObject();

	_hpWidth = _hpMaxWidth * (*_curHp / (float)*_maxHp);
}

void EnemyHpBar::render(HDC hdc)
{
	if (*_curHp == *_maxHp && !_isBoss) return;

	if (_isBoss)
	{
		_imgBack->render(hdc, _rc.left, _rc.top);
		_imgGauge->render(hdc, _rcGauge.left, _rcGauge.top, 0, 0, _hpWidth, _imgGauge->getHeight());
		_imgPortrait->render(hdc, _rc.left + 9, _rc.top + 9);
		_imgFront->render(hdc, _rc.left, _rc.top);
	}
	else
	{
		CAMERAMANAGER->render(hdc, _imgBack, _rc.left, _rc.top);
		CAMERAMANAGER->render(hdc, _imgGauge, _rcGauge.left, _rcGauge.top, 0, 0, _hpWidth, _imgGauge->getHeight());
	}
}

void EnemyHpBar::setBossHpBar()
{
	_isBoss = TRUE;
	_isFixed = TRUE;

	_imgBack = FindImage(ImageName::UI::MonsterHpBar::BossLifeBack);
	_imgFront = FindImage(ImageName::UI::MonsterHpBar::BossLifeBase);
	_imgGauge = FindImage(ImageName::UI::MonsterHpBar::BossLifeGauge);
	_imgPortrait = FindImage(ImageName::UI::MonsterHpBar::BossSkellPortrait);

	_rc = RectMakeCenter(CENTER_X, CENTER_Y + 265, _imgBack->getWidth(), _imgBack->getHeight());
	_rcGauge = RectMakeCenter(CENTER_X + 28, CENTER_Y + 265, _imgGauge->getWidth(), _imgGauge->getHeight());

	_hpMaxWidth = _hpWidth = _imgGauge->getWidth();
}
