#pragma once

/*
위치정보, 충돌
*/

class Object
{
protected:
	float _x;
	float _y;
	RECT _rc;

	bool _isCollision[ColliderEnum::DIRECTION::DIR_CNT];

public:
	Object();
	virtual ~Object();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	bool getCollision(ColliderEnum::DIRECTION dir) { return _isCollision[dir]; }
	void setCollision(ColliderEnum::DIRECTION dir, bool collision) { _isCollision[dir] = collision; }
	virtual void pushObject(float x = 0, float y = 0) {}
	virtual void pushObject(ColliderEnum::DIRECTION dir, float x, float y) {}

	inline float getX() { return _x; }
	inline float getY() { return _y; }
	inline void setX(float x) { _x = x; }
	inline void setY(float y) { _y = y; }
	inline POINT getPt() { return PointMake(_x,_y); }

	inline RECT getRect() { return _rc; }

};

