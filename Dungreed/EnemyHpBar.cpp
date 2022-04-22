#include "Stdafx.h"
#include "EnemyHpBar.h"

using namespace EnemyHpBarSet;

EnemyHpBar::EnemyHpBar(float* x, float* y, int* maxHp, int* curHp)
	: _x(x)
	, _y(y)
	, _maxHp((float*)maxHp)
	, _curHp((float*)curHp)
{
}

EnemyHpBar::~EnemyHpBar()
{
}

HRESULT EnemyHpBar::init()
{
	return S_OK;
}

void EnemyHpBar::release()
{
}

void EnemyHpBar::update()
{
	_rcMaxHp = RectMakeCenter(
		*_x, 
		*_y + _moveY + ENEMY_HP_BAR_H,
		ENEMY_HP_BAR_W,
		ENEMY_HP_BAR_H
	);

	_rcCurHp = RectMake(
		_rcMaxHp.left + 4,
		_rcMaxHp.top + 4, 
		(ENEMY_HP_BAR_W - 8) * (*_curHp / *_maxHp),
		ENEMY_HP_BAR_H - 8
	);

	if (*_curHp <= 0) Object::deleteObject();
}

void EnemyHpBar::render(HDC hdc)
{
	if (*_curHp == *_maxHp) return;

	CAMERAMANAGER->printRectangle(hdc, _rcMaxHp, Color::Black, true, Color::Black);
	CAMERAMANAGER->printRectangle(hdc, _rcCurHp, Color::Red, true, Color::Red);
}
