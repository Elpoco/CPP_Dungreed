#pragma once

class Object
{
protected:
	float _x;
	float _y;
	RECT _rc;

	BOOL _isLive;

public:
	Object();
	virtual ~Object();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void deleteEffect() {}

	inline float getX() { return _x; }
	inline float getY() { return _y; }
	inline void setX(float x) { _x = x; }
	inline void setY(float y) { _y = y; }
	inline POINT getPt() { return PointMake(_x,_y); }

	inline RECT getRect() { return _rc; }
	inline BOOL isLive() { return _isLive; }
	inline void deleteObject() { _isLive = FALSE; }

	virtual void collisionObject() { deleteObject(); }
	virtual void pushObject(float x, float y) { _x += x; _y += y; }
	virtual void pushObject(DIRECTION dir, float distance) {}
	virtual void stopObject() {}
};

