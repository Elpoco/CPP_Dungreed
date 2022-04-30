#include "Stdafx.h"
#include "NPC.h"

#include "UI.h"
#include "ShopNPC.h"

NPC::NPC()
	: _isOpen(FALSE)
{
	_x = CENTER_X;
	_y = CENTER_Y;
}

NPC::~NPC()
{
}

HRESULT NPC::init()
{

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
	UIMANAGER->showKeyboard(KEY::F, _x, _rc.top);

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
}

void NPC::closeNpc()
{
	_isOpen = FALSE;
	UIMANAGER->offUI();
	for (auto ui : _vUI)
	{
		ui->hide();
	}
}
