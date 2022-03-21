#include "Stdafx.h"
#include "GameNode.h"

HRESULT GameNode::init(void)
{
	// 이제 안씀
	return S_OK;

	// 타이머 초기화
	SetTimer(_hWnd, 1, 10, NULL);

	// 키매니저 초기화
	KEYMANAGER->init();
	
	// 랜덤함수 초기화
	RND->init();

	// 백버퍼 초기화
	//this->setBackBuffer();

	// 함수가 성공적으로 실행되었음을 알리는 S_OK 반환
	// Success_OK
	return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		// 로케일 설정 (#include "locale.h")
		setlocale(LC_ALL, "Korean");

		// 타이머 초기화
		SetTimer(_hWnd, 1, 10, NULL);

		// 키매니저 초기화
		KEYMANAGER->init();

		// 랜덤함수 초기화
		RND->init();

		// 이미지매니저 초기화
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
		// 타이머 해제
		KillTimer(_hWnd, 1);

		// 키매니저 싱글톤 해제
		KEYMANAGER->releaseSingleton();

		// 랜덤함수 싱글톤 해제
		RND->releaseSingleton();

		// 이미지매니저 싱글톤 해제
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();

		// 폰트매니저 싱글톤 해제
		FONTMANAGER->releaseSingleton();

		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		TEXTDATAMANAGER->release();
		TEXTDATAMANAGER->releaseSingleton();

		// 씬 매니저 해제
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();

		JSONDATAMANAGER->release();
		JSONDATAMANAGER->releaseSingleton();

		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();
	}

	// 포인터 변수들은 안하면 메모리 누수...
	// 백버퍼 이미지 해제
	//SAFE_DELETE(_backBuffer);

	// DC 해제
	ReleaseDC(_hWnd, _hdc);
}

void GameNode::update(void)
{
	// 새로고침
	// 버퍼링이 추가되면 고민이 필요하다..
	//InvalidateRect(_hWnd, NULL, false);
}

void GameNode::render(void)
{
}

LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	/*
	Window Procedure: 메세지를 운영체제에 전달 -> 강제로 운영체제가 호출 해준다.
			ㄴ 윈도우를 생성할때 반드시 지정해 줘야 한다.
			ㄴ WinMain이 아닌, 운영체제에 의해 호출되는 콜백 함수

	hWnd: 어느 윈도우에서 발생한 메세지인지 구분
	iMessage: 메세지 구분 번호
	wParam: Unsigned int 마우스 버튼의 상태, 키보드 조합 키의 상태를 전달
	lParam: Unsigned long 마우스 클릭 좌표를 전달
	*/

	// GDI -> HDC -> Handle to a Device Context
	//HDC hdc;			// 핸들DC
	//PAINTSTRUCT ps;		// 페인트 구조체

	switch (iMessage)
	{
	case WM_TIMER:
		this->update();
		break;
	case WM_PAINT:			// 출력에 관한 모든것을 담당한다 (문자, 그림, 도형 등 화면에 보이는 모든것)
		//hdc = BeginPaint(hWnd, &ps);
		this->render();
		//EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:		// 키보드 키가 눌렸을때 메세지 발생
		switch (wParam)
		{
		case VK_ESCAPE:		// ESC 키를 누르면 화면 종료
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:		// 소멸자
		/*
		PostQuitMessage 함수는 메세지 큐에 Quit 메세지를 보내는 역활을 한다.
		즉, Quit 메세지를 수신하는 순간 GetMessage 함수 -> FALSE를 반환함으로 메세지 루프 종료된다.
		*/
		PostQuitMessage(0);
		return 0;
	}

	// 윈도우 프로시저에서 처리되지 않은 나머지 메세지를 처리해준다.
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
