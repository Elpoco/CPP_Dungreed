#pragma once
#include "UI.h"

class MiniMap : public UI
{
private:
	enum class MINIMAP_OBJ_TYPE
	{
		ENEMY,
		NPC,
		OBJ,
	};

	struct tagMinimapObj
	{
		MINIMAP_OBJ_TYPE type;
		POINT pt;
	};

private:
	ImageBase* _imgBorder;
	ImageBase* _imgBlock;
	ImageBase* _imgPlayer;
	ImageBase* _imgEnemy;
	ImageBase* _imgDoor;
	ImageBase* _imgNPC;
	ImageBase* _imgTresure;
	MapToolEnum::MAP_OBJ* _arrType; // 타일의 타입을 담을 배열
	BOOL _isDungeon;

	int _tileCntX;
	int _tileCntY;

	int _miniMapX;
	int _miniMapY;
	int _miniMapW;
	int _miniMapH;

	int _playerX;
	int _playerY;
	
	ObjectManager::vObjects* _vObject;
	vector<tagMinimapObj> _vObect;

public:
	MiniMap();
	virtual ~MiniMap();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void settingMiniMap();
	void updateObjectPosition();

	void setDungeon(BOOL isDungeon) { _isDungeon = isDungeon; }
};

