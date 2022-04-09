#pragma once
#include "Object.h"
class Bullet : public Object
{
private:
	FRAME_INFO	_frameInfo;
	string		_imgName; 
	string		_destroyImgName;
	Image*		_img;
	ImageGp*	_gpImg;

	float _startX;
	float _startY;
	float _moveX;
	float _moveY;
	float _speed;
	float _damage;
	float _distance;

public:
	Bullet(string imgName, float x, float y, float moveX, float moveY, float speed, 
		float damage = 0.0f, string destroyImgName = "", float distance = 1500);
	~Bullet();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void deleteEffect() override;

	void move();
	void animation();

};

