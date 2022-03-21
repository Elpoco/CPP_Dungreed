#pragma once
/*
- 기존에 사용한 API 공용함수
GetTickCount()   ->
GetTickCount64() -> ?
*/
/*
Timer
- 시간을 측정하는 함수들은 굉장히 많고 기본적으로 윈도우가 시작된 이후 지난 시간을
  Milli Second 단위로 반환

- 보통 타이머를 구현할때 알아둬야 할 개념은 해상도와 클럭

해상도?
- 다양한 시간 함수들은 시간을 측정하기 위한 저마다의 Tick 계산 로직이 있다.
	ㄴ 1분을 기준으로 올마나 많은 프레임으로 나눌 수 있는지를 뜻한다.
- 1분동안 얼마나 많은 Tick으로 나눠서 시간의 정확도를 높이느냐에 따라서
	고해상도와 저해상도로 나뉜다.

Clock (진동수)
- 타이머에서 얘기하는 클럭은 CPU 클럭(Clock)을 의미한다.
- 클럭 자체는 디지털 회로의 전기적 진동 수이며 Hz로 표기
	ㄴ 1Hz: 1초라는 가정하에 신호(0 or 1)를 한번 준다.
		ㄴ 1비트를 한번 옮긴다는 의미
- 1GHz 10의 9제곱 -> 10억번
- 3.00 GHz -> 30억번
	ㄴ 1초에 30억개의 비트를 옮길 수 있다.

※ 고성능 타이머의 경우 성능 향상 시키기 위해서는 중첩이 필요하다
	ㄴ 대략 9백만분의 1초까지 측정

- 기본값으로 셋팅하고 사용할시 백만분의 1초까지 측정 가능
*/

class Timer
{
private:
	float _timeScale;			// 경과시간 조절
	float _timeElapsed;			// 마지막 시간과 현재시간의 경과값
	bool _isHardware;			// 고성능 타이머 지원 여부

	// __int64 == INT64_MAX;
	__int64 _curTime;			// 현재 시간
	__int64 _lastTime;			// 이전 시간
	__int64 _periodFrequency;	// 시간 주기

	unsigned long _frameRate;
	unsigned long _FPSFrameCount;
	float _FPSTimeElapsed;
	float _worldTime;

public:
	HRESULT init(void);
	// 현재 시간을 계산
	void tick(float lockFPS = 0.0f);

	// 현재 FPS
	unsigned long getFrameRate(char* str = nullptr) const;
	// 마지막 시간과 현재 시간의 경과량
	inline float getElapsedTime(void) const { return _timeElapsed; }
	// 전체 경과 시간
	inline float getWorldTime(void) const { return _worldTime; }

	Timer() {}
	~Timer() {}

};
