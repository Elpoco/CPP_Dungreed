#include "Stdafx.h"
#include "Utils.h"

using Gdiplus::PointF;
using Gdiplus::RectF;
using Gdiplus::Graphics;
using Gdiplus::Pen;
using Gdiplus::SolidBrush;
using Gdiplus::Color;

namespace MY_UTIL
{
	float GetDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrt(x * x + y * y);
	}

	float GetAngle(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;
		float d = sqrt(x * x + y * y);
		float angle = acos(x / d);

		if (y > 0)angle = PI_2 - angle;

		return angle;
	}

	int GetAngleDeg(float startX, float startY, float endX, float endY)
	{
		return GetAngle(startX, startY, endX, endY) / PI * 180;
	}

	int radToDeg(float angle)
	{
		return angle / PI * 180;
	}

	bool MouseInRect(RECT& rc)
	{
		return PtInRect(&rc, _ptMouse);
	}

	// ========================
	// # Print[ POINT, RECT ] #
	// ========================
	void PrintRectangle(HDC hdc, float x, float y, int width, int height)
	{
		Rectangle(hdc, x, y, x + width, y + height);
	}

	void PrintRectangle(HDC hdc, RECT rc)
	{
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	}

	void PrintRectangleColor(HDC hdc, RECT rc, Color penColor, bool isFill, Color fillColor)
	{
		Graphics graphics(hdc);

		RectF rcf = RectToRectF(rc);

		if (isFill)
		{
			SolidBrush brush(fillColor);

			graphics.FillRectangle(&brush, rcf);
		}
		else
		{
			Pen pen(penColor);

			graphics.DrawRectangle(&pen, rcf);
		}
	}

	void PrintRectangleColor(HDC hdc, float x, float y, int width, int height, Color penColor, bool isFill, Color fillColor)
	{
		PrintRectangleColor(hdc, RectMake(x, y, width, height), penColor, isFill, fillColor);
	}

	void PrintRectangleByPoint(HDC hdc, POINT pt, float width, float height, Color penColor, bool isFill, Color fillColor)
	{
		PrintRectangleColor(hdc, RectMakeCenter(pt.x, pt.y, width, height), penColor, isFill, fillColor);
	}

	void PrintPoint(HDC hdc, float x, float y, int ptX, int ptY, char* format)
	{
		char str[128];
		wsprintf(str, format, ptX, ptY);
		TextOut(hdc, x, y, str, strlen(str));
	}
}