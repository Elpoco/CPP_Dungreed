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

	// 골드
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

	// 체력
	void hit(int dmg);
	void recovery(int hp);

	// 아이템 관련
	void setTrueDmg(BOOL b) { _trueDmg = b; }
	BOOL getTrueDmg() { return _trueDmg; }

};

