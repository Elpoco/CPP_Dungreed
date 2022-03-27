#include "Stdafx.h"
#include "UIManager.h"

#include "UI.h"

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

HRESULT UIManager::init()
{
	return S_OK;
}

void UIManager::release()
{
}

void UIManager::update()
{
}

void UIManager::render()
{
	viUI iter = _vUi.begin();
	for (; iter != _vUi.end(); ++iter)
	{
		(*iter)->render();
	}
}

void UIManager::addUI(UI* ui)
{
	_vUi.push_back(ui);
}
