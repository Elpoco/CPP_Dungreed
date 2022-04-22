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

	return S_OK;
}

void Inventory::release()
{
}

void Inventory::update()
{
	if (IsOnceKeyDown(KEY::CHANGE_EQUIP)) swapEquipSlot();

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
	if (IsOnceKeyUp(KEY::CLICK_L))   offClick();
	if (IsOnceKeyUp(KEY::CLICK_R))	 equipClick();
}

void Inventory::render(HDC hdc)
{
	renderEquipBase(hdc);

	if (!_isOpen) return;
	
	if (_isHover) _imgHover->render(hdc, _rcHover.left, _rcHover.top);
	

	renderInventoryItem(hdc);
}

void Inventory::settingUI()
{
	// 우측하단 장착 장비
	_equipBase = new UI(ImageName::UI::Inventory::equipBase);
	_equipBase->setX(WINSIZE_X - _equipBase->getWidth() * 0.5f - 20);
	_equipBase->setY(WINSIZE_Y - _equipBase->getHeight() * 0.5f - 10);
	_rcEquipBase = _equipBase->getRect();

	_equipBaseBack = new UI(ImageName::UI::Inventory::equipBase);
	_equipBaseBack->setX(WINSIZE_X - _equipBaseBack->getWidth() * 0.5f - 10);
	_equipBaseBack->setY(WINSIZE_Y - _equipBaseBack->getHeight() * 0.5f - 20);

	OBJECTMANAGER->addObject(ObjectEnum::OBJ_TYPE::UI, _equipBaseBack);
	OBJECTMANAGER->addObject(ObjectEnum::OBJ_TYPE::UI, _equipBase);

	// 인벤토리 베이스
	UI* invenBase = new UI(ImageName::UI::Inventory::Base);
	invenBase->setX(WINSIZE_X - invenBase->getWidth() * 0.5f);
	invenBase->setY(CENTER_Y);
	_vUI.push_back(invenBase);
	OBJECTMANAGER->addUI(invenBase);

	RECT rcbase = invenBase->getRect();
	float baseX = invenBase->getX();
	float baseY = invenBase->getY();

	// 닫기 버튼
	Button* btnClose = new Button(ImageName::UI::Inventory::exitBtn);
	btnClose->setX(rcbase.left - btnClose->getWidth() * 0.5f);
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
		_arrSlot[i].pt = PointMake(x - 33, y);
		// 장착 방어구
		_arrSlot[2 + i].pt = PointMake(x + 33, y);
	}

	// 악세칸
	for (int i = ACC_0; i < ACC_CNT; i++)
	{
		int x = baseX - 86;
		int y = baseY - 62;
		_arrSlot[i].pt = PointMake(x + (i - ACC_0) * 61, y);
	}

	// 장비칸
	for (int i = INVEN_0; i < INVEN_CNT; i++)
	{
		UI* inven = new UI(ImageName::UI::Inventory::Cell);
		int x = (i - INVEN_0) % 5;
		int y = (i - INVEN_0) / 5;

		_arrSlot[i].pt.x = 61 + invenBase->getRect().left + x * 65;
		_arrSlot[i].pt.y = 25 + CENTER_Y + y * 65;

		inven->setX(_arrSlot[i].pt.x);
		inven->setY(_arrSlot[i].pt.y);

		_vUI.push_back(inven);
		OBJECTMANAGER->addUI(inven);
	}

	// 인벤 칸들 위치 렉트
	for (int i = 0; i < INVEN_CNT; i++)
	{
		_arrSlot[i].rc = RectMakeCenter(
			_arrSlot[i].pt.x,
			_arrSlot[i].pt.y,
			57,
			57
		);
	}

	for (auto ui : _vUI)
	{
		ui->hide();
	}

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

int Inventory::checkCell()
{
	// 마우스가 올라가있는 칸의 인덱스 구하기
	int idx = CLICK_NONE;

	for (int i = 0; i < INVEN_CNT; i++)
	{
		if (MouseInRect(_arrSlot[i].rc)) 
			idx = i;
	}

	return idx;
}

void Inventory::onClick()
{
	_clickCell = checkCell();

	// 아이템이 없으면 클릭 없애기
	if (!_arrSlot[_clickCell].item)
	{
		_clickCell = CLICK_NONE;
		return;
	}
	
	SOUNDMANAGER->play(SoundName::Item::PickUpItem, _sound);
}

void Inventory::offClick()
{
	if (MouseInRect(_rcClose)) toggleInventory();

	if (_clickCell == CLICK_NONE) return;

	for (int i = 0; i < INVEN_CNT; i++)
	{
		if (MouseInRect(_arrSlot[i].rc))
		{
			// 일단 끼던거 해제
			if (_arrSlot[WEAPON_0].item) _arrSlot[WEAPON_0].item->unequip();
			if (_arrSlot[WEAPON_1].item) _arrSlot[WEAPON_1].item->unequip();

			// 놓을때 아이템이 있는경우
			if (_arrSlot[i].item)
			{
				SOUNDMANAGER->play(SoundName::Item::PickUpItem, _sound);

				Item* preItem = _arrSlot[i].item;
				_arrSlot[i].item = _arrSlot[_clickCell].item;
				_arrSlot[_clickCell].item = preItem;

				if(i < WEAPON_CNT) preItem->unequip();
			}
			else
			{
				// 장착칸일 경우
				if (i < EQUIP_CNT)
				{
					if (checkType(i, _arrSlot[_clickCell].item))
					{
						SOUNDMANAGER->play(SoundName::Item::Equip, _sound);
						_arrSlot[i].item = _arrSlot[_clickCell].item;
					}
				}
				else
				{
					SOUNDMANAGER->play(SoundName::Item::PickUpItem, _sound);
					_arrSlot[i].item = _arrSlot[_clickCell].item;
				}
				_arrSlot[_clickCell].item = NULL;
			}

			// 장착 슬롯 아이템 장착
			if (_arrSlot[_equipIdx].item) _arrSlot[_equipIdx].item->equip();
			break;
		}
	}
	
	_clickCell = CLICK_NONE;
}

