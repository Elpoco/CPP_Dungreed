#include "Stdafx.h"
#include "EffectManager.h"

HRESULT EffectManager::init(void)
{
	IMAGEMANAGER->addFrameImage("effect_missile", "Resources/Images/Object/effect_missile.bmp", 0.0f, 0.0f, 330, 97, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("effect_beam", "Resources/Images/Object/effect_beam.bmp", 0.0f, 0.0f, 237, 73, 3, 1, true, RGB(255, 0, 255));
	return S_OK;
}

void EffectManager::release(void)
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		SAFE_DELETE(_viEffect->image);
	}
	_vEffect.clear();
}

void EffectManager::update(void)
{
	_viEffect = _vEffect.begin();
	for (; _viEffect != _vEffect.end();)
	{
		if (_viEffect->timeCount + _viEffect->worldTimeCount <= GetTickCount()) 
		{
			_viEffect->worldTimeCount = GetTickCount();
			if (_viEffect->image->getFrameX() == _viEffect->image->getMaxFrameX())
			{
				_viEffect = _vEffect.erase(_viEffect);
			}
			else
			{
				_viEffect->image->setFrameX(++_viEffect->currentX);
				++_viEffect;
			}
		}
		else ++_viEffect;
	}
}

void EffectManager::render(HDC hdc)
{
	_viEffect = _vEffect.begin();
	for (; _viEffect != _vEffect.end(); ++_viEffect)
	{
		_viEffect->image->frameRender(hdc,
			_viEffect->x - _viEffect->image->getFrameWidth() / 2,
			_viEffect->y - _viEffect->image->getFrameHeight() / 2,
			_viEffect->currentX, _viEffect->currentY);
	}
}

void EffectManager::addEffect(char* name, int x, int y)
{
	tagEffect effect;
	effect.image = IMAGEMANAGER->findImage(name);
	effect.x = x;
	effect.y = y;
	effect.timeCount = 150;
	effect.worldTimeCount = GetTickCount();
	effect.currentX = 0;
	effect.currentY = 0;
	_vEffect.push_back(effect);
}
