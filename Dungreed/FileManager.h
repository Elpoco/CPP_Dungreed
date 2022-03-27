#pragma once
#include "SingletonBase.h"

class FileManager : public SingletonBase<FileManager>
{
public:
	FileManager();
	~FileManager();

	HRESULT init();
	void release();

	template<typename T>
	inline int saveFile(string filePath, string fileName, T* saveArr, DWORD arrSize)
	{
		HANDLE hFile;
		DWORD write;
		bool res;
	
		hFile = CreateFile((filePath + fileName).c_str(), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			cout << "File save fail" << endl;
			return FALSE;
		}

		res = WriteFile(hFile, saveArr, arrSize, &write, NULL);
		CloseHandle(hFile);

		if (!res) 
			return FALSE;

		return TRUE;
	}

	template<typename T>
	inline int loadFile(string filePath, string fileName, T* loadArr, DWORD arrSize)
	{
		HANDLE hFile;
		DWORD read;
		bool res;

		hFile = CreateFile((filePath + fileName).c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			cout << "File load fail" << endl;
			return FALSE;
		}

		res = ReadFile(hFile, loadArr, arrSize, &read, NULL);
		CloseHandle(hFile);

		if (!res) 
			return FALSE;

		return TRUE;
	}


};
