#pragma once
#include "SingletonBase.h"

class Object;

using namespace ColliderEnum;

class CollisionManager : public SingletonBase<CollisionManager>
{
private:
	ObjectManager::mapObjects* _mObjects;

public:
	CollisionManager();
	~CollisionManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void setObject(ObjectManager::mapObjects* mObjects) { _mObjects = mObjects; }

	// 타일 충돌
	void tileCollision();

	// 몬스터 인식
	void enemyScanCollision();

};

