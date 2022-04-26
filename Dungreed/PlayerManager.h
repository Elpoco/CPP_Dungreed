#pragma once
#include "SingletonBase.h"

namespace PlayerManagerSet
{
	constexpr int DEFAULT_DASH_CNT = 3;
	constexpr float DEFAULT_DASH_TIME = 2.0f;
}

class PlayerManager : public SingletonBase<PlayerManager>
{
private:
	float _dashChargeTime;
	float _dashTime;
	int _dashMaxCnt;
	int _dashCnt;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void dash();
	void chargeDash();
	BOOL canDash() { return _dashCnt < 1; }
	int getDashCnt() { return _dashCnt; }
	int getDashMaxCnt() { return _dashMaxCnt; }

};

