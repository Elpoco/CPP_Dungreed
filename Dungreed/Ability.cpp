#include "Stdafx.h"
#include "Ability.h"

using namespace AbilitySet;

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

	if (IsOnceKeyDown(KEY::RELOAD)) PLAYERMANAGER->resetAbility();

	if (MouseInRect(_rcExitBtn))
	{
		if (IsOnceKeyUp(KEY::CLICK_L)) UIMANAGER->offUI();
	}

	for (int i = 0; i < ABILITY_CNT; i++)
	{
		_isHover[i] = FALSE;
		if (MouseInRect(_rcBtn[i]))
		{
			_isHover[i] = TRUE;
			if (IsOnceKeyUp(KEY::CLICK_L)) clickBtn(i);
		}
	}
}

void Ability::render(HDC hdc)
{
	if (!_isShow) return;
	UI::render(hdc);

	FindImage(ImageName::ChangeScene)->alphaRender(hdc, 0, 0, 200);
	_uiLabel->render(hdc);
	_imgButton->frameRender(hdc, _rcExitBtn.left, _rcExitBtn.top, 0, MouseInRect(_rcExitBtn));

	_uiR->render(hdc);
	FONTMANAGER->drawString(hdc, _uiR->getRect().right + 3, _uiR->getY() - 13, 25, FW_BOLD, " 초기화", ColorSet::WHITE);

	int startX = WINSIZE_X - 300;
	int startY = WINSIZE_Y - 100;
	int width = FindImage(ImageName::UI::Ability::AbilityTextBar)->getFrameWidth();
	int height = FindImage(ImageName::UI::Ability::AbilityTextBar)->getHeight();

	FindImage(ImageName::UI::Ability::AbilityTextBar)->frameRender(hdc, startX, startY, 0, 0);
	for (int i = 1; i <= 11; i++)
	{
		FindImage(ImageName::UI::Ability::AbilityTextBar)->frameRender(hdc, startX + width * i, startY, 1, 0);
	}
	FindImage(ImageName::UI::Ability::AbilityTextBar)->frameRender(hdc, startX + width * 12, startY, 2, 0);

	SIZE size = FONTMANAGER->drawString(hdc, startX + 18, startY + 14, 25, 0, "남은 포인트 : ", ColorSet::WHITE);
	SIZE size2;
	FONTMANAGER->drawNumber(hdc, startX + 32 + size.cx, startY + 1 + height * 0.5f, 22, 0, to_string(PLAYERMANAGER->getAbility()).c_str(), ColorSet::WHITE, DIR::CENTER);

	_uiWrath->render(hdc);
	_uiPatience->render(hdc);
	_uiGreed->render(hdc);

	FONTMANAGER->drawString(hdc, _uiWrath->getX(), _uiWrath->getY() - 68, 35, 0, "분노", ColorSet::WHITE, DIR::CENTER);
	FONTMANAGER->drawString(hdc, _uiPatience->getX(), _uiPatience->getY() - 78, 35, 0, "인내", ColorSet::WHITE, DIR::CENTER);
	FONTMANAGER->drawString(hdc, _uiGreed->getX(), _uiGreed->getY() - 70, 35, 0, "탐욕", ColorSet::WHITE, DIR::CENTER);

	FONTMANAGER->drawNumber(hdc, _uiWrath->getX(), _uiWrath->getY() + 2, 40, 0, to_string(PLAYERMANAGER->getWrath()).c_str(), ColorSet::WRATH, DIR::CENTER);
	FONTMANAGER->drawNumber(hdc, _uiPatience->getX(), _uiPatience->getY() - 8, 40, 0, to_string(PLAYERMANAGER->getPatience()).c_str(), ColorSet::PATIENCE, DIR::CENTER);
	FONTMANAGER->drawNumber(hdc, _uiGreed->getX(), _uiGreed->getY(), 40, 0, to_string(PLAYERMANAGER->getGreed()).c_str(), ColorSet::GREED, DIR::CENTER);

	size = FONTMANAGER->drawString(hdc, _uiWrath->getX(), _uiWrath->getY(), 25, 0, " ", ColorSet::WHITE, DIR::CENTER);
	size2 = FONTMANAGER->drawNumber(hdc, _uiWrath->getX() - 5 - size.cx, _uiWrath->getRect().bottom - 107, 22, 0, to_string(PLAYERMANAGER->getWrath() * POWER).c_str(), ColorSet::GREEN, DIR::RIGHT);
	FONTMANAGER->drawString(hdc, _uiWrath->getX() - 5 - size.cx - size2.cx, _uiWrath->getRect().bottom - 110, 25, 0, "+", ColorSet::GREEN, DIR::RIGHT);
	FONTMANAGER->drawString(hdc, _uiWrath->getX() - 5 + size.cx, _uiWrath->getRect().bottom - 110, 25, 0, "위력", ColorSet::WHITE);

	size2 = FONTMANAGER->drawNumber(hdc, _uiPatience->getX() - 10 - size.cx, _uiPatience->getRect().bottom - 107, 22, 0, to_string(PLAYERMANAGER->getPatience() * DEFENSE).c_str(), ColorSet::GREEN, DIR::RIGHT);
	FONTMANAGER->drawString(hdc, _uiPatience->getX() - 10 - size.cx - size2.cx, _uiPatience->getRect().bottom - 110, 25, 0, "+", ColorSet::GREEN, DIR::RIGHT);
	FONTMANAGER->drawString(hdc, _uiPatience->getX() - 10 + size.cx, _uiPatience->getRect().bottom - 110, 25, 0, "방어력", ColorSet::WHITE);

	size2 = FONTMANAGER->drawNumber(hdc, _uiGreed->getX() - 20 - size.cx, _uiGreed->getRect().bottom - 107, 22, 0, to_string(PLAYERMANAGER->getGreed() * MAX_HP).c_str(), ColorSet::GREEN, DIR::RIGHT);
	FONTMANAGER->drawString(hdc, _uiGreed->getX() - 20 - size.cx - size2.cx, _uiGreed->getRect().bottom - 110, 25, 0, "+", ColorSet::GREEN, DIR::RIGHT);
	FONTMANAGER->drawString(hdc, _uiGreed->getX() - 20 + size.cx, _uiGreed->getRect().bottom - 110, 25, 0, "최대 체력", ColorSet::WHITE);

	for (int i = 0; i < ABILITY_CNT; i++)
	{
		_imgAblityBtn[i]->frameRender(hdc, _rcBtn[i].left, _rcBtn[i].top, 0, _isHover[i]);
	}
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

	_uiR = new UI(ImageName::UI::Keyboard::R);
	_uiR->setX(WINSIZE_X - 400);
	_uiR->setY(WINSIZE_Y - 70);

	_uiWrath = new UI(ImageName::UI::Ability::Wrath);
	_uiWrath->setX(CENTER_X - _uiWrath->getWidth() - 100);
	_uiWrath->setY(CENTER_Y);

	_uiPatience = new UI(ImageName::UI::Ability::Patience);
	_uiPatience->setX(CENTER_X);
	_uiPatience->setY(CENTER_Y + 10);

	_uiGreed = new UI(ImageName::UI::Ability::Greed);
	_uiGreed->setX(CENTER_X + _uiGreed->getWidth() + 100);
	_uiGreed->setY(CENTER_Y + 2);

	_imgAblityBtn[0] = FindImage(ImageName::UI::Ability::btnWrath);
	_imgAblityBtn[1] = FindImage(ImageName::UI::Ability::btnPatience);
	_imgAblityBtn[2] = FindImage(ImageName::UI::Ability::btnGreed);

	_rcBtn[0] = RectMakeCenter(_uiWrath->getX(), _uiWrath->getRect().bottom - 30, _imgAblityBtn[0]->getFrameWidth(), _imgAblityBtn[0]->getFrameHeight());
	_rcBtn[1] = RectMakeCenter(_uiPatience->getX(), _uiPatience->getRect().bottom - 30, _imgAblityBtn[0]->getFrameWidth(), _imgAblityBtn[0]->getFrameHeight());
	_rcBtn[2] = RectMakeCenter(_uiGreed->getX(), _uiGreed->getRect().bottom - 30, _imgAblityBtn[0]->getFrameWidth(), _imgAblityBtn[0]->getFrameHeight());

}

void Ability::animation()
{
}

void Ability::clickBtn(int idx)
{
	if (PLAYERMANAGER->getAbility() < 1) return;
	switch (idx)
	{
	case 0:
		PLAYERMANAGER->wrathUp();
		break;
	case 1:
		PLAYERMANAGER->patienceUp();
		break;
	case 2:
		PLAYERMANAGER->greeUp();
		break;
	default:
		break;
	}
	SOUNDMANAGER->play(SoundName::Ability_Up, _sound);
	OBJECTMANAGER->addEffect(ImageName::UI::Ability::AbilityFX, _rcBtn[idx].left + 27, _rcBtn[idx].top + 27, 255, ObjectEnum::OBJ_TYPE::EFFECT_FRONT, TRUE);
}
