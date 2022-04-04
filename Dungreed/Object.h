#pragma once

/*
위치정보, 충돌
*/

class Object
{
protected:
	float _x;
	float _y;
	RectF _rc;

	PointF _prove[ColliderEnum::DIRECTION::DIR_CNT];
	bool _isCollision[ColliderEnum::DIRECTION::DIR_CNT];

public:
	Object();
	virtual ~Object();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	PointF* getProve() { return _prove; }

	bool getCollision(ColliderEnum::DIRECTION dir) { return _isCollision[dir]; }
	void setCollision(ColliderEnum::DIRECTION dir, bool collision) { _isCollision[dir] = collision; }

	inline float getX() { return _x; }
	inline float getY() { return _y; }
	inline void setX(float x) { _x = x; }
	inline void setY(float y) { _y = y; }
	inline PointF getPt() { return { _x,_y }; }

	inline RectF getRect() { return _rc; }

};

