#include "Stdafx.h"
#include "Animation.h"

Animation::Animation(void) : _frameNum(0),
						     _frameWidth(0),
						     _frameHeight(0),
						     _frameNumWidth(0),
						     _frameNumHeight(0),
						     _frameUpdateSec(0),
						     _elapsedSec(0),
						     _nowPlayIdx(0),
						     _isPlay(false),
						     _loop(false)
{
}

HRESULT Animation::init(int totalW, int totalH, float frameW, float frameH)
{
	// 가로 프레임 수
	_frameWidth = frameW;
	_frameNumWidth = ceil(totalW / _frameWidth);

	// 세로 프레임 수
	_frameHeight = frameH;
	_frameNumHeight = ceil(totalH / _frameHeight);

	// 총 프레임 수 계산
	_frameNum = _frameNumWidth * _frameNumHeight;

	_frameList.clear();

	for (int i = 0; i < _frameNumHeight; i++) 
	{
		for (int j = 0; j < _frameNumWidth; j++)
		{
			POINT framePos;
			framePos.x = j * _frameWidth;
			framePos.y = i * _frameHeight;
			
			_frameList.push_back(framePos);
		}
	}

	// 기본 프레임으로 셋팅
	setDefPlayFrame();

	return S_OK;
}

void Animation::release(void)
{
	//! Do Nothing
}

// 기본 프레임 셋팅
void Animation::setDefPlayFrame(bool reverse, bool loop)
{
	// 루프 돌건지?
	_loop = loop;

	_playList.clear();
	if (reverse)
	{
		if (_loop)
		{
			// 갈때 프레임
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
			// 올때 프레임
			for (int i = _frameNum - 2; i > 0; i--)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			// 갈때 프레임
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
			// 올때 프레임
			for (int i = _frameNum - 2; i >= 0; i--)
			{
				_playList.push_back(i);
			}
		}
	}
	else
	{
		// 갈때 프레임
		for (int i = 0; i < _frameNum; i++)
		{
			_playList.push_back(i);
		}
	}
}

// 원하는 프레임만 재생
void Animation::setPlayFrame(int* playArr, int arrLen, bool loop)
{
	// 루프 돌건지?
	_loop = loop;
	_nowPlayIdx = 0;
	_playList.clear();
	if (_loop)
	{
		// 갈때 프레임
		for (int i = 0; i < arrLen; i++)
		{
			_playList.push_back(playArr[i]);
		}
		// 올때 프레임
		for (int i = arrLen - 2; i > 0; i--)
		{
			_playList.push_back(playArr[i]);
		}
	}
	else
	{
		// 갈때 프레임
		for (int i = 0; i < arrLen; i++)
		{
			_playList.push_back(playArr[i]);
		}
		// 올때 프레임
		for (int i = arrLen - 2; i >= 0; i--)
		{
			_playList.push_back(playArr[i]);
		}
	}
	
}

// 구간을 잘라서 재생
void Animation::setPlayFrame(int start, int end, bool reverse, bool loop)
{
	// 루프 돌건지?
	_loop = loop;
	_nowPlayIdx = 0;
	_playList.clear();
	if (reverse)
	{
		if (_loop)
		{
			// 갈때 프레임
			for (int i = start; i < end; i++)
			{
				_playList.push_back(i);
			}
			// 올때 프레임
			for (int i = end - 2; i > start; i--)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			// 갈때 프레임
			for (int i = start; i < end; i++)
			{
				_playList.push_back(i);
			}
			// 올때 프레임
			for (int i = end - 2; i >= start; i--)
			{
				_playList.push_back(i);
			}
		}
	}
	else
	{
		// 갈때 프레임
		for (int i = start; i < end; i++)
		{
			_playList.push_back(i);
		}
	}
}

// 초당 프레임 갱신 횟수
void Animation::setFPS(int framePerSec)
{
	_frameUpdateSec = 1.0f / framePerSec;
}

// 프레임 업데이트
void Animation::frameUpdate(float elpasedTime)
{
	if (_isPlay)
	{
		_elapsedSec += elpasedTime;

		// 프레임 업데이트 시간이 되었으면
		if (_elapsedSec >= _frameUpdateSec)
		{
			_elapsedSec -= _frameUpdateSec;

			_nowPlayIdx++;
			if (_nowPlayIdx == _playList.size())
			{
				if (_loop)
				{
					_nowPlayIdx = 0;
				}
				else
				{
					_nowPlayIdx--;
					_isPlay = false;
				}
			}
		}
	}
}

void Animation::AniStart(void)
{
	_isPlay = true;
	_nowPlayIdx = 0;
}

void Animation::AniStop(void)
{
	_isPlay = false;
	_nowPlayIdx = 0;
}

void Animation::AniPause(void)
{
	_isPlay = false;
}

void Animation::AniResume(void)
{
	_isPlay = true;
}
