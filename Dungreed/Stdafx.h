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

#include <ole2.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")

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
#include "Define.h"
#include "Enums.h"
#include "Structs.h"
#include "String.h"
#include "Config.h"

#include "CommonMacroFuntion.h"
#include "RandomFuntion.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "ImageGpManager.h"
#include "FontManager.h"
#include "Utils.h"
#include "TimeManager.h"
#include "TextDataManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "JsonSaveLoader.h"

#include "ObjectManager.h"
#include "EffectManager.h"
#include "CameraManager.h"
#include "UIManager.h"
#include "FileManager.h"
#include "TileManager.h"
#include "MessageBoxManager.h"
#include "CollisionManager.h"

using namespace MY_UTIL;
using Gdiplus::RectF;
using Gdiplus::PointF;
using Gdiplus::Color;

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

#define OBJECTMANAGER ObjectManager::getSingleton()
#define EFFECTMANAGER EffectManager::getSingleton()
#define CAMERAMANAGER CameraManager::getSingleton()
#define UIMANAGER UIManager::getSingleton()
#define FILEMANAGER FileManager::getSingleton()
#define TILEMANAGER	TileManager::getSingleton()
#define MSGBOXMANAGER MessageBoxManager::getSingleton()
#define COLLISIONMANAGER CollisionManager::getSingleton()
#define GPIMAGEMANAGER ImageGpManager::getSingleton()

// =============
// # ���� ���� #
// =============
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern PointF		_ptMouse;
extern bool			_isDebug;
