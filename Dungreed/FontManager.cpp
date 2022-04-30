#include "Stdafx.h"
#include "FontManager.h"

void FontManager::drawText(HDC hdc, STRING_INFO stringInfo, int fontSize, int fontWidth, COLORREF color)
{
	//SetBkMode(hdc, OPAQUE);
	SetBkMode(hdc, TRANSPARENT);

	HFONT hFont = CreateFont(
		fontSize, 0, 0, 5, fontWidth,
		0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT(FontName::text));

	auto oldFont = (HFONT)SelectObject(hdc, hFont);
	auto oldColor = GetTextColor(hdc);

	SetTextColor(hdc, color);

	/////////////////
	int strLen = strlen(stringInfo.str);

	SIZE size;
	GetTextExtentPoint32(hdc, stringInfo.str, strLen, &size);

	if (size.cx > stringInfo.width)
	{
		// 공백크기는 4, 16
		int len = strLen + 1;
		char* tmp = new char[len];
		strcpy(tmp, stringInfo.str);

		char* arrStr = strtok(tmp, " ");

		int strWidth = 0;
		int line = 0;

		for (int i = 0; arrStr != NULL; i++)
		{
			TextOut(hdc, stringInfo.startX + strWidth, stringInfo.startY + line * size.cy, arrStr, strlen(arrStr));
			GetTextExtentPoint32(hdc, arrStr, strlen(arrStr), &size);
			strWidth += size.cx + 4;
			if (strWidth > stringInfo.width)
			{
				strWidth = 0;
				line++;
			}
			arrStr = strtok(NULL, " ");
		}

		SAFE_DELETE_ARRAY(tmp);
	}
	else
	{
		TextOut(hdc, stringInfo.startX, stringInfo.startY, stringInfo.str, strLen);
	}
	////////////////

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);

	SetTextColor(hdc, oldColor);
}

SIZE FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth, const char* printString, COLORREF color, BOOL centerX)
{
	SetBkMode(hdc, TRANSPARENT);

	HFONT hFont = CreateFont(
		fontSize, 0, 0, 5, fontWidth,
		0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT(fontName));

	auto oldFont = (HFONT)SelectObject(hdc, hFont);
	auto oldColor = GetTextColor(hdc);
	
	int strLen = strlen(printString);

	SIZE size;
	GetTextExtentPoint32(hdc, printString, strLen, &size);

	SetTextColor(hdc, color);

	if (centerX) 
		destX = destX - size.cx * 0.5f;

	TextOut(hdc, destX, destY, printString, strLen);


	SelectObject(hdc, oldFont);
	DeleteObject(hFont);

	SetTextColor(hdc, oldColor);

	return size;
}

SIZE FontManager::drawNumber(HDC hdc, int destX, int destY, int fontSize, int fontWidth, const char* str, COLORREF colorSet)
{
	return drawText(hdc, destX, destY, FontName::num, fontSize, fontWidth, str, colorSet);
}

SIZE FontManager::drawString(HDC hdc, int destX, int destY, int fontSize, int fontWidth, const char* str, COLORREF colorSet)
{
	return drawText(hdc, destX, destY, FontName::text, fontSize, fontWidth, str, colorSet);
}

SIZE FontManager::drawStringCenterX(HDC hdc, int destX, int destY, int fontSize, int fontWidth, const char* str, COLORREF colorSet)
{
	return drawText(hdc, destX, destY, FontName::text, fontSize, fontWidth, str, colorSet, TRUE);
}
