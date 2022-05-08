#include "Stdafx.h"
#include "Sword.h"

#include "CosmosSwrod.h"

Sword::Sword(Code::ITEM code)
	: Item(code)
	, _effectName(ImageName::Effect::Weapon::basicSwing)
	, _soundName(SoundName::Item::Weapon::swing2)
	, _isFirst(TRUE)
{
}

Sword::~Sword()
{
}

HRESULT Sword::init()
{
	Item::init();
	_handleX = _frameInfo.width * 0.3f;

	switch (_itemInfo.code)
	{
	case Code::ITEM::BAMBOO_SWORD:
		_effectName = ImageName::Effect::Weapon::BambooSwing;
		_soundName = SoundName::Item::Weapon::swing1;
		break;
	case Code::ITEM::LIGHTSABER:
		_effectName = ImageName::Effect::Weapon::SwingFX;
		_soundName = SoundName::Item::Weapon::LightSaver;
		break;
	case Code::ITEM::COSMOSSWORD:
		_skill = new CosmosSwrod;
		_effectName = ImageName::Effect::Weapon::CosmosSwingFX;
		_soundName = SoundName::Item::Weapon::swing5;
		break;
	case Code::ITEM::THREETIEREDBATON:
		_effectName = ImageName::Effect::Weapon::BambooSwing;
		_soundName = SoundName::Item::Weapon::swing1;
		break;
	default:
		break;
	}

	return S_OK;
}

void Sword::release()
{
	Item::release();
}

void Sword::update()
{
	Item::update();
	
	if (!_isEquip) return;

	if (UIMANAGER->isUI()) return;

	if (_isFirst)
	{
		if (PLAYERMANAGER->getPlayerIsLeft()) _degree -= 200;
		else _degree += 20;
	}
	else
	{
		if (PLAYERMANAGER->getPlayerIsLeft()) _degree += 10;
		else _degree += 150;
	}
}

void Sword::render(HDC hdc)
{
	Item::render(hdc);
}

RECT Sword::attack()
{
	if (_lastAttack + 1.0f / (_itemInfo.atkSpeed * PLAYERMANAGER->getAtkSpeed()) >= TIMEMANAGER->getWorldTime()) return { 0,0,0,0 };
	_lastAttack = TIMEMANAGER->getWorldTime();

	_isFirst = !_isFirst;

	float effectAngle = GetAngle(PLAYERMANAGER->getPlayerHand(), CAMERAMANAGER->calAbsPt(_ptMouse));
	float effectX = cosf(effectAngle) * _frameInfo.height + PLAYERMANAGER->getPlayerHand().x;
	float effectY = -sinf(effectAngle) * _frameInfo.height + PLAYERMANAGER->getPlayerHand().y;

	SOUNDMANAGER->play(_soundName, _sound);

	CAMERAMANAGER->cameraShake(3);

	return OBJECTMANAGER->addEffect(
		_effectName,
		effectX,
		effectY,
		RadToDeg(effectAngle),
		PointMake(effectX, effectY)
	);
}

void Sword::equip()
{
	Item::equip();

	switch (_itemInfo.code)
	{
	case Code::ITEM::LIGHTSABER:
		PLAYERMANAGER->setTrueDmg(TRUE);
		break;
	default:
		break;
	}
}

void Sword::unequip()
{
	Item::unequip();

	switch (_itemInfo.code)
	{
	case Code::ITEM::LIGHTSABER:
		PLAYERMANAGER->setTrueDmg(FALSE);
		break;
	default:
		break;
	}
}
