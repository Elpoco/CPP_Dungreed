#pragma once
#include "Object.h"
class Tresure : public Object
{
private:
	ImageBase* _img;
	BOOL _isOpen;

public:
	Tresure(float x, float y);
	virtual ~Tresure();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void collisionObject() override;

};

