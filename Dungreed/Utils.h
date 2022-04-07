#pragma once

// =========
// # Utils #
// =========
#define DEG_TO_RAD		0.017453f
#define PI				3.141592653f
#define PI_2			6.283185308f

#define FLOAT_EPSILON	0.001f

#define FLOAT_TO_INT(f1)	static_cast<int>(f1+EPSILON)
#define FLOAT_EQUAL(f1, f2)	(fabs(f1-f2) <=FLOAT_EPSILON)

namespace MY_UTIL
{
	float GetDistance(float startX, float startY, float endX, float endY);
	float GetAngle(float startX, float startY, float endX, float endY);
	int GetAngleDeg(float startX, float startY, float endX, float endY);

	bool MouseInRect(RECT& rc);

	// ===============
	// # POINT, RECT #
	// ===============
	inline POINT PointMake(float x, float y)
	{
		POINT pt = { x,y };
		return pt;
	}

	inline Gdiplus::PointF PointFMake(float x, float y)
	{
		Gdiplus::PointF pt = { x,y };
		return pt;
	}

	inline Gdiplus::PointF PointToPointF(POINT pt)
	{
		Gdiplus::PointF ptF = { (float)pt.x, (float)pt.y };
		return ptF;
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

	inline Gdiplus::RectF RectFMake(float x, float y, float width, float height)
	{
		Gdiplus::RectF rc = { x, y, width, height };
		return rc;
	}

	inline RECT RectMakeCenter(float x, float y, float width, float height)
	{
		RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
		return rc;
	}

	inline Gdiplus::RectF RectFMakeCenter(float x, float y, float width, float height)
	{
		Gdiplus::RectF rc = { x - width / 2, y - height / 2, width, height };
		return rc;
	}

	inline Gdiplus::RectF RectToRectF(RECT rc)
	{
		return RectFMake(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
	}

	// ========================
	// # Print[ POINT, RECT ] #
	// ========================
	void PrintRectangle(HDC hdc, float x, float y, int width, int height);
	void PrintRectangle(HDC hdc, RECT rc);
	void PrintRectangleColor(HDC hdc, RECT rc, Color penColor = Color::Black, bool isFill = false, Color fillColor = Color::White);
	void PrintRectangleColor(HDC hdc, float x, float y, int width, int height, Color penColor = Color::Black, bool isFill = false, Color fillColor = Color::White);
	void PrintRectangleByPoint(HDC hdc, POINT pt, float width, float height, Color penColor = Color::Black, bool isFill = false, Color fillColor = Color::White);

	void PrintPoint(HDC hdc, float x, float y, int ptX, int ptY, char* format = "%d, %d");

	// ============
	// # template #
	// ============
	template<typename T>
	void swapValue(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	template<typename T>
	int castingToInt(T num)
	{
		return static_cast<int>(num);
	}
}