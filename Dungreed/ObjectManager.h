#pragma once
#include "SingletonBase.h"

class Object;

class ObjectManager : public SingletonBase<ObjectManager>
{	
public:
	typedef vector<Object*> vObjects;
	typedef map<ObjectEnum::OBJ_TYPE, vObjects> mapObjects;

private:
	mapObjects _mObjects;

public:
	ObjectManager();
	~ObjectManager();
	
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void addObject(ObjectEnum::OBJ_TYPE type, Object* object);
	void addPlayer(float x, float y);
	void addEnemy(Code::UNIT code, float x, float y);
	void addNPC(Code::NPC code, float x, float y, Code::MAP mapCode = Code::MAP::TOWN);
	void addBullet(ObjectEnum::OBJ_TYPE type, string imgName, float x, float y, float angle, float speed,
		int damage = 1, string destroyImgName = "", float distance = 1000, BOOL super = FALSE, BOOL imgRotate = FALSE, float scale = 1.0f);
	
	RECT addEffect(string imgName, float x, float y, float angle);
	RECT addEffect(string imgName, float x, float y, int angle, POINT rotateCenter);
	RECT addEffect(string imgName, float x, float y, BYTE alpha = 0, ObjectEnum::OBJ_TYPE type = ObjectEnum::OBJ_TYPE::EFFECT);
	
	void addUI(Object* obj);
	void addUI(string imgName, int x, int y, BOOL fixed = TRUE, BOOL show = TRUE);
	void addButton(Object* obj);
	void addButton(string imgName, int x, int y, BOOL fixed = TRUE, CALLBACK_FUNC cb = nullptr);
	void addImageFont(float x, float y, int num);
	void addImageFont(float x, float y, char* str, ImageFontEnum::FONT_SIZE size = ImageFontEnum::FONT_SIZE::SMALL);
	void addDynamicImageFont(float x, float y, int num, int dir, ImageFontEnum::FONT_TYPE type = ImageFontEnum::FONT_TYPE::DAMAGE);
	
	void addItem(Object* obj);
	void addDropItem(Object* obj);
	void addTresure(float x, float y, Code::TRESURE_TYPE type = Code::TRESURE_TYPE::NONE);

	void clearObjects(ObjectEnum::OBJ_TYPE type);

	Object* getPlayer() { return _mObjects.find(ObjectEnum::OBJ_TYPE::PLAYER)->second[0]; }
	vObjects* getEnemy() { return &_mObjects.find(ObjectEnum::OBJ_TYPE::ENEMY)->second; }
	vObjects* getNPC() {return  &_mObjects.find(ObjectEnum::OBJ_TYPE::NPC)->second;}
	vObjects* getDungeonObj() {return  &_mObjects.find(ObjectEnum::OBJ_TYPE::DUNGEON_OBJ)->second;}

};

