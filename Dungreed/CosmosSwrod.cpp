#include "Stdafx.h"
#include "CosmosSwrod.h"

CosmosSwrod::CosmosSwrod()
{
	_iconName = ImageName::Item::Weapon::CosmosSkill;
	_cooltime = 3.0f;
}

CosmosSwrod::~CosmosSwrod()
{
}

void CosmosSwrod::run(float x, float y, float angle)
{
	_runTime = TIMEMANAGER->getWorldTime();
	SOUNDMANAGER->play(SoundName::Item::Weapon::CosmicDash, _sound);
	OBJECTMANAGER->addBullet(
		ObjectEnum::OBJ_TYPE::PLAYER_OBJ,
		ImageName::Item::Weapon::CosmosSwordAura,
		x,
		y,
		angle,
		9.0f,
		RND->getFromIntTo(15 + PLAYERMANAGER->getBulletPower(), 25 + PLAYERMANAGER->getBulletPower()),
		"",
		2000.0f,
		TRUE,
		TRUE,
		1.0f,
		TRUE
	);
}
