#pragma once
#include "Object.h"

class DropItem : public Object
{
private:
	ImageBase* _img;
	string _imgName;
	FRAME_INFO _frameInfo;
	bool _isStop;
	float _dropSpeed;

	Code::Item _itemCode;

public:
	DropItem(Code::Item code, float x, float y);
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

	Code::Item getCode() { return _itemCode; }

};

