#pragma once
#include "Unit.h"
class Enemy : public Unit
{
protected:
	float	_hp;
	bool	_isAutoLeft;	// �÷��̾� ��ġ�� ���� �ڵ����� ��������

	RectF	_rcScan;		// �÷��̾� Ž�� ����
	POINT	_scanScale;		// Ž�� ���� ����
	PointF	_ptPlayer;		// �÷��̾� ��ġ
	RectF	_rcPlayer;		// �÷��̾� ��Ʈ
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

	inline RectF getScanRect() { return _rcScan; }
	inline int getPlayerScan() { return _isPlayerScan; }
	void scanPlayer(PointF ptPlayer, RectF rcPlayer);

};

