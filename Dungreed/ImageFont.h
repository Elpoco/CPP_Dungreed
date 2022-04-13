#pragma once
#include "UI.h"
class ImageFont : public UI
{
protected:
	Image* _img;
	int _num;

public:
	ImageFont(float x, float y, int num, BOOL fixed = TRUE);
	virtual ~ImageFont();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

};

