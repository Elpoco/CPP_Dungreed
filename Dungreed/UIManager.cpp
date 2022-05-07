#include "Stdafx.h"
#include "UIManager.h"

#include "UI.h"
#include "Cursor.h"
#include "Inventory.h"
#include "PlayerHpBar.h"
#include "MiniMap.h"
#include "WorldMap.h"
#include "ImageFont.h"
#include "ItemInfo.h"
#include "DropItemInfo.h"

UIManager::UIManager()
	: _isUI(FALSE)
	, _showMapInfo(FALSE)
	, _infoSpeed(0.0f)
{
}

UIManager::~UIManager()
{
}

HRESULT UIManager::init()
{
	_cursor = new Cursor;
	OBJECTMANAGER->addObject(ObjectEnum::OBJ_TYPE::CURSOR, _cursor);
	ShowCursor(false);

	initKeyboard();
	initReload();
	initItemInfo();
	initBossInfo();
	initMapInfo();

	return S_OK;
}

void UIManager::release()
{
}

void UIManager::update()
{
	updateKeyboard();
	updateReload();
	if (_showBossInfo) updateBossInfo();
	if (_showMapInfo) updateMapInfo();
	if (_isShowItemInfo) updateDropItemInfo();

	if (IsOnceKeyDown(KEY::INVENTORY)) toggleInventory();
	if (IsStayKeyDown(KEY::WORLD_MAP)) showWorldMap();
	if (IsOnceKeyUp(KEY::WORLD_MAP)) hideWorldMap();
	if (IsOnceKeyDown(KEY::ESC))
	{
		if (_inventory->isOpen())
		{
			toggleInventory();
		}
		_isUI = FALSE;
	}
}

void UIManager::render(HDC hdc)
{
}

void UIManager::setCursorType(UIEnum::CURSOR_TYPE cursorType)
{
	switch (cursorType)
	{
	case UIEnum::NONE:
		ShowCursor(true);
		break;
	case UIEnum::NORMAL:
		ShowCursor(false);
		break;
	case UIEnum::TARGET:
		ShowCursor(false);
		break;
	default:
		break;
	}
	_cursor->setCursor(cursorType);
}

void UIManager::initInventory()
{
	_inventory = new Inventory;
	OBJECTMANAGER->addUI(_inventory);
	ITEMMANAGER->setInventory(_inventory);
}

void UIManager::toggleInventory()
{
	if (!_inventory) return;

	if (_isUI)
	{
		_inventory->close();
		_isUI = FALSE;
	}
	else
	{
		_inventory->open();
		_isUI = TRUE;
	}
}

void UIManager::initPlayerHpBar(int* maxHp, int* curHp)
{
	OBJECTMANAGER->addUI(new PlayerHpBar(maxHp, curHp));
}

void UIManager::initMiniMap()
{
	_miniMap = new MiniMap;
	OBJECTMANAGER->addUI(_miniMap);
}

void UIManager::updateMiniMap()
{
	_miniMap->settingMiniMap();
}

void UIManager::enterDungeon()
{
	_miniMap->setDungeon(TRUE);
}

void UIManager::initWorldMap()
{
	_worldMap = new WorldMap;
	_worldMap->hide();
	_worldMap->setFree();
	OBJECTMANAGER->addObject(ObjectEnum::OBJ_TYPE::UI_FRONT, _worldMap);
}

void UIManager::showWorldMap()
{
	if (!_worldMap) return;

	_worldMap->show();
	_isUI = TRUE;
}

void UIManager::hideWorldMap()
{
	if (!_worldMap) return;

	_worldMap->hide();
	_isUI = FALSE;
}

void UIManager::initKeyboard()
{
	UI* ui;

	ui = new UI(ImageName::UI::Keyboard::F, 0, 0, FALSE, FALSE, TRUE);
	_mKey.insert(make_pair(KEY::F, ui));
	OBJECTMANAGER->addUI(ui);
	ui = new UI(ImageName::UI::Keyboard::ESC, 0, 0, FALSE, FALSE, TRUE);
	_mKey.insert(make_pair(KEY::ESC, ui));
	OBJECTMANAGER->addUI(ui);
}

void UIManager::showKeyboard(KEY key, float x, float top)
{
	auto pair = _mKey.find(key);
	if (!pair->second.key->isShow())
	{
		pair->second.isShow = TRUE;
		pair->second.key->show(x, top - pair->second.key->getHeight() * 0.5f);
	}
}

void UIManager::updateKeyboard()
{
	for (auto pair : _mKey)
	{
		if (pair.second.isShow)
		{
			pair.second.isShow = FALSE;
			pair.second.key->hide();
		}
	}
}

void UIManager::initReload()
{
	_isShowReload = FALSE;

	_uiReloadBar = new UI(ImageName::UI::Item::reloadBar, 0,0, FALSE, FALSE, TRUE);
	_uiReloadBase = new UI(ImageName::UI::Item::reloadBase, 0, 0, FALSE, FALSE, TRUE);

	OBJECTMANAGER->addUI(_uiReloadBar);
	OBJECTMANAGER->addUI(_uiReloadBase);
}

