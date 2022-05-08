#pragma once
#include "Object.h"

class Worm : public Object
{
private:
	enum class WORM_STATE
	{
		IDLE,
		EAT,
	};

private:
	ImageBase* _img;
	ImageBase* _imgEat;
	FRAME_INFO _frameInfo;
	WORM_STATE _state;

public:
	Worm();
	virtual ~Worm();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void collisionObject() override;

	void animation();

	void setPos(POINT pt);
	void changeRoom();

};

