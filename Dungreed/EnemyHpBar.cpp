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

	if (*_curHp <= 0) Object::deleteObject();

	_hpWidth = _hpMaxWidth * (*_curHp / (float)*_maxHp);
}

void EnemyHpBar::render(HDC hdc)
{
	if (*_curHp == *_maxHp) return;

	CAMERAMANAGER->render(hdc, _imgBack, _rc.left, _rc.top);
	CAMERAMANAGER->render(hdc, _imgGauge, _rcGauge.left, _rcGauge.top, 0, 0, _hpWidth, _imgGauge->getHeight());
}
