#pragma once
// ===============================================================
// # Utils # (����ȭ ��Ű�� ���� ����, Ȥ�� ������ ��ɵ��� ��Ƶ� ��)
// ===============================================================

// ��׸� 1���� ���� ��
#define DEG_TO_RAD		0.017453f
#define PI				3.141592653f
#define PI_2			6.283185308f

// ���� + ������ ������
/*
�ε��Ҽ��� -> �Ǽ��� ��Ȯ�� ǥ���� �� ����
why? �Ǽ��� 
��ǻ�ʹ� ��¿ �� ���� �ٻ簪���� ǥ���Ѵ�.
�ٻ簪�� �� ���� ���� - Rounding Error
2D ��ǥ�迡�� ����� ũ�� �ν��� �������� 3D ��ǥ�迡�� ���� �ٸ� ����� �߻��Ѵ�.
*/
#define FLOAT_EPSILON	0.001f

// �Ǽ��� ���������� ��ȯ
#define FLOAT_TO_INT(f1)	static_cast<int>(f1+EPSILON)
// �� �Ǽ��� ������ ��
//	�� fabs�� �Ҽ��� ���� ���밪 ��ȯ (abs -> int)
#define FLOAT_EQUAL(f1, f2)	(fabs(f1-f2) <=FLOAT_EPSILON)

namespace MY_UTIL
{
	// �� �������� �Ÿ��� ���Ѵ�.
	float getDistance(float startX, float startY, float endX, float endY);
	// start���� end������ ���� �������� ���Ѵ�.
	float getAngle(float startX, float startY, float endX, float endY);
}