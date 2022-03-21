#include "stdafx.h"
#include "SoundManager.h"

SoundManager::SoundManager() : _system(nullptr),
								_channel(nullptr),
								_sound(nullptr)
{
}

HRESULT SoundManager::init(void)
{
	// ���� �ý��� ����
	System_Create(&_system);

	// �ý��� �ʱ�ȭ
	_system->init(totalSoundChannel, FMOD_INIT_NORMAL, 0);

	// ä�� �� ��ŭ �޸� ���� �� ���带 ����
	_sound = new Sound*[totalSoundChannel];
	_channel = new Channel*[totalSoundChannel];

	// �޸� �ѹ� ����
	memset(_sound, 0, sizeof(Sound*) * (totalSoundChannel));
	memset(_channel, 0, sizeof(Channel*) * (totalSoundChannel));

	return S_OK;
}

void SoundManager::release(void)
{
	// destroy
	if (_channel != nullptr || _sound != nullptr)
	{
		for (int i = 0; i < totalSoundChannel; i++)
		{
			if (_channel != nullptr)
			{
				if (_channel[i]) _channel[i]->stop();
			}

			if (_sound != nullptr)
			{
				if (_sound != nullptr) _sound[i]->release();
			}
		}
	}

	SAFE_DELETE_ARRAY(_channel);
	SAFE_DELETE_ARRAY(_sound);

	if (_system != nullptr)
	{
		_system->release();
		_system->close();
	}
}

void SoundManager::update(void)
{
	// ���� �ý��� ������Ʈ
	// �� ������ �ٲ�ų� ����� ���� ���带 ä�ο��� ���µ� �پ��� �۾��� �ڵ����� �Ѵ�.
	_system->update();
}

void SoundManager::setUp(char* fileName, int soundKind, bool background, bool loop)
{
	if (loop)
	{
		if (background)
		{
			// ���� �̸�, ���带 ���� ���� �ɼ�, �ǵ��(�����ڿ��� ���尡 ����Ǵ� ���� ������ ���� �Ҳ���?)
			_system->createStream(fileName, FMOD_LOOP_NORMAL, 0, &_sound[soundKind]);
		}
		else
		{
			_system->createSound(fileName, FMOD_LOOP_NORMAL, 0, &_sound[soundKind]);
		}
	}
	else
	{
		// FMOD_DEFAULT: �ѹ� �÷���
		_system->createSound(fileName, FMOD_DEFAULT, 0, &_sound[soundKind]);
	}
}

// ���� �÷��� (volume ������ Max -> 1.0)
void SoundManager::play(int soundKind, float volume)
{
	// ���� �÷���
	_system->playSound(FMOD_CHANNEL_FREE, _sound[soundKind], false, &_channel[soundKind]);

	// ���� ����
	_channel[soundKind]->setVolume(volume);
}

void SoundManager::addSound(string keyName, string soundName, bool background, bool loop)
{
	if (loop)
	{
		if (background)
		{
			// ���� �̸�, ���带 ���� ���� �ɼ�, �ǵ��(�����ڿ��� ���尡 ����Ǵ� ���� ������ ���� �Ҳ���?)
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
	}
	else
	{
		// FMOD_DEFAULT: �ѹ� �÷���
		_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
	}

	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}

void SoundManager::play(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			// ���� �÷���
			_system->playSound(FMOD_CHANNEL_FREE, _sound[count], false, &_channel[count]);

			// ���� ����
			_channel[count]->setVolume(volume);
			break;
		}
	}
}

void SoundManager::stop(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->stop();
			break;
		}
	}
}

void SoundManager::pause(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(true);
			break;
		}
	}
}

void SoundManager::resume(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(false);
			break;
		}
	}
}

bool SoundManager::isPlaySound(string keyName)
{
	bool isPlay;
	int count = 0;

	arrSoundsIter iter = _mTotalSounds.begin();

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}
	return isPlay;
}

bool SoundManager::isPauseSound(string keyName)
{
	bool isPause;
	int count = 0;

	arrSoundsIter iter = _mTotalSounds.begin();

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPause);
			break;
		}
	}
	return isPause;
}
