#include "Stdafx.h"
#include "Gun.h"

#include "Effect.h"
#include "Bullet.h"

#include "LalaMagicWand.h"

using namespace GunSet;

Gun::Gun(Code::ITEM code)
	: Item(code)
	, _isReload(FALSE)
	, _bulletSpeed(DEFAULT_BULLET_SPEED)
	, _reloadTick(DEFAULT_RELOAD_TICK)
	, _itemAtkSpeed(0.0f)
	, _itemDmg(0)
	, _itemScale(1.0f)
	, _isPenetrate(FALSE)
	, _bulletImgName(ImageName::Item::Weapon::Bullet02)
	, _shootingImgName(ImageName::Effect::Weapon::shooting)
	, _hitImgName(ImageName::Effect::Weapon::shootingHit)
	, _isAuto(FALSE)
	, _isSuper(FALSE)
{
}

Gun::~Gun()
{
}

HRESULT Gun::init()
{
	Item::init();

	_bulletCnt = _itemInfo.bulletCnt;
	_handleY = _frameInfo.height * 0.5f;

	switch (_itemInfo.code)
	{
	case Code::ITEM::GATLINGGUN:
		_bulletImgName = ImageName::Item::Weapon::Bullet03;
		break;
	case Code::ITEM::LALA:
		_bulletImgName = ImageName::Item::Weapon::StarBullet;
		_handleX = _img->getWidth() * 0.2f;
		_handleY = _img->getHeight();
		_bulletSpeed = 4.0f;
		_shootingImgName = ImageName::Effect::Weapon::StarBulletFX;
		_hitImgName = ImageName::Effect::Weapon::StarBulletFX;
		_skill = new LalaMagicWand;
		_isAuto = TRUE;
		_isSuper = TRUE;
		break;
	default:
		break;
	}

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

	// 총알을 다 쓰거나 재장전 키 누를때
	BOOL isReloadKey = IsOnceKeyDown(KEY::RELOAD) && _bulletCnt < _itemInfo.bulletCnt;
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
		_bulletCnt = _itemInfo.bulletCnt;
	}


	if (UIMANAGER->isUI()) return;
	this->settingShootingPoint();


	if (_itemInfo.code == Code::ITEM::LALA)
	{
		if (PLAYERMANAGER->getPlayerIsLeft()) _degree -= 180;
	}
	else
	{
		_frameInfo.y = PLAYERMANAGER->getPlayerIsLeft();
	}
}

void Gun::render(HDC hdc)
{
	Item::render(hdc);
	//CAMERAMANAGER->printRectangle(hdc, _shootingX, _shootingY, 2, 2);
}

RECT Gun::attack()
{
	settingAcc();

	if (_lastAttack + 1.0f / (_itemInfo.atkSpeed * _itemAtkSpeed) >= TIMEMANAGER->getWorldTime()) return { 0,0,0,0 };
	_lastAttack = TIMEMANAGER->getWorldTime();
	if (--_bulletCnt < 0) return { 0,0,0,0 };

	if (_itemInfo.code == Code::ITEM::LALA)
	{
		Effect* effect = new Effect(_shootingImgName,
			_shootingX,
			_shootingY
		);
		OBJECTMANAGER->addObject(ObjectEnum::OBJ_TYPE::EFFECT, effect);
	}
	else
	{
		Effect* effect = new Effect(_shootingImgName,
			_shootingX,
			_shootingY,
			_degree,
			PointMake(_shootingX, _shootingY)
		);
		effect->setFollowing(&_shootingX, &_shootingY, &_degree);
		OBJECTMANAGER->addObject(ObjectEnum::OBJ_TYPE::EFFECT, effect);
	}


	float bulletAngle = RND->getFloat(0.08f) - 0.04f;

	if (_isMulti)
	{
		for (int i = 0; i < 2; i++)
		{
			OBJECTMANAGER->addBullet(
				ObjectEnum::OBJ_TYPE::PLAYER_OBJ,
				_bulletImgName,
				_shootingX,
				_shootingY,
				_angle + bulletAngle - 0.06f * (i ? 1 : -1),
				_bulletSpeed,
				RND->getFromIntTo(_itemInfo.minDmg, _itemInfo.maxDmg),
				_hitImgName,
				1000.0f,
				_isSuper,
				TRUE,
				_itemScale,
				_isPenetrate,
				_isAuto
			);
		}
	}
	
	OBJECTMANAGER->addBullet(
		ObjectEnum::OBJ_TYPE::PLAYER_OBJ,
		_bulletImgName,
		_shootingX,
		_shootingY,
		_angle + bulletAngle,
		_bulletSpeed,
		RND->getFromIntTo(_itemInfo.minDmg + _itemDmg, _itemInfo.maxDmg + _itemDmg),
		_hitImgName,
		1000.0f,
		_isSuper,
		TRUE,
		_itemScale,
		_isPenetrate,
		_isAuto
	);

	string sound = SoundName::Item::Weapon::Gun;
	if (_itemInfo.code == Code::ITEM::LALA) sound = SoundName::Item::Weapon::MagicWandAttack;

	SOUNDMANAGER->play(sound, _sound - 0.5f);

	return { 0,0,0,0 };
}

void Gun::settingAcc()
{
	_isMulti = FALSE;
	_isSize = FALSE;
	_itemAtkSpeed = 1.0f;
	_itemDmg = 0;
	_itemScale = 1.0f;

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

	if (_isSize)
	{
		_itemAtkSpeed -= 0.7f;
		_itemDmg += 5;
		_itemScale = 2.0f;
	}

	if (_isMulti)
	{
		_itemDmg -= 3;
	}
}

void Gun::settingShootingPoint()
{
	// 총구 위치 구하기
	_shootingX = PLAYERMANAGER->getPlayerHand().x + cosf(_angle) * (_frameInfo.width - 10);
	_shootingY = PLAYERMANAGER->getPlayerHand().y - sinf(_angle) * (_frameInfo.width - 10);
	_degree = RadToDeg(_angle);

	switch (_itemInfo.code)
	{
	case Code::ITEM::GATLINGGUN:
		break;
	default:
		break;
	}
}
