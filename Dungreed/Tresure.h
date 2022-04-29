#pragma once
#include "Object.h"
class Tresure : public Object
{
private:
	enum class TRESURE_TYPE
	{
		BASIC,
		BLUE,

		TYPE_CNT,

		BOSS,
	};

private:
	ImageBase* _img;
	TRESURE_TYPE _type;
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

