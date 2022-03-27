#pragma once
#include "SingletonBase.h"

class UI;

class UIManager : public SingletonBase<UIManager>
{
public:
	UIManager();
	~UIManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void addUI(UI* ui);

private:
	typedef vector<UI*> vUI;
	typedef vector<UI*>::iterator viUI;

private:
	vUI _vUi;

};

