#pragma once
#include "Object.h"

/*
애니메이션, 상태값
*/

class Unit : public Object
{
protected:
	FRAME_INFO  _frameInfo;
	int			_state;

	RECT		_rcAttack;

	// collision
	bool _isCollision[ColliderEnum::DIRECTION::DIR_CNT];

	// Image
	vector<ImageBase*> _vImages;
	int _imgCurrent;
	float _imgWidth;
	float _imgHeight;
	bool _isStopAnimation;

	BOOL _isLeft;
	BOOL _isJump;
	BOOL _isFall;
	BOOL _isFlying;
	BOOL _isDash;
	BOOL _isHit;
	float _hitTime;

	float _moveSpeed;
	float _jumpSpeed;
	float _gravity;

	float _imgAngle;
	BYTE _imgAlpha;
	POINT _rotateCenter;


public:
	Unit();
	virtual ~Unit();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void deleteEffect() override {}

	void move();
	void animation();

	void checkCollision();
	virtual void pushObject(float x, float y) override {}
	void pushObject(ColliderEnum::DIRECTION dir, float x, float y);
	bool getCollision(ColliderEnum::DIRECTION dir) { return _isCollision[dir]; }
	void setCollision(ColliderEnum::DIRECTION dir, bool collision) { _isCollision[dir] = collision; }

	void updateRect();

	void jump();

	virtual void hitAttack(int dmg, int dir) {}
	virtual int getDmg() override { return 1; }

	inline void setFrameX(int frameX) { _frameInfo.x = frameX; }
	inline void setFrameY(int frameY) { _frameInfo.y = frameY; }

	inline float getWidth() { return _imgWidth; }
	inline float getHeight() { return _imgHeight; }
	inline RECT getAtkRect() { return _rcAttack; }
	inline BOOL isJump() { return _isJump; }
	inline BOOL isJumping() { return _isJump && _gravity < _jumpSpeed; }
	inline BOOL isDash() { return _isDash; }

};

