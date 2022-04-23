#pragma once
#include "SingletonBase.h"

class FontManager : public SingletonBase <FontManager>
{
public:
	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth,
		char* printString, int length, COLORREF color);
	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth,
		LPCWSTR printString, int length, COLORREF color);

	void drawNumber(HDC hdc, int destX, int destY, int fontSize, int fontWidth, char* str, COLORREF color = ColorSet::BLACK);
	void drawNumber(HDC hdc, int destX, int destY, int fontSize, int fontWidth, LPCWSTR str, COLORREF color = ColorSet::BLACK);
	
	void drawString(HDC hdc, int destX, int destY, int fontSize, int fontWidth, char* str, COLORREF color = ColorSet::BLACK);
	void drawString(HDC hdc, int destX, int destY, int fontSize, int fontWidth, LPCWSTR str, COLORREF color = ColorSet::BLACK);

	FontManager() {}
	~FontManager() {}

};

