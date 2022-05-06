#pragma once
#include "Unit.h"

class Enemy : public Unit
{
protected:
	ENEMY_INFO _info;

	bool	_isAutoLeft;	// �÷��̾� ��ġ�� ���� �ڵ����� ��������
	int		_maxHp;
	int		_curHp;
	BOOL	_startSpawn;
	BOOL	_isSpawn;

	RECT	_rcScan;		// �÷��̾� Ž�� ����
	POINT	_scanScale;		// Ž�� ���� ����
	RECT	_rcPlayer;		// �÷��̾� ��Ʈ
	POINT	_ptPlayer;		// �÷��̾� ��ġ
	int		_isPlayerScan;	// �÷��̾� Ž�� �ߴ���

	int		_isDead;
	bool	_isAttack;

	float _moveHpBarX;
	float _moveHpBarY;

	vector<float> _atkBulletTime;

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
	void setAtkBulletTime(float bulletTime) { _atkBulletTime.push_back(bulletTime); }
	BOOL findAtkBulletTime(float bulletTime) { return find(_atkBulletTime.begin(), _atkBulletTime.end(), bulletTime) == _atkBulletTime.end(); }
	virtual int getDmg() override { return _info.dmg; }

	virtual void settingHpBar();

	void scanPlayer(POINT ptPlayer, RECT rcPlayer);
	inline RECT getScanRect() { return _rcScan; }
	inline int getPlayerScan() { return _isPlayerScan; }

	inline void settingHp(int hp) { _maxHp = _curHp = hp; }
	inline BOOL isSpawn() { return _isSpawn; }

	inline void doneSpawn() { _isSpawn = TRUE; }
};

