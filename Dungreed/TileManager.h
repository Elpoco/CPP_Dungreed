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
	HRESULT init(int tileCntX, int tileCntY);
	void release();
	void update();
	void render(HDC hdc);

	void tileRender(HDC hdc, TILE tile);

	void setRenderSize(int width, int height);
	void setTileFrame(int idx, int frameX, int frameY, MapToolEnum::TILE_TYPE type);

	TILE getTile(PointF pt);
	PointF getTilePt(PointF pt);
	int getTileIndex(PointF pt);
	MapToolEnum::TILE_TYPE getTileType(PointF pt);

	int saveMap(string str = String::tempSaveFile);
	int loadMap(string str = String::tempSaveFile);

};

