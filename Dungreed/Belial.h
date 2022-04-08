#pragma once
#include "Enemy.h"
class Belial : public Enemy
{
private:
	enum BELIAL_MOTION
	{
		IDLE,
		ATTACK,
		DIE
	};

	enum class BELIAL_SKILL
	{
		NONE,
		SHOOTING_BULLET
	};

	typedef struct tagBelialBullet
	{
		bool fire;
		RECT rc;
		float x;
		float y;
		float moveX;
		float moveY;
		float speed;
		int frameX;
	} BELIAL_BULLET;

private:
	FRAME_INFO _backFrameInfo;
	int _backFrameX;
	Image* _imgBack;
	RECT _rcBack;

	BYTE _skillTick;
	BYTE _skillActCnt;
	BELIAL_SKILL _skill;
	float _shootAngle;

public:
	Belial(float x, float y);
	~Belial();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void move();
	void animation();

	void initAnimation();

	void shootingBullet();

};

