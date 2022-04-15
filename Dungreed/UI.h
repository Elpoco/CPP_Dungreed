#pragma once
#include "Object.h"

class UI : public Object
{
protected:
	ImageBase* _img;
	FRAME_INFO _frameInfo;
	string _sceneName;
	BOOL _isFixed; // TRUE 절대좌표 랜더, FALSE 상대좌표 랜더
	BOOL _isShow;
	int _width;
	int _height;

public:
	UI();
	UI(string imgName, int x = 0, int y = 0, BOOL fixed = TRUE, BOOL show = TRUE);
	virtual ~UI();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void setX(float x) override;
	virtual void setY(float y) override;
	
	void animation();

	inline BOOL isFixed() {	return _isFixed; }
	inline BOOL isShow() { return _isShow; }

	inline void show() { _isShow = TRUE; }
	inline void hide() { _isShow = FALSE; }

	inline int getWidth() { return _width; }
	inline int getHeight() { return _height; }
};

