#pragma once
#include "ImageFont.h"

namespace DynamicFontSet
{
	constexpr float SHOW_TIME = 2.0f;
}

class DynamicFont : public ImageFont
{
private:
	float _initTime;
	BYTE _alpha;
	float _down;
	int _dir;

public:
	DynamicFont(float x, float y, int num, int dir);
	virtual ~DynamicFont();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void move();

};

