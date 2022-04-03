#include "Stdafx.h"
#include "SkelDog.h"

SkelDog::SkelDog()
{
}

SkelDog::~SkelDog()
{
}

HRESULT SkelDog::init()
{
	Enemy::init();
	this->initAnimation();

	return S_OK;
}

void SkelDog::release()
{
	Enemy::release();
}

void SkelDog::update()
{
	Enemy::update();
}

void SkelDog::render(HDC hdc)
{
	Enemy::render(hdc);
}

void SkelDog::initAnimation()
{
	_vImages.push_back(IMAGEMANAGER->findImage(ImageName::Enemy::dogIdle));

	_imgWidth = _vImages[0]->getFrameWidth();
	_imgHeight = _vImages[0]->getFrameHeight();
}
