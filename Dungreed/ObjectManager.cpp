#include "Stdafx.h"
#include "ObjectManager.h"

#include "Object.h"

using namespace ObjectEnum;

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

HRESULT ObjectManager::init()
{
	_mObjects.insert(make_pair(TYPE::ITEM, vector<Object*> ()));
	_mObjects.insert(make_pair(TYPE::ENEMY, vector<Object*> ()));
	_mObjects.insert(make_pair(TYPE::PLAYER, vector<Object*> ()));
	_mObjects.insert(make_pair(TYPE::EFFECT, vector<Object*> ()));
	_mObjects.insert(make_pair(TYPE::ENEMY_OBJ, vector<Object*> ()));
	_mObjects.insert(make_pair(TYPE::PLAYER_OBJ, vector<Object*> ()));
	_mObjects.insert(make_pair(TYPE::PLAYER_OBJ, vector<Object*> ()));

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
				(*iter)->release();
				SAFE_DELETE(*iter);
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
