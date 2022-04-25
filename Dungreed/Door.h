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

class Door : public NPC
{
private:
	enum class DOOR_STATE
	{
		IDLE,
		CLOSE,
		OPEN,
	};

	struct tagParticle
	{
		Direction::DIR dir;
		bool isOn;
		int imgIdx;
		float startX;
		float startY;
		float x;
		float y;
		float speed;
		BYTE alpha;

		tagParticle()
		{
			isOn = false;
		}
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
	tagParticle _particle[DoorSet::PARTICLE_CNT];

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

