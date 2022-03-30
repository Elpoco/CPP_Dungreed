#include "Stdafx.h"
#include "ObjectManager.h"

#include "Object.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

HRESULT ObjectManager::init()
{
	COLLISIONMANAGER->setObjectVector(&_vObjects);
	
	return S_OK;
}

void ObjectManager::release()
{
}

void ObjectManager::update()
{
	for (Object* obj : _vObjects)
	{
		obj->update();
	}
}

void ObjectManager::render(HDC hdc)
{
	for (Object* obj : _vObjects)
	{
		obj->render(hdc);
	}
}

void ObjectManager::addObject(Object* object)
{
	object->init();
	_vObjects.push_back(object);
}
