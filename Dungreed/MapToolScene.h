#pragma once
#include "GameNode.h"

using namespace MapTool;

class MapToolScene : public GameNode
{
private:
	RECT _rcTileWindow;
	RECT _rcToolWindow;
	RECT _btnSave;
	RECT _btnLoad;

	bool _isBtn;

	float _x;
	float _y;

	float _cX;
	float _cY;

	POINT _curTile;

	Image* mapImg;
	Image* tileImg;

public:
	MapToolScene();
	~MapToolScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void clickDrawTile();
	void clickUndoTile();

	void clickChangeTile();

	void clickSave();
	void clickLoad();
	
};

