#pragma once
#include "UI.h"

class MiniMap : public UI
{
private:
	struct tagMiniMap
	{

	};

private:
	ImageBase* _imgBlock;
	ImageBase* _imgPlayer;
	MapToolEnum::MAP_OBJ* _arrType;

	int _tileCntX;
	int _tileCntY;
	int _miniMapX;
	int _miniMapY;
	int _miniMapW;
	int _miniMapH;

	int _playerX;
	int _playerY;

public:
	MiniMap();
	virtual ~MiniMap();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void settingMiniMap();
	void updateUnitPosition();
};

