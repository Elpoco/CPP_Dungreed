#include "Stdafx.h"
#include "FontManager.h"

void FontManager::drawText(HDC hdc, int destX, int destY, char * fontName, int fontSize, int fontWidth, char* printString, int length, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);

	HFONT hFont = CreateFont(
		fontSize, 0, 0, 5, fontWidth,
		0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT(fontName));

	auto oldFont = (HFONT)SelectObject(hdc, hFont);
	auto oldColor = GetTextColor(hdc);

	SetTextColor(hdc, color);
	TextOut(hdc, destX, destY, printString, length);

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);

	SetTextColor(hdc, oldColor);
}

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth, LPCWSTR printString, int length, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);

	HFONT hFont = CreateFont(
		fontSize, 0, 0, 5, fontWidth,
		0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT(fontName));

	auto oldFont = (HFONT)SelectObject(hdc, hFont);
	auto oldColor = GetTextColor(hdc);
	
	SetTextColor(hdc, color);
	TextOutW(hdc, destX, destY, printString, length);

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);

	SetTextColor(hdc, oldColor);
}

void FontManager::drawNumber(HDC hdc, int destX, int destY, int fontSize, int fontWidth, char * str, COLORREF color)
{
	drawText(hdc, destX, destY, FontName::num, fontSize, fontWidth, str, strlen(str), color);
}

void FontManager::drawNumber(HDC hdc, int destX, int destY, int fontSize, int fontWidth, LPCWSTR str, COLORREF color)
{
	drawText(hdc, destX, destY, FontName::num, fontSize, fontWidth, str, wcslen(str), color);
}

void FontManager::drawString(HDC hdc, int destX, int destY, int fontSize, int fontWidth, char* str, COLORREF color)
{
	drawText(hdc, destX, destY, FontName::text, fontSize, fontWidth, str, strlen(str), color);
}

void FontManager::drawString(HDC hdc, int destX, int destY, int fontSize, int fontWidth, LPCWSTR str, COLORREF color)
{
	drawText(hdc, destX, destY, FontName::text, fontSize, fontWidth, str, wcslen(str), color);
}
