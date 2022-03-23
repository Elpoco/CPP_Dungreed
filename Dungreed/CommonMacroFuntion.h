#pragma once
// CommonMacroFuntion: 필요한 함수는 직접 만들어 추가하자

//POINT
inline POINT PointMake(int x, int y)
{
	POINT pt = { x,y };
	return pt;
}

// 선그리기
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

// RECT 만들기
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

// RECT 중심점에 만들기
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

// 사각형 그리기(렉탱글 함수 사용)
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

// 타원 그리기 (Ellipse() 함수 사용)
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

// 타원 센터점 중심으로 그리기 (Ellipse() 함수 사용)
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

inline void RectangleMakeRect(HDC hdc, RECT rc, int x, int y) {
	Rectangle(hdc, x+rc.left, y+rc.top, x+rc.right, y+rc.bottom);
}

inline void PolygonMake(HDC hdc, POINT points[], int size) {
	Polygon(hdc, points, size);
}

// 원 충돌 함수
inline bool CollisionEllipseCheck(RECT rc1, RECT rc2) {
	float rc1Radius = (rc1.right - rc1.left) / 2;
	float rc2Radius = (rc2.right - rc2.left) / 2;

	float rX = (rc1.left + rc1Radius) - (rc2.left + rc2Radius);
	float rY = (rc1.top + (rc1.bottom - rc1.top) / 2) - (rc2.top + (rc2.bottom - rc2.top) / 2);

	float length = (rc1Radius + rc2Radius)*(rc1Radius + rc2Radius);

	if (length >= (rX * rX + rY * rY)) 
	{
		return true;
	}
	return false;
}

template <typename T>
inline int GetArrLen(T arr[]) {
	return sizeof(*arr) / sizeof(*arr[0]);
}