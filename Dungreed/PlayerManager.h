#pragma once
#include "SingletonBase.h"
#pragma warning(disable:4996)

namespace PlayerManagerSet
{
	constexpr float DEFAULT_DASH_TIME = 1.5f;
	constexpr int DEFAULT_DASH_CNT = 2;
	constexpr int DEFAULT_HP = 80;
}

class PlayerManager : public SingletonBase<PlayerManager>
{
private:
	int _level;

	float _dashChargeTime;
	float _dashTime;
	int _dashMaxCnt;
	int _dashCnt;

	int _maxHp;
	int _curHp;

	int _coin;

	BOOL _trueDmg;

	POINT* _ptPlayerBody;
	POINT* _ptPlayerHand;
	BOOL* _isPlayerLeft;

public:
	PlayerManager();
	~PlayerManager();

	HRESULT init();
	void release();
	void update();
	void render();

	int getLevel() { return _level; }

	void dash();
	void chargeDash();
	BOOL canDash() { return _dashCnt < 1; }
	int getDashCnt() { return _dashCnt; }
	int getDashMaxCnt() { return _dashMaxCnt; }
	void addDashCnt(int cnt) { _dashMaxCnt += cnt; }

	// ���
	void addCoin(int coin) { _coin += coin; }
	void useCoin(int coin) { _coin -= coin; }
	int getCoin() { return _coin; }
	char* getCoinChar()
	{
		string str = to_string(_coin);
		int len = str.length();
		char* arrChar;
		arrChar = new char[len];
		strcpy(arrChar, str.c_str());
		return arrChar;
	}

	// ü��
	void hit(int dmg);
	void recovery(int hp);

	// ������ ����
	void setTrueDmg(BOOL b) { _trueDmg = b; }
	BOOL getTrueDmg() { return _trueDmg; }

	void setPlayerBody(POINT* pt) { _ptPlayerBody = pt; }
	void setPlayerHand(POINT* pt) { _ptPlayerHand = pt; }
	void setPlayerLeft(BOOL* isLeft) { _isPlayerLeft = isLeft; }
	POINT getPlayerBody() { return *_ptPlayerBody; }
	POINT getPlayerHand() { return *_ptPlayerHand; }
	BOOL getPlayerIsLeft() { return *_isPlayerLeft; }

};

