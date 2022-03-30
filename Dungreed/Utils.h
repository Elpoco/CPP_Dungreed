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
	float getDistance(float startX, float startY, float endX, float endY);
	float getAngle(float startX, float startY, float endX, float endY);

	void printPoint(HDC hdc, float x, float y, int ptX, int ptY, char* format = "%d, %d");
	bool ptInRectF(RectF rect);

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