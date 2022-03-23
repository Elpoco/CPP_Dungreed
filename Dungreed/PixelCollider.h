#pragma once

class Unit;

class PixelCollider
{
private:
	enum COLLIDER_DIRECTION
	{
		LEFT,
		TOP,
		RIGHT,
		BOTTOM,
		DIR_CNT
	};

private:
	Unit* _unit;
	POINT _prove[DIR_CNT];

public:
	HRESULT init(Unit* unit);
	void release(void);
	void update(void); 
	void render(HDC hdc);

	void setProve(void);

	PixelCollider() {}
	~PixelCollider() {}
};
