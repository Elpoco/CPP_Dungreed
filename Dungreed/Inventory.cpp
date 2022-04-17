#include "Stdafx.h"
#include "Inventory.h"

#include "Item.h"
#include "Button.h"

using namespace InventorySet;

Inventory::Inventory()
	: _isOpen(FALSE)
	, _isSawp(FALSE)
	, _isHover(FALSE)
	, _swapTick(10)
	, _equipIdx(0)
	, _clickCell(CLICK_NONE)
{
}

Inventory::~Inventory()
{
}

HRESULT Inventory::init()
{
	settingUI();

	//for (int i = INVEN_0; i < INVEN_CNT; i++)
	//{
	//	if (i > INVEN_5)
	//	{
	//		_arrItems[i] = NULL;
	//		continue;
	//	}
	//	if (i < INVEN_3)
	//	{
	//		_arrItems[i] = ITEMMANAGER->getItem(Code::ITEM::SHOT_SWORD);
	//	}
	//	else
	//	{
	//		_arrItems[i] = ITEMMANAGER->getItem(Code::ITEM::COLT);
	//	}
	//	OBJECTMANAGER->addObject(ObjectEnum::TYPE::ITEM_FRONT, _arrItems[i]);
	//}
	//sortItem();

	_arrItems[WEAPON_0] = ITEMMANAGER->getItem(Code::ITEM::SHOT_SWORD);
	_arrItems[WEAPON_0]->equip();
	OBJECTMANAGER->addItem(_arrItems[WEAPON_0]);

	return S_OK;
}

void Inventory::release()
{
}

void Inventory::update()
{
	if (IsOnceKeyDown(KEY::INVENTORY)) toggleInventory();
	if (IsOnceKeyDown(KEY::CHANGE_EQUIP)) swapEquip();

	if (_isSawp)
	{
		if (--_swapTick >= 0)
		{
			int dir = _swapTick >= 5 ? 1 : -1;

			_equipBase->setX(_equipBase->getX() + dir);
			_equipBase->setY(_equipBase->getY() - dir);

			_equipBaseBack->setX(_equipBaseBack->getX() - dir);
			_equipBaseBack->setY(_equipBaseBack->getY() + dir);
		}
		else
		{
			_isSawp = FALSE;
			_swapTick = 10;
		}
	}

	if (!_isOpen) return;

	hoverSlot();

	if (IsOnceKeyDown(KEY::CLICK_L)) onClick();
	if (IsStayKeyDown(KEY::CLICK_L)) dragItem();
	if (IsOnceKeyUp(KEY::CLICK_L))   offClick();
	if (IsOnceKeyDown(KEY::ESC))     toggleInventory();
}

void Inventory::render(HDC hdc)
{
	renderEquipBase(hdc);

	if (!_isOpen) return;
	renderInventoryItem(hdc);

	if (_isHover)
	{
		_imgHover->render(hdc, _rcHover.left, _rcHover.top);
	}
}

