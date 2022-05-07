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
	BOOL _isPenetrate;
	BOOL _isAuto;
	BOOL _isFind;
	POINT _ptEnemy;
	float _initTime;

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

	BOOL isAuto() { return _isAuto; }
	void setAuto() { _isAuto = TRUE; }
	void findEnemy(POINT pt);
	void eraseEnemy() { _isFind = FALSE; }

	void setSuper() { _isSuper = TRUE; }
	void setRotate() { _isImgRotate = TRUE; }
	void setScale(float scale) { _scale = scale; }
	void setPenetrate() { _isPenetrate = TRUE; }
	BOOL getPenetrate() { return _isPenetrate; }
	float getInitTime() { return _initTime; }

};

