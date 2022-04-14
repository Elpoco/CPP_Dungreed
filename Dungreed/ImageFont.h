#pragma once
#include "UI.h"
class ImageFont : public UI
{
protected:
	ImageBase* _img;
	int _num;
	int* _arrNum;
	int _arrLen;
	int _imgWidth;
	int _imgHeight;

public:
	ImageFont(float x, float y, int num, BOOL fixed = TRUE);
	virtual ~ImageFont();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

};

