#pragma once
class Object
{
private:
	typedef vector<Image*> vImages;

	struct tagFrameInfo
	{
		int tick;
		int cnt;
		int x;
		int y;

		tagFrameInfo()
		{
			tick = 8;
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

	// Position
	float _x;
	float _y;
	RECT _rc;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void animation(void);
	void updateRect(void);

	void setFrameY(int frameY) { _frameInfo.y = frameY; }

	const float getX(void) { return _x; }
	const float getY(void) { return _y; }
	const RECT getRect(void) { return _rc; }

	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }

	Object();
	virtual ~Object() {}
};

