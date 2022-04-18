#pragma once

class Object
{
protected:
	float _x;
	float _y;
	RECT _rc;
	RECT _rcRender;
	int _rcResizeW;
	int _rcResizeH;
	int _rcMoveX;
	int _rcMoveY;

	BOOL _isLive;
	BOOL _isRender;

public:
	Object();
	virtual ~Object();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	inline float getX() { return _x; }
	inline float getY() { return _y; }
	virtual inline void setX(float x) { _x = x; }
	virtual inline void setY(float y) { _y = y; }
	inline POINT getPt() { return PointMake(_x, _y); }

	inline RECT getRect() { return _rc; }
	inline BOOL isLive() { return _isLive; }
	inline void deleteObject() { _isLive = FALSE; }

	virtual void collisionObject() { deleteObject(); }
	virtual void pushObject(float x, float y) { _x += x; _y += y; }
	virtual void pushObject(DIRECTION dir, float distance) {}
	virtual void stopObject() {}
	virtual void resumeObject() {}

	virtual void deleteEffect() {}
	virtual int getDmg() { return 1; }

	virtual void setRender(BOOL isRender) { _isRender = isRender; }
};

