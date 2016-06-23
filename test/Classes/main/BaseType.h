/*
/////////////////////////////////////////////////////////////////////////////////
//�ļ����ƣ�BaseType.h
//����������ϵͳ�ײ����ͻ����ļ�������Ȩ��Ա�����޸Ĵ��ļ�����
//�汾˵����Windows����ϵͳ��Ҫ����꣺__WINDOWS__
//			Linux����ϵͳ��Ҫ����꣺__LINUX__
//�޸������
//
/////////////////////////////////////////////////////////////////////////////////

*/
#ifndef __BASETYPE_H__
#define __BASETYPE_H__
/*
///////////////////////////////////////////////////////////////////////
//��׼�������Ͷ���
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
//�������ݺ궨��
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
//����Ԥ����궨��
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
//����ָ��ֵɾ���ڴ�
*/
#ifndef SAFE_DELETE
#define SAFE_DELETE(x)	if( (x)!=NULL ) { delete (x); (x)=NULL; }
#endif
/*
//����ָ��ֵɾ�����������ڴ�
*/
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x)	if( (x)!=NULL ) { delete[] (x); (x)=NULL; }
#endif
/*
//����ָ�����free�ӿ�
*/
#ifndef SAFE_FREE
#define SAFE_FREE(x)	if( (x)!=NULL ) { free(x); (x)=NULL; }
#endif
/*
//����ָ�����Release�ӿ�
*/
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x)	if( (x)!=NULL ) { (x)->Release(); (x)=NULL; }
#endif

#define SCALEW(x) CCDirector::sharedDirector()->getWinSize().width * (x) / 1024.0f
#define SCALEH(x) CCDirector::sharedDirector()->getWinSize().height * (x) / 768.0f

/*
//����ת��
*/
int GBKToUTF8(std::string& gbkStr, const char* toCode, const char* fromCode);

#define UTF8(x) GBKToUTF8(x, "gb2312", "utf-8")
/*
//��ȡ��Ļ����
*/
cocos2d::CCPoint getScreenPos(cocos2d::CCNode* obj, bool pixels = false);

// View������С
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
