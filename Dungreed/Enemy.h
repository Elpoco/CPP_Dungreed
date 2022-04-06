#pragma once
#include "Unit.h"
class Enemy : public Unit
{
protected:
	float	_hp;
	bool	_isAutoLeft;	// 플레이어 위치에 따라 자동으로 변경할지

	RECT	_rcScan;		// 플레이어 탐지 범위
	POINT	_scanScale;		// 탐지 범위 배율
	POINT	_ptPlayer;		// 플레이어 위치
	RECT	_rcPlayer;		// 플레이어 렉트
	int		_isPlayerScan;	// 플레이어 탐지 했는지
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

