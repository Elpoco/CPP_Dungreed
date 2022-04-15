#pragma once
#include "UI.h"

class ImageFont : public UI
{
protected:
	ImageFontEnum::FONT_TYPE _type;
	ImageBase* _img;
	int _num;
	int* _arrNum;
	int _arrLen;
	int _imgWidth;
	int _imgHeight;
	BYTE _alpha;

public:
	ImageFont(float x, float y, int num, ImageFontEnum::FONT_TYPE type = ImageFontEnum::FONT_TYPE::NORMAL);
	virtual ~ImageFont();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void settingImage(ImageFontEnum::FONT_TYPE type);

};

