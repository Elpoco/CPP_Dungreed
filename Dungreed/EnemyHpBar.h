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
	RECT _rcMaxHp;
	RECT _rcCurHp;
	float* _x;
	float* _y;
	float* _maxHp;
	float* _curHp;
	float _moveY;

public:
	EnemyHpBar(float* x, float* y, int* maxHp, int* curHp);
	virtual ~EnemyHpBar();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void settingY(float y) { _moveY = y; }

};

