#include "Stdafx.h"
#include "TextDataManager.h"

HRESULT TextDataManager::init(void)
{
	return S_OK;
}

void TextDataManager::release(void)
{
	//! Do Nothing
}

// ����¥�� �����͸� ��ƵѰ�
// ��� �����͸� ���� ������ ©�� ����
void TextDataManager::save(const char * fileName, vector<string> vStr)
{
	HANDLE file;
	char str[SAVE_BUFFER];
	DWORD write;

	/*
	strcpy: ���ڿ� ���� �Լ�
	strcpy_s:
	strncpy_s: ������ ũ�⸦ ���ڷ� ����� �� �ִ�. (����)
				���� �ڵ����� "NULL"���� ����
	*/

	strncpy_s(str, SAVE_BUFFER, vectorArrayCombine(vStr), SAVE_BUFFER - 1);

	/*
	CreateFile() : ���� ����� ��ġ�� ����ų� �о�´�.
	�� ��ȯ���� ����� �� �ִ� Handle

	CreateFile
	(
		�����ϰų� �� ������ �̸�, 
		���� ����Ÿ��, 
		������ ������ ���� ����(0�� ����X), 
		�ڽĿ��� ��� ����, 
		���� ���� ��� ����,
		������ �ɼǰ� ����(�б� ���� ���...), 
		���Ͽ� ���� �Ӽ� ��
	)

	CREATE_ALWAYS: ���ο� ���� ����, ������ ���� ����� �����
	FILE_ATTRIBUTE_NORMAL: �ٸ� �Ӽ����� ������ �ʰڴ�
	*/

	file = CreateFile(fileName, GENERIC_WRITE,
		0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	/*
	WriteFile(): 
	1. CreateFile()���� �Ҵ�� �ڵ�
	2. ���Ͽ� ������� ��Ʈ�� ��
	3. �󸶳� �а� ���������� ���� ũ��
	4. �󸶳� �а� ���������� ���� ������� ����ȴ�. (�ּ�)
	*/
	WriteFile(file, str, strlen(str), &write, NULL);
	CloseHandle(file);
}

// ���� ����� ������
// ����¥�� �����͸� ��ǥ ������ �� �����ϴ� ���� �����ϰ� �װ��� ������� �Ҷ� ���ϴ�.
char * TextDataManager::vectorArrayCombine(vector<string> vArray)
{
	char str[SAVE_BUFFER];
	ZeroMemory(str, sizeof(str));

	for (int i = 0; i < vArray.size(); i++)
	{
		// c_str(): Ÿ�� ĳ���� ������
		// string �ڷ����� char* ������ ��ȯ
		strncat_s(str, SAVE_BUFFER, vArray[i].c_str(), SAVE_BUFFER - 1);

		if (i + 1 < vArray.size()) strcat_s(str, ",");

		// strxxx_s: ���� �����÷ο� ������ ������ ũ�⸦ ��Ȯ�ϰ� ���� �� �ְ� �߰��� �Լ�
	}

	return str;
}

vector<string> TextDataManager::load(const char * fileName)
{
	HANDLE file;
	char str[LOAD_BUFFER];
	DWORD read;

	memset(str, 0, LOAD_BUFFER);

	file = CreateFile(fileName, GENERIC_READ,
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, LOAD_BUFFER, &read, NULL);
	CloseHandle(file);

	return charArraySeparation(str);
}

vector<string> TextDataManager::charArraySeparation(char charArray[])
{
	vector<string> vArray;
	char* temp;
	char* separator = ",";
	// token: �����Ϸ��� �ν��� �� �ִ� �⺻ ���
	//		  ������, �ĺ�, ���� ��ȣ ���...
	char* tokenA;
	char* tokenB;

	/*
	strtok(): ���ڿ��� ��ū���� �и��Ѵ�.
	strtok
	(
		���ڿ��� ��ū���� �и��ϰ� ���� �迭�� �޸� �ּ�, 
		�и� ���� �и� ����,
		�߶󳻱��� �� ���� ���ڿ��� �޸� �ּ�
	)
	*/
	tokenA = strtok_s(charArray, separator, &tokenB);
	vArray.push_back(tokenA);

	while (NULL != (tokenA = strtok_s(NULL, separator, &tokenB)))
	{
		vArray.push_back(tokenA);
	}

	return vArray;
}