void Inventory::settingUI()
{
	UI* invenBase = new UI(ImageName::UI::Inventory::Base);
	invenBase->setX(WINSIZE_X - invenBase->getWidth() / 2);
	invenBase->setY(CENTER_Y);
	_vUI.push_back(invenBase);
	OBJECTMANAGER->addUI(invenBase);

	RECT rcbase = invenBase->getRect();
	float baseX = invenBase->getX();
	float baseY = invenBase->getY();

	// 닫기 버튼
	Button* btnClose = new Button(ImageName::UI::Inventory::exitBtn);
	btnClose->setX(rcbase.left - btnClose->getWidth() / 2);
	btnClose->setY(CENTER_Y - 220);
	_rcClose = btnClose->getRect();
	_vUI.push_back(btnClose);
	OBJECTMANAGER->addButton(btnClose);

	// 장착슬롯
	_equipSlot[0] = new UI(ImageName::UI::Inventory::EquipSlot1On);
	_equipSlot[0]->setX(baseX - 75);
	_equipSlot[0]->setY(rcbase.top + 125);

	_equipSlot[1] = new UI(ImageName::UI::Inventory::EquipSlot2On);
	_equipSlot[1]->setX(baseX + 87);
	_equipSlot[1]->setY(rcbase.top + 125);

	for (int i = 0; i < 2; i++)
	{
		_equipSlot[i]->hide();
		OBJECTMANAGER->addUI(_equipSlot[i]);

		int x = _equipSlot[i]->getX();
		int y = _equipSlot[i]->getY() + 9;
		
		// 장착 무기
		_ptInven[i] = PointMake(x - 33, y);
		// 장착 방어구
		_ptInven[2 + i] = PointMake(x + 33, y);
	}

	// 악세칸
	for (int i = ACC_0; i < ACC_CNT; i++)
	{
		int x = baseX - 86;
		int y = baseY - 62;
		_ptInven[i] = PointMake(x + (i - ACC_0) * 61, y);
	}

	// 장비칸
	for (int i = INVEN_0; i < INVEN_CNT; i++)
	{
		UI* inven = new UI(ImageName::UI::Inventory::Cell);
		int x = (i - INVEN_0) % 5;
		int y = (i - INVEN_0) / 5;

		_ptInven[i].x = 61 + invenBase->getRect().left + x * 65;
		_ptInven[i].y = 25 + CENTER_Y + y * 65;

		inven->setX(_ptInven[i].x);
		inven->setY(_ptInven[i].y);

		_vUI.push_back(inven);
		OBJECTMANAGER->addUI(inven);
	}

	for (int i = 0; i < INVEN_CNT; i++)
	{
		_rcInven[i] = RectMakeCenter(
			_ptInven[i].x,
			_ptInven[i].y,
			57,
			57
		);
	}

	for (auto ui : _vUI)
	{
		ui->hide();
	}

	// 우측하단 장착 장비
	_equipBase = new UI(ImageName::UI::Inventory::equipBase);
	_equipBase->setX(WINSIZE_X - _equipBase->getWidth() / 2 - 20);
	_equipBase->setY(WINSIZE_Y - _equipBase->getHeight() / 2 - 10);
	_rcEquipBase = _equipBase->getRect();

	_equipBaseBack = new UI(ImageName::UI::Inventory::equipBase);
	_equipBaseBack->setX(WINSIZE_X - _equipBaseBack->getWidth() / 2 - 10);
	_equipBaseBack->setY(WINSIZE_Y - _equipBaseBack->getHeight() / 2 - 20);

	OBJECTMANAGER->addObject(ObjectEnum::TYPE::UI, _equipBaseBack);
	OBJECTMANAGER->addObject(ObjectEnum::TYPE::UI, _equipBase);

	// 마우스 오버 테두리
	_imgHover = FindImage(ImageName::UI::Inventory::on);
	_imgInvenHover = FindImage(ImageName::UI::Inventory::Cell_On);
}

void Inventory::toggleInventory()
{
	_isOpen = !_isOpen;
	if (_isOpen)
	{
		UIMANAGER->setCursorType(UIEnum::CURSOR_TYPE::NORMAL);
		SOUNDMANAGER->play(SoundName::invenOpen, _sound);
		for (auto ui : _vUI)
		{
			if (ui) ui->show();
		}
		_equipSlot[_equipIdx]->show();
	}
	else
	{
		UIMANAGER->setCursorType(UIEnum::CURSOR_TYPE::TARGET);
		_clickCell = CLICK_NONE;
		for (auto ui : _vUI)
		{
			if(ui) ui->hide();
		}
		_equipSlot[_equipIdx]->hide();
	}
}

void Inventory::onClick()
{
	for (int i = 0; i < INVEN_CNT; i++)
	{
		if (MouseInRect(_rcInven[i]))
		{
			_clickCell = i;
			if(_arrItems[i]) SOUNDMANAGER->play(SoundName::Item::PickUpItem, _sound);
		}
	}
}

