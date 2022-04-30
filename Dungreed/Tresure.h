#pragma once
#include "Object.h"
class Tresure : public Object
{
private:
	ImageBase* _img;
	Code::TRESURE_TYPE _type;
	BOOL _isOpen;
	BOOL _isStop;

public:
	Tresure(float x, float y, Code::TRESURE_TYPE type = Code::TRESURE_TYPE::NONE);
	virtual ~Tresure();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void collisionObject() override;	
	virtual void stopObject() override { _isStop = TRUE; }

};

