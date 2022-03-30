#pragma once

inline PointF PointMake(int x, int y)
{
	PointF pt = { x,y };
	return pt;
}

inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

inline RectF RectMake(float x, float y, float width, float height)
{
	RectF rc = { x, y, x + width, y + height };
	return rc;
}

inline RectF RectMakeCenter(float x, float y, float width, float height)
{
	RectF rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
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
	RectF rc = { rcDest. + width / 2, rcDest.top + height / 2,
				rcDest.right - width / 2, rcDest.bottom - height / 2 };

	return rc;
}

inline void RectangleMakeRect(HDC hdc, RECTF rc) {

	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

inline void ColorRectangleMake(HDC hdc, RECTF rc, COLORREF color = RGB(0, 0, 0), bool isTrans = false)
{
	HGDIOBJ hPen = SelectObject(hdc, GetStockObject(DC_PEN));
	HGDIOBJ hBrush = SelectObject(hdc, GetStockObject(WHITE_BRUSH));
	SetDCPenColor(hdc, color);

	if (isTrans) SelectObject(hdc, GetStockObject(NULL_BRUSH));

	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

	SelectObject(hdc, hPen);
	SelectObject(hdc, hBrush);
}

inline void PolygonMake(HDC hdc, POINT points[], int size) {
	Polygon(hdc, points, size);
}
