#pragma once
#include "GameNode.h"

class Object;

class GameScene : public GameNode
{
private:
	typedef struct tagTownDeco
	{
		ImageBase* img;
		float x;
		float y;
	} TOWN_DECO;

private:
	LocationEnum::LOCATION _location;

	// Town
	Image* _imgLayer;
	Image* _imgBackground;
	RECT _rcLayer;
	RECT _rcBackground;
	RECT _rcEntrance;

	ImageBase* _imgEnter;
	FRAME_INFO _enterFrame;
	RECT _rcEnter;
	BOOL _isEnter;

	// 마을 장식
	vector<TOWN_DECO> _vTownDeco;

public:
	GameScene();
	~GameScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void updateTown();
	void renderTown(HDC hdc);
	void renderBackTown(HDC hdc);

	void loadDungeon();

};

