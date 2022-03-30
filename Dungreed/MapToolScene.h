#pragma once
#include "GameNode.h"

class Object;

class MapToolScene : public GameNode
{
private:
	RECTF _rcTileWindow;
	RECTF _rcToolWindow;
	RECTF _btnSave;
	RECTF _btnLoad;

	RECT _rcSelectTile;

	POINT _curTile;
	POINT _selectedTileCnt; // 선택된 타일 갯수
	POINT _startCursor;

	bool _isDrag;

	Object* _camera;
	float _x; // 타일선택 카메라
	float _y; // 타일선택 카메라

	Image* _mapImg;
	Image* _tileImg;

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
	
	void settingSelectTileRect();
	void drawSelectTile(HDC hdc);

};

