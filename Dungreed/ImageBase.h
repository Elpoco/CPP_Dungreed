#pragma once
// Interface
class ImageBase
{
public:
	virtual void render(HDC hdc, float x, float y) {}
	virtual void render(HDC hdc, float x, float y, int angle, POINT rotate) {}
	virtual void render(HDC hdc, float x, float y, int sourX, int sourY, int sourWidth, int sourHeight) {}
	virtual void alphaRender(HDC hdc, float x, float y, BYTE alpha) {}
	virtual void rotateRender(HDC hdc, float destX, float destY, int frameX, int frameY, float angle) {}

	virtual void frameRender(HDC hdc, float x, float y, int frameX, int frameY) {}
	virtual void frameRender(HDC hdc, float x, float y, int frameX, int frameY, int angle, POINT rotateCenter) {}
	virtual void frameAlphaRender(HDC hdc, float x, float y, int frameX, int frameY, BYTE alpha) {}

	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
	virtual int getFrameWidth() = 0;
	virtual int getFrameHeight() = 0;
	virtual int getMaxFrameX() = 0;
	virtual int getMaxFrameY() = 0;
};

