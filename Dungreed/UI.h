#pragma once
#include "GameNode.h"

class UI : public GameNode
{
public:
	UI();
	~UI();

	HRESULT init();
	HRESULT init(string imageName, RECT rc);
	void release();
	void update();
	void render();

	RECT getRect() { return _rc; }

private:
	float _x;
	float _y;
	RECT _rc;

	Image* _image;

};

