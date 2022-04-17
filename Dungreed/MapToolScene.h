#pragma once
#include "GameNode.h"

class Object;

using namespace MapToolEnum;
using namespace MapToolSet;

namespace MapToolSceneSet
{
//	constexpr char* tempSaveFile = "testSave";
//	constexpr char* tempSaveFile = "Town";
	constexpr char* tempSaveFile = FileName::Dungeon;
}

class MapToolScene : public GameNode
{
private:


private:
	Object* _camera;

	ImageBase* _imgObject;
	ImageBase* _imgTile;
	ImageBase* _imgTool;

	RECT _rcTileWindow;
	RECT _rcToolWindow;
	RECT _rcObjectWindow;
	RECT _rcTilePickWindow;

	RECT _rcHoverTile;

	int _objectIdx;

	RECT _btnSave;
	RECT _btnLoad;

	POINT _curTile;			// ���� Ÿ��
	POINT _selectedTileCnt; // ���õ� Ÿ�� ����
	RECT _rcSelectTile;
	POINT _startCursor;

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
	
	// ������ Ÿ�� ��Ʈ
	void calSelectTile();
	void settingSelectTileRect();
	void drawSelectTile(HDC hdc);
	void settingHoverTile();
};

