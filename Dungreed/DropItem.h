#pragma once
#include "Object.h"

class DropItem : public Object
{
private:
	Code::ITEM	_itemCode;
	ImageBase*	_img;
	FRAME_INFO	_frameInfo;
	BOOL		_isStop;
	float		_dropSpeed;
	float		_gravity;
	float		_scatterX;

public:
	DropItem(Code::ITEM code, float x, float y, BOOL scatter = FALSE);
	virtual ~DropItem();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void collisionObject() override;
	virtual void pushObject(DIR dir, float distance) override;
	virtual void stopObject() override { _isStop = TRUE; }
	BOOL isStop() { return _isStop; }

	void move();
	void animation();

	void pickUpPlayer(R_L dir);

	Code::ITEM getCode() { return _itemCode; }

};

