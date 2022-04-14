#pragma once
#include "ImageFont.h"

namespace DynamicFontSet
{
	constexpr float SHOW_TIME = 2.0f;
}

class DynamicFont : public ImageFont
{
private:
	ImageBase* _imgGold;

	BYTE	_alpha;
	float	_initTime;
	float	_down;
	int		_dir;
	int		_type; // 0 µ¥¹ÌÁö, 1 °ñµå

public:
	DynamicFont(float x, float y, int num, int dir, int type);
	virtual ~DynamicFont();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void move();

};

