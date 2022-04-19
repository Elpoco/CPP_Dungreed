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
	for (int i = 0; i < (int)OBJ_TYPE::TYPE_CNT; i++)
	{
		_mObjects.insert(make_pair((OBJ_TYPE)i, vector<Object*>()));
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

			if (_isDebug)
			{
				BOOL isPlayer = pairObject.first == ObjectEnum::OBJ_TYPE::PLAYER;
				BOOL isEnemy = pairObject.first == ObjectEnum::OBJ_TYPE::ENEMY;
				
				if (!isPlayer && !isEnemy) continue;
				CAMERAMANAGER->printRectangle(hdc, obj->getRect(), Color::Green);
				CAMERAMANAGER->printPoint(hdc, obj->getRect().left, obj->getRect().top, obj->getX(), obj->getY(), "x: %d, y: %d");
			}
		}
	}
}

void ObjectManager::addObject(OBJ_TYPE type, Object* object)
{
	object->init();
	_mObjects.find(type)->second.push_back(object);
}

void ObjectManager::addUnit(Code::UNIT code, float x, float y)
{
	switch (code)
	{
	case Code::UNIT::PLAYER:
		addObject(OBJ_TYPE::PLAYER, new Player(x, y));
		break;
	case Code::UNIT::SKEL_DOG:
		addObject(OBJ_TYPE::ENEMY, new SkelDog(x, y));
		break;
	case Code::UNIT::LITTLE_GHOST:
		addObject(OBJ_TYPE::ENEMY, new LittleGhost(x, y));
		break;
	case Code::UNIT::BELIAL:
		addObject(OBJ_TYPE::ENEMY, new Belial(x, y));
		break;
	case Code::UNIT::NIFLEHEIM:
		addObject(OBJ_TYPE::ENEMY, new Niflheim(x, y));
		break;
	case Code::UNIT::UNIT_CNT:
		break;
	default:
		break;
	}
}

void ObjectManager::addBullet(OBJ_TYPE type, string imgName, float x, float y, float angle, float speed, int damage, string destroyImgName, float distance)
{
	addObject(type, new Bullet(imgName, x, y, angle, speed, damage, destroyImgName));
}

RECT ObjectManager::addEffect(string imgName, float x, float y, BYTE alpha, OBJ_TYPE type)
{
	Effect* effect = new Effect(imgName, x, y, alpha);
	addObject(type, effect);

	return effect->getRect();
}

RECT ObjectManager::addEffect(string imgName, float x, float y, int angle, POINT rotateCenter)
{
	Effect* effect = new Effect(imgName, x, y, angle, rotateCenter);
	addObject(OBJ_TYPE::EFFECT, effect);

	return effect->getRect();
}

void ObjectManager::addUI(Object* obj)
{
	addObject(OBJ_TYPE::UI, obj);
}

void ObjectManager::addUI(string imgName, int x, int y, BOOL fixed, BOOL show)
{
	addObject(OBJ_TYPE::UI, new UI(imgName, x, y, fixed, show));
}

void ObjectManager::addButton(Object* obj)
{
	addObject(OBJ_TYPE::BUTTON, obj);
}

void ObjectManager::addButton(string imgName, int x, int y, BOOL fixed, CALLBACK_FUNC cb)
{
	addObject(OBJ_TYPE::BUTTON, new Button(imgName, x, y, fixed, cb));
}

void ObjectManager::addImageFont(float x, float y, int num)
{
	addObject(OBJ_TYPE::UI, new ImageFont(x, y, num));
}

void ObjectManager::addDynamicImageFont(float x, float y, int num, int dir, ImageFontEnum::FONT_TYPE type)
{
	addObject(OBJ_TYPE::UI, new DynamicFont(x, y, num, dir, type));
}

void ObjectManager::addItem(Object * obj)
{
	addObject(OBJ_TYPE::ITEM, obj);
}

void ObjectManager::addDropItem(Object* obj)
{
	addObject(OBJ_TYPE::ITEM_DROP, obj);
}
