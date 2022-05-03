#pragma once
#include "Enemy.h"

class Skel : public Enemy
{
private:
	enum SKEL_MOTION
	{
		IDLE,
		MOVE,
	};

	enum class SKEL_TYPE
	{
		SWORD,
		BOW,
		NONE,

		TYPE_CNT
	};

private:
	ImageBase* _imgWeapon;
	FRAME_INFO _weaponFrame;
	SKEL_TYPE  _skelType;

	float _attackTime;
	float _angleWeapon;
	float _anglePlayer;

	int _atkCnt;

	int _handX;

public:
	Skel(float x, float y, Code::UNIT code);
	virtual ~Skel();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void move();
	void initAnimation();

	void attack();
	virtual void frameUpdateEvent() override;

};

