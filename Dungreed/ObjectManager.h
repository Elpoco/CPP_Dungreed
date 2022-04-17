#pragma once
#include "SingletonBase.h"

class Object;

class ObjectManager : public SingletonBase<ObjectManager>
{	
public:
	typedef map<ObjectEnum::TYPE, vector<Object*>> mapObjects;

private:
	mapObjects _mObjects;

public:
	ObjectManager();
	~ObjectManager();
	
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void addObject(ObjectEnum::TYPE type, Object* object);
	void addUnit(Code::UNIT code, float x, float y);
	void addBullet(ObjectEnum::TYPE type, string imgName, float x, float y, float angle, float speed, int damage = 1, string destroyImgName = "", float distance = 1500);
	RECT addEffect(string imgName, float x, float y, BYTE alpha = 0, ObjectEnum::TYPE type = ObjectEnum::TYPE::EFFECT);
	RECT addEffect(string imgName, float x, float y, int angle, POINT rotateCenter);
	void addUI(Object* obj);
	void addUI(string imgName, int x, int y, BOOL fixed = TRUE, BOOL show = TRUE);
	void addButton(Object* obj);
	void addButton(string imgName, int x, int y, BOOL fixed = TRUE, CALLBACK_FUNC cb = nullptr);
	void addImageFont(float x, float y, int num);
	void addDynamicImageFont(float x, float y, int num, int dir, ImageFontEnum::FONT_TYPE type = ImageFontEnum::FONT_TYPE::DAMAGE);
	void addItem(Object* obj);
	void addDropItem(Object* obj);

	Object* getPlayer() { return _mObjects.find(ObjectEnum::TYPE::PLAYER)->second[0]; }

};

