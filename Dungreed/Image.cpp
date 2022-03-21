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
	// �� �ʱ�ȭ ���� -> �̹��� ������ ���� ����ִٸ� ������ ���� �ϰڴ�.
	if (_imageInfo != NULL) this->release();

	// ��������� ������
	// ��Ÿ��    false�϶� ������
	//assert(_imageInfo != NULL);
	// ������		���Ÿ���� ������ ���
	//static_assert

	// DC ��������
	HDC hdc = GetDC(_hWnd);
	
	// �̹��� ���� ���� ���� �� �ʱ�ȭ
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	// 1. hdc�� ȣȯ�Ǵ� DC�� �����Ѵ�.
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	// 2. hdc�� ȣȯ�Ǵ� ������ ��Ʈ���� width, height ũ��� �����
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	// ���� �̸�
	_fileName = NULL;
	_isTrans = FALSE;
	_transColor = RGB(0, 0, 0);

	// ���ҽ��� �����µ� �����ߴ�
	if (_imageInfo->hBit == 0) {
		release();
		return E_FAIL;
	}

	// DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const DWORD resID, int width, int height, BOOL isTrans, COLORREF transColor)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);

	// �̹��� ���� ���� ���� �� �ʱ�ȭ
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE;

	_imageInfo->resID = resID;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	// 3. LoadBitmap ��Ʈ���� �ҷ����� �Լ��Դϴ�.
	// 4. MAKEINTRESOURCE (���ҽ��� �������µ� �ٽ����� �Լ�) ��ũ�δ� ������ ������ ���ҽ� ���̵� ���ڿ��� �ٲ��ش�.
	_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->resID));
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	// ���� �̸�
	_fileName = NULL;
	_isTrans = isTrans;
	_transColor = transColor;

	// ���ҽ��� �����µ� �����ߴ�
	if (_imageInfo->hBit == 0) {
		release();
		return E_FAIL;
	}

	// DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const char* fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);

	// �̹��� ���� ���� ���� �� �ʱ�ȭ
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	// 5. LoadImage  ����� �Լ��δ� LoadBitmap �Լ��� ������ LoadImage �Լ��� �� ���� ����� �����մϴ�.
	// 6. LR_LOADFROMFILE   lpszName �μ��� ���ҽ� ��� ���� ��θ� ����� �ҷ��ɴϴ�.
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	
	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	// ���ҽ��� �����µ� �����ߴ�
	if (_imageInfo->hBit == 0) {
		release();
		return E_FAIL;
	}

	// DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

