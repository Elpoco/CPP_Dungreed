#include "Stdafx.h"
#include "Cursor.h"

Cursor::Cursor()
	: _cursorCurrent(UIEnum::CURSOR_TYPE::NORMAL)
{
	_isFixed = TRUE; // 절대좌표로 하기위해
}

Cursor::~Cursor()
{
}

HRESULT Cursor::init()
{
	UI::init();

	_vCursor.push_back({ IMAGEMANAGER->findImage(ImageName::none), false });
	_vCursor.push_back({ IMAGEMANAGER->findImage(ImageName::UI::Cursor::cursor), false });
	_vCursor.push_back({ IMAGEMANAGER->findImage(ImageName::UI::Cursor::attack), true });

	return S_OK;
}

void Cursor::release()
{
	UI::release();
}

void Cursor::update()
{
	_sceneName = SCENEMANAGER->getCurrentSceneName();
	UI::update();

	if (_vCursor[_cursorCurrent].isCenter)
	{
		_rc = RectMakeCenter(
			_ptMouse.x, _ptMouse.y,
			_vCursor[_cursorCurrent].img->getWidth(),
			_vCursor[_cursorCurrent].img->getHeight()
		);
	}
	else
	{
		_rc = RectMake(
			_ptMouse.x, _ptMouse.y,
			_vCursor[_cursorCurrent].img->getWidth(),
			_vCursor[_cursorCurrent].img->getHeight()
		);
	}
}

void Cursor::render(HDC hdc)
{
	_vCursor[_cursorCurrent].img->render(hdc, _rc.left, _rc.top);
}
