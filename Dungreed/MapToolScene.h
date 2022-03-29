#pragma once
#include "GameNode.h"

class Object;

class MapToolScene : public GameNode
{
private:
	RECT _rcTileWindow;
	RECT _rcToolWindow;
	RECT _btnSave;
	RECT _btnLoad;

	RECT _rcSelectTile;

	POINT _curTile;
	POINT _selectedTileCnt; // ���õ� Ÿ�� ����
	POINT _startCursor;

	bool _isDrag;

	Object* _camera;
	float _x; // Ÿ�ϼ��� ī�޶�
	float _y; // Ÿ�ϼ��� ī�޶�

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

