#include "Stdafx.h"
#include "GameNode.h"

HRESULT GameNode::init(void)
{
	// ���� �Ⱦ�
	return S_OK;

	// Ÿ�̸� �ʱ�ȭ
	SetTimer(_hWnd, 1, 10, NULL);

	// Ű�Ŵ��� �ʱ�ȭ
	KEYMANAGER->init();
	
	// �����Լ� �ʱ�ȭ
	RND->init();

	// ����� �ʱ�ȭ
	//this->setBackBuffer();

	// �Լ��� ���������� ����Ǿ����� �˸��� S_OK ��ȯ
	// Success_OK
	return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		// ������ ���� (#include "locale.h")
		setlocale(LC_ALL, "Korean");

		// Ÿ�̸� �ʱ�ȭ
		SetTimer(_hWnd, 1, 10, NULL);

		// Ű�Ŵ��� �ʱ�ȭ
		KEYMANAGER->init();

		// �����Լ� �ʱ�ȭ
		RND->init();

		// �̹����Ŵ��� �ʱ�ȭ
		IMAGEMANAGER->init();

		TIMEMANAGER->init();

		TEXTDATAMANAGER->init();

		SCENEMANAGER->init();

		SOUNDMANAGER->init();

		JSONDATAMANAGER->init();

		EFFECTMANAGER->init();
	}

	return S_OK;
}

//void GameNode::setBackBuffer(void)
//{
//	_backBuffer = new Image;
//	_backBuffer->init(WINSIZE_X, WINSIZE_Y);
//}

void GameNode::release(void)
{
	if (_managerInit)
	{
		// Ÿ�̸� ����
		KillTimer(_hWnd, 1);

		// Ű�Ŵ��� �̱��� ����
		KEYMANAGER->releaseSingleton();

		// �����Լ� �̱��� ����
		RND->releaseSingleton();

		// �̹����Ŵ��� �̱��� ����
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();

		// ��Ʈ�Ŵ��� �̱��� ����
		FONTMANAGER->releaseSingleton();

		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		TEXTDATAMANAGER->release();
		TEXTDATAMANAGER->releaseSingleton();

		// �� �Ŵ��� ����
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();

		JSONDATAMANAGER->release();
		JSONDATAMANAGER->releaseSingleton();

		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();
	}

	// ������ �������� ���ϸ� �޸� ����...
	// ����� �̹��� ����
	//SAFE_DELETE(_backBuffer);

	// DC ����
	ReleaseDC(_hWnd, _hdc);
}

void GameNode::update(void)
{
	// ���ΰ�ħ
	// ���۸��� �߰��Ǹ� ����� �ʿ��ϴ�..
	//InvalidateRect(_hWnd, NULL, false);
}

void GameNode::render(void)
{
}

LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	/*
	Window Procedure: �޼����� �ü���� ���� -> ������ �ü���� ȣ�� ���ش�.
			�� �����츦 �����Ҷ� �ݵ�� ������ ��� �Ѵ�.
			�� WinMain�� �ƴ�, �ü���� ���� ȣ��Ǵ� �ݹ� �Լ�

	hWnd: ��� �����쿡�� �߻��� �޼������� ����
	iMessage: �޼��� ���� ��ȣ
	wParam: Unsigned int ���콺 ��ư�� ����, Ű���� ���� Ű�� ���¸� ����
	lParam: Unsigned long ���콺 Ŭ�� ��ǥ�� ����
	*/

	// GDI -> HDC -> Handle to a Device Context
	//HDC hdc;			// �ڵ�DC
	//PAINTSTRUCT ps;		// ����Ʈ ����ü

	switch (iMessage)
	{
	case WM_TIMER:
		this->update();
		break;
	case WM_PAINT:			// ��¿� ���� ������ ����Ѵ� (����, �׸�, ���� �� ȭ�鿡 ���̴� ����)
		//hdc = BeginPaint(hWnd, &ps);
		this->render();
		//EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:		// Ű���� Ű�� �������� �޼��� �߻�
		switch (wParam)
		{
		case VK_ESCAPE:		// ESC Ű�� ������ ȭ�� ����
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:		// �Ҹ���
		/*
		PostQuitMessage �Լ��� �޼��� ť�� Quit �޼����� ������ ��Ȱ�� �Ѵ�.
		��, Quit �޼����� �����ϴ� ���� GetMessage �Լ� -> FALSE�� ��ȯ������ �޼��� ���� ����ȴ�.
		*/
		PostQuitMessage(0);
		return 0;
	}

	// ������ ���ν������� ó������ ���� ������ �޼����� ó�����ش�.
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
