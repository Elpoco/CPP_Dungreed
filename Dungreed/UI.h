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
	BOOL _isFree; // scene넘어갈때 삭제 안함
	int _width;
	int _height;
	BYTE _alpha;

	BOOL _isFadeIn;
	float _showStartTime;
	float _showTime;

public:
	UI();
	UI(string imgName, int x = 0, int y = 0, BOOL fixed = TRUE, BOOL show = TRUE, BOOL free = FALSE);
	virtual ~UI();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render(HDC hdc) override;

	virtual void setX(float x) override;
	virtual void setY(float y) override;

	void setLeft(float left);
	void setTop(float top);
	void setRight(float right);
	void setBottom(float bottom);
	
	void animation();

	inline BOOL isFixed() {	return _isFixed; }
	inline BOOL isShow() { return _isShow; }
	inline void setFree() { _isFree = TRUE; }

	void show(float x, float y);
	virtual void show() { _isShow = TRUE; }
	virtual void hide() { _isShow = FALSE; }

	inline int getWidth() { return _width; }
	inline int getHeight() { return _height; }

	inline void setAlpha(BYTE alpha) { _alpha = alpha; }
	inline void fadeIn() { _alpha = 0; _isFadeIn = TRUE; _isShow = TRUE;}
	inline void showTime(float time) { _showStartTime = TIMEMANAGER->getWorldTime(); _showTime = time; }

};

