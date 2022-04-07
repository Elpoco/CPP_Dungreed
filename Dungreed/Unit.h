#pragma once
#include "Object.h"

/*
�ִϸ��̼�, ���°�
*/

class Unit : public Object
{
private:
	FRAME_INFO _frameInfo;

protected:
	string	_name;
	RECT	_rcAttack;
	BYTE	_state;

	// Image
	vector<Image*> _vImages;
	int _imgCurrent;
	float _imgWidth;
	float _imgHeight;

	bool _isLeft;
	bool _isJump;
	bool _isFall;
	bool _isFlying;

	float _moveSpeed;
	float _jumpSpeed;
	float _gravity;

	int _reSize;	// ��Ʈ�� �̹��� ��������


public:
	Unit();
	virtual ~Unit();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void move();
	void animation();

	void checkCollision();
	virtual void pushObject(ColliderEnum::DIRECTION dir, float x, float y) override;

	void updateRect();
	void updateProve();

	void jump();
	bool isJump() { return _isJump; }

	virtual void hitAttack(int dmg) {}

	inline void setFrameY(int frameY) { _frameInfo.y = frameY; }

	inline float getWidth() { return _imgWidth; }
	inline float getHeight() { return _imgHeight; }
	inline RECT getAtkRect() { return _rcAttack; }

};

