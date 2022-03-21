#pragma once
#include "SingletonBase.h"

/*
FMOD
-Sound Engine ���̺귯��
��Unreal Engine �� Unity Engine ���� ���̼��� ������� �⺻ ����Ǿ� �ִ�.
	���̿��� ��κ��� �÷������� ����ϱ� ���� ���� �غ� ����� �Ѵ�.

FMOD�� ����� ��ǥ�� ����
-���̿���ũ, ���� ���� ��ũ����Ʈ

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
�� C++11 �߰� �Ǿ���.
�� �ش� ��ü�� �Լ��� ���ϰ��� "������" Ÿ�ӿ� �� �� �ִ�.(��)
�� C++17 ���ʹ� ���ٽĿ��� ������ �ȴ�.

�� ������ Ÿ�ӿ� ���� �����ǹǷ� �Լ� ȣ�Ⱓ ���ø� ���ڷ� �Ѱ��ٶ� �����ϴ�.

const �� constexpr�� �������� �ʱ�ȭ ���ο� ���� �߽߰ñ�
�� const ������ �ʱ�ȭ�� ��Ÿ�ӱ��� ������ų �� ������
	constexpr ������ �ݵ�� ������ Ÿ�ӿ� �ʱ�ȭ�� �Ǿ� �־�� �Ѵ�.
*/
// c++
constexpr auto soundBuffer = 10;
constexpr auto extraSoundChannel = 5;
constexpr auto totalSoundChannel = soundBuffer + extraSoundChannel;

// c
// ������ ä�� ���� (����)
//#define EXTRA_SOUND_CHANNEL 5

// �� ���� ����
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
	// ���� ���� �¾�
	void setUp(char* fileName, int soundKind, bool background, bool loop);
	// ���� �÷���
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

