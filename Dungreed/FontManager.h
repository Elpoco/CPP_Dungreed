#pragma once
#include "SingletonBase.h"

class FontManager : public SingletonBase <FontManager>
{
public:
	void drawText(HDC hdc, STRING_INFO stringInfo, int fontSize, int fontWidth, COLORREF color);
	SIZE drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth, const char* printString, COLORREF color, BOOL centerX = FALSE);

	SIZE drawNumber(HDC hdc, int destX, int destY, int fontSize, int fontWidth, const char* str, COLORREF colorSet = ColorSet::BLACK);
	SIZE drawString(HDC hdc, int destX, int destY, int fontSize, int fontWidth, const char* str, COLORREF colorSet = ColorSet::BLACK);
	SIZE drawStringCenterX(HDC hdc, int destX, int destY, int fontSize, int fontWidth, const char* str, COLORREF colorSet = ColorSet::BLACK);

	FontManager() {}
	~FontManager() {}

};