void Inventory::offClick()
{
	for (int i = 0; i < INVEN_CNT; i++)
	{
		if (MouseInRect(_rcInven[i]))
		{
			if(_arrItems[_clickCell]) SOUNDMANAGER->play(SoundName::Item::PickUpItem, _sound);
	
			// 놓을때 아이템이 있는경우
			if (_arrItems[i])
			{
				Item* preItem = _arrItems[i];
				_arrItems[i] = _arrItems[_clickCell];
				_arrItems[_clickCell] = preItem;
				if (i < EQUIP_CNT) // 장착 칸일경우
				{
					preItem->unequip();
					if (_equipIdx == i)
					{
						_arrItems[i]->equip();
						_arrItems[i]->update();
					}
				}
			}
			else
			{
				_arrItems[i] = _arrItems[_clickCell];
				_arrItems[_clickCell] = NULL;
				if (i < EQUIP_CNT)
				{
					if (_equipIdx == i)
					{
						_arrItems[i]->equip();
						_arrItems[i]->update();
					}
				}
			}
			break;
		}
	}
	
	sortItem();
	
	_clickCell = CLICK_NONE;

	if (MouseInRect(_rcClose)) toggleInventory();
}

void Inventory::sortItem()
{
	for (int i = 0; i < INVEN_CNT; i++)
	{
		if (!_arrItems[i]) continue;
	
		_arrItems[i]->setX(_ptInven[i].x);
		_arrItems[i]->setY(_ptInven[i].y);
	}
}

void Inventory::dragItem()
{
	if (_clickCell == CLICK_NONE || !_arrItems[_clickCell]) return;
	_arrItems[_clickCell]->setX(_ptMouse.x);
	_arrItems[_clickCell]->setY(_ptMouse.y);
}

void Inventory::hoverSlot()
{
	_isHover = FALSE;
	for (int i = 0; i < INVEN_CNT; i++)
	{
		if (MouseInRect(_rcInven[i]))
		{
			_isHover = TRUE;
			_rcHover = _rcInven[i];
			return;
		}
	}
}

void Inventory::swapEquip()
{
	SOUNDMANAGER->play(SoundName::swapEquip, _sound);
	_isSawp = TRUE;

	if (_arrItems[_equipIdx])
	{
		_arrItems[_equipIdx]->unequip();
	}
	_equipSlot[_equipIdx]->hide();
	
	_equipIdx = !_equipIdx;
	
	if (_arrItems[_equipIdx])
	{
		_arrItems[_equipIdx]->equip();
		_arrItems[_equipIdx]->update();
	}
	
	if (!_isOpen) return;
	_equipSlot[_equipIdx]->show();
}

void Inventory::renderEquipBase(HDC hdc)
{
	if (!_arrItems[_equipIdx]) return;
	
	ImageBase* img = _arrItems[_equipIdx]->getImage();
	
	img->frameRender(
		hdc,
		_equipBase->getX() - img->getFrameWidth() / 2,
		_equipBase->getY() - img->getFrameHeight() / 2,
		0, 
		0
	);
}

void Inventory::renderInventoryItem(HDC hdc)
{
	ImageBase* img;
	
	for (int i = 0; i < INVEN_CNT; i++)
	{
		int equip = _equipIdx == i ? 1 : 0; // 장착중인 장비는 살짝 올라감

		if (_arrItems[i])
		{
			img = _arrItems[i]->getImage();
			if (!img) continue;

			if (_clickCell == i)
			{
				img->frameRender(
					hdc,
					_ptMouse.x - img->getFrameWidth() / 2,
					_ptMouse.y - img->getFrameHeight() / 2,
					0,
					0
				);
			}
			else
			{
				img->frameRender(
					hdc,
					_ptInven[i].x - img->getFrameWidth() / 2,
					_ptInven[i].y - img->getFrameHeight() / 2 - equip,
					0,
					0
				);
			}
		}
	}
}

BOOL Inventory::pickUpItem(Code::ITEM code)
{
	for (int i = INVEN_0; i < INVEN_CNT; i++)
	{
		if (!_arrItems[i])
		{
			_arrItems[i] = ITEMMANAGER->getItem(code);
			OBJECTMANAGER->addItem(_arrItems[i]);
			return TRUE;
		}
	}
	return FALSE;
}
