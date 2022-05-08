#include "Stdafx.h"
#include "FoodShop.h"

using namespace FoodShopSet;

FoodShop::FoodShop()
{
}

FoodShop::~FoodShop()
{
}

HRESULT FoodShop::init()
{
	UI::init();

	initUI();

	return S_OK;
}

void FoodShop::release()
{
	UI::release();
}

void FoodShop::update()
{
	if (!_isShow) return;
	UI::update();
	animation();

	if (MouseInRect(_rcExitBtn))
	{
		if (IsOnceKeyUp(KEY::CLICK_L)) UIMANAGER->offUI();
	}

	clickEvent();
}

void FoodShop::render(HDC hdc)
{
	if (!_isShow) return;
	UI::render(hdc);

	_imgBack->render(hdc, 0, 0);
	_imgTable->frameRender(hdc, _uiBase3->getRect().left + 1, _uiBase3->getRect().top + 1, _tableFrame.x, 0);
	_uiLabel->render(hdc);
	_imgButton->frameRender(hdc, _rcExitBtn.left, _rcExitBtn.top, 0, MouseInRect(_rcExitBtn));
	_uiBase0->render(hdc);
	_uiBase3->render(hdc);
	_uiRect->render(hdc);
	_uiCoin->render(hdc);
	_uiEsc->render(hdc);
	FONTMANAGER->drawNumber(hdc, _uiCoin->getRect().left - 5, _uiCoin->getRect().top + 1, 23, 0, PLAYERMANAGER->getCoinChar(), ColorSet::YELLOW, DIR::RIGHT);
	FONTMANAGER->drawString(hdc, _uiEsc->getRect().right + 3, _uiEsc->getY() - 13, 25, FW_BOLD, " 나가기", ColorSet::WHITE);

	for (int i = 0; i < FOOD_CNT; i++)
	{
		if (_food[i].isSell)
		{
			IMAGEMANAGER->render(ImageName::UI::NPC::RestaurantMenuSell, hdc, _uiMenu[i]->getRect().left, _uiMenu[i]->getRect().top);
			continue;
		}

		if (MouseInRect(_uiMenu[i]->getRect()))
		{
			_uiMenuSelect->setX(_uiMenu[i]->getX());
			_uiMenuSelect->setY(_uiMenu[i]->getY());
			_uiMenuSelect->render(hdc);
			_food[i].img->alphaRender(hdc,
				_uiBase3->getX() - _food[i].img->getWidth() * 0.5f,
				_uiBase3->getY() - _food[i].img->getHeight() * 0.5f,
				255
			);
		}
		else
		{
			_uiMenu[i]->render(hdc);
		}

		SIZE size = FONTMANAGER->drawString(hdc, _uiMenu[i]->getRect().left + 10, _uiMenu[i]->getRect().top + 3, 30, 0, _food[i].name.c_str(), ColorSet::FOOD_NAME);
		if (_food[i].recovery == 0)
		{
			SIZE size2 = FONTMANAGER->drawNumber(hdc, _uiMenu[i]->getRect().left + 10, _uiMenu[i]->getRect().top + 3 + size.cy, 17, 0, ("+" + to_string(_food[i].power)).c_str(), ColorSet::GREEN);
			FONTMANAGER->drawString(hdc, _uiMenu[i]->getRect().left + 10 + size2.cx, _uiMenu[i]->getRect().top + 2 + size.cy, 17, FW_BOLD, " 위력", ColorSet::WHITE);
		}
		else
		{
			SIZE size2 = FONTMANAGER->drawNumber(hdc, _uiMenu[i]->getRect().left + 10, _uiMenu[i]->getRect().top + 3 + size.cy, 17, 0, ("+" + to_string(_food[i].recovery)).c_str(), ColorSet::GREEN);
			FONTMANAGER->drawString(hdc, _uiMenu[i]->getRect().left + 10 + size2.cx, _uiMenu[i]->getRect().top + 2 + size.cy, 17, FW_BOLD, " 회복", ColorSet::WHITE);
		}
		FONTMANAGER->drawNumber(hdc, _uiMenu[i]->getRect().right - 32, _uiMenu[i]->getRect().bottom - 24, 17, 0, to_string(_food[i].price).c_str(), ColorSet::WHITE, DIR::RIGHT);
	}

}

void FoodShop::show()
{
	_isShow = TRUE;
	SOUNDMANAGER->pause(SoundName::IceDungeon);
	SOUNDMANAGER->play(SoundName::Foodshop, _sound);
}

void FoodShop::hide()
{
	_isShow = FALSE;
	SOUNDMANAGER->stop(SoundName::Foodshop);
	SOUNDMANAGER->resume(SoundName::IceDungeon);
}

