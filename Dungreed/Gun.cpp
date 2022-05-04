#include "Stdafx.h"
#include "Gun.h"

#include "Effect.h"

using namespace GunSet;

Gun::Gun(Code::ITEM code)
	: Item(code)
	, _isReload(FALSE)
	, _bulletSpeed(DEFAULT_BULLET_SPEED)
	, _reloadTick(DEFAULT_RELOAD_TICK)
	, _itemAtkSpeed(0.0f)
	, _itemDmg(0)
{
}

Gun::~Gun()
{
}

HRESULT Gun::init()
{
	Item::init();

	_bulletCnt = _info.bulletCnt;
	_handleY = _frameInfo.height * 0.5f;

	this->settingShootingPoint();

	return S_OK;
}

void Gun::release()
{
	Item::release();
}

void Gun::update()
{
	Item::update();

	if (!_isEquip) return;
	_rc.left -= 10;
	_frameInfo.y = ITEMMANAGER->getPlayerIsLeft();

	// 총알을 다 쓰거나 재장전 키 누를때
	BOOL isReloadKey = IsOnceKeyDown(KEY::RELOAD) && _bulletCnt < _info.bulletCnt;
	if (!_isReload && (_bulletCnt <= 0 || isReloadKey))
	{
		_isReload = TRUE;
		_lastAttack += _reloadTick;
		_reloadStartTime = TIMEMANAGER->getWorldTime();
		UIMANAGER->showReloadBar(_reloadTick);
		SOUNDMANAGER->play(SoundName::Item::Reload2, _sound);
	}
	if (_isReload && _reloadStartTime + _reloadTick < TIMEMANAGER->getWorldTime())
	{
		_isReload = FALSE;
		_bulletCnt = _info.bulletCnt;
	}


	if (UIMANAGER->isUI()) return;
	this->settingShootingPoint();
}

void Gun::render(HDC hdc)
{
	Item::render(hdc);
	CAMERAMANAGER->printRectangle(hdc, _shootingX, _shootingY, 5, 5);
}

RECT Gun::attack()
{
	settingAcc();

	if (_lastAttack + 1.0f / (_info.atkSpeed * _itemAtkSpeed) >= TIMEMANAGER->getWorldTime()) return { 0,0,0,0 };
	_lastAttack = TIMEMANAGER->getWorldTime();
	if (--_bulletCnt < 0) return { 0,0,0,0 };

	//Effect* effect = new Effect(ImageName::Effect::Weapon::shooting,
	//	_shootingX,
	//	_shootingY,
	//	_degree,
	//	PointMake(_shootingX, _shootingY)
	//);
	//effect->setFollowing(&_shootingX, &_shootingY, &_degree);
	//OBJECTMANAGER->addObject(ObjectEnum::OBJ_TYPE::EFFECT, effect);

	if (_isMulti)
	{
		shootMultiBullet();
	}

	OBJECTMANAGER->addBullet(
		ObjectEnum::OBJ_TYPE::PLAYER_OBJ,
		_bulletImgName,
		_shootingX,
		_shootingY,
		_angle + RND->getFloat(0.08f) - 0.04f,
		_bulletSpeed,
		RND->getFromIntTo(_info.minDmg + _itemDmg, _info.maxDmg + _itemDmg),
		ImageName::Effect::Weapon::shootingHit
	);

	string sound = SoundName::Item::Weapon::Gun;

	//switch (_info.code)
	//{
	//case Code::ITEM::GATLINGGUN:
	//	sound = SoundName::Item::Weapon::GatlingGun;
	//	break;
	//default:
	//	break;
	//}

	SOUNDMANAGER->play(sound, _sound - 0.5f);

	return { 0,0,0,0 };
}

void Gun::settingAcc()
{
	_isMulti = FALSE;
	_isSize = FALSE;
	_itemAtkSpeed = 1.0f;
	_itemDmg = 0;

	for (int i = 0; i < 4; i++)
	{
		Code::ITEM code = ITEMMANAGER->getEquipAccCode(i);
		switch (code)
		{
		case Code::ITEM::MULTI_BULLET:
			_isMulti = TRUE;
			break;
		case Code::ITEM::MAGNIFYINGGLASS:
			_isSize = TRUE;
			break;
		default:
			break;
		}
	}

	_bulletImgName = ImageName::Item::Weapon::Bullet02;

	switch (_info.code)
	{
	case Code::ITEM::GATLINGGUN:
		_bulletImgName = ImageName::Item::Weapon::Bullet03;
		break;
	default:
		break;
	}

	if (_isSize)
	{
		_bulletImgName += "_big";
		_itemAtkSpeed -= 0.7f;
		_itemDmg += 5;
	}

	if (_isMulti)
	{
		_itemDmg -= 3;
	}
}

void Gun::shootMultiBullet()
{
	OBJECTMANAGER->addBullet(
		ObjectEnum::OBJ_TYPE::PLAYER_OBJ,
		_bulletImgName,
		_shootingX,
		_shootingY,
		_angle + RND->getFloat(0.08f) + 0.02f,
		_bulletSpeed,
		RND->getFromIntTo(_info.minDmg, _info.maxDmg),
		ImageName::Effect::Weapon::shootingHit
	);

	OBJECTMANAGER->addBullet(
		ObjectEnum::OBJ_TYPE::PLAYER_OBJ,
		_bulletImgName,
		_shootingX,
		_shootingY,
		_angle + RND->getFloat(0.08f) - 0.1f,
		_bulletSpeed,
		RND->getFromIntTo(_info.minDmg, _info.maxDmg),
		ImageName::Effect::Weapon::shootingHit
	);
}

void Gun::settingShootingPoint()
{
	// 총구 위치 구하기
	_angle = GetAngle(ITEMMANAGER->getPlayerBody(), CAMERAMANAGER->calAbsPt(_ptMouse));
	_shootingX = ITEMMANAGER->getPlayerHand().x + cosf(_angle) * _frameInfo.width;
	_shootingY = ITEMMANAGER->getPlayerHand().y - sinf(_angle) * _frameInfo.width;
	_degree = RadToDeg(_angle);
}
