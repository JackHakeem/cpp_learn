/*
/////////////////////////////////////////////////////////////////////////////////
//文件名称：BaseType.h
//功能描述：系统底层类型基础文件，无授权人员不得修改此文件内容
//版本说明：Windows操作系统需要定义宏：__WINDOWS__
//			Linux操作系统需要定义宏：__LINUX__
//修改情况：
//
/////////////////////////////////////////////////////////////////////////////////

*/
#ifndef __BASETYPE_H__
#define __BASETYPE_H__
/*
///////////////////////////////////////////////////////////////////////
//标准数据类型定义
///////////////////////////////////////////////////////////////////////
*/
#include <string>
#include "cocos2d.h"
#include <list>
#include <map>
#include "SpriteNode.h"
#include "LayerNode.h"

#pragma warning (disable:4005)
#pragma warning (disable:4244)
#pragma warning (disable:4996)
#pragma warning (disable:4819)
#pragma warning (disable:4715)
#pragma warning (disable:4530)

using namespace std;

typedef signed char	int8;
typedef signed short int16;
typedef signed int int32;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
//typedef unsigned int uint32_t;
typedef unsigned int uint;
typedef float float32;
typedef char sint8;

typedef unsigned long DWORD;
typedef uint16	PacketID_t;

//typedef unsigned long Number;
//typedef INT64 Number;

//#define NULL (0)

#define TILE_WIDTH 60
#define TILE_HEIGHT 30

//#define MAP_MAX_CELL_H 30
//#define MAP_MAX_CELL_W 30

#define MAX_CELLS_X 200
#define MAX_CELLS_Y 200
#define VERSION_91
///////////////////////////////////////////////////////////////////////
#define MVC_MODEL_PROXY_MAXSIZE 50
/*
///////////////////////////////////////////////////////////////////////
//基本数据宏定义
///////////////////////////////////////////////////////////////////////
*/
#define PACKET_MAX_ID 65530

const float g_defaultFontSize = 14.0f;
const float g_CrystalFontSize = 20.0f;
const float g_RoleFontSize = 20.0f;
const char g_sDefaultFont[54] = "Marker Felt";
const char g_sSimHeiFont[54] = "Arial";
const int32 NONEINT = -1;
/*
///////////////////////////////////////////////////////////////////////
//调试预定义宏定义
///////////////////////////////////////////////////////////////////////
*/
#if defined(NDEBUG)
	#define _MY_TRY try
	#define _MY_CATCH catch(...)
#else
	#define _MY_TRY try
	#define _MY_CATCH catch(...)
#endif

/*
//根据指针值删除内存
*/
#ifndef SAFE_DELETE
#define SAFE_DELETE(x)	if( (x)!=NULL ) { delete (x); (x)=NULL; }
#endif
/*
//根据指针值删除数组类型内存
*/
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x)	if( (x)!=NULL ) { delete[] (x); (x)=NULL; }
#endif
/*
//根据指针调用free接口
*/
#ifndef SAFE_FREE
#define SAFE_FREE(x)	if( (x)!=NULL ) { free(x); (x)=NULL; }
#endif
/*
//根据指针调用Release接口
*/
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x)	if( (x)!=NULL ) { (x)->Release(); (x)=NULL; }
#endif

#define SCALEW(x) CCDirector::sharedDirector()->getWinSize().width * (x) / 1024.0f
#define SCALEH(x) CCDirector::sharedDirector()->getWinSize().height * (x) / 768.0f

/*
//编码转换
*/
int GBKToUTF8(std::string& gbkStr, const char* toCode, const char* fromCode);

#define UTF8(x) GBKToUTF8(x, "gb2312", "utf-8")
/*
//获取屏幕坐标
*/
cocos2d::CCPoint getScreenPos(cocos2d::CCNode* obj, bool pixels = false);

// View背景大小
#define BG_SIZE_960_640 CCSizeMake(960,640)


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
static std::string AUDIO_FORMAT = "mp3";
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
static std::string AUDIO_FORMAT = "mp3";
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
static std::string AUDIO_FORMAT = "ogg";
#endif

#endif
