#pragma once
#include "UI.h"
class MiniMap : public UI
{
private:
	float _mapWidth;
	float _mapHeight;
	int _tileCntX;
	int _tileCntY;

public:
	MiniMap();
	virtual ~MiniMap();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void settingMiniMap();
};

