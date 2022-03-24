#pragma once
#include "SingletonBase.h"
class MapManager : public SingletonBase<MapManager>
{
private:


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	MapManager() {}
	~MapManager() {}
};

