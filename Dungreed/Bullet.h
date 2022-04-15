#pragma once
#include "Object.h"
class Bullet : public Object
{
private:
	FRAME_INFO	_frameInfo;
	ImageBase*	_img;
	string		_imgName; 
	string		_destroyImgName;

	float _startX;
	float _startY;
	float _angle;
	float _speed;
	float _distance;
	int   _damage;

	BOOL _isGP;

public:
	Bullet(string imgName, float x, float y, float angle, float speed, 
		int damage, string destroyImgName = "", float distance = 1500);
	virtual ~Bullet();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void deleteEffect() override;
	virtual void collisionObject() override;

	virtual int getDmg() override { return _damage; }

	void move();
	void animation();

};

