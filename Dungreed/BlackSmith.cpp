#include "Stdafx.h"
#include "BlackSmith.h"

BlackSmith::BlackSmith()
	: _isDrop(FALSE)
{
}

BlackSmith::~BlackSmith()
{
}

HRESULT BlackSmith::init()
{
	return S_OK;
}

void BlackSmith::release()
{
}

void BlackSmith::update()
{
}

void BlackSmith::render(HDC hdc)
{
}

void BlackSmith::show()
{
	ITEMMANAGER->dropItem(RND->getRndEnum(Code::ITEM::SHOT_SWORD, Code::ITEM::ITEM_CNT), _x, _y);
}
