#pragma once
#include "Unit.h"
class Enemy : public Unit
{
private:
	string name;

public:
	Enemy();
	~Enemy();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;


};

