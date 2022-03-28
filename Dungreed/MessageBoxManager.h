#pragma once
#include "SingletonBase.h"
class MessageBoxManager : public SingletonBase<MessageBoxManager>
{
public:
	MessageBoxManager();
	~MessageBoxManager();

	HRESULT init();
	void release();

	void showMessage(char* str, char* strTitle = "Alert");
};

