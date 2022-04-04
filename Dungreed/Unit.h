#pragma once
#include "Object.h"

/*
애니메이션, 상태값
*/

class Unit : public Object
{
private:
	FRAME_INFO _frameInfo;

protected:
	string _name;

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

	int _reSize;	// 렉트랑 이미지 리사이즈


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

	void updateRect();
	void updateProve();

	inline void setFrameY(int frameY) { _frameInfo.y = frameY; }

	inline float getWidth() { return _imgWidth; }
	inline float getHeight() { return _imgHeight; }

	virtual void jump();

};

