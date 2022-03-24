#pragma once
#include "SingletonBase.h"

#define INIT_X		0
#define INIT_Y		0

class CameraManager : public SingletonBase<CameraManager>
{
private:
	float _x;
	float _y;

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	inline float getRelX(float x) { return x - _x; }
	inline float getRelY(float y) { return y - _y; }
	inline float getAbsX() { return _x; }
	inline float getAbsY() { return _y; }
	inline void setAbsX(float x) { _x = x; }
	inline void setAbsY(float y) { _y = y; }

	inline void updateX(float x) { _x += x; }
	inline void updateY(float y) { _y += y; }

	CameraManager() {}
	~CameraManager() {}

};

