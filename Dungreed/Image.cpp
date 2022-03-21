#include "Stdafx.h"
#include "Image.h"
#include "Animation.h"

Image::Image() : _imageInfo(NULL)
			   , _fileName(NULL)
		  	   , _isTrans(FALSE)
			   , _transColor(RGB(0,0,0)) 
			   , _blendImage(NULL)
{
}

HRESULT Image::init(int width, int height)
{
	// 재 초기화 방지 -> 이미지 정보에 값이 들어있다면 릴리즈 부터 하겠다.
	if (_imageInfo != NULL) this->release();

	// 릴리즈에서는 무시함
	// 런타임    false일때 동작함
	//assert(_imageInfo != NULL);
	// 컴파일		상수타입을 잡을때 사용
	//static_assert

	// DC 가져오기
	HDC hdc = GetDC(_hWnd);
	
	// 이미지 정보 새로 생성 후 초기화
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	// 1. hdc와 호환되는 DC를 생성한다.
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	// 2. hdc와 호환되는 포맷의 비트맵을 width, height 크기로 만든다
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	// 파일 이름
	_fileName = NULL;
	_isTrans = FALSE;
	_transColor = RGB(0, 0, 0);

	// 리소스를 얻어오는데 실패했다
	if (_imageInfo->hBit == 0) {
		release();
		return E_FAIL;
	}

	// DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const DWORD resID, int width, int height, BOOL isTrans, COLORREF transColor)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);

	// 이미지 정보 새로 생성 후 초기화
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE;

	_imageInfo->resID = resID;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	// 3. LoadBitmap 비트맵을 불러오는 함수입니다.
	// 4. MAKEINTRESOURCE (리소스를 가져오는데 핵심적인 함수) 메크로는 정수로 지정한 리소스 아이디를 문자열로 바꿔준다.
	_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->resID));
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	// 파일 이름
	_fileName = NULL;
	_isTrans = isTrans;
	_transColor = transColor;

	// 리소스를 얻어오는데 실패했다
	if (_imageInfo->hBit == 0) {
		release();
		return E_FAIL;
	}

	// DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const char* fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);

	// 이미지 정보 새로 생성 후 초기화
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	// 5. LoadImage  비슷한 함수로는 LoadBitmap 함수가 있지만 LoadImage 함수가 더 많은 기능을 지원합니다.
	// 6. LR_LOADFROMFILE   lpszName 인수를 리소스 대신 파일 경로를 사용해 불러옵니다.
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	
	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	// 리소스를 얻어오는데 실패했다
	if (_imageInfo->hBit == 0) {
		release();
		return E_FAIL;
	}

	// DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

