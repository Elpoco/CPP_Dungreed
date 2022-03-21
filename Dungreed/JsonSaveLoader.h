#pragma once
#include "SingletonBase.h"

/*
Json (JavaScript Object Notation)

- 인터넷에서 자료를 주고 받을 때 그 자료를 표현하는 방법
- 자료의 종류에 큰 제한은 없으며, 특히 컴퓨터 프로그램의 변수값을 표현하는데 아주 적합
- 그 형식은 자바 스크립트의 구문 형식을 따르지만, 프로그래밍 언어나 플랫폼에 "독립적"이므로
C, C++, C#, 자바, 자바 스크립트, 펄, 파이썬 등등 많은 객체지향 언어(+절차)에서 이용할 수 있다.
- XML, HTTP 보다 "대개"의 상황에서 더 빠르다.
*/

class JsonSaveLoader : public SingletonBase<JsonSaveLoader>
{
private:
	void saveString(char* fileName, string data);
	void saveStringWithFileStream(char* fileName, string data);

	string loadString(char* fileName);
	string loadStringWithFileStream(char* fileName);

public:
	HRESULT init(void);
	void release(void);
	void saveJsonFile(char* fileName, Json::Value root);
	Json::Value loadJsonFile(char* fileName);

	JsonSaveLoader() {};
	~JsonSaveLoader() {};

};

