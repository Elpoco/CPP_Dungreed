#include "Stdafx.h"
#include "LalaMagicWand.h"

LalaMagicWand::LalaMagicWand()
{
	_iconName = ImageName::Item::Weapon::LalaSkill;
	_cooltime = 6.0f;
}

LalaMagicWand::~LalaMagicWand()
{
}

void LalaMagicWand::run(float x, float y, float angle)
{
	_runTime = TIMEMANAGER->getWorldTime();
	SOUNDMANAGER->play(SoundName::Item::Weapon::MagicWandSkill, _sound);

	float scale = 1.0f;

	for (int i = 0; i < 4; i++)
	{
		Code::ITEM code = ITEMMANAGER->getEquipAccCode(i);
		switch (code)
		{
		case Code::ITEM::MAGNIFYINGGLASS:
			scale = 2.0f;
			break;
		default:
			break;
		}
	}

	for (int i = 0; i < 8; i++)
	{
		OBJECTMANAGER->addBullet(
			ObjectEnum::OBJ_TYPE::PLAYER_OBJ,
			ImageName::Item::Weapon::StarBullet,
			x,
			y,
			PI_2 / 8 * i,
			4.0f,
			RND->getFromIntTo(13, 20),
			"",
			2000.0f,
			TRUE,
			TRUE,
			scale,
			FALSE,
			TRUE
		);
	}
}
