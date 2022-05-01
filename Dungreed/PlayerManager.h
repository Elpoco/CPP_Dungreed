#pragma once
#include "SingletonBase.h"
#pragma warning(disable:4996)

namespace PlayerManagerSet
{
	constexpr int DEFAULT_DASH_CNT = 3;
	constexpr float DEFAULT_DASH_TIME = 1.5f;
}

class PlayerManager : public SingletonBase<PlayerManager>
{
private:
	float _dashChargeTime;
	float _dashTime;
	int _dashMaxCnt;
	int _dashCnt;
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

};

