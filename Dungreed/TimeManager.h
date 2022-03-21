#pragma once
#include "SingletonBase.h"
#include "Timer.h"

// �߻����丮�� ����°� �� ����
class TimeManager : public SingletonBase<TimeManager>
{
private:
	Timer* _timer;

public:
	HRESULT init(void);
	void release(void);
	void update(float lock = 0.0f);
	void render(HDC hdc);

	// ��ü �ð�
	inline float getWorldTime(void) const { return _timer->getWorldTime(); }
	// ������ ��� �ð�
	inline float getElapsedTime(void) const { return _timer->getElapsedTime(); }

	TimeManager() {}
	~TimeManager() {}

};

