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
#include "NPC.h"

#include "SkelDog.h"
#include "LittleGhost.h"
#include "Banshee.h"
#include "Bat.h"
#include "Skel.h"

#include "Belial.h"
#include "Niflheim.h"

#include "Door.h"
#include "Tresure.h"

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
		_mObjects.insert(make_pair((OBJ_TYPE)i, vObjects()));
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
				CAMERAMANAGER->printPoint(
					hdc, 
					obj->getRect().left, 
					obj->getRect().top, 
					obj->getX(), 
					obj->getY(), 
					"x: %d, y: %d"
				);
			}
		}
	}

	UIMANAGER->render(hdc);
}

void ObjectManager::addObject(OBJ_TYPE type, Object* object)
{
	object->init();
	_mObjects.find(type)->second.push_back(object);
}

void ObjectManager::addPlayer(float x, float y)
{
	addObject(OBJ_TYPE::PLAYER, new Player(x, y));
}

void ObjectManager::addEnemy(Code::UNIT code, float x, float y)
{
	Enemy* enemy;
	switch (code)
	{
	case Code::UNIT::SKEL_DOG:
		enemy = new SkelDog(x, y);
		break;
	case Code::UNIT::LITTLE_GHOST:
		enemy = new LittleGhost(x, y);
		break;
	case Code::UNIT::BANSHEE:
		enemy = new Banshee(x, y);
		break;
	case Code::UNIT::BAT:
	case Code::UNIT::GIANT_BAT:
	case Code::UNIT::RED_GIANT_BAT:
		enemy = new Bat(x, y, code);
		break;
	case Code::UNIT::SKEL:
	case Code::UNIT::SKEL_BOW:
		enemy = new Skel(x, y, code);
		break;

	case Code::UNIT::BELIAL:
		enemy = new Belial(x, y);
		break;
	case Code::UNIT::NIFLEHEIM:
		enemy = new Niflheim(x, y);
		break;

	default:
		enemy = new SkelDog(x, y);
		break;
	}
	addObject(OBJ_TYPE::ENEMY, enemy);
	if(code < Code::UNIT::BOSS) enemy->settingHpBar();
}

void ObjectManager::addNPC(Code::NPC code, float x, float y, Code::MAP mapCode)
{
	NPC* npc;
	switch (code)
	{
	default:
	case Code::NPC::SHOP:
		npc = new NPC(code, x, y);
		break;
	case Code::NPC::DUNGEON_SHOP:
		npc = new NPC(code, x, y, mapCode);
		break;
	}
	addObject(ObjectEnum::OBJ_TYPE::NPC, npc);
}

void ObjectManager::addBullet(OBJ_TYPE type, string imgName, float x, float y, float angle, float speed, int damage,
	string destroyImgName, float distance, BOOL super, BOOL imgRotate)
{
	addObject(type, new Bullet(imgName, x, y, angle, speed, damage, destroyImgName, distance, super, imgRotate));
}

RECT ObjectManager::addEffect(string imgName, float x, float y, BYTE alpha, OBJ_TYPE type)
{
	Effect* effect = new Effect(imgName, x, y, alpha);
	addObject(type, effect);

	return effect->getRect();
}

RECT ObjectManager::addEffect(string imgName, float x, float y, float angle)
{
	Effect* effect = new Effect(imgName, x, y, angle);
	addObject(OBJ_TYPE::EFFECT, effect);

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

void ObjectManager::addImageFont(float x, float y, char* str, ImageFontEnum::FONT_SIZE size)
{
	addObject(OBJ_TYPE::UI_FRONT, new ImageFont(x, y, str, size));
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

void ObjectManager::addTresure(float x, float y, Code::TRESURE_TYPE type)
{
	addObject(OBJ_TYPE::DUNGEON_OBJ, new Tresure(x, y, type));
}

void ObjectManager::clearObjects(ObjectEnum::OBJ_TYPE type)
{
	for (auto& obj : _mObjects.find(type)->second)
	{
		obj->deleteObject();
	}
}
