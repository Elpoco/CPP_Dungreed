#pragma once

using Gdiplus::PointF;
using Gdiplus::RectF;
using Gdiplus::Graphics;
using Gdiplus::Pen;
using Gdiplus::SolidBrush;
using Gdiplus::Color;

inline PointF PointMake(float x, float y)
{
	PointF pt = { x,y };
	return pt;
}

inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

inline RECT RectMake(float x, float y, float width, float height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

inline RectF RectFMake(float x, float y, float width, float height)
{
	RectF rc = { x, y, width, height };
	return rc;
}

inline RECT RectMakeCenter(float x, float y, float width, float height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

inline RectF RectFMakeCenter(float x, float y, float width, float height)
{
	RectF rc = { x - width / 2, y - height / 2, width, height };
	return rc;
}

inline void RectangleMake(HDC hdc, float x, float y, float width, float height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

inline void RectangleMakeCenter(HDC hdc, float x, float y, float width, float height)
{
	Rectangle(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

inline RectF CollisionAreaResizing(RectF &rcDest, int width, int height)
{
	RectF rc = { rcDest.GetLeft() + width / 2, rcDest.GetTop() + height / 2,
				rcDest.GetRight() - width / 2, rcDest.GetBottom() - height / 2 };

	return rc;
}

inline void RectangleMakeRect(HDC hdc, RectF rc) {

	Rectangle(hdc, rc.GetLeft(), rc.GetTop(), rc.GetRight(), rc.GetBottom());
}

inline void RectangleMake(HDC hdc, RectF rc, bool isFill = true, Color color = Color::Black, Color fillColor = Color::White)
{
	Graphics graphics(hdc);

	if (isFill)
	{
		SolidBrush brush(fillColor);

		graphics.FillRectangle(&brush, rc);
	}
	else
	{
		Pen pen(color);

		graphics.DrawRectangle(&pen, rc);
	}
}

inline void RectangleMakePoint(HDC hdc, PointF pt, float width, float height, Color color = Color::White)
{
	Graphics graphics(hdc);
	SolidBrush brush(color);

	graphics.FillRectangle(&brush, RectFMakeCenter(pt.X, pt.Y, width, height));
}

inline void PolygonMake(HDC hdc, POINT points[], int size) {
	Polygon(hdc, points, size);
}
