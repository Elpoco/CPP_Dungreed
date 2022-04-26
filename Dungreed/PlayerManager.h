#pragma once
#include "SingletonBase.h"

namespace PlayerManagerSet
{
	constexpr int DEFAULT_DASH_CNT = 3;
}

class PlayerManager : public SingletonBase<PlayerManager>
{
private:
	int _dashMaxCnt;
	int _dashCnt;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void dash() { _dashCnt--; }
	BOOL canDash() { return _dashCnt < 1; }
	int getDashCnt() { return _dashCnt; }
	int getDashMaxCnt() { return _dashMaxCnt; }

};

