#include "Stdafx.h"
#include "MapToolScene.h"

HRESULT MapToolScene::init(void)
{
	return S_OK;
}

void MapToolScene::release(void)
{
}

void MapToolScene::update(void)
{
}

void MapToolScene::render(void)
{
	IMAGEMANAGER->render("Tile1", getMemDC());
}
