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

	POINT _curTile;			// ���� Ÿ��
	POINT _selectedTileCnt; // ���õ� Ÿ�� ����
	PointF _startCursor;

	bool _isDrag;

	Object* _camera;
	float _x; // Ÿ�ϼ��� ī�޶�
	float _y; // Ÿ�ϼ��� ī�޶�

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
	
	// ������ Ÿ�� ��Ʈ
	void calSelectTile();
	void settingSelectTileRect();
	void drawSelectTile(HDC hdc);
	void settingHoverTile();

	TILE_TYPE getTileType(int x, int y);

};

