#pragma once

// =========
// # Utils #
// =========
#define EPSILON				0.001f
#define TO_INT(n)			static_cast<int>(n)
#define FLOAT_TO_INT(f1)	static_cast<int>(f1+EPSILON)

namespace MY_UTIL
{
	BOOL IsOnceKeyDown(int key);
	BOOL IsOnceKeyUp(int key);
	BOOL IsStayKeyDown(int key);
	BOOL IsToggleKey(int key);

	ImageBase* FindImage(string imgName);

	float GetDistance(float startX, float startY, float endX, float endY);
	float GetDistance(POINT startPt, POINT endPt);
	float GetAngle(float startX, float startY, float endX, float endY);
	float GetAngle(POINT startPt, POINT endPt);
	int GetAngleDeg(float startX, float startY, float endX, float endY);
	int GetAngleDeg(POINT startPt, POINT endPt);
	int RadToDeg(float angle);
	float DegToRad(int angle);

	bool MouseInRect(RECT& rc);

	// =======
	// # LOG #
	// =======
	inline void LogPos(char* name, float x, float y)
	{
		cout << name << "__x: " << x << ", y:" << y << endl;
	}

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
		RECT rc = { x - width * 0.5f, y - height * 0.5f, x + width * 0.5f, y + height * 0.5f };
		return rc;
	}

	inline Gdiplus::RectF RectFMakeCenter(float x, float y, float width, float height)
	{
		Gdiplus::RectF rc = { x - width * 0.5f, y - height * 0.5f, width, height };
		return rc;
	}

	inline Gdiplus::RectF RectToRectF(RECT rc)
	{
		return RectFMake(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
	}

	// ========================
	// # Print[ POINT, RECT ] #
	// ========================
	static Gdiplus::Graphics* _graphics;
	void PrintRectangle(HDC hdc, float x, float y, int width, int height);
	void PrintRectangle(HDC hdc, RECT rc);
	void PrintRectangleColor(HDC hdc, RECT rc, Color penColor = Color::Black, bool isFill = false, Color fillColor = Color::White);
	void PrintRectangleColor(HDC hdc, float x, float y, int width, int height, Color penColor = Color::Black, bool isFill = false, Color fillColor = Color::White);
	void PrintRectangleByPoint(HDC hdc, POINT pt, float width, float height, Color penColor = Color::Black, bool isFill = false, Color fillColor = Color::White);

	void PrintPoint(HDC hdc, float x, float y, int ptX, int ptY, char* format = "%d, %d");

	void exitGame();

	template<typename T>
	void swapValue(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}
}