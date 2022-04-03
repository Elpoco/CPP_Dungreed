#pragma once
#include "SingletonBase.h"

class Object;

class ObjectManager : public SingletonBase<ObjectManager>
{	
public:
	typedef map<ObjectEnum::TYPE, vector<Object*>> mapObjects;

private:
	mapObjects _mObjects;
	vector<Object*> _vObjects;

public:
	ObjectManager();
	~ObjectManager();
	
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void addObject(ObjectEnum::TYPE type, Object* object);

};

