#pragma once
#include "SingletonBase.h"
#include "Image.h"

/*
STL 맵의 핵심
- 키, 값을 잊지 말자
- 첫번째 first -> 키
- 두번째 second -> 값
- 추가하는 방법은 insert를 사용하고 키와 밸류 두개를 동시에 추가해야 하니
	pair or make_pair를 사용하여 추가한다.

- pair(): 두가지 자료형을 하나로 묶는 구조체 (템플릿 구조체이기에 어떤 자료형이 와도 OK)
- make_pair(): 말 그대로 pair를 만들어 주는 함수
	ㄴ p.first = x, p.second = y;
	ㄴ p = make_pair(x,y); 형태로

- 하나의 키에 여러개의 값을 저장하고 싶으면 <multimap> 사용
- pair 자체를  확장시켜 사용하고 싶으면 <tuple>을 사용하자
*/

class ImageManager : public SingletonBase<ImageManager>
{
private:
	// 맵으로 만든 이미지 목록
	typedef map<string, Image*> mapImageList;
	// 맵으로 만든 이미지 목록의 반복자
	typedef map<string, Image*>::iterator mapImageIter;

private:
	mapImageList _mImageList;

public:
	HRESULT init(void);
	void release(void);

	// 빈 비트맵 초기화
	Image* addImage(string strKey, int width, int height);
	// 이미지 파일로 초기화
	Image* addImage(string strKey, const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	// 프레임 이미지 파일로 초기화
	Image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	Image* addFrameImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	Image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	// 이미지 키값으로 찾기
	Image* findImage(string strKey);
	// 이미지 키값으로 삭제
	bool deleteImage(string strKey);
	// 이미지 전체 삭제
	bool deleteAll();

	// 렌더
	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	// 클리핑
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	// 알파 렌더
	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	// 프레임 렌더
	void frameRender(string strKey, HDC hdc, int destX, int destY, int tick);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	// 루프 렌더
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	ImageManager() {}
	~ImageManager() {}
};

