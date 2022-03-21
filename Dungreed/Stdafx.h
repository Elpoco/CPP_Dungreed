#pragma once
#include<SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

//! ������ �ܼ�â
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

//! ���̺귯��
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "lib/FMOD/fmodex_vc")
#pragma comment(lib, "Jsoncpp/lib_json/json_vc71_libmtd.lib")

//!�ܺ� ��� ����
#include "inc/FMOD/fmod.hpp"
#include "Jsoncpp/include/json/json.h"

//! C ��Ÿ�� ���
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <mmsystem.h>
#include <mciapi.h>

//! C++ ��Ÿ�� ���
#include <iostream>
#include <random>
#include <bitset>
#include <vector>
#include <map>
#include <cassert>
#include <algorithm>
#include <functional>
#include <fstream>
#include <queue>

using namespace std;

// =================================
// # ���� ���� ��������� �̰��� �߰� #
// =================================
#include "CommonMacroFuntion.h"
#include "RandomFuntion.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "Utils.h"
#include "TimeManager.h"
#include "TextDataManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "JsonSaveLoader.h"

#include "EffectManager.h"

using namespace MY_UTIL;

// =======================
// # �̱����� �̰��� �߰� #
// =======================
#define RND RandomFuntion::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()
#define TEXTDATAMANAGER TextDataManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()
#define SOUNDMANAGER SoundManager::getSingleton()
#define JSONDATAMANAGER JsonSaveLoader::getSingleton()

#define EFFECTMANAGER EffectManager::getSingleton()

// ==========================
// # ��ũ�� # (������â �ʱ�ȭ)
// ==========================
#define WINNAME				(LPSTR)(TEXT("Windows API"))

#define WINSTART_X			100
#define WINSTART_Y			100
#define WINSIZE_X			1280
//#define WINSIZE_X			600
#define WINSIZE_Y			800
#define WINSTYLE			WS_CAPTION | WS_SYSMENU       //caption Ÿ��Ʋ��, sysmenu X ��ư

// ========================
// # ��ũ�� # (��� �� ȿ��)
// ========================
#define CENTER_X		WINSIZE_X / 2
#define CENTER_Y		WINSIZE_Y / 2

#define MAGENTA			RGB(255,0,255)

#define PATH_RESOURCE	"Resources/"
#define PATH_IMAGE		PATH_RESOURCE"Images/"
#define PATH_SOUND		PATH_RESOURCE"Sounds/"
#define PATH_BACKGROUND	PATH_IMAGE"Background/"
#define PATH_OBJECT		PATH_IMAGE"Object/"
#define PATH_UNIT		PATH_IMAGE"Unit/"
#define PATH_ENEMY		PATH_UNIT"Enemy/"

// =============================================
// # ��ũ�� �Լ� # (Ŭ�������� �����Ҵ�� �κ� ����)
// =============================================
#define SAFE_DELETE(p)			{if(p) {delete (p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p)=nullptr;}}

// =============
// # ���� ���� #
// =============
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;
