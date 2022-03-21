#pragma once
//1. #include "Animation.h"

// �� ����Ѵ� -> �Ǵ��ϸ� �ȴ�.
class Animation;

/*
Ŭ���� ���漱�� (Class Forward Declaration)

���� ����, ��ó���� #include

1. is a ����		: ���׽ý��� ����.					->	 #include
2. has a ����	: ���׽ô��� ������ ������ �ִ�.		->	 ���漱��

- Ŭ���� ���漱���� �Լ� ���漱��� ����ϸ鼭�� �ٸ� ���� �ִ�.

- #include ��ó���⸦ ���� ��� �� ��쿡�� ��ó���� �ܰ谡 ������� �ȴ�.
	�� ������ �ð� ���� ����

- �̸� �ذ��ϱ� ���� ���� ������ �̿��� ���� �ִ�.
1. Ŭ������ ������ / ���� �������� �̸��� ������ ���
2. �Ű� ������ ���� Ÿ���� ���� �̸��� ������ ���
3. �޸� ����
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
	BOOL			_isTrans;		// ���� ����
	COLORREF		_transColor;	// ������ ���� RGB��   RGB(���� 1����Ʈ 0~255 �� ǥ�� ����)

	BLENDFUNCTION	_blendFunc;
	LPIMAGE_INFO	_blendImage;

public:
	// �� ��Ʈ�� �ʱ�ȭ
	HRESULT init(int width, int height);
	// �̹��� ���ҽ� �ʱ�ȭ
	HRESULT init(const DWORD resID, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	// �̹��� ���Ϸ� �ʱ�ȭ
	HRESULT init(const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	// ������ �̹��� ���Ϸ� �ʱ�ȭ
	HRESULT init(const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));


	// ���� ���� �ʱ�ȭ
	HRESULT initForAlphaBlend(void);

	// ���� �÷�Ű ���� (���� ��������, �����)
	void setTransColor(BOOL isTrans, COLORREF transColopr);

	// ����
	void release(void);

	// ����
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	// Ŭ����
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	// ���� ����
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	// ������ ����
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int tick, BYTE alpha = 0, bool reverseFrameX = false);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	// ���� ����
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	// �ִ� ����
	void aniRender(HDC hdc, int destX, int destY, Animation* ani);

	// ==============
	// # �ζ��� �Լ� #
	// ==============

	// DC���
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	// �̹��� X��ǥ
	inline float getX(void) { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }
	// �̹��� Y��ǥ
	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }

	// �̹��� ���� ��ǥ
	inline void setCenter(float x, float y) {
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	// �̹��� ����, ����ũ��
	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }

	// �ٿ�� �ڽ� (�浹�� ��Ʈ)
	inline RECT boundingBox(void) {
		RECT rc = {
			(int)_imageInfo->x,
			(int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->width,
			(int)_imageInfo->y + _imageInfo->height
		};
		return rc;
	}

	// �ٿ�� �ڽ� (�浹�� ��Ʈ)
	inline RECT boundingBoxWithFrame(void) {
		RECT rc = {
			(int)_imageInfo->x,
			(int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->frameWidth,
			(int)_imageInfo->y + _imageInfo->frameHeight
		};
		return rc;
	}

	// ������ X
	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX) {
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX) {
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	// ������ Y
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY) {
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY) {
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	// �̹��� 1 ������ ����, ���� ũ��
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	// �ִ� ������ x, y ����
	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

	Image();
	~Image() {}
};

