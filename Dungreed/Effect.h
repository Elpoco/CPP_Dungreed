#pragma once
#include "Object.h"

class Effect : public Object
{
private:
	FRAME_INFO _frameInfo;

protected:
	ImageBase* _img;
	string _imgName;

	BYTE _alpha;

	POINT _rotateCenter;
	float _angle;
	int _degree;

	BOOL	_isFollow;
	float*	_followX;
	float*	_followY;
	int*	_followDegree;

	BOOL _isFixed;

public:
	Effect(string imgName, float x, float y, float angle);
	Effect(string imgName, float x, float y, BYTE alpha = 255);
	Effect(string imgName, float x, float y, int angle, POINT rotateCenter);
	virtual ~Effect();
	
	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void animation();

	virtual void deleteEffect() override;
	
	void setFollowing(float* x, float* y, int* degree)
	{
		_isFollow = TRUE;
		_followX = x;
		_followY = y;
		_followDegree = degree;
	}

	void setFixed() { _isFixed = TRUE; }
	
};