void FoodShop::initUI()
{
	_imgBack = FindImage(ImageName::ChangeScene);
	_imgTable = FindImage(ImageName::UI::NPC::RestaurantTable);
	_imgButton = FindImage(ImageName::UI::Button::Exit);

	_tableFrame.maxFrameX = _imgTable->getMaxFrameX();

	_uiLabel = new UI(ImageName::UI::NPC::FoodShopLabel);
	_uiLabel->setX(CENTER_X);
	_uiLabel->setY(_uiLabel->getHeight() * 0.5f);

	_uiBase0 = new UI(ImageName::UI::NPC::Base_0);
	_uiBase0->setX(CENTER_X - _uiBase0->getWidth() * 0.5f - 135);
	_uiBase0->setY(_uiLabel->getHeight() + _uiBase0->getHeight() * 0.5f + 10);

	_uiBase3 = new UI(ImageName::UI::NPC::Base_3);
	_uiBase3->setX(CENTER_X + _uiBase3->getWidth() * 0.5f - 115);
	_uiBase3->setY(_uiLabel->getHeight() + _uiBase3->getHeight() * 0.5f + 10);

	_uiMenuSelect = new UI(ImageName::UI::NPC::RestaurantMenuSelected);

	_uiRect = new UI(ImageName::UI::NPC::RestaurantRect);
	_uiRect->setX(_uiBase3->getRect().right - _uiRect->getWidth() * 0.5f);
	_uiRect->setY(_uiBase3->getRect().bottom + _uiRect->getHeight() * 0.5f + 20);

	_uiCoin = new UI(ImageName::UI::NPC::GoldCoin);
	_uiCoin->setX(_uiRect->getRect().right - 23);
	_uiCoin->setY(_uiRect->getY());

	_uiEsc = new UI(ImageName::UI::Keyboard::ESC);
	_uiEsc->setX(_uiRect->getRect().left - 100);
	_uiEsc->setY(_uiRect->getY());

	int menuTop = _uiBase0->getRect().top + 55;
	for (int i = 0; i < FOOD_CNT; i++)
	{
		_uiMenu[i] = new  UI(ImageName::UI::NPC::RestaurantMenu);
		_uiMenu[i]->setX(_uiBase0->getX());
		_uiMenu[i]->setY(menuTop + (_uiMenu[i]->getHeight() + 15) * i);
	}

	_rcExitBtn = RectMakeCenter(
		_uiLabel->getRect().right - _imgButton->getFrameWidth() + 15,
		_uiLabel->getY(),
		_imgButton->getFrameWidth(),
		_imgButton->getFrameHeight()
	);

	_food[0].img = FindImage(ImageName::UI::FOOD::Bread);
	_food[0].name = "빵";
	_food[0].price = 100;
	_food[0].recovery = 10;

	_food[1].img = FindImage(ImageName::UI::FOOD::FriedEgg);
	_food[1].name = "계란 프라이";
	_food[1].price = 200;
	_food[1].recovery = 15;

	_food[2].img = FindImage(ImageName::UI::FOOD::GrilledMushroom);
	_food[2].name = "구운 버섯";
	_food[2].price = 300;
	_food[2].recovery = 20;

	_food[3].img = FindImage(ImageName::UI::FOOD::TamatoSoup);
	_food[3].name = "토마토수프";
	_food[3].price = 400;
	_food[3].recovery = 25;

	_food[4].img = FindImage(ImageName::UI::FOOD::OnionSoup);
	_food[4].name = "양파 수프";
	_food[4].price = 500;
	_food[4].recovery = 30;


	_food[5].img = FindImage(ImageName::UI::FOOD::PeaSoup);
	_food[5].name = "완두콩 수프";
	_food[5].price = 500;
	_food[5].power = 1;

	_food[6].img = FindImage(ImageName::UI::FOOD::VegetableSalsaSoup);
	_food[6].name = "야채 살사 수프";
	_food[6].price = 600;
	_food[6].power = 3;

	_food[7].img = FindImage(ImageName::UI::FOOD::Lemonade);
	_food[7].name = "레몬에이드";
	_food[7].price = 700;
	_food[7].power = 5;

	_food[8].img = FindImage(ImageName::UI::FOOD::DeluxeBurger);
	_food[8].name = "디럭스 버거";
	_food[8].price = 800;
	_food[8].power = 7;

	_food[9].img = FindImage(ImageName::UI::FOOD::ChocolateCookie);
	_food[9].name = "초콜릿 쿠키";
	_food[9].price = 900;
	_food[9].power = 10;

	for (int i = 0; i < TOTAL_FOOD; i++)
	{
		int idx = RND->getInt(TOTAL_FOOD);
		tagFood temp = _food[i];
		_food[i] = _food[idx];
		_food[idx] = temp;
	}
}

void FoodShop::animation()
{
	if (_tableFrame.cnt++ > _tableFrame.tick)
	{
		_tableFrame.cnt = 0;
		if (++_tableFrame.x > _tableFrame.maxFrameX) _tableFrame.x = 0;
	}
}

void FoodShop::clickEvent()
{
	for (int i = 0; i < FOOD_CNT; i++)
	{
		if (!_food[i].isSell && MouseInRect(_uiMenu[i]->getRect()) && IsOnceKeyUp(KEY::CLICK_L))
		{
			if (PLAYERMANAGER->getCoin() < _food[i].price) return;
			PLAYERMANAGER->useCoin(_food[i].price);
			PLAYERMANAGER->recovery(_food[i].recovery);
			PLAYERMANAGER->powerUp(_food[i].power);
			_food[i].isSell = TRUE;
			SOUNDMANAGER->play(SoundName::BuyFood, _sound);
		}
	}
}
