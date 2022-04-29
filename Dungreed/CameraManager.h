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

	float _mapWidth;
	float _mapHeight;

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

	void render(HDC hdc, string imageName, float x, float y);
	void render(HDC hdc, ImageBase* img, float x, float y);
	void render(HDC hdc, ImageBase* img, float x, float y, BYTE alpha);
	void render(HDC hdc, ImageBase* img, float x, float y, int angle, POINT rotateCenter);
	void render(HDC hdc, ImageBase* img, float x, float y, int sourX, int sourY, int sourWidth, int sourHeight);
	void frameRender(HDC hdc, ImageBase* img, float x, float y, int frameX, int frameY);
	void frameRender(HDC hdc, ImageBase* img, float x, float y, int frameX, int frameY, BYTE alpha);
	void frameRender(HDC hdc, ImageBase* img, float x, float y, int frameX, int frameY, float angle);
	void frameRender(HDC hdc, ImageBase* img, float x, float y, int frameX, int frameY, int angle, POINT rotateCenter);

	void followCamera(Object* object);
	void cameraInitPos();
	void updateMapSize();
	inline void lockCamera() { _isLock = true; }
	inline void unlockCamera() { _isLock = false; }
	inline void startFollow() { _isFollow = true; }
	inline void stopFollow() { _isFollow = false; }

	inline float getAbsX() { return _x; }
	inline float getAbsY() { return _y; }

	inline float calRelX(float x) { return x - _x; }
	inline float calRelY(float y) { return y - _y; }
	inline float calAbsX(float x) { return x + _x; }
	inline float calAbsY(float y) { return y + _y; }
	inline RECT calRelRc(RECT rc) { return { (long)(rc.left - _x), (long)(rc.top - _y), (long)(rc.right - _x), (long)(rc.bottom - _y) }; }
	POINT calRelPt(POINT pt);
	POINT calAbsPt(POINT pt);

};

