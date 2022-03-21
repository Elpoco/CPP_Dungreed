#include "Stdafx.h"
#include "JsonSaveLoader.h"

HRESULT JsonSaveLoader::init(void)
{
	//! Do Noting
	return S_OK;
}

void JsonSaveLoader::release(void)
{
	//! Do Noting
}

void JsonSaveLoader::saveString(char* fileName, string data)
{
	TCHAR* buf = (TCHAR*)data.c_str();
	HANDLE file;
	// Byte Order Mark: ����Ʈ ���� ǥ��
	WORD BOM = 0xFEFF;
	DWORD dwBytes = 0;
	DWORD dwRead;

	file = CreateFile
	(
		fileName,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	// INVALID_HANDLE_VALUE: �ʱ�ȭ�� ���� ���Ǹ� ���� ���� -1
	if (file == INVALID_HANDLE_VALUE)
	{
		MessageBox(_hWnd, "���� ���� ����", "����", MB_OK);
	}
	else
	{
		//WriteFile(file, &BOM, 2, &dwBytes, NULL);
		WriteFile(file, buf, strlen(buf) * sizeof(TCHAR), &dwRead, NULL);
		CloseHandle(file);
	}
}

string JsonSaveLoader::loadString(char* fileName)
{
	TCHAR buf[8193];
	ZeroMemory(buf, sizeof(buf));

	HANDLE file;
	DWORD dwBytes;

	file = CreateFile
	(
		fileName,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (file == INVALID_HANDLE_VALUE)
	{
		MessageBox(_hWnd, "���� ���� ����", "����", MB_OK);
		return "";
	}
	else
	{
		ReadFile(file, buf, 8192, &dwBytes, NULL);
		CloseHandle(file);
	}

	return string(buf);
}

void JsonSaveLoader::saveStringWithFileStream(char* fileName, string data)
{
	ofstream outFile(fileName);

	outFile << data << endl;

	outFile.close();
}

string JsonSaveLoader::loadStringWithFileStream(char* fileName)
{
	ifstream fileIn;

	/*
	ios::in		������ �б⸸ ������ ���� ����
	ios::out	������ ���⸸ ������ ���� ����
	ios::ate	���� ������ �ɶ� ������ ������ ���� ������ �̵�
	ios::binary	���̳ʸ� ���� ����
	ios::app	�����͸� �� ������ ���� �߰�
	*/
	fileIn.open(fileName, ios::in);

	char data;
	string jsonStr;

	while (fileIn.get(data))
	{
		jsonStr += data;
	}

	fileIn.close();

	return jsonStr;
}

void JsonSaveLoader::saveJsonFile(char* fileName, Json::Value root)
{
	Json::StyledWriter writer;
	string outputConfig = writer.write(root);

	saveStringWithFileStream(fileName, outputConfig);
}

Json::Value JsonSaveLoader::loadJsonFile(char* fileName)
{
	string jsonStr = loadStringWithFileStream(fileName);

	if (jsonStr == "")
	{
		MessageBox(_hWnd, "�����Ͱ� ����", "Warning", MB_OK);
		return NULL;
	}

	Json::Reader reader;
	Json::Value root;

	// �ļ� & �Ľ�
	// �Ľ�: Ư�� ������ �о� �鿩�� �̸� �ٸ� ���α׷��̳� ���� ��ƾ�� ����� �� �ִ� ������ ǥ�� �������
	// ��ȯ �����ִ°�
	// �ļ�: �Ľ��� ���ִ� ���μ���

	bool parsingRet = reader.parse(jsonStr, root);

	if (!parsingRet)
	{
		string errMsg = reader.getFormatedErrorMessages();
		MessageBox(_hWnd, errMsg.c_str(), "����", MB_OK);
		PostQuitMessage(0);
	}

	return Json::Value();
}
