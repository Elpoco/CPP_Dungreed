#pragma once
class Animation
{
private:
	// 프레임 리스트
	typedef vector<POINT> vFrameList;
	// 프레임 플레이 리스트
	typedef vector<int>	vPlayList;

private:
	vFrameList _frameList;
	vPlayList _playList;

	int _frameNum;			// 프레임 수
	int _frameWidth;		// 프레임 가로 크기
	int _frameHeight;		// 프레임 세로 크기
	int _frameNumWidth;		// 가로 프레임 총 갯수
	int _frameNumHeight;	// 세로 프레임 총 갯수

	float _frameUpdateSec;	// 초당 프레임 업데이트 수
	float _elapsedSec;		// 프레임과 프레임 사이의 시간

	bool _isPlay;
	bool _loop;
	DWORD _nowPlayIdx;

public:
	HRESULT init(int totalW, int totalH, float frameW, float frameH);
	void release(void);

	void setDefPlayFrame(bool reverse = false, bool loop = false);
	void setPlayFrame(int* playArr = nullptr, int arrLen = 0, bool loop = false);
	void setPlayFrame(int start, int end, bool reverse = false, bool loop = false);

	// 초당 프레임 갱신 횟수
	void setFPS(int framePerSec);
	// 프레임 업데이트
	void frameUpdate(float elpasedTime);

	void AniStart(void);
	void AniStop(void);
	void AniPause(void);
	void AniResume(void);

	// 플레이 중인지?
	inline bool isPlay(void) { return _isPlay; }
	// 프레임 위치 얻어오겠다.
	inline POINT getFramePos(void) { return _frameList[_playList[_nowPlayIdx]]; }

	// 현재 애니메이션의 프레임 위치 순서를 얻어온다.
	inline int getFrameIdx(void)
	{
		POINT ptPos = getFramePos();
		int frameX = ptPos.x / _frameWidth;
		int frameY = ptPos.y / _frameHeight;

		return frameX + frameY * _frameNumWidth;
	}

	// 프레임 가로, 세로 크기를 얻어온다.
	inline int getFrameWidth(void) { return _frameWidth; }
	inline int getFrameHeight(void) { return _frameHeight; }
	inline DWORD getNowPlayIdx(void) { return _nowPlayIdx; }

	Animation(void);
	~Animation() {}

};

