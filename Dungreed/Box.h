#pragma once
#include "Object.h"

class Box : public Object
{

public:
	Box();
	virtual ~Box();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

};

