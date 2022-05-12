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

		KEYMANAGER		->init();
		RND				->init();
		IMAGEMANAGER	->init();
		TIMEMANAGER		->init();
		TEXTDATAMANAGER	->init();
		SOUNDMANAGER	->init();
		//JSONDATAMANAGER	->init();
		OBJECTMANAGER	->init();
		CAMERAMANAGER	->init();
		TIMEMANAGER		->init();
		FILEMANAGER		->init();
		TILEMANAGER		->init();
		MSGBOXMANAGER	->init();
		SCENEMANAGER	->init();
		COLLISIONMANAGER->init();
		GPIMAGEMANAGER	->init();
		ITEMMANAGER		->init();
		UIMANAGER		->init();
		DBMANAGER		->init();
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

		//JSONDATAMANAGER->release();
		//JSONDATAMANAGER->releaseSingleton();

		OBJECTMANAGER->release();
		OBJECTMANAGER->releaseSingleton();

		CAMERAMANAGER->release();
		CAMERAMANAGER->releaseSingleton();

		FILEMANAGER->release();
		FILEMANAGER->releaseSingleton();

		TILEMANAGER->release();
		TILEMANAGER->releaseSingleton();

		MSGBOXMANAGER->release();
		MSGBOXMANAGER->releaseSingleton();

		COLLISIONMANAGER->release();
		COLLISIONMANAGER->releaseSingleton();
		
		GPIMAGEMANAGER->release();
		GPIMAGEMANAGER->releaseSingleton();

		ITEMMANAGER->release();
		ITEMMANAGER->releaseSingleton();

		UIMANAGER->release();
		UIMANAGER->releaseSingleton();

		DBMANAGER->release();
		DBMANAGER->releaseSingleton();

		MAPMANAGER->release();
		MAPMANAGER->releaseSingleton();
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
	case WM_SETFOCUS:
		_isWindowFocus = true;
		break;
	case WM_KILLFOCUS:
		_isWindowFocus = false;
		break;
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
	case WM_CHAR:
		if (KEYMANAGER->isTyping())
		{
			KEYMANAGER->typing(wParam);
		}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			//PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
