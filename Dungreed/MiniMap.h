#pragma once
#include "UI.h"

namespace MiniMapSet
{
	constexpr int MAP_Y = 10;
}

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

	int _playerIdx;

public:
	MiniMap();
	virtual ~MiniMap();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void settingMiniMap();
	void updatePlayerPosition();
};

