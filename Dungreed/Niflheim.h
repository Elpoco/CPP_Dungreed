#pragma once
#include "Enemy.h"

class NiflheimPillar;

namespace NiflheimSet
{
	constexpr float SKILL_TIME   = 2.0f;
	constexpr float BULLET_SPEED = 3.5f;
	constexpr int PILLAR_CNT	 = 4;
	constexpr int BULLET_CNT	 = 30;
	constexpr int BULLET_CNT_L	 = 19;
	constexpr int BULLET_DMG	 = 6;
}

class Niflheim : public Enemy
{
private:
	enum NIFLHEIM_MOTION
	{
		IDLE,
		ATTACK,
		DIE
	};

	enum class NIFLHEIM_SKILL
	{
		NONE,
		AROUND,		   // �ֺ��� �𿩼� ��������
		WIDE,   // �׹������� ���� ��������
		WIDE_LINE, // �׹������� ���� �÷��̾����� ��������
		LINE_UP,	   // �߾ӿ� �������� �𿩼� ��������
		FULL_ATTACK,   // ������� �÷��̾����� ����
		SKILL_CNT
	};

	friend class NiflheimPillar;

private:
	NiflheimPillar* _pillar[NiflheimSet::PILLAR_CNT];
	bool _onInitPillar;

	NIFLHEIM_SKILL  _skill;
	NIFLHEIM_SKILL	_lastSkill;
	int				_skillTick;
	int 			_skillActCnt;
	bool			_skillAuto;
	float			_skillCooldown;

	int _skillFirstTick;
	POINT _ptLastPlayer;

public:
	Niflheim(float x, float y);
	virtual ~Niflheim();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void deleteEffect() override;
	virtual void hitAttack(int dmg, int dir) override;

	void move();
	void animation();
	void initAnimation();

	void initPillar();
	void attackAnimation();
	void shootBullet(float x, float y, float angle);
	void turnAround();
	void moveAndFire();
};

