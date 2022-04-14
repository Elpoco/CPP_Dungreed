#include "Stdafx.h"
#include "ObjectManager.h"

#include "Object.h"

#include "UI.h"
#include "Button.h"
#include "ImageFont.h"
#include "DynamicFont.h"

#include "Bullet.h"
#include "Effect.h"

#include "Player.h"
#include "SkelDog.h"
#include "LittleGhost.h"
#include "Belial.h"
#include "Niflheim.h"

using namespace ObjectEnum;

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

HRESULT ObjectManager::init()
{
	for (int i = 0; i < (int)TYPE::TYPE_CNT; i++)
	{
		_mObjects.insert(make_pair((TYPE)i, vector<Object*>()));
	}

	COLLISIONMANAGER->setObject(&_mObjects);

	return S_OK;
}

void ObjectManager::release()
{
	for (auto& pairObject : _mObjects)
	{
		for (Object* obj : pairObject.second)
		{
			obj->release();
			SAFE_DELETE(obj);
		}
		pairObject.second.clear();
	}
	_mObjects.clear();
}

void ObjectManager::update()
{
	for (auto& pairObject : _mObjects)
	{
		vector<Object*>::iterator iter = pairObject.second.begin();
		for (; iter != pairObject.second.end();)
		{
			if ((*iter)->isLive())
			{
				(*iter)->update();
				++iter;
			}
			else
			{
				(*iter)->deleteEffect();
				(*iter)->release();
				SAFE_DELETE(*iter);
				*iter = nullptr;
				iter = pairObject.second.erase(iter);
			}
		}
	}
}

void ObjectManager::render(HDC hdc)
{
	for (auto pairObject : _mObjects)
	{
		for (Object* obj : pairObject.second)
		{
			obj->render(hdc);
		}
	}
}

void ObjectManager::addObject(ObjectEnum::TYPE type, Object* object)
{
	object->init();
	_mObjects.find(type)->second.push_back(object);
}

void ObjectManager::addUnit(Code::Unit code, float x, float y)
{
	switch (code)
	{
	case Code::Unit::PLAYER:
		addObject(ObjectEnum::TYPE::PLAYER, new Player(x, y));
		break;
	case Code::Unit::SKEL_DOG:
		addObject(ObjectEnum::TYPE::ENEMY, new SkelDog(x, y));
		break;
	case Code::Unit::LITTLE_GHOST:
		addObject(ObjectEnum::TYPE::ENEMY, new LittleGhost(x, y));
		break;
	case Code::Unit::BELIAL:
		addObject(ObjectEnum::TYPE::ENEMY, new Belial(x, y));
		break;
	case Code::Unit::NIFLEHEIM:
		addObject(ObjectEnum::TYPE::ENEMY, new Niflheim(x, y));
		break;
	case Code::Unit::UNIT_CNT:
		break;
	default:
		break;
	}
}

void ObjectManager::addBullet(string imgName, float x, float y, float angle, float speed, float damage, string destroyImgName, float distance)
{
	addObject(ObjectEnum::TYPE::ENEMY_OBJ, new Bullet(imgName, x, y, angle, speed, damage, destroyImgName));
}

RECT ObjectManager::addEffect(string imgName, float x, float y, BYTE alpha, ObjectEnum::TYPE type)
{
	Effect* effect = new Effect(imgName, x, y, alpha);
	addObject(type, effect);

	return effect->getRect();
}

RECT ObjectManager::addEffect(string imgName, float x, float y, int angle, POINT rotateCenter)
{
	Effect* effect = new Effect(imgName, x, y, angle, rotateCenter);
	addObject(ObjectEnum::TYPE::EFFECT, effect);

	return effect->getRect();
}

void ObjectManager::addUI(Object* obj)
{
	addObject(ObjectEnum::TYPE::UI, dynamic_cast<UI*>(obj));
}

void ObjectManager::addUI(string imgName, int x, int y, BOOL fixed, BOOL show)
{
	addObject(ObjectEnum::TYPE::UI, new UI(imgName, x, y, fixed, show));
}

void ObjectManager::addButton(Object* obj)
{
	addObject(ObjectEnum::TYPE::BUTTON, obj);
}

void ObjectManager::addButton(string imgName, int x, int y, BOOL fixed, CALLBACK_FUNC cb)
{
	addObject(ObjectEnum::TYPE::BUTTON, new Button(imgName, x, y, fixed, cb));
}

void ObjectManager::addImageFont(float x, float y, int num, BOOL fixed)
{
	addObject(ObjectEnum::TYPE::UI, new ImageFont(x, y, num, fixed));
}

void ObjectManager::addDynamicImageFont(float x, float y, int num, int dir, int type)
{
	addObject(ObjectEnum::TYPE::UI, new DynamicFont(x, y, num, dir, type));
}

void ObjectManager::addDropItem(Object* obj)
{
	addObject(ObjectEnum::TYPE::ITEM_DROP, obj);
}
