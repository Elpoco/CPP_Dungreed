#pragma once
#include "SingletonBase.h"

class Object;

using namespace ColliderEnum;

class CollisionManager : public SingletonBase<CollisionManager>
{
private:
	ObjectManager::mapObjects* _mObjects;

	bool _onTileCollision;

public:
	CollisionManager();
	~CollisionManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void setObject(ObjectManager::mapObjects* mObjects) { _mObjects = mObjects; }

	// 타일 충돌
	void onTileCollision() { _onTileCollision = true; }
	void offTIleCollision() { _onTileCollision = false; }
	void tileCollision();
	void collisionBlock(Object* obj, TILE tile, DIRECTION dir);

	// 몬스터 인식범위
	void enemyScanCollision();

};

