#pragma once
#include "SingletonBase.h"

class Object;

using namespace ColliderEnum;

class CollisionManager : public SingletonBase<CollisionManager>
{
private:
	typedef vector<Object*> vObjects;

private:
	vObjects* _vObjects;

	bool _onTileCollision;

public:
	CollisionManager();
	~CollisionManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void setObjectVector(vObjects* vObjects) { _vObjects = vObjects; }

	void onTileCollision() { _onTileCollision = true; }
	void offTIleCollision() { _onTileCollision = false; }
	void tileCollision();
	void collisionBlock(Object* obj, Tile tile, DIRECTION dir);

};

