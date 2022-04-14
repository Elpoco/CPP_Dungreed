#pragma once
#include "SingletonBase.h"

class Object;

class ObjectManager : public SingletonBase<ObjectManager>
{	
public:
	typedef map<ObjectEnum::TYPE, vector<Object*>> mapObjects;

private:
	mapObjects _mObjects;
	vector<Object*> _vObjects;

public:
	ObjectManager();
	~ObjectManager();
	
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void addObject(ObjectEnum::TYPE type, Object* object);
	void addUnit(Code::Unit code, float x, float y);
	void addBullet(string imgName, float x, float y, float angle, float speed, float damage = 0.0f, string destroyImgName = "", float distance = 1500);
	RECT addEffect(string imgName, float x, float y, BYTE alpha = 0, ObjectEnum::TYPE type = ObjectEnum::TYPE::EFFECT);
	RECT addEffect(string imgName, float x, float y, int angle, POINT rotateCenter);
	void addUI(Object* obj);
	void addUI(string imgName, int x, int y, BOOL fixed, BOOL show = TRUE);
	void addButton(Object* obj);
	void addButton(string imgName, int x, int y, BOOL fixed = TRUE, CALLBACK_FUNC cb = nullptr);
	void addImageFont(float x, float y, int num, BOOL fixed = TRUE);
	void addDynamicImageFont(float x, float y, int num, int dir, int type = 0);
	void addDropItem(Object* obj);

};

