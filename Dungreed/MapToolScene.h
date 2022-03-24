#pragma once
#include "GameNode.h"

#define TILE_CNT	100

class Tile;

class MapToolScene : public GameNode
{
private:
	vector<Tile*> _vTiles;
	vector<Tile*>::iterator _viTiles;

	int x;
	int y;

	int mX;
	int mY;

public:
	HRESULT init(void);

	void release(void);
	void update(void);
	void render(void);

	MapToolScene() {}
	~MapToolScene() {}
};

