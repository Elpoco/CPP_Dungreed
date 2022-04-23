#pragma once
#include "SingletonBase.h"

#define KEY_MAX 256

class KeyManager : public SingletonBase <KeyManager>
{
private:
	bitset<KEY_MAX> _keyUp;
	bitset<KEY_MAX> _keyDown;

	BOOL _isTyping;
	char _str[256] = "";

public:
	HRESULT init(void);

	BOOL isOnceKeyDown(int key);
	BOOL isOnceKeyUp(int key);
	BOOL isStayKeyDown(int key);
	BOOL isToggleKey(int key);

	bitset<KEY_MAX> getKeyUp(void) { return _keyUp; }
	bitset<KEY_MAX> getKeyDown(void) { return _keyDown; }

	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }

	void typing(char ch);
	char* getTypingStr() { return _str; }
	void setTyping(BOOL isTyping) { _isTyping = isTyping; }
	BOOL isTyping() { return _isTyping; }

	KeyManager() {}
	~KeyManager() {}
};
