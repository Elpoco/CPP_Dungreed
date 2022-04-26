#include "Stdafx.h"
#include "PlayerManager.h"

using namespace PlayerManagerSet;

HRESULT PlayerManager::init()
{
	_dashMaxCnt = _dashCnt = DEFAULT_DASH_CNT;
	return S_OK;
}

void PlayerManager::release()
{
}

void PlayerManager::update()
{
}

void PlayerManager::render()
{
}
