#include "Stdafx.h"
#include "Door.h"

using namespace DoorSet;

Door::Door(Direction::DIR dir, int tileX, int tileY, BOOL isOpen)
	: _dir(dir)
	, _tileX(tileX)
	, _tileY(tileY)
	, _isOpen(isOpen)
{
}

Door::~Door()
{
}

HRESULT Door::init()
{
	if (_dir == DIR::RIGHT)
	{
		_imgDoor = FindImage(ImageName::Dungeon::DoorRight);
	}
	else if (_dir == DIR::LEFT)
	{
		_imgDoor = FindImage(ImageName::Dungeon::DoorLeft);
	}
	else
	{
		_imgDoor = FindImage(ImageName::Dungeon::Door);
	}

	_frameInfo.maxFrameX = _imgDoor->getMaxFrameX();
	_frameInfo.width = _imgDoor->getFrameWidth();
	_frameInfo.height = _imgDoor->getFrameHeight();
	_frameInfo.endFrameX = FRAME_IDLE_E;
	_state = DOOR_STATE::CLOSE;

	_x = _tileX * TILE_SIZE;
	_y = _tileY * TILE_SIZE;

	_rc = RectMake(_x, _y, _frameInfo.width, _frameInfo.height);

	// 문열릴때 네모 이펙트
	_imgParticle[0] = FindImage(ImageName::Dungeon::sqaure1);
	_imgParticle[1] = FindImage(ImageName::Dungeon::sqaure2);
	_imgParticle[2] = FindImage(ImageName::Dungeon::sqaure3);
	_imgParticle[3] = FindImage(ImageName::Dungeon::sqaure4);
	_imgParticle[4] = FindImage(ImageName::Dungeon::sqaure5);

	SOUNDMANAGER->play(SoundName::Dungeon::DoorMove, _sound);

	return S_OK;
}

void Door::release()
{
}

void Door::update()
{
	animation();
	if (IsOnceKeyDown(KEY::F4)) openDoor();
}

void Door::render(HDC hdc)
{
	if (_isOpen)
	{
		for (int i = 0; i < PARTICLE_CNT; i++)
		{
			if (!_particle[i].isOn) continue;
			CAMERAMANAGER->render(
				hdc,
				_imgParticle[_particle[i].imgIdx],
				_particle[i].x,
				_particle[i].y,
				_particle[i].alpha
			);
		}
	}
	else
	{
		CAMERAMANAGER->frameRender(hdc, _imgDoor, _rc.left, _rc.top, _frameInfo.x, _frameInfo.y);
	}
}

void Door::collisionObject()
{
	if (_isOpen)
	{
		MAPMANAGER->chageRoom(_dir);
	}
	else
	{
		switch (_dir)
		{
		case Direction::LEFT:
			OBJECTMANAGER->getPlayer()->pushObject(DIR::LEFT, _rc.right);
			break;
		case Direction::TOP:
			OBJECTMANAGER->getPlayer()->pushObject(DIR::TOP, _rc.bottom);
			break;
		case Direction::RIGHT:
			OBJECTMANAGER->getPlayer()->pushObject(DIR::RIGHT, _rc.left);
			break;
		case Direction::BOTTOM:
			OBJECTMANAGER->getPlayer()->pushObject(DIR::BOTTOM, _rc.top);
			break;
		default:
			break;
		}
	}
}

void Door::animation()
{
	if (_isOpen) 
	{
		for (int i = 0; i < PARTICLE_CNT; i++)
		{
			if (_particle[i].isOn) continue;
			_particle[i].isOn = true;
			_particle[i].imgIdx = RND->getInt(PARTICLE_IMG);
			_particle[i].dir = _dir;
			_particle[i].startX = RND->getFromIntTo(_rc.left, _rc.right);
			_particle[i].startY = RND->getFromIntTo(_rc.top, _rc.bottom);
			_particle[i].startX = _particle[i].startX - _imgParticle[_particle[i].imgIdx]->getWidth() * 0.5f;
			_particle[i].startY = _particle[i].startY - _imgParticle[_particle[i].imgIdx]->getHeight() * 0.5f;
			_particle[i].x = _particle[i].startX;
			_particle[i].y = _particle[i].startY;
			_particle[i].speed = RND->getFromFloatTo(0.5f, 1.0f);
			_particle[i].alpha = RND->getFromIntTo(100, 200);
			break;
		}
		for (int i = 0; i < PARTICLE_CNT; i++)
		{
			if (!_particle[i].isOn) continue;

			_particle[i].alpha--;
			if(_particle[i].dir == DIR::LEFT)		_particle[i].x += _particle[i].speed;
			else if(_particle[i].dir == DIR::RIGHT) _particle[i].x -= _particle[i].speed;
			else if(_particle[i].dir == DIR::TOP)	_particle[i].y += _particle[i].speed;
			else									_particle[i].y -= _particle[i].speed;

			int distance = GetDistance(
				_particle[i].startX,
				_particle[i].startY,
				_particle[i].x, 
				_particle[i].y
			);
			if(distance > PARTICLE_DIS) _particle[i].isOn = false;
		}
	}
	else
	{
		if (_frameInfo.cnt++ > _frameInfo.tick)
		{
			_frameInfo.cnt = 0;
			_frameInfo.x++;
			if (_frameInfo.x > _frameInfo.endFrameX)
			{
				_frameInfo.startFrameX = FRAME_IDLE_S;
				_frameInfo.x = _frameInfo.startFrameX;
				if (_state == DOOR_STATE::OPEN) _isOpen = TRUE;
			}
		}
	}
}

void Door::setTileX(int tileX)
{
	_x = tileX * TILE_SIZE;
	_rc = RectMake(_x, _y, _frameInfo.width, _frameInfo.height);
}

void Door::setTileY(int tileY)
{
	_y = tileY * TILE_SIZE;
	_rc = RectMake(_x, _y, _frameInfo.width, _frameInfo.height);
}

void Door::openDoor()
{
	_frameInfo.x = FRAME_IDLE_E;
	_frameInfo.endFrameX = _frameInfo.maxFrameX;
	_state = DOOR_STATE::OPEN;
	SOUNDMANAGER->play(SoundName::Dungeon::DoorMove, _sound);
}

void Door::closeDoor()
{
	_frameInfo.x = 0;
	_frameInfo.startFrameX = FRAME_IDLE_S;
	_frameInfo.endFrameX = FRAME_IDLE_E;
	_state = DOOR_STATE::IDLE;
	_isOpen = FALSE;
	for (int i = 0; i < PARTICLE_CNT; i++)
	{
		_particle[i].isOn = FALSE;
	}
	SOUNDMANAGER->play(SoundName::Dungeon::DoorMove, _sound);
}
