#pragma once
#include "SingletonBase.h"

/*
Json (JavaScript Object Notation)

- ���ͳݿ��� �ڷḦ �ְ� ���� �� �� �ڷḦ ǥ���ϴ� ���
- �ڷ��� ������ ū ������ ������, Ư�� ��ǻ�� ���α׷��� �������� ǥ���ϴµ� ���� ����
- �� ������ �ڹ� ��ũ��Ʈ�� ���� ������ ��������, ���α׷��� �� �÷����� "������"�̹Ƿ�
C, C++, C#, �ڹ�, �ڹ� ��ũ��Ʈ, ��, ���̽� ��� ���� ��ü���� ���(+����)���� �̿��� �� �ִ�.
- XML, HTTP ���� "�밳"�� ��Ȳ���� �� ������.
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

