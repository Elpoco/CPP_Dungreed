#include "Stdafx.h"
#include "Sword.h"

Sword::Sword(Code::ITEM code)
	: Item(code)
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
		if (ITEMMANAGER->getPlayerIsLeft()) _degree -= 200;
		else _degree += 20;
	}
	else
	{
		if (ITEMMANAGER->getPlayerIsLeft()) _degree += 10;
		else _degree += 150;
	}
}

void Sword::render(HDC hdc)
{
	Item::render(hdc);
}

RECT Sword::attack()
{
	if (_lastAttack + 1.0f / _info.atkSpeed >= TIMEMANAGER->getWorldTime()) return { 0,0,0,0 };
	_lastAttack = TIMEMANAGER->getWorldTime();

	_isFirst = !_isFirst;

	float effectAngle = GetAngle(ITEMMANAGER->getPlayerHand(), CAMERAMANAGER->calAbsPt(_ptMouse));
	float effectX = cosf(effectAngle) * _frameInfo.height + ITEMMANAGER->getPlayerHand().x;
	float effectY = -sinf(effectAngle) * _frameInfo.height + ITEMMANAGER->getPlayerHand().y;

	string effectName = ImageName::Effect::Weapon::basicSwing;

	switch (_info.code)
	{
	default:
	case Code::ITEM::SHOT_SWORD:
		SOUNDMANAGER->play(SoundName::Item::Weapon::swing2, _sound);
		break;
	case Code::ITEM::BAMBOO_SWORD:
		SOUNDMANAGER->play(SoundName::Item::Weapon::swing1, _sound);
		effectName = ImageName::Effect::Weapon::BambooSwing;
		break;
	case Code::ITEM::LIGHTSABER:
		SOUNDMANAGER->play(SoundName::Item::Weapon::LightSaver, _sound);
		effectName = ImageName::Effect::Weapon::SwingFX;
		break;
	}

	CAMERAMANAGER->cameraShake(3);

	return OBJECTMANAGER->addEffect(
		effectName,
		effectX,
		effectY,
		RadToDeg(effectAngle),
		PointMake(effectX, effectY)
	);
}

void Sword::equip()
{
	Item::equip();

	switch (_info.code)
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

	switch (_info.code)
	{
	case Code::ITEM::LIGHTSABER:
		PLAYERMANAGER->setTrueDmg(FALSE);
		break;
	default:
		break;
	}
}
