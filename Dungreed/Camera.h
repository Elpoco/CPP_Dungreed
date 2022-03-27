#pragma once
#include "GameNode.h"

class UI;
class Object;

class Camera : public GameNode
{
private:
	float _x;
	float _y;

public:
	Camera();
	~Camera();

	HRESULT init();
	void release();
	void update();
	void render();

	inline float getX() { return _x; }
	inline float getY() { return _y; }
	
	inline void moveX(float x) { _x += x; }
	inline void moveY(float y) { _y += y; }

	inline void setCameraPos(float x, float y) { _x = x; _y = y; }

};

