#pragma once
#include "Unit.h"

class EnemyHpBar;

class Enemy : public Unit
{
protected:
	ENEMY_INFO _info;

	bool	_isAutoLeft;	// �÷��̾� ��ġ�� ���� �ڵ����� ��������
	float	_hp;
	float	_maxHp;
	BOOL	_startSpawn;
	BOOL	_isSpawn;

	RECT	_rcScan;		// �÷��̾� Ž�� ����
	POINT	_scanScale;		// Ž�� ���� ����
	RECT	_rcPlayer;		// �÷��̾� ��Ʈ
	POINT	_ptPlayer;		// �÷��̾� ��ġ
	int		_isPlayerScan;	// �÷��̾� Ž�� �ߴ���

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

