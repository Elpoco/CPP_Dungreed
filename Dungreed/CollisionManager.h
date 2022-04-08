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

	// �÷��̾� �浹 ���� ����
	void renderPlayer(HDC hdc, Object* obj);
	void renderEnemy(HDC hdc, Object* obj);
	void renderBullet(HDC hdc, Object* obj);

	// Ÿ�� �浹
	void tileCollision();

	// �÷��̾�� ���� �浹 ����
	void playerEnemyCollision();

	// ����ü �浹 ����
	void shootingCollision();

};

