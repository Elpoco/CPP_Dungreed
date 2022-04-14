#include "Stdafx.h"
#include "SoundLoader.h"

SoundLoader::SoundLoader()
{
}

SoundLoader::~SoundLoader()
{
}

HRESULT SoundLoader::init()
{
	loadSounds();

	return S_OK;
}

void SoundLoader::release()
{
}

void SoundLoader::loadSounds()
{
	// ========
	// # Item #
	// ========
	SOUNDMANAGER->addSound(SoundName::title, PATH_SOUND"Title.wav", true, true);
	SOUNDMANAGER->addSound(SoundName::invenOpen, PATH_SOUND"Inventory_open.wav", false, false);
	SOUNDMANAGER->addSound(SoundName::Item::getCoin, PATH_SOUND"Get_Coin.wav", false, false);
	SOUNDMANAGER->addSound(SoundName::Item::getItem, PATH_SOUND"Get_Item.wav", false, false);
}
