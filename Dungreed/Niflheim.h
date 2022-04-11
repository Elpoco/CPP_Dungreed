#pragma once
#include "Enemy.h"

class NiflheimPillar;

constexpr int PILLAR_CNT = 4;

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
		MUSTER,		   // �ֺ��� �𿩼� ��������
		DISSOLUTION,   // �׹������� ���� ��������
		DISSOLUTION_L, // �׹������� ���� �÷��̾����� ��������
		LINE_UP,	   // �߾ӿ� �������� �𿩼� ��������
		FULL_ATTACK,   // ������� �÷��̾����� ����
		SKILL_CNT
	};

private:
	NiflheimPillar* _pillar[PILLAR_CNT];
	NIFLHEIM_SKILL _skill;

public:
	Niflheim(float x, float y);
	~Niflheim();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void deleteEffect() override;

	void move();
	void animation();
	void initAnimation();
};

