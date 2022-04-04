#include "Stdafx.h"
#include "TownScene.h"

TownScene::TownScene()
{
}

TownScene::~TownScene()
{
}

HRESULT TownScene::init()
{
	_layer = IMAGEMANAGER->findImage(ImageName::Town::townLayerDay);

	return S_OK;
}

void TownScene::release()
{
}

void TownScene::update()
{
}

void TownScene::render()
{
	IMAGEMANAGER->render(ImageName::Town::cloud, getMemDC());
	IMAGEMANAGER->render(ImageName::Town::townBgDay, getMemDC());
	_layer->render(getMemDC(), 0, WINSIZE_Y - _layer->getHeight());
}
