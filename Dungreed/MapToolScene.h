#pragma once
#include "GameNode.h"

class Object;

using namespace MapToolEnum;
using namespace MapToolSet;

class MapToolScene : public GameNode
{
private:
	RECT _rcTileWindow;
	RECT _rcToolWindow;
	RECT _btnSave;
	RECT _btnLoad;

	RECT _rcSelectTile;
	RECT _rcHoverTile;

	POINT _curTile;			// ���� Ÿ��
	POINT _selectedTileCnt; // ���õ� Ÿ�� ����
	POINT _startCursor;

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
};

