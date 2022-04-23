#pragma once
#include "UI.h"

class ImageFont : public UI
{
protected:
	ImageFontEnum::FONT_TYPE _type;
	ImageBase* _img;

	BYTE	_alpha;
	char*	_str;
	int		_num;
	int*	_arrNum;
	int		_arrLen;
	int		_imgWidth;
	int		_imgHeight;

public:
	ImageFont(float x, float y, int num, ImageFontEnum::FONT_TYPE type = ImageFontEnum::FONT_TYPE::NORMAL);
	ImageFont(float x, float y, char* str);
	virtual ~ImageFont();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void initNumber();
	void initString();

	void settingImage(ImageFontEnum::FONT_TYPE type);

	void setNumber(int num);

};

