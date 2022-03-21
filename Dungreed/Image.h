#pragma once
//1. #include "Animation.h"

// 잘 써야한다 -> 판단하면 된다.
class Animation;

/*
클래스 전방선언 (Class Forward Declaration)

전방 선언, 전처리문 #include

1. is a 관계		: 제네시스는 차다.					->	 #include
2. has a 관계	: 제네시느는 바퀴를 가지고 있다.		->	 전방선언

- 클래스 전방선언은 함수 전방선언과 비슷하면서도 다른 점이 있다.

- #include 전처리기를 많이 사용 할 경우에는 전처리기 단계가 길어지게 된다.
	ㄴ 컴파일 시간 또한 증가

- 이를 해결하기 위해 전방 선언을 이용할 수도 있다.
1. 클래스의 포인터 / 참조 형식으로 이름만 참조할 경우
2. 매개 변수나 리턴 타입을 위한 이름만 참조할 경우
3. 메모리 절약
*/

class Image
{
public:

	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,
		LOAD_FILE,
		LOAD_EMPTY,
		LOAD_END
	};

	// DWORD: Unsigened long
	// WORD: Unsigened short
	// BYTE: Unsigened char

	typedef struct tagImage
	{
		DWORD		resID;
		HDC			hMemDC;
		HBITMAP		hBit;
		HBITMAP		hOBit;
		float		x;
		float		y;
		int			width;
		int			height;
		int			currentFrameX;
		int			currentFrameY;
		int			maxFrameX;
		int			maxFrameY;
		int			frameWidth;
		int			frameHeight;
		BYTE		loadType;

		int count;

		tagImage()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;

			count = 0;
		}
	} IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;
	CHAR*			_fileName;
	BOOL			_isTrans;		// 배경색 유무
	COLORREF		_transColor;	// 배경색을 없앨 RGB값   RGB(각각 1바이트 0~255 농도 표현 가능)

	BLENDFUNCTION	_blendFunc;
	LPIMAGE_INFO	_blendImage;

public:
	// 빈 비트맵 초기화
	HRESULT init(int width, int height);
	// 이미지 리소스 초기화
	HRESULT init(const DWORD resID, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	// 이미지 파일로 초기화
	HRESULT init(const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	// 프레임 이미지 파일로 초기화
	HRESULT init(const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));


	// 알파 블렌드 초기화
	HRESULT initForAlphaBlend(void);

	// 투명 컬러키 셋팅 (배경색 날릴건지, 어떤색깔)
	void setTransColor(BOOL isTrans, COLORREF transColopr);

	// 해제
	void release(void);

	// 렌더
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	// 클리핑
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	// 알파 렌더
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	// 프레임 렌더
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int tick, BYTE alpha = 0, bool reverseFrameX = false);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	// 루프 렌더
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	// 애니 랜더
	void aniRender(HDC hdc, int destX, int destY, Animation* ani);

	// ==============
	// # 인라인 함수 #
	// ==============

	// DC얻기
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	// 이미지 X좌표
	inline float getX(void) { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }
	// 이미지 Y좌표
	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }

	// 이미지 센터 좌표
	inline void setCenter(float x, float y) {
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	// 이미지 가로, 세로크기
	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }

	// 바운드 박스 (충돌용 렉트)
	inline RECT boundingBox(void) {
		RECT rc = {
			(int)_imageInfo->x,
			(int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->width,
			(int)_imageInfo->y + _imageInfo->height
		};
		return rc;
	}

	// 바운드 박스 (충돌용 렉트)
	inline RECT boundingBoxWithFrame(void) {
		RECT rc = {
			(int)_imageInfo->x,
			(int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->frameWidth,
			(int)_imageInfo->y + _imageInfo->frameHeight
		};
		return rc;
	}

	// 프레임 X
	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX) {
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX) {
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	// 프레임 Y
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY) {
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY) {
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	// 이미지 1 프레임 가로, 세로 크기
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	// 최대 프레임 x, y 갯수
	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

	Image();
	~Image() {}
};

