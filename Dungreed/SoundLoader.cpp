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
	SOUNDMANAGER->addSound(SoundName::title, PATH_SOUND"Title.wav", true, true);
	// ========
	// # Item #
	// ========
	SOUNDMANAGER->addSound(SoundName::invenOpen, PATH_SOUND"Inventory_open.wav", false, false);
	SOUNDMANAGER->addSound(SoundName::swapEquip, PATH_SOUND"Swap_weapon.wav", false, false);

	SOUNDMANAGER->addSound(SoundName::Item::getCoin, PATH_SOUND"Get_Coin.wav", false, false);
	SOUNDMANAGER->addSound(SoundName::Item::getItem, PATH_SOUND"Get_Item.wav", false, false);
	SOUNDMANAGER->addSound(SoundName::Item::Equip, PATH_SOUND"Equip.wav", false, false);
	SOUNDMANAGER->addSound(SoundName::Item::PickUpItem, PATH_SOUND"PickUpItem.wav", false, false);

	// ==========
	// # Weapon #
	// ==========
	SOUNDMANAGER->addSound(SoundName::Item::Weapon::swing2, PATH_SOUND"swing2.wav", false, false);
	SOUNDMANAGER->addSound(SoundName::Item::Weapon::Gun, PATH_SOUND"Gun.wav", false, false);


}
