#pragma once
#include "Object.h"
class Bullet : public Object
{
private:
	FRAME_INFO	_frameInfo;
	ImageBase*	_img;
	string		_imgName; 
	string		_destroyImgName;

	int _width;
	int _height;

	float _startX;
	float _startY;
	float _angle;
	float _speed;
	float _distance;
	float _scale;
	int   _damage;

	BOOL _isSuper;
	BOOL _isImgRotate;

	BOOL _isAuto;
	int _dir;

public:
	Bullet(string imgName, float x, float y, float angle, float speed, 
		int damage, string destroyImgName = "", float distance = 1500, BOOL super = FALSE, BOOL imgRotate = FALSE);
	virtual ~Bullet();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void deleteEffect() override;
	virtual void stopObject() override;
	virtual void collisionObject() override;

	virtual int getDmg() override { return _damage; }

	void move();
	void animation();

	void findEnemy();

	void setSuper() { _isSuper = TRUE; }
	void setRotate() { _isImgRotate = TRUE; }
	void setScale(float scale) { _scale = scale; }

};

