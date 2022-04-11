#include "Stdafx.h"
#include "Niflheim.h"

#include "NiflheimPillar.h"

Niflheim::Niflheim(float x, float y)
	: _skill(NIFLHEIM_SKILL::NONE)
{
	_startSpawn = TRUE;
	_isSpawn = TRUE;

	_x = x;
	_y = y;
}

Niflheim::~Niflheim()
{
}

HRESULT Niflheim::init()
{
	Enemy::init();
	this->initAnimation();
	Unit::updateRect();

	_name = "니플헤임";
	_isFlying = true;

	for (int i = 0; i < PILLAR_CNT; i++)
	{
		int intervalX = i % 2;
		int intervalY = i / 2;
		_pillar[i] = new NiflheimPillar(_x + 115 - 250 * intervalX, _y + 115 - 250 * intervalY);
		_pillar[i]->setPosAddress(&_x, &_y);
		OBJECTMANAGER->addObject(ObjectEnum::TYPE::ENEMY, _pillar[i]);
	}

	return S_OK;
}

void Niflheim::release()
{
	Enemy::release();
	for (int i = 0; i < PILLAR_CNT; i++)
	{
		if (_pillar[i])
		{
			_pillar[i]->deleteObject();
		}
	}
}

void Niflheim::update()
{
	Enemy::update();
	this->move();
	Unit::updateRect();
	this->animation();
}

void Niflheim::render(HDC hdc)
{
	Enemy::render(hdc);
}

void Niflheim::deleteEffect()
{
}

void Niflheim::move()
{
}

void Niflheim::animation()
{
}

void Niflheim::initAnimation()
{
	_vImages.push_back(IMAGEMANAGER->findImage(ImageName::Enemy::Niflheim::idle));
	_vImages.push_back(IMAGEMANAGER->findImage(ImageName::Enemy::Niflheim::attack));

	_imgWidth = _vImages[0]->getFrameWidth();
	_imgHeight = _vImages[0]->getFrameHeight();
}
