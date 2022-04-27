#pragma once
#include "SingletonBase.h"

class Object;

using namespace Direction;

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

	// 타입별 렌더
	void renderPlayer(HDC hdc, Object* obj);
	void renderEnemy(HDC hdc, Object* obj);
	void renderBullet(HDC hdc, Object* obj);
	void renderUI(HDC hdc, Object* obj);
	void renderItem(HDC hdc, Object* obj);
	void renderNpc(HDC hdc, Object* obj);
	void renderDungeonObj(HDC hdc, Object* obj);

	// 타일 충돌
	void collisionTile();
	void unitTileCollision(ObjectManager::vObjects vObjects);
	// 플레이어 몬스터 충돌
	void collisionPlayerEnemy();
	// 투사체 충돌
	void collisionShooting();
	// 버튼 충돌
	void collisionButton();
	// 아이템 플레이어 충돌
	void collisionItem();
	// NPC 플레이어 충돌
	void collisionNpc();
	// 던전 오브젝트 충돌
	void collisionDungeonObj();

};

