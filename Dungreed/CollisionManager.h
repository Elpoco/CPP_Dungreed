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

	// Ÿ�Ժ� ����
	void renderPlayer(HDC hdc, Object* obj);
	void renderEnemy(HDC hdc, Object* obj);
	void renderBullet(HDC hdc, Object* obj);
	void renderUI(HDC hdc, Object* obj);
	void renderItem(HDC hdc, Object* obj);
	void renderNpc(HDC hdc, Object* obj);
	void renderDungeonObj(HDC hdc, Object* obj);

	// Ÿ�� �浹
	void collisionTile();
	void unitTileCollision(ObjectManager::vObjects vObjects);
	// �÷��̾� ���� �浹
	void collisionPlayerEnemy();
	// ����ü �浹
	void collisionShooting();
	// ��ư �浹
	void collisionButton();
	// ������ �÷��̾� �浹
	void collisionItem();
	// NPC �÷��̾� �浹
	void collisionNpc();
	// ���� ������Ʈ �浹
	void collisionDungeonObj();

};

