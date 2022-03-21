#pragma once
#include "SingletonBase.h"

class RandomFuntion : public SingletonBase<RandomFuntion>
{
public:
	RandomFuntion()
	{
		// API 공용 함수: GetTickCount (따로 타이머가 구축이 안되어 있는 환경이면 무조건 써야 하는 놈)
		// GetTickCount: OS가 부팅된 후의 경과 시간을 체크
		// - 기본적으로 ms 단위로 체크가 가능하며, 
		// ms 단위로 시간값을 반환 하기에 난수에 적절하다.
		srand(GetTickCount());
	}
	~RandomFuntion() {}

	HRESULT init() { return S_OK; }

	inline int getInt(int num)
	{
		return rand() % num;
	}

	// 주의사항 0이 나오면 터진다
	inline int getFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}

	float getFloat(void)
	{
		return (float)rand() / (float)RAND_MAX;
	}

	float getFloat(float num)
	{
		return (float)rand() / (float)RAND_MAX * num;
	}

	float getFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;
		return (rnd * (toNum - fromNum) + fromNum);
	}

};