#include "Stdafx.h"
#include "GameNode.h"

HRESULT GameNode::init(void)
{
	return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		setlocale(LC_ALL, "Korean");

		SetTimer(_hWnd, 1, 10, NULL);

		KEYMANAGER->init();

		RND->init();

		IMAGEMANAGER->init(getMemDC());

		TIMEMANAGER->init();

		TEXTDATAMANAGER->init();

		SCENEMANAGER->init();

		SOUNDMANAGER->init();

		JSONDATAMANAGER->init();

		EFFECTMANAGER->init();

		CAMERAMANAGER->init();

		TIMEMANAGER->init();
		
		UIMANAGER->init();

		FILEMANAGER->init();

		TILEMANAGER->init();
	}

	return S_OK;
}

void GameNode::release(void)
{
	if (_managerInit)
	{
		KillTimer(_hWnd, 1);

		KEYMANAGER->releaseSingleton();

		RND->releaseSingleton();

		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		
		FONTMANAGER->releaseSingleton();

		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		TEXTDATAMANAGER->release();
		TEXTDATAMANAGER->releaseSingleton();

		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();

		JSONDATAMANAGER->release();
		JSONDATAMANAGER->releaseSingleton();

		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();

		CAMERAMANAGER->release();
		CAMERAMANAGER->releaseSingleton();

		UIMANAGER->release();
		UIMANAGER->releaseSingleton();

		FILEMANAGER->release();
		FILEMANAGER->releaseSingleton();

		TILEMANAGER->release();
		TILEMANAGER->releaseSingleton();
	}

	ReleaseDC(_hWnd, _hdc);
}

void GameNode::update(void)
{
}

void GameNode::render(void)
{
}

LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_TIMER:
		this->update();
		break;
	case WM_PAINT:
		this->render();
		break;
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
