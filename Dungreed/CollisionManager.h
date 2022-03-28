#pragma once
#include "SingletonBase.h"

class Collider;
class Object;

class CollisionManager : public SingletonBase<CollisionManager>
{
private:
	typedef vector<Collider*> vColliders;
	typedef vector<Collider*>::iterator viColliders;

private:
	vColliders _vColliders;

public:
	CollisionManager();
	~CollisionManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void addObject(Object* object);

	void tileCollision();

};

