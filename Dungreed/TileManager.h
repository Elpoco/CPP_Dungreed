#pragma once
#include "SingletonBase.h"

class TileManager : public SingletonBase<TileManager>
{
private:
	Image* _imgTile;
	TILE* _tiles;

	int _renderWidth;
	int _renderHeight;
	int _tileCntX;
	int _tileCntY;
	int _tileTotalCnt;

public:
	TileManager();
	~TileManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void tileRender(HDC hdc, TILE tile);

	void setRenderSize(int width, int height);
	//void setTileFrame(int idx, int frameX, int frameY, MapToolEnum::TERRAIN terrain, MapToolEnum::MAP_OBJECT object);
	void setTileFrame(int idx, int frameX, int frameY, MapToolEnum::TYPE type);

	TILE getTile(int idx) { return _tiles[idx]; }
	TILE getTile(float x, float y);
	TILE getTile(POINT pt);
	POINT getTilePt(POINT pt);
	int getTileIndex(float x, float y);
	int getTileIndex(POINT pt);
	//MapToolEnum::TILE_TYPE getTileType(PointF pt);

	int saveMap(string str = String::tempSaveFile);
	int loadMap(string str = String::tempSaveFile);

};

