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
	bool _isCollision[Direction::DIR::DIR_CNT];

	// Image
	vector<ImageBase*> _vImages;
	int _imgCurrent;
	float _imgWidth;
	float _imgHeight;
	bool _isStopAnimation;

	BOOL _isLeft;
	BOOL _isJump;
	BOOL _isJumpFlag;
	BOOL _isDownJump;
	BOOL _isDownFlag;
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

	virtual void setX(float x) override;
	virtual void setY(float y) override;

	void move();
	void updateAnimation();
	virtual void frameUpdateEvent() {}

	void checkCollision();
	virtual void pushObject(float x, float y) override {}
	virtual void pushObject(DIR dir, float distance) override;
	void pushObject(Direction::DIR dir, float x, float y);
	bool getCollision(Direction::DIR dir) { return _isCollision[dir]; }
	void setCollision(Direction::DIR dir, bool collision) { _isCollision[dir] = collision; }

	void updateRect();

	void jump();
	void downJump();

	virtual void hitAttack(int dmg, int dir) {}
	virtual int getDmg() override { return 1; }

	inline void setFrameX(int frameX) { _frameInfo.x = frameX; }
	inline void setFrameY(int frameY) { _frameInfo.y = frameY; }

	inline float getWidth() { return _imgWidth; }
	inline float getHeight() { return _imgHeight; }
	inline RECT getAtkRect() { return _rcAttack; }
	inline BOOL isJump() { return _isJump; }
	inline BOOL isJumping() { return _isJump && _gravity < _jumpSpeed; }
	inline BOOL isDownJumping() { return _isDownJump; }
	inline BOOL isDash() { return _isDash; }
	inline BOOL isFlying() { return _isFlying; }

};

