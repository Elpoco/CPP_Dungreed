#pragma once
#include "UI.h"

namespace EnemyHpBarSet
{
	constexpr float ENEMY_HP_BAR_W = 60;
	constexpr float ENEMY_HP_BAR_H = 15;
}

class EnemyHpBar : public UI
{
private:
	ImageBase* _imgBack;
	ImageBase* _imgGauge;
	RECT	   _rcGauge;

	BOOL _isBoss;

	float*	_x;
	float*	_y;
	float	_moveY;
	int*	_maxHp;
	int*	_curHp;
	int		_hpMaxWidth;
	int		_hpWidth;

public:
	EnemyHpBar(float* x, float* y, int* maxHp, int* curHp);
	virtual ~EnemyHpBar();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void settingY(float y) { _moveY = y; }

};

