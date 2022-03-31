#pragma once
#include "GameNode.h"

class Object;

using namespace MapToolEnum;
using namespace MapToolSet;

class MapToolScene : public GameNode
{
private:
	RectF _rcTileWindow;
	RectF _rcToolWindow;
	RectF _btnSave;
	RectF _btnLoad;

	RectF _rcSelectTile;
	RectF _rcHoverTile;

	POINT _curTile;			// 현재 타일
	POINT _selectedTileCnt; // 선택된 타일 갯수
	PointF _startCursor;

	bool _isDrag;

	Object* _camera;
	float _x; // 타일선택 카메라
	float _y; // 타일선택 카메라

	Image* _imgMap;
	Image* _imgTile;

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
	
	// 선택한 타일 렉트
	void calSelectTile();
	void settingSelectTileRect();
	void drawSelectTile(HDC hdc);
	void settingHoverTile();

	TILE_TYPE getTileType(int x, int y);

};

