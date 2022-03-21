#include "Stdafx.h"
#include "ProgressBar.h"

HRESULT ProgressBar::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_rc = RectMakeCenter(_x, _y, width, height);

	_progressBarUp = IMAGEMANAGER->addImage("BarUp",
		"Resources/Images/Object/HpBarUp.bmp",
		0, 0, width, height, true, RGB(255, 0, 255));

	_progressBarDown = IMAGEMANAGER->addImage("BarDown",
		"Resources/Images/Object/HpBarDown.bmp",
		0, 0, width, height, true, RGB(255, 0, 255));

	_width = _progressBarUp->getWidth();

	return S_OK;
}

void ProgressBar::release(void)
{
}

void ProgressBar::update(void)
{
	_rc = RectMakeCenter(_x, _y, _progressBarDown->getWidth(), _progressBarDown->getHeight());
}

void ProgressBar::render(void)
{
	_progressBarDown->render(getMemDC(),
		_rc.left + _progressBarDown->getWidth() / 2,
		_y + _progressBarDown->getHeight() / 2,
		0, 0,
		_progressBarDown->getWidth(),
		_progressBarDown->getHeight());

	_progressBarUp->render(getMemDC(),
		_rc.left + _progressBarDown->getWidth() / 2,
		_y + _progressBarDown->getHeight() / 2,
		0, 0,
		_width,
		_progressBarDown->getHeight());
}

void ProgressBar::setGauge(float currentScore, float maxScore)
{
	_width = (currentScore / maxScore) * _progressBarDown->getWidth();
}
