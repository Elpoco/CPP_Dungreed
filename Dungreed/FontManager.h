#pragma once
#include "SingletonBase.h"
/*
font = CreateFont(
	문자 크기, 문자폭, 문자전체 기울기, 문자 방향, 문자 굵기,
	기울기 (true, false), 밑줄 (할꺼냐, 말꺼냐), 취소선(),
	문자 세팅, 출력 정확도, 클리핑 정확도, 출력의 질, 자간, 폰트
);
*/
class FontManager : public SingletonBase <FontManager>
{
public:
	void drawText(HDC hdc, int destX, int destY, char* fileName, char* fontName, int fontSizem, int fontWidth,
		char* printString, int length, COLORREF color);

	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth,
		char* printString, int length, COLORREF color);

	// LPCWSTR (W) -> wide char -> UniCode
	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth,
		LPCWSTR printString, int length, COLORREF color);

	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth,
		LPCWSTR* printStringArr, int length, COLORREF color);

	FontManager() {}
	~FontManager() {}

};