// �Լ� �����Ҷ� cahr * fileName �̷����̸� �ȵ� cpp boost���� ���ϱ� �������� �ν���
HRESULT Image::init(const char* fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);

	// �̹��� ���� ���� ���� �� �ʱ�ȭ
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	// 5. LoadImage  ����� �Լ��δ� LoadBitmap �Լ��� ������ LoadImage �Լ��� �� ���� ����� �����մϴ�.
	// 6. LR_LOADFROMFILE   lpszName �μ��� ���ҽ� ��� ���� ��θ� ����� �ҷ��ɴϴ�.
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

	// ���ҽ��� �����µ� �����ߴ�
	if (_imageInfo->hBit == 0) {
		release();
		return E_FAIL;
	}

	// DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);

	// �̹��� ���� ���� ���� �� �ʱ�ȭ
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	// 5. LoadImage  ����� �Լ��δ� LoadBitmap �Լ��� ������ LoadImage �Լ��� �� ���� ����� �����մϴ�.
	// 6. LR_LOADFROMFILE   lpszName �μ��� ���ҽ� ��� ���� ��θ� ����� �ҷ��ɴϴ�.
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

	// ���ҽ��� �����µ� �����ߴ�
	if (_imageInfo->hBit == 0) {
		release();
		return E_FAIL;
	}

	// DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	if (_imageInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);

	// �̹��� ���� ���� ���� �� �ʱ�ȭ
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	// 5. LoadImage  ����� �Լ��δ� LoadBitmap �Լ��� ������ LoadImage �Լ��� �� ���� ����� �����մϴ�.
	// 6. LR_LOADFROMFILE   lpszName �μ��� ���ҽ� ��� ���� ��θ� ����� �ҷ��ɴϴ�.
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

	// ���ҽ��� �����µ� �����ߴ�
	if (_imageInfo->hBit == 0) {
		release();
		return E_FAIL;
	}

	// DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::initForAlphaBlend(void)
{
	HDC hdc = GetDC(_hWnd);

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0; // �ҽ��� ��Ʈ�� ȥ�� ��ų����?
	_blendFunc.BlendOp = AC_SRC_OVER; // ���ٰ���->����ü ��Ʈ���� 24 or 32�� ������

	// �̹��� ���� ���� ���� �� �ʱ�ȭ
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZE_X;
	_blendImage->height = WINSIZE_Y;

	// DC ����
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
		// �̹��� ����
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

// ���� (0, 0������ ����)
void Image::render(HDC hdc)
{
	if (_isTrans) {
		// GdiTransparentBlt(): ��Ʈ���� �ҷ��ö� Ư�� ������ �����ϰ� ������ �ִ� �Լ�
		GdiTransparentBlt(
			hdc,					// ������ ����� DC (ȭ�� DC (ȭ�鿡 ������))
			0, 0,					// ����� x, y ���� ��ǥ
			_imageInfo->width,		// ����� �̹��� ���� ũ��
			_imageInfo->height,		// ����� �̹��� ���� ũ��
			_imageInfo->hMemDC,		// ����� ��� �޸� DC
			0, 0,					// ���� ���� ����
			_imageInfo->width,		// ���� ���� ����ũ��
			_imageInfo->height,		// ���� ���� ���� ũ��
			_transColor				// �����Ҷ� ������ ����
		);
	}
	else {
		// BitBlt(): DC ���� �������� ���� ��Ӻ��� ���ִ� �Լ�
		// SRCCOPY: �ҽ� ������ ��� ������ �����Ѵ�.
		BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void Image::render(HDC hdc, int destX, int destY)
{
	if (_isTrans) {
		// GdiTransparentBlt(): ��Ʈ���� �ҷ��ö� Ư�� ������ �����ϰ� ������ �ִ� �Լ�
		GdiTransparentBlt(
			hdc,					// ������ ����� DC (ȭ�� DC (ȭ�鿡 ������))
			destX, destY,			// ����� x, y ���� ��ǥ
			_imageInfo->width,		// ����� �̹��� ���� ũ��
			_imageInfo->height,		// ����� �̹��� ���� ũ��
			_imageInfo->hMemDC,		// ����� ��� �޸� DC
			0, 0,					// ���� ���� ����
			_imageInfo->width,		// ���� ���� ����ũ��
			_imageInfo->height,		// ���� ���� ���� ũ��
			_transColor				// �����Ҷ� ������ ����
		);
	}
	else {
		// BitBlt(): DC ���� �������� ���� ��Ӻ��� ���ִ� �Լ�
		// SRCCOPY: �ҽ� ������ ��� ������ �����Ѵ�.
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

// Ŭ����
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
	// ���ĺ��带 ó�� ����ϴ���?
	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans) {
		// 1. ����ؾ� �� DC�� �׷��� �ִ� ������ ���� �̹����� �׸���.
		BitBlt(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc,
			0, 0,
			SRCCOPY
		);

		// 2. ���� �̹����� ����� ������ ���� �̹����� �׸���.
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

		// 3. ���� �̹����� ȭ�鿡 �׸���.
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

	// �̹��� ����ó��
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
	// offset ���� ������ ��� ������ �ϰڴ�.
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	// �׷����� ���� ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	// �׷����� DC ���� (ȭ�� ũ��)
	RECT rcDest;

	// �׷��� �� ��ü ����
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	// ���� ��������
	for (int y = 0; y < drawAreaH; y += sourHeight) {
		// �ҽ� ������ ���� ���
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		// �ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ� (ȭ������� ��������)
		if (y + sourHeight > drawAreaH) {
			// �Ѿ �׸��� ����ŭ �÷��ְڴ�.
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		// �׷����� ����
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
