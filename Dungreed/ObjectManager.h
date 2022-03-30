#pragma once
#include "SingletonBase.h"

class Object;

class ObjectManager : public SingletonBase<ObjectManager>
{	
private:
	vector<Object*> _vObjects;

public:
	ObjectManager();
	~ObjectManager();
	
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void addObject(Object* object);

};

