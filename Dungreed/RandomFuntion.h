#pragma once
#include "SingletonBase.h"

class RandomFuntion : public SingletonBase<RandomFuntion>
{
public:
	RandomFuntion()
	{
		srand(GetTickCount());
	}
	~RandomFuntion() {}

	HRESULT init() { return S_OK; }

	inline int getInt(int num)
	{
		return rand() % num;
	}

	inline int getFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}

	int getSigned()
	{
		return rand() % 2 == 0 ? -1 : 1;
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