void UIManager::updateReload()
{
	if (!_isShowReload) return;

	_reloadX = OBJECTMANAGER->getPlayer()->getX();
	_reloadY = OBJECTMANAGER->getPlayer()->getY() - 45;
	_uiReloadBase->setX(_reloadX);
	_uiReloadBase->setY(_reloadY);
	_uiReloadBar->setX(_reloadX - 32 + 63 * ((TIMEMANAGER->getWorldTime() - _reloadStartTime) / _reloadTick));
	_uiReloadBar->setY(_reloadY);

	if (_reloadTick <= TIMEMANAGER->getWorldTime() - _reloadStartTime)
	{
		_isShowReload = FALSE;
		_uiReloadBase->hide();
		_uiReloadBar->hide();
		OBJECTMANAGER->addEffect(ImageName::UI::Item::reloadEffect, _reloadX, _reloadY);
	}
}

void UIManager::showReloadBar(float reloadTick)
{
	_reloadTick = reloadTick;
	_reloadStartTime = TIMEMANAGER->getWorldTime();
	_isShowReload = TRUE;
	_uiReloadBase->show();
	_uiReloadBar->show();
}

// ==============
// # 아이템 정보 #
// ==============

void UIManager::initItemInfo()
{
	_uiItemInfo = new ItemInfo;
	_uiItemInfo->setFree();
	_uiItemInfo->hide();
	OBJECTMANAGER->addObject(ObjectEnum::OBJ_TYPE::UI_FRONT, _uiItemInfo);

	_uiDropItemInfo = new DropItemInfo;
	_uiDropItemInfo->setFree();
	_uiDropItemInfo->hide();
	OBJECTMANAGER->addObject(ObjectEnum::OBJ_TYPE::UI_FRONT, _uiDropItemInfo);
}

void UIManager::showItemInfo(ITEM_INFO itemInfo)
{
	_uiItemInfo->setInfo(itemInfo);
	_uiItemInfo->show();
}

void UIManager::showDropItemInfo(ITEM_INFO itemInfo)
{
	_uiDropItemInfo->setInfo(itemInfo);
	_uiDropItemInfo->show();
	_itemInfoTime = TIMEMANAGER->getWorldTime();
	_isShowItemInfo = TRUE;
}

void UIManager::updateDropItemInfo()
{
	if (_itemInfoTime + 1.5f < TIMEMANAGER->getWorldTime())
	{
		_isShowItemInfo = FALSE;
		_uiDropItemInfo->hide();
	}
}

void UIManager::initBossInfo()
{
	_bossIntro = new UI(ImageName::BossIntro, CENTER_X, CENTER_Y);
	OBJECTMANAGER->addObject(ObjectEnum::OBJ_TYPE::UI_FRONT, _bossIntro);
	_bossIntro->setFree();
	_bossIntro->hide();

	_bossInfo = new ImageFont(140, 450, "TEST");
	OBJECTMANAGER->addObject(ObjectEnum::OBJ_TYPE::UI_FRONT, _bossInfo);
	_bossInfo->setFree();
	_bossInfo->hide();
}

void UIManager::showBossInfo(char* bossName)
{
	_showBossInfo = TRUE;
	_bossIntro->show();
	_bossInfo->show();
	_bossInfo->setString(bossName);
}

void UIManager::updateBossInfo()
{
	if (!CAMERAMANAGER->isCameraMove())
	{
		_showBossInfo = FALSE;
		_bossInfo->hide();
		_bossIntro->hide();
	}
}

void UIManager::initMapInfo()
{
	_mapInfo = new ImageFont(CENTER_X, 200, "TEST");
	OBJECTMANAGER->addObject(ObjectEnum::OBJ_TYPE::UI_FRONT, _mapInfo);
	_mapInfo->setFree();
	_mapInfo->hide();
}

void UIManager::showMapInfo(char* mapName)
{
	_showMapInfo = TRUE;
	_showInfoTime = 3;
	_showStartTime = TIMEMANAGER->getWorldTime();
	_mapInfo->show();
	_mapInfo->setString(mapName);
	_mapInfo->setX(-_mapInfo->getWidth());
	_infoSpeed = 18.0f;
	_isIn = TRUE;
}

void UIManager::updateMapInfo()
{
	int curX = _mapInfo->getX();

	_infoSpeed += _isIn ? -0.2f : 0.2f;

	if (curX < CENTER_X && _infoSpeed < 0 && _isIn)
	{
		_infoSpeed = 0.0f;
		if (_showStartTime + _showInfoTime < TIMEMANAGER->getWorldTime())
		{
			_infoSpeed = -9.0f;
			_isIn = FALSE;
		}
	}
	else
	{
		_mapInfo->setX(curX + _infoSpeed);
	}
}

