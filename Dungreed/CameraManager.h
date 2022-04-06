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
	bool _isLock;

public:
	CameraManager();
	~CameraManager();

	HRESULT init();
	void release();
	void update();

	void printPoint(HDC hdc, float x, float y, int ptX, int ptY, char* format = "%d, %d");
	void printRectangle(HDC hdc, float x, float y, int width, int height);
	void printRectangle(HDC hdc, RECT rc, Color penColor = Color::Black, bool isFill = false,  Color fillColor = Color::White);
	void printRectanglePoint(HDC hdc, POINT point, int width, int height, Color color = Color::Black);
	void printRectangleCenter(HDC hdc, float x, float y, int width, int height);

	int checkObjectInCamera(float x, float y, int width, int height);

	void render(HDC hdc, Image* img, float x, float y);
	void render(HDC hdc, ImageGp* img, float x, float y, int angle = 0, POINT rotateCenter = { 0,0 });
	void frameRender(HDC hdc, Image* img, float x, float y, int frameX, int frameY);

	void followCamera(Object* object);
	void lockCamera() { _isLock = true; }
	void unlockCamera() { _isLock = false; }
	void startFollow() { _isFollow = true; }
	void stopFollow() { _isFollow = false; }

	float getAbsX() { return _x; }
	float getAbsY() { return _y; }

	float calRelX(float x) { return x - _x; }
	float calRelY(float y) { return y - _y; }
	float calAbsX(float x) { return x + _x; }
	float calAbsY(float y) { return y + _y; }
	RECT calRelRc(RECT rc) { return { (long)(rc.left - _x), (long)(rc.top - _y), (long)(rc.right - _x), (long)(rc.bottom - _y) }; }
	POINT calRelPt(POINT pt) { return PointMake(pt.x - _x, pt.y - _y);}
	POINT calAbsPt(POINT pt) { return PointMake(pt.x + _x, pt.y + _y); }

};

