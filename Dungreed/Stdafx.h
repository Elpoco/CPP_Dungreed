#pragma once
#include<SDKDDKVer.h>

#include <Windows.h>

//! 디버깅용 콘솔창
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

//! 라이브러리
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "lib/FMOD/fmodex_vc")
#pragma comment(lib, "Jsoncpp/lib_json/json_vc71_libmtd.lib")

//!외부 헤더 파일
#include "inc/FMOD/fmod.hpp"
#include "Jsoncpp/include/json/json.h"

//! C 런타임 헤더
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <mmsystem.h>
#include <mciapi.h>

#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")

//! C++ 런타임 헤더
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
// # 내가 만든 헤더파일을 이곳에 추가 #
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

#include "Enums.h"
#include "Config.h"

#include "EffectManager.h"
#include "CameraManager.h"
#include "UIManager.h"
#include "FileManager.h"
#include "TileManager.h"
#include "MessageBoxManager.h"
#include "CollisionManager.h"

using namespace MY_UTIL;

// =======================
// # 싱글톤을 이곳에 추가 #
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
#define CAMERAMANAGER CameraManager::getSingleton()
#define UIMANAGER UIManager::getSingleton()
#define FILEMANAGER FileManager::getSingleton()
#define TILEMANAGER	TileManager::getSingleton()
#define MSGBOXMANAGER MessageBoxManager::getSingleton()
#define COLLISIONMANAGER CollisionManager::getSingleton()

// ==========================
// # 매크로 # (윈도우창 초기화)
// ==========================
#define WINNAME				(LPSTR)(TEXT("Dungreed"))

#define WINSTART_X			100
#define WINSTART_Y			100
#define WINSIZE_X			1280
#define WINSIZE_Y			800
#define WINSTYLE			WS_CAPTION | WS_SYSMENU

// ========================
// # 매크로 # (기능 및 효율)
// ========================
#define CENTER_X		(WINSIZE_X / 2)
#define CENTER_Y		(WINSIZE_Y / 2)

// =============
// # 파일 경로 #
// =============
#define PATH_RESOURCE	"Resources/"

#define PATH_IMAGE		PATH_RESOURCE"Images/"
#define PATH_SOUND		PATH_RESOURCE"Sounds/"
#define PATH_DATA		PATH_RESOURCE"Data/"

#define PATH_BACKGROUND	PATH_IMAGE"Background/"
#define PATH_OBJECT		PATH_IMAGE"Object/"
#define PATH_UNIT		PATH_IMAGE"Unit/"
#define PATH_MAPTOOL	PATH_IMAGE"MapTool/"

// =============================================
// # 매크로 함수 # (클래스에서 동적할당된 부분 해제)
// =============================================
#define SAFE_DELETE(p)			{if(p) {delete (p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p)=nullptr;}}

// =============
// # 전역 변수 #
// =============
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;
extern bool			_isDebug;

struct fPOINT
{
	float x;
	float y;
};