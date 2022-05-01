#pragma once
#include "SingletonBase.h"
#pragma warning(disable:4996)

namespace PlayerManagerSet
{
	constexpr float DEFAULT_DASH_TIME = 1.5f;
	constexpr int DEFAULT_DASH_CNT = 3;
	constexpr int DEFAULT_HP = 80;
}

class PlayerManager : public SingletonBase<PlayerManager>
{
private:
	float _dashChargeTime;
	float _dashTime;
	int _dashMaxCnt;
	int _dashCnt;

	int _maxHp;
	int _curHp;

	int _coin;

public:
	PlayerManager();
	~PlayerManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void dash();
	void chargeDash();
	BOOL canDash() { return _dashCnt < 1; }
	int getDashCnt() { return _dashCnt; }
	int getDashMaxCnt() { return _dashMaxCnt; }

	// °ñµå
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

	// Ã¼·Â
	void hit(int dmg);
	void recovery(int hp);

};

