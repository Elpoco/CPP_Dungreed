#pragma once
#include "SingletonBase.h"

class TileManager : public SingletonBase<TileManager>
{
private:
	typedef struct tagTile
	{
		RECT rc;
		POINT pos;
		int tileFrameX;
		int tileFrameY;
		MapTool::TILE_TYPE type;
		
		tagTile()
		{
			rc = { 0,0,0,0 };
			pos = { 0,0 };
			tileFrameX = 0;
			tileFrameY = 0;
			type = MapTool::TILE_TYPE::NONE;
		}
	} Tile;

private:
	Image* _imgTile;
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
	void setTileFrame(int idx, int frameX, int frameY, MapTool::TILE_TYPE type);

	int getTileIndex(POINT pt);
	MapTool::TILE_TYPE getTileType(POINT pt);

	int saveMap(string str = String::tempSaveFile);
	int loadMap(string str = String::tempSaveFile);

};

