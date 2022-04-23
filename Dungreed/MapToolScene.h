#pragma once
#include "GameNode.h"

class Object;

namespace MapToolSceneSet
{
	constexpr int TOOL_SIZE_X = TOOL_TILE_SIZE * 8;
	constexpr int TOOL_START_X = WINSIZE_X - TOOL_SIZE_X;
	constexpr float CAMERA_SPPED = 10.0f;
//	constexpr char* tempSaveFile = "testSave";
//	constexpr char* tempSaveFile = "Town";
	constexpr char* tempSaveFile = FileName::Dungeon;
}

class MapToolScene : public GameNode
{
private:
	Object* _camera;

	ImageBase* _imgObject;
	ImageBase* _imgTile;
	ImageBase* _imgTool;

	RECT _rcTileWindow;		// 타일 그리는 윈도우
	RECT _rcToolWindow;		// 도구 윈도우
	RECT _rcObjectWindow;	// 타일 타입
	RECT _rcTilePickWindow; // 타일 그림

	RECT _rcHoverTile;      // 마우스 올릴때 표시되는 파란렉트

	int _objectIdx;

	RECT _btnSave;
	RECT _btnLoad;

	POINT _curTile;			// 현재 타일
	POINT _selectedTileCnt; // 선택된 타일 갯수
	POINT _startCursor;     // 여러타일 드래그할때 시작 포인트
	RECT  _rcSelectTile;	// 선택한 타일 빨간렉트

	bool _isDrag;
	int _tilePickX;
	int _tilePickY;

public:
	MapToolScene();
	~MapToolScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void hoverTile();
	void selectObjectTile();
	void selectTile();

	POINT getMousePointIdx();

	void clickDrawTile();
	void clickUndoTile();

	void clickSave();
	void clickLoad();
	
	// 선택한 타일 렉트
	void calSelectTile();
	void settingSelectTileRect();
	void drawSelectTile(HDC hdc);
};

