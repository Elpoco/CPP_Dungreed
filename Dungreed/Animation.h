#pragma once
class Animation
{
private:
	// ������ ����Ʈ
	typedef vector<POINT> vFrameList;
	// ������ �÷��� ����Ʈ
	typedef vector<int>	vPlayList;

private:
	vFrameList _frameList;
	vPlayList _playList;

	int _frameNum;			// ������ ��
	int _frameWidth;		// ������ ���� ũ��
	int _frameHeight;		// ������ ���� ũ��
	int _frameNumWidth;		// ���� ������ �� ����
	int _frameNumHeight;	// ���� ������ �� ����

	float _frameUpdateSec;	// �ʴ� ������ ������Ʈ ��
	float _elapsedSec;		// �����Ӱ� ������ ������ �ð�

	bool _isPlay;
	bool _loop;
	DWORD _nowPlayIdx;

public:
	HRESULT init(int totalW, int totalH, float frameW, float frameH);
	void release(void);

	void setDefPlayFrame(bool reverse = false, bool loop = false);
	void setPlayFrame(int* playArr = nullptr, int arrLen = 0, bool loop = false);
	void setPlayFrame(int start, int end, bool reverse = false, bool loop = false);

	// �ʴ� ������ ���� Ƚ��
	void setFPS(int framePerSec);
	// ������ ������Ʈ
	void frameUpdate(float elpasedTime);

	void AniStart(void);
	void AniStop(void);
	void AniPause(void);
	void AniResume(void);

	// �÷��� ������?
	inline bool isPlay(void) { return _isPlay; }
	// ������ ��ġ �����ڴ�.
	inline POINT getFramePos(void) { return _frameList[_playList[_nowPlayIdx]]; }

	// ���� �ִϸ��̼��� ������ ��ġ ������ ���´�.
	inline int getFrameIdx(void)
	{
		POINT ptPos = getFramePos();
		int frameX = ptPos.x / _frameWidth;
		int frameY = ptPos.y / _frameHeight;

		return frameX + frameY * _frameNumWidth;
	}

	// ������ ����, ���� ũ�⸦ ���´�.
	inline int getFrameWidth(void) { return _frameWidth; }
	inline int getFrameHeight(void) { return _frameHeight; }
	inline DWORD getNowPlayIdx(void) { return _nowPlayIdx; }

	Animation(void);
	~Animation() {}

};

