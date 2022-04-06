#pragma once
#include "Unit.h"
class Enemy : public Unit
{
protected:
	float	_hp;
	bool	_isAutoLeft;	// �÷��̾� ��ġ�� ���� �ڵ����� ��������

	RECT	_rcScan;		// �÷��̾� Ž�� ����
	POINT	_scanScale;		// Ž�� ���� ����
	POINT	_ptPlayer;		// �÷��̾� ��ġ
	RECT	_rcPlayer;		// �÷��̾� ��Ʈ
	int		_isPlayerScan;	// �÷��̾� Ž�� �ߴ���
	int		_isDead;

	BYTE	_state;
	bool	_isAttack;
	

public:
	Enemy();
	~Enemy();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void move();
	void animation();

	inline RECT getScanRect() { return _rcScan; }
	inline int getPlayerScan() { return _isPlayerScan; }
	void scanPlayer(POINT ptPlayer, RECT rcPlayer);

};

