#pragma once
#include "GameNode.h"

class Object;

namespace MapToolSceneSet
{
	constexpr int TOOL_SIZE_X = TOOL_TILE_SIZE * 8;
	constexpr int TOOL_START_X = WINSIZE_X - TOOL_SIZE_X;
	constexpr float CAMERA_SPPED = 10.0f;
	constexpr char* tempSaveFile = "testSave";
}

class MapToolScene : public GameNode
{
private:
	Object* _camera;

	ImageBase* _imgObject;
	ImageBase* _imgTile;
	ImageBase* _imgTool;

	RECT _rcTileWindow;		// Ÿ�� �׸��� ������
	RECT _rcToolWindow;		// ���� ������
	RECT _rcToolTileHover;	// ���콺 ���� ���� ��Ʈ
	RECT _rcObjectWindow;	// Ÿ�� Ÿ��
	RECT _rcTilePickWindow; // Ÿ�� �׸�

	RECT _rcHoverTile;      // ���콺 �ø��� ǥ�õǴ� �Ķ���Ʈ


	POINT _curTile;			// ���� Ÿ��
	POINT _selectedTileCnt; // ���õ� Ÿ�� ����
	POINT _startCursor;     // ����Ÿ�� �巡���Ҷ� ���� ����Ʈ
	RECT  _rcSelectTile;	// ������ Ÿ�� ������Ʈ
	int _objectIdx;			// ������ ������Ʈ Ÿ��

	// Ÿ�� ������ ��ġ
	int _tilePickX;
	int _tilePickY;

	// �� ����
	RECT _rcMapName;
	BOOL _isTyping;
	char* _mapName;

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

	// ������ Ÿ�� ��Ʈ
	void calSelectTile();
	void settingSelectTileRect();
	void drawSelectTile(HDC hdc);
};

