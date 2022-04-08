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

	// 플레이어 충돌 정보 렌더
	void renderPlayer(HDC hdc, Object* obj);
	void renderEnemy(HDC hdc, Object* obj);
	void renderBullet(HDC hdc, Object* obj);

	// 타일 충돌
	void tileCollision();

	// 플레이어와 몬스터 충돌 관리
	void playerEnemyCollision();

	// 투사체 충돌 관리
	void shootingCollision();

};

