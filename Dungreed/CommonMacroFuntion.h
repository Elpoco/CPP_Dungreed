#pragma once

inline POINT PointMake(int x, int y)
{
	POINT pt = { x,y };
	return pt;
}

inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

inline RECT RectMake(int x, int y, int width, int height, int posX, int posY)
{
	RECT rc = { x + posX, y + posY, x + width + posX, y + height + posY };
	return rc;
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
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

inline RECT CollisionAreaResizing(RECT &rcDest, int width, int height)
{
	RECT rc = { rcDest.left + width / 2, rcDest.top + height / 2,
				rcDest.right - width / 2, rcDest.bottom - height / 2 };

	return rc;
}

inline void RectangleMakeRect(HDC hdc, RECT rc) {

	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

inline void ColorRectangleMake(HDC hdc, RECT rc, COLORREF color = RGB(0, 0, 0), bool isTrans = false)
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
