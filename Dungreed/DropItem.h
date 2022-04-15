#pragma once
#include "Object.h"

class DropItem : public Object
{
private:
	Code::ITEM	_itemCode;
	FRAME_INFO	_frameInfo;
	ImageBase*	_img;
	float		_dropSpeed;
	bool		_isStop;

public:
	DropItem(Code::ITEM code, float x, float y);
	virtual ~DropItem();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void collisionObject(int dir) override;
	virtual void pushObject(DIRECTION dir, float distance) override;
	virtual void stopObject() override { _isStop = true; }

	void move();
	void animation();

	Code::ITEM getCode() { return _itemCode; }

};

