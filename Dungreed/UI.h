#pragma once
#include "Object.h"

class UI : public Object
{
protected:
	ImageBase* _img;
	FRAME_INFO _frameInfo;
	string _sceneName;
	BOOL _isFixed; // TRUE ������ǥ ����, FALSE �����ǥ ����
	BOOL _isShow;
	BOOL _isFree; // scene�Ѿ�� ���� ����
	int _width;
	int _height;
	BYTE _alpha;

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

};

