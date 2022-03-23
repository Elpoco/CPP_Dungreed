#pragma once
#include "SingletonBase.h"

class CameraManager : public SingletonBase<CameraManager>
{
private:
	float _x;
	float _y;

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	inline float getRelX(float x) { x - _x; }
	inline float getRelY(float y) { y - _y; }

	inline void updateX(float x) { _x += x; }
	inline void updateY(float y) { _y += y; }

	CameraManager() {}
	~CameraManager() {}

};

