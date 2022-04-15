#pragma once
#include "Unit.h"

class EnemyHpBar;

class Enemy : public Unit
{
protected:
	ENEMY_INFO _info;

	bool	_isAutoLeft;	// 플레이어 위치에 따라 자동으로 변경할지
	float	_hp;
	float	_maxHp;
	BOOL	_startSpawn;
	BOOL	_isSpawn;

	RECT	_rcScan;		// 플레이어 탐지 범위
	POINT	_scanScale;		// 탐지 범위 배율
	RECT	_rcPlayer;		// 플레이어 렉트
	POINT	_ptPlayer;		// 플레이어 위치
	int		_isPlayerScan;	// 플레이어 탐지 했는지

	int		_isDead;
	bool	_isAttack;

	EnemyHpBar* _hpBar;
	float _moveHpBarX;
	float _moveHpBarY;

public:
	Enemy();
	virtual ~Enemy();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void deleteEffect() override;

	void move();
	void animation();

	virtual void hitAttack(int dmg, int dir) override;

	void scanPlayer(POINT ptPlayer, RECT rcPlayer);
	inline RECT getScanRect() { return _rcScan; }
	inline int getPlayerScan() { return _isPlayerScan; }

	inline void settingHp(int hp) { _maxHp = _hp = hp; }
	inline BOOL isSpawn() { return _isSpawn; }

	inline void doneSpawn() { _isSpawn = TRUE; }
};

