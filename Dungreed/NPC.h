#pragma once
#include "Object.h"

class NPC : public Object
{
protected:
	Code::NPC _npcCode;
	Code::MAP _mapCode;
	ImageBase* _img;
	FRAME_INFO _frameInfo;

	BOOL _isOpen;

	UI* _uiNPC;

public:
	NPC(Code::NPC code, float x, float y, Code::MAP mapCode = Code::MAP::TOWN);
	virtual ~NPC();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	void initAnimation();
	void updateAnimation();

	virtual void collisionObject() override;
	virtual void openNpc(); 
	virtual void closeNpc();

};

