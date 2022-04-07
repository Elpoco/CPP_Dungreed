#pragma once
#include "Unit.h"

class EnemyHpBar;

class Enemy : public Unit
{
protected:
	bool	_isAutoLeft;	// �÷��̾� ��ġ�� ���� �ڵ����� ��������
	float	_hp;
	float	_maxHp;

	RECT	_rcScan;		// �÷��̾� Ž�� ����
	POINT	_scanScale;		// Ž�� ���� ����
	RECT	_rcPlayer;		// �÷��̾� ��Ʈ
	POINT	_ptPlayer;		// �÷��̾� ��ġ
	int		_isPlayerScan;	// �÷��̾� Ž�� �ߴ���

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

