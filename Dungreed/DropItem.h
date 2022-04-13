#pragma once
#include "Object.h"


class DropItem : public Object
{
private:
	ImageBase* _img;
	FRAME_INFO _frameInfo;
	bool _isCollision;
	float _dropSpeed;

public:
	DropItem(float x, float y);
	virtual ~DropItem();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void stopObject() override { _isCollision = true; }

	void move();
	void animation();

};

