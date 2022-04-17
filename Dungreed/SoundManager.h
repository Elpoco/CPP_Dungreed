#pragma once
#include "SingletonBase.h"

enum SOUNDKIND
{
	SOUND_BGM = 0,
	SOUND_EFFEECT_1,
	SOUND_EFFECT_2,
	SOUND_END
};

constexpr auto soundBuffer = 15;
constexpr auto extraSoundChannel = 5;
constexpr auto totalSoundChannel = soundBuffer + extraSoundChannel;

using namespace FMOD;

class SoundLoader;

class SoundManager : public SingletonBase<SoundManager>
{
private:
	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundsIter;
	typedef map<string, Channel**> arrChannels;
	typedef map<string, Channel**>::iterator arrChannelsIter;
	
	System* _system;
	Sound** _sound;
	Channel** _channel;
	
	arrSounds _mTotalSounds;

	SoundLoader* _soundLoader;

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	void setUp(char* fileName, int soundKind, bool background, bool loop);
	void play(int soundKind, float volume);

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

