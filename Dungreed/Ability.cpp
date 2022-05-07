#include "Stdafx.h"
#include "Ability.h"

Ability::Ability()
{
}

Ability::~Ability()
{
}

HRESULT Ability::init()
{
	UI::init();

	initUI();

	return S_OK;
}

void Ability::release()
{
	UI::release();
}

void Ability::update()
{
	if (!_isShow) return;
	UI::update();
	animation();

	if (MouseInRect(_rcExitBtn))
	{
		if (IsOnceKeyUp(KEY::CLICK_L)) UIMANAGER->offUI();
	}
}

void Ability::render(HDC hdc)
{
	if (!_isShow) return;
	UI::render(hdc);

	FindImage(ImageName::ChangeScene)->alphaRender(hdc, 0, 0, 200);
	_uiLabel->render(hdc);
	_imgButton->frameRender(hdc, _rcExitBtn.left, _rcExitBtn.top, 0, MouseInRect(_rcExitBtn));
}

void Ability::show()
{
	_isShow = TRUE;
}

void Ability::hide()
{
	_isShow = FALSE;
}

void Ability::initUI()
{
	_imgButton = FindImage(ImageName::UI::Button::Exit);

	_uiLabel = new UI(ImageName::UI::Ability::Label);
	_uiLabel->setX(CENTER_X);
	_uiLabel->setY(_uiLabel->getHeight() * 0.5f);

	_rcExitBtn = RectMakeCenter(
		_uiLabel->getRect().right - _imgButton->getFrameWidth() + 15,
		_uiLabel->getY(),
		_imgButton->getFrameWidth(),
		_imgButton->getFrameHeight()
	);
}

void Ability::animation()
{
}
