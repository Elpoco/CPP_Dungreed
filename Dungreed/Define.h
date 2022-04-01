#pragma once

// ==========
// # Window #
// ==========
#define WINNAME				(LPSTR)(TEXT("Dungreed"))

#define WINSTART_X			100
#define WINSTART_Y			100
#define WINSIZE_X			1280
#define WINSIZE_Y			800
#define WINSTYLE			WS_CAPTION | WS_SYSMENU
#define CENTER_X		(WINSIZE_X / 2)
#define CENTER_Y		(WINSIZE_Y / 2)

// ==============
// # 매크로 함수 #
// ==============
#define SAFE_DELETE(p)			{if(p) {delete (p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p)=nullptr;}}

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
#define PATH_ITEM		PATH_IMAGE"Item/"

// ===========
// # Setting #
// ===========

#define TILE_RES_SIZE		16
#define TILE_SCALE			3
#define TILE_SIZE			(TILE_RES_SIZE * TILE_SCALE)