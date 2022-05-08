#include "Stdafx.h"
#include "ItemShop.h"

#include "Item.h"

using namespace ItemShopSet;

ItemShop::ItemShop()
	: _itemCnt(0)
	, _code(Code::NPC::SHOP)
{
}

ItemShop::ItemShop(Code::NPC code)
	: _itemCnt(0)
	, _code(code)
{
}

ItemShop::~ItemShop()
{
}

HRESULT ItemShop::init()
{
	UI::init();

	initUI();

	suffleItem();

	return S_OK;
}

void ItemShop::release()
{
	UI::release();
}

void ItemShop::update()
{
	UI::update();
	if (!_isShow) return;

	hoverImg();

	if (MouseInRect(_uiBase->getRect())) clickEvent();
	if (IsOnceKeyDown(KEY::RELOAD)) suffleItem();
}

void ItemShop::render(HDC hdc)
{
	UI::render(hdc);
	if (!_isShow) return;

	_uiBase->render(hdc);
	renderItemSlot(hdc);
}

void ItemShop::show()
{
	UIMANAGER->toggleInventory();
	_isShow = TRUE;
}

void ItemShop::initUI()
{
	if (_code == Code::NPC::SHOP)
	{
		_uiBase = new UI(ImageName::UI::NPC::ShopBase);
	}
	else
	{
		_uiBase = new UI(ImageName::UI::NPC::DungeonShopBase);
	}
	_uiBase->setX(_uiBase->getWidth() * 0.5f);
	_uiBase->setY(CENTER_Y);
	
	ImageBase* tmpImg = FindImage(ImageName::UI::NPC::ShopItem);
	int imgHeight = tmpImg->getHeight();
	int top = _uiBase->getRect().top + 95 + imgHeight * 0.5f;
	int imgPos = imgHeight + 3;
	
	for (int i = 0; i < MAX_ITEM_CNT; i++)
	{
		UI* itemSlot = new UI(ImageName::UI::NPC::ShopItem);
		itemSlot->setX(_uiBase->getWidth() * 0.5f - 3);
		itemSlot->setY(top + i * imgPos);
		_arrUI[i] = itemSlot;
		_rcSlots[i] = itemSlot->getRect();
	}
	
	_uiSelect = new UI(ImageName::UI::NPC::ShopItem_Selected);
	_uiSelect->hide();
}

void ItemShop::renderItemSlot(HDC hdc)
{
	for (int i = 0; i < _itemCnt; i++)
	{
		_arrUI[i]->render(hdc);
	}

	_uiSelect->render(hdc);

	ImageBase* img;
	ITEM_INFO info;
	for (int i = 0; i < _itemCnt; i++)
	{
		// 아이템 이미지
		img = _vItems[i]->getImage();
		img->frameRender(
			hdc,
			_rcSlots[i].left - img->getFrameWidth() * 0.5f + 33,
			_arrUI[i]->getY() - img->getFrameHeight() * 0.5f,
			0, 
			0
		);

		// 아이템 정보
		info = _vItems[i]->getInfo();
		DWORD itemColor = ColorSet::WHITE;
		switch (info.grade)
		{
		case Code::ITEM_GRADE::UNCOMMON:
			itemColor = ColorSet::UNCOMMON;
			break;
		case Code::ITEM_GRADE::RARE:
			itemColor = ColorSet::RARE;
			break;
		case Code::ITEM_GRADE::LEGEND:
			itemColor = ColorSet::LEGEND;
			break;
		default:
			break;
		}

		FONTMANAGER->drawString(hdc, _rcSlots[i].left + 75, _rcSlots[i].top + 5, 26, FW_BOLD, info.name.c_str(), itemColor);
		FONTMANAGER->drawNumber(hdc, _rcSlots[i].right - 45, _rcSlots[i].bottom - 28, 19, 0, to_string(info.price).c_str(), ColorSet::WHITE, DIR::RIGHT);
	}
}

void ItemShop::hoverImg()
{
	_uiSelect->hide();
	for (int i = 0; i < _itemCnt; i++)
	{
		if (MouseInRect(_rcSlots[i]))
		{
			_uiSelect->setX(_arrUI[i]->getX());
			_uiSelect->setY(_arrUI[i]->getY());
			_uiSelect->show();
			_vItems[i]->itemHover();
			break;
		}
	}
}

void ItemShop::clickEvent()
{
	if (IsOnceKeyUp(KEY::CLICK_L)) clickItem();
}

void ItemShop::clickItem()
{
	for (int i = 0; i < _itemCnt; i++)
	{
		if (MouseInRect(_rcSlots[i]))
		{
			if (_vItems[i])
			{
				if (PLAYERMANAGER->getCoin() < _vItems[i]->getInfo().price) return;
				if (ITEMMANAGER->giveItem(_vItems[i]))
				{
					PLAYERMANAGER->useCoin(_vItems[i]->getInfo().price);
					_vItems.erase(_vItems.begin() + i);
					_itemCnt--;
					SOUNDMANAGER->play(SoundName::Item::getItem, _sound);
					return;
				}
			}
		}
	}
}

void ItemShop::suffleItem()
{
	_itemCnt = 0;
	_vItems.clear();
	int arrCode[(int)Code::ITEM::ITEM_CNT];
	for (int i = 0; i < (int)Code::ITEM::ITEM_CNT; i++)
	{
		arrCode[i] = i;
	}

	for (int i = 0; i < (int)Code::ITEM::ITEM_CNT; i++)
	{
		int idx = RND->getInt((int)Code::ITEM::ITEM_CNT);
		int temp = arrCode[i];
		arrCode[i] = arrCode[idx];
		arrCode[idx] = temp;
	}

	for (int i = 0; i < MAX_ITEM_CNT; i++)
	{
		_vItems.push_back(ITEMMANAGER->getItem((Code::ITEM)arrCode[i]));
		_itemCnt++;
	}
}
