#pragma once
#include "Enemy.h"

namespace BelialSet
{
	constexpr float SKILL_TIME	= 2.0f;
	constexpr int	BULLET_CNT	= 20;
	constexpr int	SWORD_CNT	= 6;
	constexpr int	LASER_CNT	= 15;
}

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
		LASER,
		SKILL_CNT
	};

	enum BELIAL_HAND_STATE
	{
		HAND_IDLE,
		LASER,
		STATE_CNT
	};

	enum class BELIAL_LASER_STATE
	{
		NONE,
		START,
		FIND,
		SHOOT,
		SHOOTING,
		DONE,
		CNT
	};

	typedef struct tagBelialHand
	{
		BELIAL_HAND_STATE state;
		FRAME_INFO frameInfo;
		RECT rc;
		bool isLeft;
		float x;
		float y;

		BELIAL_LASER_STATE laserState;
		float playerY;

		tagBelialHand()
		{
			state = HAND_IDLE;
			laserState = BELIAL_LASER_STATE::NONE;
		}
	} BELIAL_HAND;

private:
	FRAME_INFO	_backFrameInfo;
	RECT		_rcBack;
	Image*		_imgBack;

	BELIAL_SKILL	_skill;
	BELIAL_SKILL	_lastSkill;
	int				_skillTick;
	int 			_skillActCnt;
	bool			_skillAuto;
	float			_skillCooldown;

	float _shootAngle;
	int	  _shootDir;

	Image*		_imgHand[STATE_CNT];
	BELIAL_HAND _hand[RL];
	int			_laserDir;

public:
	Belial(float x, float y);
	virtual ~Belial();

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
	void laser();

};

