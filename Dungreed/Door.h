#pragma once
#include "NPC.h"

namespace DoorSet
{
	constexpr int FRAME_IDLE_S = 8;
	constexpr int FRAME_IDLE_E = 15;
	constexpr int PARTICLE_IMG = 5;
	constexpr int PARTICLE_CNT = 20;
	constexpr int PARTICLE_DIS = 50;
}

class Door : public Object
{
private:
	enum class DOOR_STATE
	{
		IDLE,
		CLOSE,
		OPEN,
	};

private:
	ImageBase* _imgDoor;
	FRAME_INFO _frameInfo;
	DOOR_STATE _state;
	Direction::DIR _dir;
	int _tileX;
	int _tileY;

	BOOL _isOpen;

	ImageBase* _imgParticle[DoorSet::PARTICLE_IMG];
	PARTICLE _particle[DoorSet::PARTICLE_CNT];

public:
	Door(Direction::DIR dir, int tileX, int tileY, BOOL isOpen = FALSE);
	virtual ~Door();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void collisionObject() override;

	void animation();

	void setTileX(int tileX);
	void setTileY(int tileY);
	void openDoor();
	void closeDoor();

};

