#pragma once

/*
애니메이션, 위치정보, 충돌
*/

class Object
{
private:
	typedef vector<Image*> vImages;
	typedef vector<Image*>::iterator viImages;

	struct tagFrameInfo
	{
		int tick;
		int cnt;
		int x;
		int y;

		tagFrameInfo()
		{
			tick = 10;
			cnt = 0;
			x = 0;
			y = 0;
		}
	};

private:
	tagFrameInfo _frameInfo;

protected:
	// Image
	vImages _vImages;
	int _imgCurrent;
	float _imgWidth;
	float _imgHeight;

	// Position
	float _x;
	float _y;
	RectF _rc;

	PointF _prove[ColliderEnum::DIRECTION::DIR_CNT];
	bool _isCollision[ColliderEnum::DIRECTION::DIR_CNT];

	bool _isLeft;

public:
	Object();
	virtual ~Object();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void animation();

	void settingProve();
	PointF* getProve() { return _prove; }

	void setCollision(ColliderEnum::DIRECTION dir, bool collision) { _isCollision[dir] = collision; }
	bool getCollision(ColliderEnum::DIRECTION dir) { return _isCollision[dir]; }

	void setFrameY(int frameY) { _frameInfo.y = frameY; }	

	float getX() { return _x; }
	float getY() { return _y; }
	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }

	float getWidth() { return _imgWidth; }
	float getHeight() { return _imgHeight; }
	RectF getRect() { return _rc; }

};

