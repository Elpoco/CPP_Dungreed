#pragma once
#include "SingletonBase.h"

class Tile;

using namespace MapTool;

class TileManager : public SingletonBase<TileManager>
{
private:
	Image* _tileImg;
	Tile* _tiles[TILE_CNT_X * TILE_CNT_Y];

	int _renderWidth;
	int _renderHeight;
	int _tileCntX;
	int _tileCntY;

public:
	TileManager();
	~TileManager();

	HRESULT init();
	HRESULT init(int tileCntX, int tileCntY);
	void release();
	void update();
	void render();

	void setRenderSize(int width, int height);

	void setTileFrame(int idx, int frameX, int frameY, TILE_TYPE type);

	void saveMap(string str = "");
	void loadMap(string str = "");

};

