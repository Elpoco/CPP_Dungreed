#pragma once
#include "UI.h"

class WorldMap : public UI
{
private:
	ImageBase* _imgButton;
	UI* _uiLabel;
	UI* _uiEsc;

	UI* _uiBase;

	UI* _uiCurRoom;
	UI* _uiRoom[MapManagerSet::MAP_CNT];

	RECT _rcExitBtn;

	BOOL _showCurRoom;
	float _curRoomTime;

	BOOL* _arrIsClear;

public:
	WorldMap();
	virtual ~WorldMap();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void initUI();

};

