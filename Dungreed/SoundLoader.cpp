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
	SOUNDMANAGER->addSound(SoundName::Item::collecting, PATH_SOUND"EC_Collect.wav", false, false);
}
