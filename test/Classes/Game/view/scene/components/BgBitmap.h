//
//  BgBitmap.h
//  HLQS
//
//  Created by edward liu on 12-2-27.
//  Copyright (c) 2012 4399. All rights reserved.
//

#ifndef HLQS_BgBitmap_h
#define HLQS_BgBitmap_h
#include "BaseType.h"
#include "utils/loader/LoaderItem.h"
#define MAP_SPRITE_MAX 500

using namespace cocos2d;

class BgBitmap: public CCLayer
{
public:
    BgBitmap();
    BgBitmap(const BgBitmap&);
    
    ~BgBitmap();

public:
	int _totalWidth;
	int _totalHeight;
	int _w;  // -offsetx
    int _h;  // -offsety

	int width_left;
	int width_right;
	int height_top;
	int height_bottom;
	int bmCol;
	int bmRow;

	int width_left_;//jae
	int width_right_;
	int height_top_;
	int height_bottom_;
	int m_needLoadCnt;
	int m_loadedCnt;
public:
    std::string _extension;
    std::string _rootURL;
    int _bitmapWidth;
    int _bitmapHeight;
	int _totalTiles;
	int _picWidth;
	int _picHeight;

    int _offsetX;
    int _offsetY;
    
	int _xscale;
	int _yscale;

	CCPoint _mapPos;

	std::map<std::string, LoaderItem> _loadedDic;
	std::map<std::string, LoaderItem> _bitmapDic;
	std::map<std::string, LoaderItem> _thumbsDic;
	std::map<std::string, LoaderItem> _pidDic;

	std::string _rootPath;
	CCRect _renderRect;
	
	LoaderItem _loaditem;
    //int _map_id;
    //string _map_name;
    CCSprite* _mapSprites[MAP_SPRITE_MAX];
    
	CCSize _mapSize;

	//struct SyncStruct
	//{
	//	int bmCol;
	//	int i;
	//	int j;
	//	SyncStruct()
	//	{
	//		bmCol = 0;
	//		i = 0;
	//		j = 0;
	//	}
	//};
	//list<SyncStruct> syncData;
public:
    
    void getMapInfoFromFile(string szFile);
    void build(int w, int h, std::string rootPath, int offsetX = 0, int offsetY =0, std::string extension = ".jpg", int bitmapWidth = 600, int bitmapHeight = 600);
	virtual void load(CCLayer* layer, CCPoint pos);
	CCPoint getMapPos();
	CCSize getMapSize();
	CCSize getMapSizeV();
	void setMapPos(CCPoint pos);
	virtual void dispose();
	//void loadingCallBackND( CCObject* pObject, void* data );//jae
	//void loadingCallBack( CCObject* pObject );

//Begin Kenfly 20121113
	virtual void load(CCLayer* layer, CCPoint pos, CCObject* target, SEL_CallFuncO selector);
private:
	//void initSmallMap(CCPoint pos);
	void loadCompleteHandler(CCNode* node, void* data);
	std::map<std::string, int> m_callbackDic;

	CCSize _smallMapSize;
	CCTexture2D* _smallMap;
	//CCObject* callbackTarget;
	//SEL_CallFuncO callbackSelector;
//End Kenfly 20121113
};

#endif