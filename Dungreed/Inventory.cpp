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

	//_arrItems[WEAPON_0] = ITEMMANAGER->getItem(Code::ITEM::SHOT_SWORD);
	//_arrItems[WEAPON_0]->equip();
	//OBJECTMANAGER->addItem(_arrItems[WEAPON_0]);

	return S_OK;
}

void Inventory::release()
{
}

void Inventory::update()
{
	if (IsOnceKeyDown(KEY::INVENTORY)) toggleInventory();
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
	if (IsOnceKeyUp(KEY::CLICK_R))	 equipItem();
	if (IsOnceKeyDown(KEY::ESC))     toggleInventory();
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
	// �����ϴ� ���� ���
	_equipBase = new UI(ImageName::UI::Inventory::equipBase);
	_equipBase->setX(WINSIZE_X - _equipBase->getWidth() / 2 - 20);
	_equipBase->setY(WINSIZE_Y - _equipBase->getHeight() / 2 - 10);
	_rcEquipBase = _equipBase->getRect();

	_equipBaseBack = new UI(ImageName::UI::Inventory::equipBase);
	_equipBaseBack->setX(WINSIZE_X - _equipBaseBack->getWidth() / 2 - 10);
	_equipBaseBack->setY(WINSIZE_Y - _equipBaseBack->getHeight() / 2 - 20);

	OBJECTMANAGER->addObject(ObjectEnum::OBJ_TYPE::UI, _equipBaseBack);
	OBJECTMANAGER->addObject(ObjectEnum::OBJ_TYPE::UI, _equipBase);

	// �κ��丮 ���̽�
	UI* invenBase = new UI(ImageName::UI::Inventory::Base);
	invenBase->setX(WINSIZE_X - invenBase->getWidth() / 2);
	invenBase->setY(CENTER_Y);
	_vUI.push_back(invenBase);
	OBJECTMANAGER->addUI(invenBase);

	RECT rcbase = invenBase->getRect();
	float baseX = invenBase->getX();
	float baseY = invenBase->getY();

	// �ݱ� ��ư
	Button* btnClose = new Button(ImageName::UI::Inventory::exitBtn);
	btnClose->setX(rcbase.left - btnClose->getWidth() / 2);
	btnClose->setY(CENTER_Y - 220);
	_rcClose = btnClose->getRect();
	_vUI.push_back(btnClose);
	OBJECTMANAGER->addButton(btnClose);

	// ��������
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

		// ���� ����
		_arrSlot[i].pt = PointMake(x - 33, y);
		// ���� ��
		_arrSlot[2 + i].pt = PointMake(x + 33, y);
	}

	// �Ǽ�ĭ
	for (int i = ACC_0; i < ACC_CNT; i++)
	{
		int x = baseX - 86;
		int y = baseY - 62;
		_arrSlot[i].pt = PointMake(x + (i - ACC_0) * 61, y);
	}

	// ���ĭ
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

	// ���콺 ���� �׵θ�
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
		if (MouseInRect(_arrSlot[i].rc))
		{
			if (_arrSlot[i].item == NULL)
			{
				_clickCell = CLICK_NONE;
				return;
			}
			_clickCell = i;
			if(_arrSlot[i].item) SOUNDMANAGER->play(SoundName::Item::PickUpItem, _sound);
		}
	}
}

void Inventory::offClick()
{
	if (_clickCell == CLICK_NONE) return;

	for (int i = 0; i < INVEN_CNT; i++)
	{
		if (MouseInRect(_arrSlot[i].rc))
		{
			/*switch (_arrItems[_clickCell]->getItemType())
			{
			case Code::ITEM_TYPE::WEAPON:
				continue;
				break;
			default:
				break;
			}*/
			// �������� ������ ���� �߻�
			if(_arrSlot[_clickCell].item) SOUNDMANAGER->play(SoundName::Item::PickUpItem, _sound);
	
			// ������ �������� �ִ°��
			if (_arrSlot[i].item)
			{
				Item* preItem = _arrSlot[i].item;
				_arrSlot[i].item = _arrSlot[_clickCell].item;
				_arrSlot[_clickCell].item = preItem;
				if (i < EQUIP_CNT) // ���� ĭ�ϰ��
				{
					preItem->unequip();
					if (_equipIdx == i) // ������ ���¸�
					{
						_arrSlot[i].item->equip();
						_arrSlot[i].item->update();
					}
				}
			}
			else
			{
				_arrSlot[i].item = _arrSlot[_clickCell].item;
				if (i < EQUIP_CNT)
				{
					if(_clickCell < EQUIP_CNT) _arrSlot[_clickCell].item->unequip();

					if (_equipIdx == i)
					{
						_arrSlot[i].item->equip();
						_arrSlot[i].item->update();
					}
				}
				_arrSlot[_clickCell].item = NULL;
			}
			break;
		}
	}
	
	_clickCell = CLICK_NONE;

	if (MouseInRect(_rcClose)) toggleInventory();
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

void Inventory::equipItem()
{
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
		_arrSlot[_equipIdx].item->update();
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
		int equip = _equipIdx == i ? 1 : 0; // �������� ���� ��¦ �ö�

		if (_arrSlot[i].item)
		{
			img = _arrSlot[i].item->getImage();
			if (!img) continue;

			//if (_clickCell == i)
			//{
			//	continue;
			//}
			//else
			{
				img->frameRender(
					hdc,
					_arrSlot[i].pt.x - img->getFrameWidth() / 2,
					_arrSlot[i].pt.y - img->getFrameHeight() / 2 - equip,
					0,
					0
				);
			}
		}
	}
	
	// Ŭ���� �������� �� ���� ���� �ǰ�
	if (_clickCell != CLICK_NONE)
	{
		img = _arrSlot[_clickCell].item->getImage();
		img->frameRender(
			hdc,
			_ptMouse.x - img->getFrameWidth() / 2,
			_ptMouse.y - img->getFrameHeight() / 2,
			0,
			0
		);
	}
}

void Inventory::addItem(Item* item)
{
	for (int i = 0; i < INVEN_CNT; i++)
	{
		// �������� ������ �Ѿ
		if (_arrSlot[i].item) continue;

		_arrSlot[i].item = item;
		OBJECTMANAGER->addItem(_arrSlot[i].item);

		if (i == _equipIdx) _arrSlot[i].item->equip();
		return;
	}
}
