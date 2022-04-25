#pragma once
#include "SingletonBase.h"

class TileManager : public SingletonBase<TileManager>
{
private:
	ImageBase* _imgObject;
	Image* _imgTile;
	TILE* _tiles;

	BOOL _isShowObj;

	string _curMapName;
	int _renderWidth;
	int _renderHeight;

public:
	TileManager();
	~TileManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void initTile();

	void tileRender(HDC hdc, TILE tile);

	void setRenderSize(int width, int height);
	void setTile(int idx, int frameX, int frameY, int type);

	TILE getTile(int idx) { return _tiles[idx]; }
	TILE getTile(float x, float y);
	TILE getTile(POINT pt);
	POINT getTilePt(POINT pt);
	int getTileIndex(float x, float y);
	int getTileIndex(POINT pt);

	int saveMap(string str);
	int loadMap(string str);

	void setShowObj(BOOL isShow) { _isShowObj = isShow; }
	BOOL getShowObj() { return _isShowObj; }

	int getCurrentMapTileCntX();
	int getCurrentMapTileCntY();
	float getCurrentMapTileWidth();
	float getCurrentMapTileHeight();
	Code::MAP getCurrentMapCode();

	void getDoorPos(POINT* ptDoor);

	const TILE* getTiles() { return _tiles; }

};

