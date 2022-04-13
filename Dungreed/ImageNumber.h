#pragma once
#include "UI.h"
class ImageNumber : public UI
{
private:
	Image* _img;

public:
	ImageNumber(float x, float y, int num, BOOL fixed = FALSE);
	virtual ~ImageNumber();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

};

