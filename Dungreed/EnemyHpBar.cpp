#include "Stdafx.h"
#include "EnemyHpBar.h"

EnemyHpBar::EnemyHpBar()
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

void EnemyHpBar::update(float x, float y, float per)
{
	_rcMaxHp = RectMakeCenter(x, y, ENEMY_HP_BAR_W, ENEMY_HP_BAR_H);
	_rcCurHp = RectMake(_rcMaxHp.left + 4, _rcMaxHp.top + 4, (ENEMY_HP_BAR_W - 8)*per, ENEMY_HP_BAR_H - 8);
}

void EnemyHpBar::render(HDC hdc)
{
	CAMERAMANAGER->printRectangle(hdc, _rcMaxHp, Color::Black, true, Color::Black);
	CAMERAMANAGER->printRectangle(hdc, _rcCurHp, Color::Red, true, Color::Red);
}