// 함수 정의할때 cahr * fileName 이런식이면 안됨 cpp boost에서 곱하기 연산으로 인식함
HRESULT Image::init(const char* fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);

	// 이미지 정보 새로 생성 후 초기화
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	// 5. LoadImage  비슷한 함수로는 LoadBitmap 함수가 있지만 LoadImage 함수가 더 많은 기능을 지원합니다.
	// 6. LR_LOADFROMFILE   lpszName 인수를 리소스 대신 파일 경로를 사용해 불러옵니다.
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	// 리소스를 얻어오는데 실패했다
	if (_imageInfo->hBit == 0) {
		release();
		return E_FAIL;
	}

	// DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);

	// 이미지 정보 새로 생성 후 초기화
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	// 5. LoadImage  비슷한 함수로는 LoadBitmap 함수가 있지만 LoadImage 함수가 더 많은 기능을 지원합니다.
	// 6. LR_LOADFROMFILE   lpszName 인수를 리소스 대신 파일 경로를 사용해 불러옵니다.
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX - 1;
	_imageInfo->maxFrameY = maxFrameY - 1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	// 리소스를 얻어오는데 실패했다
	if (_imageInfo->hBit == 0) {
		release();
		return E_FAIL;
	}

	// DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);

	// 이미지 정보 새로 생성 후 초기화
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	// 5. LoadImage  비슷한 함수로는 LoadBitmap 함수가 있지만 LoadImage 함수가 더 많은 기능을 지원합니다.
	// 6. LR_LOADFROMFILE   lpszName 인수를 리소스 대신 파일 경로를 사용해 불러옵니다.
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX - 1;
	_imageInfo->maxFrameY = maxFrameY - 1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	// 리소스를 얻어오는데 실패했다
	if (_imageInfo->hBit == 0) {
		release();
		return E_FAIL;
	}

	// DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::initForAlphaBlend(void)
{
	HDC hdc = GetDC(_hWnd);

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0; // 소스랑 비트맵 혼합 시킬건지?
	_blendFunc.BlendOp = AC_SRC_OVER; // 접근가능->구조체 비트맵을 24 or 32로 쓸건지

	// 이미지 정보 새로 생성 후 초기화
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZE_X;
	_blendImage->height = WINSIZE_Y;

	// DC 해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void Image::setTransColor(BOOL isTrans, COLORREF transColopr)
{
	_isTrans = isTrans;
	_transColor = transColopr;
}

void Image::release(void)
{
	if (_imageInfo) {
		// 이미지 삭제
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		_isTrans = FALSE;
		_transColor = RGB(0, 0, 0);
	}

	if (_blendImage) {
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		SAFE_DELETE(_blendImage);
	}
}

// 렌더 (0, 0지점에 렌더)
void Image::render(HDC hdc)
{
	if (_isTrans) {
		// GdiTransparentBlt(): 비트맵을 불러올때 특정 색상을 제외하고 복사해 주는 함수
		GdiTransparentBlt(
			hdc,					// 복사할 장소의 DC (화면 DC (화면에 보여줄))
			0, 0,					// 복사될 x, y 시작 좌표
			_imageInfo->width,		// 복사될 이미지 가로 크기
			_imageInfo->height,		// 복사될 이미지 세로 크기
			_imageInfo->hMemDC,		// 복사될 대상 메모리 DC
			0, 0,					// 복사 시작 지점
			_imageInfo->width,		// 복사 영역 가로크기
			_imageInfo->height,		// 복사 영역 세로 크기
			_transColor				// 복사할때 제외할 색상
		);
	}
	else {
		// BitBlt(): DC 간의 영역끼리 서로 고속복사 해주는 함수
		// SRCCOPY: 소스 영역을 대상 영역에 복사한다.
		BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void Image::render(HDC hdc, int destX, int destY)
{
	if (_isTrans) {
		// GdiTransparentBlt(): 비트맵을 불러올때 특정 색상을 제외하고 복사해 주는 함수
		GdiTransparentBlt(
			hdc,					// 복사할 장소의 DC (화면 DC (화면에 보여줄))
			destX, destY,			// 복사될 x, y 시작 좌표
			_imageInfo->width,		// 복사될 이미지 가로 크기
			_imageInfo->height,		// 복사될 이미지 세로 크기
			_imageInfo->hMemDC,		// 복사될 대상 메모리 DC
			0, 0,					// 복사 시작 지점
			_imageInfo->width,		// 복사 영역 가로크기
			_imageInfo->height,		// 복사 영역 세로 크기
			_transColor				// 복사할때 제외할 색상
		);
	}
	else {
		// BitBlt(): DC 간의 영역끼리 서로 고속복사 해주는 함수
		// SRCCOPY: 소스 영역을 대상 영역에 복사한다.
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

// 클리핑
void Image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_isTrans) {
		GdiTransparentBlt(
			hdc,
			destX, destY,
			sourWidth,
			sourHeight,
			_imageInfo->hMemDC,
			sourX, sourY,
			sourWidth,
			sourHeight,
			_transColor
		);
	}
	else {
		BitBlt(hdc, destX, destY, sourWidth, sourHeight, _imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void Image::alphaRender(HDC hdc, BYTE alpha)
{
	// 알파블렌드를 처음 사용하는지?
	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans) {
		// 1. 출력해야 될 DC에 그려져 있는 내용을 블렌드 이미지에 그린다.
		BitBlt(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc,
			0, 0,
			SRCCOPY
		);

		// 2. 원본 이미지의 배경을 없앤후 블렌드 이미지에 그린다.
		GdiTransparentBlt(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor
		);

		// 3. 블렌드 이미지를 화면에 그린다.
		AlphaBlend(
			hdc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc
		);
	}
	else {
		AlphaBlend(
			hdc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc
		);
	}
}

void Image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans) {
		BitBlt(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc,
			destX, destY,
			SRCCOPY
		);

		GdiTransparentBlt(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor
		);

		AlphaBlend(
			hdc,
			destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc
		);
	}
	else {
		AlphaBlend(
			hdc,
			destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc
		);
	}
}

void Image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	
}

void Image::frameRender(HDC hdc, int destX, int destY)
{
	if (_isTrans) {
		GdiTransparentBlt(
			hdc,
			destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor
		);
	}
	else {
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight, _imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void Image::frameRender(HDC hdc, int destX, int destY, int tick, BYTE alpha, bool reverseFrameX)
{
	if (_imageInfo->currentFrameX > _imageInfo->maxFrameX) {
		_imageInfo->currentFrameX = 0;
	}
	if (_imageInfo->currentFrameY > _imageInfo->maxFrameY) {
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if (_imageInfo->currentFrameX < 0) {
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}

	_imageInfo->x = destX;
	_imageInfo->y = destY;

	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	// 이미지 예외처리
	if (_isTrans) {
		BitBlt(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			hdc,
			destX, destY,
			SRCCOPY
		);

		GdiTransparentBlt(
			hdc,
			destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor
		);

		AlphaBlend(
			hdc,
			destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_blendImage->hMemDC,
			0,0,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_blendFunc
		);
	}
	else {
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight, _imageInfo->hMemDC, 
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
	
	_imageInfo->count++;
	if (!reverseFrameX && _imageInfo->count % tick == 0) {
		_imageInfo->currentFrameX++;
	}
	if (reverseFrameX && _imageInfo->count % tick == 0) {
		_imageInfo->currentFrameX--;
	}
}

void Image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _imageInfo->maxFrameX) {
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY) {
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if (_isTrans) {
		GdiTransparentBlt(
			hdc,
			destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor
		);
	}
	else {
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight, _imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void Image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	// offset 값이 음수인 경우 보정을 하겠다.
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	// 그려지는 영역 셋팅
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	// 그려지는 DC 영역 (화면 크기)
	RECT rcDest;

	// 그려야 할 전체 영역
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	// 세로 루프영역
	for (int y = 0; y < drawAreaH; y += sourHeight) {
		// 소스 영역의 높이 계산
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		// 소스 영역이 그리는 화면을 넘어갔다면 (화면밖으로 나갔을때)
		if (y + sourHeight > drawAreaH) {
			// 넘어간 그림의 값만큼 올려주겠다.
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		// 그려지는 영역
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (int x = 0; x < drawAreaW; x += sourWidth) {
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW) {
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight);
		} // end of second for
	} // end of for
}

void Image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
}

void Image::aniRender(HDC hdc, int destX, int destY, Animation * ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}
