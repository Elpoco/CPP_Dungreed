#include "Stdafx.h"
#include "Utils.h"

namespace MY_UTIL
{
	float getDistance(float startX, float startY, float endX, float endY) {
		float x = endX - startX;
		float y = endY - startY;

		return sqrt(x * x + y * y);
	}

	float getAngle(float startX, float startY, float endX, float endY) {
		float x = endX - startX;
		float y = endY - startY;
		float d = sqrt(x * x + y * y);
		float angle = acos(x / d);

		if (y > 0)angle = PI_2 - angle;

		return angle;
	}

	void printPoint(HDC hdc, float x, float y, int ptX, int ptY, char* format)
	{
		char str[128];
		wsprintf(str, format, ptX, ptY);
		TextOut(hdc, x, y, str, strlen(str));
	}
}