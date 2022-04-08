#pragma once
#include "Object.h"
class Bullet : public Object
{
private:
	float _startX;
	float _startY;
	float _moveX;
	float _moveY;
	float _speed;
	float _distance;
	string _imgName; 
	FRAME_INFO _frameInfo;

	Image* _img;
	ImageGp* _gpImg;

public:
	Bullet(string imgName, float x, float y, float moveX, float moveY, float speed, float distance = 1500);
	~Bullet();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void move();
	void animation();

};

