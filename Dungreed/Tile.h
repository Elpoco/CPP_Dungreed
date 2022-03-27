#pragma once
#include "GameNode.h"

using namespace MapTool;

class Tile : public GameNode
{
private:
	RECT _rc;
	POINT _idx;
	POINT _frame;
	TILE_TYPE _type;

	float* tempX, * tempY;

public:
	Tile();
	Tile(int x, int y);
	~Tile();

	HRESULT init();
	HRESULT init(int x, int y);
	HRESULT init(int x, int y, TILE_TYPE type);
	void release();
	void update();
	void render();

	TILE_TYPE getType() { return _type; }
	RECT getRect() { return _rc; }

	void setType(TILE_TYPE type) { _type = type; }

	void setFrame(int x, int y, TILE_TYPE type) { _frame = { x,y }; _type = type; }

};

