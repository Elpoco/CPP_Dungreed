#pragma once
#include "Enemy.h"
class NiflheimPillar : public Enemy
{
private:
	enum class PILLAR_STATE
	{
		IDLE,
		MUSTER,		   // �ֺ��� �𿩼� ��������
		DISSOLUTION,   // �׹������� ���� ��������
		DISSOLUTION_L, // �׹������� ���� �÷��̾����� ��������
		LINE_UP,	   // �߾ӿ� �������� �𿩼� ��������
		FULL_ATTACK	   // ������� �÷��̾����� ����
	};

private:
	float* _niflheimX;
	float* _niflheimY;
	float _bossAngle;
	float _bossDistance;
	float _shootAngle;

public:
	NiflheimPillar(float x, float y);
	~NiflheimPillar();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void move();
	void animation();
	void initAnimation();

	void setPosAddress(float* x, float* y) { _niflheimX = x; _niflheimY = y; }

};

