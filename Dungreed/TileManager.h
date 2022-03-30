#pragma once
#include "SingletonBase.h"



class TileManager : public SingletonBase<TileManager>
{
private:
	typedef struct tagTile
	{
		RECTF rc;
		POINTF pos;
		int tileFrameX;
		int tileFrameY;
		MapToolEnum::TILE_TYPE type;

		tagTile()
		{
			rc = { 0,0,0,0 };
			pos = { 0,0 };
			tileFrameX = 0;
			tileFrameY = 0;
			type = MapToolEnum::TILE_TYPE::NONE;
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
	void setTileFrame(int idx, int frameX, int frameY, MapToolEnum::TILE_TYPE type);

	POINTF getTilePt(POINTF pt);
	int getTileIndex(POINTF pt);
	MapToolEnum::TILE_TYPE getTileType(POINTF pt);

	int saveMap(string str = String::tempSaveFile);
	int loadMap(string str = String::tempSaveFile);

};

