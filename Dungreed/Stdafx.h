#pragma once
#include<SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#ifdef _DEBUG
//! 디버깅용 콘솔창
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif


//! 라이브러리
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "lib/FMOD/fmod_vc.lib")
//#pragma comment(lib, "Jsoncpp/lib_json/json_vc71_libmtd.lib")

//!외부 헤더 파일
#include "inc/FMOD/fmod.hpp"
//#include "Jsoncpp/include/json/json.h"

//! C 런타임 헤더
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <mmsystem.h>
#include <mciapi.h>

// gdi+
#include <ole2.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
using Gdiplus::Color;

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
#include "Define.h"
#include "Config.h"
#include "Enums.h"
#include "Extern.h"
#include "Structs.h"
#include "String.h"

#include "RandomFuntion.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "ImageGpManager.h"
#include "FontManager.h"
#include "TimeManager.h"
#include "TextDataManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
//#include "JsonSaveLoader.h"

#include "CameraManager.h"
#include "ObjectManager.h"
#include "FileManager.h"
#include "TileManager.h"
#include "MessageBoxManager.h"
#include "CollisionManager.h"
#include "ItemManager.h"
#include "UIManager.h"
#include "DataBaseManager.h"
#include "MapManager.h"
#include "PlayerManager.h"

#include "Utils.h"
using namespace MY_UTIL;

// =======================
// # 싱글톤을 이곳에 추가 #
// =======================
#define RND RandomFuntion::getSingleton()

#define KEYMANAGER			KeyManager::getSingleton()
#define IMAGEMANAGER		ImageManager::getSingleton()
#define FONTMANAGER			FontManager::getSingleton()
#define TIMEMANAGER			TimeManager::getSingleton()
#define TEXTDATAMANAGER		TextDataManager::getSingleton()
#define SCENEMANAGER		SceneManager::getSingleton()
#define SOUNDMANAGER		SoundManager::getSingleton()
//#define JSONDATAMANAGER		JsonSaveLoader::getSingleton()
#define OBJECTMANAGER		ObjectManager::getSingleton()
#define CAMERAMANAGER		CameraManager::getSingleton()
#define FILEMANAGER			FileManager::getSingleton()
#define TILEMANAGER			TileManager::getSingleton()
#define MSGBOXMANAGER		MessageBoxManager::getSingleton()
#define COLLISIONMANAGER	CollisionManager::getSingleton()
#define GPIMAGEMANAGER		ImageGpManager::getSingleton()
#define ITEMMANAGER			ItemManager::getSingleton()
#define UIMANAGER			UIManager::getSingleton()
#define DBMANAGER			DataBaseManager::getSingleton()
#define MAPMANAGER			MapManager::getSingleton()
#define PLAYERMANAGER		PlayerManager::getSingleton()