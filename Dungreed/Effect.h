#pragma once
#include "Object.h"
class Effect : public Object
{
private:
	FRAME_INFO _frameInfo;

protected:
	Image* _img;
	ImageGp* _gpImg;

	int _angle;
	POINT _rotateCenter;

public:
	Effect();
	Effect(string imgName, float x, float y, int angle = 0, POINT rotateCenter = { 0,0 });
	virtual ~Effect();
	
	virtual HRESULT init() override;
	HRESULT init(string imgName, float x, float y, int angle = 0, POINT rotateCenter = { 0,0 });
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void animation();

};

