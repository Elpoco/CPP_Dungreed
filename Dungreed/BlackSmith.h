#pragma once
#include "UI.h"
class BlackSmith : public UI
{
private:
	BOOL _isDrop;

public:
	BlackSmith();
	virtual ~BlackSmith();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void show();

};

