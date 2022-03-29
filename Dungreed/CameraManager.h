#pragma once
#include "SingletonBase.h"

class Object;

class CameraManager : public SingletonBase<CameraManager>
{
private:
	float _x;
	float _y;

	Object* _object; // 따라다닐 오브젝트
	bool _isFollow;

public:
	CameraManager();
	~CameraManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void printPoint(HDC hdc, float x, float y, int ptX, int ptY, char* format = "%d, %d");
	void printRectangle(HDC hdc, float x, float y, float width, float height);

	int checkObjectInCamera(Image* img, float x, float y);

	void render(HDC hdc, Image* img, float x, float y);
	void frameRender(HDC hdc, Image* img, float x, float y, int frameX, int frameY);

	void followCamera(Object* object);
	void startFollow() { _isFollow = true; }
	void stopFollow() { _isFollow = false; }

	float getAbsX() { return _x; }
	float getAbsY() { return _y; }
	float calRelX(float x) { return x - _x; }
	float calRelY(float y) { return y - _y; }

};

