#pragma once
#include "Unit.h"

class EnemyHpBar;

class Enemy : public Unit
{
protected:
	bool	_isAutoLeft;	// 플레이어 위치에 따라 자동으로 변경할지
	float	_hp;
	float	_maxHp;

	RECT	_rcScan;		// 플레이어 탐지 범위
	POINT	_scanScale;		// 탐지 범위 배율
	RECT	_rcPlayer;		// 플레이어 렉트
	POINT	_ptPlayer;		// 플레이어 위치
	int		_isPlayerScan;	// 플레이어 탐지 했는지

	int		_isDead;
	bool	_isAttack;

	EnemyHpBar* _hpBar;

public:
	Enemy();
	~Enemy();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void move();
	void animation();

	virtual void hitAttack(int dmg) override;

	void scanPlayer(POINT ptPlayer, RECT rcPlayer);
	inline RECT getScanRect() { return _rcScan; }
	inline int getPlayerScan() { return _isPlayerScan; }
	inline void settingHp(int hp) { _maxHp = _hp = hp; }

};

