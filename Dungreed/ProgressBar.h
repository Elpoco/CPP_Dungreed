#pragma once
#include "GameNode.h"

class ProgressBar : public GameNode
{
private:
	Image* _progressBarUp;
	Image* _progressBarDown;

	RectF _rc;
	int _x, _y;
	int _width;


public:
	HRESULT init(int x, int y, int width, int height);
	void release(void);
	void update(void);
	void render(void);

	void setGauge(float currentScore, float maxScore);

	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

	ProgressBar() {}
	virtual ~ProgressBar() {}
};

