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
	void printRectangle(HDC hdc, float x, float y, float width, float height);
	void printRectangle(HDC hdc, RectF rc, bool isFill = true, Color color = Color::Black, Color fillColor = Color::White);
	void printRectanglePoint(HDC hdc, PointF point, float width, float height, Color color = Color::Black);
	void printRectangleCenter(HDC hdc, float x, float y, float width, float height);

	int checkObjectInCamera(Image* img, float x, float y);

	void render(HDC hdc, Image* img, float x, float y);
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
	PointF calRelPt(PointF pt) { return { pt.X - _x, pt.Y - _y }; }
	PointF calAbsPt(PointF pt) { return { pt.X + _x, pt.Y + _y }; }

};

