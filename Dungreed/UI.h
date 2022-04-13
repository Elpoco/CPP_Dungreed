#pragma once
#include "Object.h"

class UI : public Object
{
private:
	ImageBase* _img;

protected:
	string _sceneName;
	BOOL _isFixed; // TRUE ������ǥ ����, FALSE �����ǥ ����
	BOOL _isShow;

public:
	UI();
	UI(string imgName, int x, int y, BOOL fixed, BOOL show = TRUE);
	virtual ~UI();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	inline BOOL isFixed() {	return _isFixed; }
	inline BOOL isShow() { return _isShow; }

};

