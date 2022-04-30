#include "Stdafx.h"
#include "NPC.h"

#include "UI.h"
#include "ItemShop.h"

NPC::NPC()
	: _isOpen(FALSE)
{
	_x = CENTER_X;
	_y = CENTER_Y;
}

NPC::NPC(Code::NPC code, float x, float y)
	: _code(code)
{
	_x = x;
	_y = y;
}

NPC::~NPC()
{
}

HRESULT NPC::init()
{
	_uiNPC = new ItemShop(&_img);
	_uiNPC->hide();
	OBJECTMANAGER->addUI(_uiNPC);
	initAnimation();

	return S_OK;
}

void NPC::release()
{
}

void NPC::update()
{
	updateAnimation();

	if (_isOpen && !UIMANAGER->isUI()) closeNpc();
}

void NPC::render(HDC hdc)
{
	CAMERAMANAGER->frameRender(hdc, _img, _rc.left, _rc.top, _frameInfo.x, _frameInfo.y);
}

void NPC::initAnimation()
{
	_frameInfo.maxFrameX = _img->getMaxFrameX();

	int width = _img->getFrameWidth();
	int height = _img->getFrameHeight();
	_rc = RectMakeCenter(_x, _y - height * 0.5f, width, height);
}

void NPC::updateAnimation()
{
	if (!_img) return;

	if (_frameInfo.cnt++ > _frameInfo.tick)
	{
		_frameInfo.cnt = 0;
		if (++_frameInfo.x > _frameInfo.maxFrameX) _frameInfo.x = 0;
	}
}

void NPC::collisionObject()
{
	if(!_isOpen) UIMANAGER->showKeyboard(KEY::F, _x, _rc.top);

	if(IsOnceKeyDown(KEY::F) && !UIMANAGER->isUI()) openNpc();
}

void NPC::openNpc()
{
	_isOpen = TRUE; 
	UIMANAGER->onUI();
	for (auto ui : _vUI)
	{
		ui->show();
	}
	_uiNPC->show();
}

void NPC::closeNpc()
{
	_isOpen = FALSE;
	UIMANAGER->offUI();
	for (auto ui : _vUI)
	{
		ui->hide();
	}
	_uiNPC->hide();
}
