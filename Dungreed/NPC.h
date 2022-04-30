#pragma once
#include "Object.h"

class NPC : public Object
{
protected:
	ImageBase* _img;
	FRAME_INFO _frameInfo;

	BOOL _isOpen;
	vector<UI*> _vUI;

public:
	NPC();
	virtual ~NPC();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void updateAnimation();

	virtual void collisionObject() override;
	virtual void openNpc(); 
	virtual void closeNpc();

};

