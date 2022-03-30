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

	bool _onTileCollision;

public:
	CollisionManager();
	~CollisionManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void addObject(Object* object);

	void onTileCollision() { _onTileCollision = true; }
	void offTIleCollision() { _onTileCollision = false; }
	void tileCollision();

};

