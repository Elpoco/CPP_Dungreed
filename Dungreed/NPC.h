#pragma once
#include "Object.h"
class NPC : public Object
{
private:

public:
	NPC();
	virtual ~NPC();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

};