void Inventory::hoverSlot()
{
	_isHover = FALSE;
	for (int i = 0; i < INVEN_CNT; i++)
	{
		if (MouseInRect(_arrSlot[i].rc))
		{
			_isHover = TRUE;
			_rcHover = _arrSlot[i].rc;
			return;
		}
	}
}

void Inventory::equipClick()
{
	_clickCell = checkCell();
	if (_clickCell == CLICK_NONE) return;
	if (!_arrSlot[_clickCell].item) return;

	switch (_clickCell)
	{
	case Inventory::WEAPON_0: case Inventory::WEAPON_1:
	case Inventory::ARMOR_0: case Inventory::ARMOR_1:
	case Inventory::ACC_0: case Inventory::ACC_1:
	case Inventory::ACC_2: case Inventory::ACC_3:
		// 해제
		for (int i = INVEN_0; i < INVEN_CNT; i++)
		{
			if (_arrSlot[i].item) continue;

			SOUNDMANAGER->play(SoundName::Item::PickUpItem, _sound);
			_arrSlot[i].item = _arrSlot[_clickCell].item;
			_arrSlot[_clickCell].item = NULL;
			_arrSlot[i].item->unequip();
			break;
		}
		break;
	default:
		// 장착
		for (int i = WEAPON_0; i < ACC_CNT; i++)
		{
			if (_arrSlot[i].item) continue;
			if (!checkType(i, _arrSlot[_clickCell].item)) continue;
			SOUNDMANAGER->play(SoundName::Item::Equip, _sound);
			_arrSlot[i].item = _arrSlot[_clickCell].item;
			_arrSlot[_clickCell].item = NULL;
			if(i == _equipIdx) _arrSlot[i].item->equip();
			break;
		}
		break;
	}

	_clickCell = CLICK_NONE;
}

BOOL Inventory::checkType(int cellIdx, Item* item)
{
	BOOL res = FALSE;

	switch (item->getItemType())
	{
	case Code::ITEM_TYPE::WEAPON:
		res = cellIdx == WEAPON_0 || cellIdx == WEAPON_1;
		break;
	case Code::ITEM_TYPE::ARMOR:
		res = cellIdx == ARMOR_0 || cellIdx == ARMOR_1;
		break;
	case Code::ITEM_TYPE::ACCESSORY:
		res = ACC_0 <= cellIdx && cellIdx <= ACC_3;
		break;
	default:
		break;
	}
	return res;
}

void Inventory::swapEquipSlot()
{
	SOUNDMANAGER->play(SoundName::swapEquip, _sound);
	_isSawp = TRUE;

	if (_arrSlot[_equipIdx].item)
	{
		_arrSlot[_equipIdx].item->unequip();
	}
	_equipSlot[_equipIdx]->hide();
	
	_equipIdx = !_equipIdx;
	
	if (_arrSlot[_equipIdx].item)
	{
		_arrSlot[_equipIdx].item->equip();
	}
	
	if (!_isOpen) return;
	_equipSlot[_equipIdx]->show();
}

void Inventory::renderEquipBase(HDC hdc)
{
	if (!_arrSlot[_equipIdx].item) return;
	
	ImageBase* img = _arrSlot[_equipIdx].item->getImage();
	
	img->frameRender(
		hdc,
		_equipBase->getX() - img->getFrameWidth() * 0.5f,
		_equipBase->getY() - img->getFrameHeight() * 0.5f,
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

		if (_arrSlot[i].item)
		{
			img = _arrSlot[i].item->getImage();
			if (!img) continue;

			// 선택한 아이템은 여기서 랜더 안함
			if (_clickCell == i)
			{
				continue;
			}
			else
			{
				img->frameRender(
					hdc,
					_arrSlot[i].pt.x - img->getFrameWidth() * 0.5f,
					_arrSlot[i].pt.y - img->getFrameHeight() * 0.5f - equip,
					0,
					0
				);
			}
		}
	}
	
	// 클릭한 아이템이 맨 위에 랜더 되게
	if (_clickCell != CLICK_NONE &&
		_arrSlot[_clickCell].item)
	{
		img = _arrSlot[_clickCell].item->getImage();
		img->frameRender(
			hdc,
			_ptMouse.x - img->getFrameWidth() * 0.5f,
			_ptMouse.y - img->getFrameHeight() * 0.5f,
			0,
			0
		);
	}
}

void Inventory::addItem(Item* item)
{
	for (int i = 0; i < INVEN_CNT; i++)
	{
		// 아이템이 있으면 넘어감
		if (_arrSlot[i].item) continue;
		if (i < EQUIP_CNT && !checkType(i, item)) continue;

		_arrSlot[i].item = item;
		OBJECTMANAGER->addItem(_arrSlot[i].item);

		if (i == _equipIdx) _arrSlot[i].item->equip();
		return;
	}
}
