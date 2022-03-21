#pragma once
#include "SingletonBase.h"

class EffectManager : public SingletonBase<EffectManager>
{
private:
	struct tagEffect
	{
		int x;
		int y;
		Image* image;
		float timeCount;
		float worldTimeCount;
		int currentX;
		int currentY;
	};

	vector<tagEffect> _vEffect;
	vector<tagEffect>::iterator _viEffect;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void addEffect(char* name, int x, int y);

	EffectManager() {}
	~EffectManager() {}
};

