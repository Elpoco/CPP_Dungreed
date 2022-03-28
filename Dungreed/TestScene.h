#pragma once
#include "GameNode.h"

class Player;

#define TILE_SIZE 48

class TestScene : public GameNode
{
private:
	Player* _player;

	enum TILE_TYPE
	{
		NONE,
		BLOCK
	};

	struct tagTile
	{
		float x;
		float y;
		TILE_TYPE type;
		RECT rc;
	};

	vector<tagTile> _vTiles;
	vector<tagTile>::iterator _viTile;

	int _proveBottom;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	TestScene() {}
	~TestScene() {}
};

