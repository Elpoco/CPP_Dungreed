#pragma once
#include "Object.h"

class UI : public Object
{
private:
	string _sceneName;
	ImageBase* _img;
	bool _isFixed;

public:
	UI(string imgName, int x, int y, bool fixed);
	~UI();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	inline string getSceneName() { return _sceneName; }

};

