#pragma once
#include "Enemy.h"

constexpr BYTE SWORD_CNT = 6;

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
		SHOOTING_BULLET,
		THROW_SWORD,
		LAZER,
		SKILL_CNT
	};

	enum BELIAL_HAND_STATE
	{
		IDLE,
		LAZER,
		STATE_CNT
	};

	typedef struct tagBelialHand
	{
		FRAME_INFO frameInfo;
		RECT rc;
		bool isLeft;
		float x;
		float y;
	} BELIAL_HAND;

private:
	FRAME_INFO _backFrameInfo;
	int _backFrameX;
	RECT _rcBack;
	Image* _imgBack;

	BELIAL_SKILL _skill;
	BYTE _skillTick;
	BYTE _skillActCnt;

	float _shootAngle;
	int	  _shootDir;

	BELIAL_HAND _hand[2];
	Image* _imgHand[STATE_CNT];
	BELIAL_HAND _handL;
	BELIAL_HAND _handR;
	FRAME_INFO _handLFrameInfo;
	FRAME_INFO _handRFrameInfo;

public:
	Belial(float x, float y);
	~Belial();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void deleteEffect() override;

	void move();
	void animation();

	void initAnimation();

	void shootingBullet();
	void throwSword();
	void lazer();

};

