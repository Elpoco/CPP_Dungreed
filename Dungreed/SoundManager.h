#pragma once
#include "SingletonBase.h"

/*
FMOD
-Sound Engine 라이브러리
ㄴUnreal Engine 과 Unity Engine 에는 라이센스 계약으로 기본 내장되어 있다.
	ㄴ이외의 대부분의 플랫폼에선 사용하기 위해 선행 준비를 해줘야 한다.

FMOD를 사용한 대표적 게임
-바이오쇼크, 월드 오브 워크레프트

*/

enum SOUNDKIND
{
	SOUND_BGM = 0,
	SOUND_EFFEECT_1,
	SOUND_EFFECT_2,
	SOUND_END
};

/*
const, constexpr
ㄴ C++11 추가 되었다.
ㄴ 해당 객체나 함수의 리턴값을 "컴파일" 타임에 알 수 있다.(값)
ㄴ C++17 부터는 람다식에도 적용이 된다.

※ 컴파일 타임에 값이 결정되므로 함수 호출간 템플릿 인자로 넘겨줄때 유용하다.

const 와 constexpr의 차이점은 초기화 여부와 오류 발견시기
ㄴ const 변수는 초기화를 런타임까지 지연시킬 수 있지만
	constexpr 변수는 반드시 컴파일 타임에 초기화가 되어 있어야 한다.
*/
// c++
constexpr auto soundBuffer = 10;
constexpr auto extraSoundChannel = 5;
constexpr auto totalSoundChannel = soundBuffer + extraSoundChannel;

// c
// 여분의 채널 갯수 (버퍼)
//#define EXTRA_SOUND_CHANNEL 5

// 총 사운드 갯수
//#define TOTAL_SOUND_CHANNEL SOUND_END + EXTRA_SOUND_CHANNEL

using namespace FMOD;

class SoundManager : public SingletonBase<SoundManager>
{
private:
	// c++
	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundsIter;
	typedef map<string, Channel**> arrChannels;
	typedef map<string, Channel**>::iterator arrChannelsIter;
	//

	// c
	System* _system;
	Sound** _sound;
	Channel** _channel;
	//

	// c++
	arrSounds _mTotalSounds;
	//

public:
	HRESULT init(void);
	void release(void);
	void update(void);


	// c
	// 사운드 파일 셋업
	void setUp(char* fileName, int soundKind, bool background, bool loop);
	// 사운드 플레이
	void play(int soundKind, float volume);
	//

	// c++
	void addSound(string keyName, string soundName, bool background, bool loop);

	void play(string keyName, float volume);
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);

	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);

	SoundManager();
	~SoundManager() {};
};

