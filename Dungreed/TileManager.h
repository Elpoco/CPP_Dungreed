#pragma once
#include "SingletonBase.h"

using namespace MapTool;

class TileManager : public SingletonBase<TileManager>
{
private:
	typedef struct tagTile
	{
		RECT rc;
		POINT idx;
		POINT tileFrame;
		TILE_TYPE type;
		
		tagTile()
		{
			rc = { 0,0,0,0 };
			idx = { 0,0 };
			tileFrame = { 0,0 };
			type = TILE_TYPE::NONE;
		}
	} Tile;

private:
	Image* _tileImg;
	Tile* _tiles;

	int _renderWidth;
	int _renderHeight;
	int _tileCntX;
	int _tileCntY;
	int _tileTotalCnt;

public:
	TileManager();
	~TileManager();

	HRESULT init();
	HRESULT init(int tileCntX, int tileCntY);
	void release();
	void update();
	void render(HDC hdc);

	void tileRender(HDC hdc, Tile tile);

	void setRenderSize(int width, int height);
	void setTileFrame(int idx, int frameX, int frameY, TILE_TYPE type);

	int getTileIndex(POINT pt);
	TILE_TYPE getTileType(POINT pt);

	int saveMap(string str = "testSave.dat");
	int loadMap(string str = "testSave.dat");

};

