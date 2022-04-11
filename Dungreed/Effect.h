#pragma once
#include "Object.h"

class Effect : public Object
{
private:
	FRAME_INFO _frameInfo;

protected:
	Image* _img;
	ImageGp* _gpImg;
	string _imgName;

	BYTE _alpha;

	int _angle;
	POINT _rotateCenter;

	callback _callback;

public:
	Effect(string imgName, float x, float y, BYTE alpha = 0);
	Effect(string imgName, float x, float y, int angle, POINT rotateCenter);
	virtual ~Effect();
	
	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void animation();

	void deleteEffect();

	void setCallback(callback callback) { _callback = callback; }

};

