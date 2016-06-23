#include "BaseType.h"
#include "BgBitmap.h"
#include "util/TileUtil.h"
#include "utils/loader/GameLoaderManage.h"
#include "utils/ScaleUtil.h"
#include "model/scene/SceneProxy.h"
#include "model/scene/vo/SceneInfoVo.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "manager/SourceCacheManage.h"

BgBitmap::BgBitmap()
{
    _w = 0;
    _h = 0;
	_totalWidth = 0;
	_totalHeight = 0;
    _bitmapWidth = 0;
    _bitmapHeight = 0;
    _offsetX = 0;
    _offsetY = 0;
	_picWidth = TileUtil::Instance()->getPicWidth();
	_picHeight = TileUtil::Instance()->getPicHeight();
	_totalTiles = 0;

	bmCol = 0;
	bmRow = 0;

	_xscale = 0;
	_yscale = 0;

	width_left_ = 0;//jae
	width_right_ = 0;
	height_top_ = 0;
	height_bottom_ = 0;
	m_needLoadCnt = 0;
	m_loadedCnt = 0;

	_mapSize = CCDirector::sharedDirector()->getWinSize();

	for(int i = 0; i < MAP_SPRITE_MAX; ++i)
		_mapSprites[i] = NULL;

	CCLayer::init();

	//Begin Kenfly 20121114
	_smallMapSize = CCSizeZero;
	_smallMap = NULL;
	//End Kenfly 20121114
}

BgBitmap::~BgBitmap()
{
}

void BgBitmap::build(int w,
                     int h,
                     std::string rootPath,
                     int offsetX,
                     int offsetY,
                     string extension,
					 int bitmapWidth,
                     int bitmapHeight)
{
	_extension = extension;
	_rootPath = rootPath;
	_w = w;
	_h = h;
	_mapSize.width = _w;
	_mapSize.height = _h;
	/*_totalWidth = w - offsetX * 2;
	_totalHeight = h - offsetY * 2;*/

	SceneProxy* sceneProxy = (SceneProxy*)g_pFacade->retrieveProxy(AppFacade_SCENE_PROXY);
	SceneInfoVo* sceneInfoVo = sceneProxy->sceneInfoVo();
	if(!sceneInfoVo)
		return;

	//bmCol = ceil((float)_w / (float)_picWidth);
	//bmRow = ceil((float)_h / (float)_picHeight);
	bmCol = sceneInfoVo->mapCols;
	bmRow = sceneInfoVo->mapRoWs;

	_totalWidth = bmCol * _picWidth;
	_totalHeight = bmRow * _picHeight;

	_totalTiles=0;

	_bitmapWidth = bitmapWidth;
	_bitmapHeight = bitmapHeight;

	_offsetX =  offsetX;
	_offsetY =  offsetY;

	//POSX edwardliu
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	width_left = _totalWidth / 2 - POSX(300);
	width_right = _totalWidth / 2 + screenSize.width + POSX(300);
	height_top = _totalHeight / 2 - screenSize.height - POSX(300);
	height_bottom = _totalHeight / 2 + POSX(300);

	//Begin Kenfly 20121114
	std::string smpath = _rootPath + "small.jpg";
	CCImage smallMap;
	if (smallMap.initWithImageFile(smpath.c_str(), CCImage::kFmtJpg))
	{
		_smallMapSize = CCSizeMake(smallMap.getWidth(), smallMap.getHeight());
		if (_smallMap)
			_smallMap->release();
		_smallMap = new CCTexture2D();
		_smallMap->initWithImage(&smallMap);
	}
	else
	{
		_smallMapSize = CCSizeZero;
		CC_SAFE_RELEASE(_smallMap);
		_smallMap = NULL; 
	}
	//End Kenfly 20121114
}

void BgBitmap::load(CCLayer* layer, CCPoint pos)
{
    
    //Doyang 20120715
    CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGB565);
	/*if(_totalTiles >= _totalHeight / _picWidth * _totalHeight / _picHeight)
	{
		return;
	}*/
	
	//int bmCol = _totalWidth / _picWidth;
	//int bmRow = _totalHeight / _picHeight;

	//syncData.clear();

	std::string rootPath = _rootPath + "%d_%d.jpg";
	char p[50] = {0};

	//int width_left_ = width_left - pos.x;
	//int width_right_ = width_right - pos.x;
	//int height_top_ = height_top + pos.y;
	//int height_bottom_ = height_bottom + pos.y;
	width_left_ = width_left - pos.x;
	width_right_ = width_right - pos.x;
	height_top_ = height_top + pos.y;
	height_bottom_ = height_bottom + pos.y;

	m_needLoadCnt = 0;
	m_loadedCnt = 0;

	for(int i = 0; i < bmRow; ++i)
	{
		for(int j = 0; j< bmCol; ++j)
		{
			if((i * bmCol + j) >= MAP_SPRITE_MAX)
				break;

			if(j * _picWidth  >= width_left_ && (j + 1) * _picWidth < width_right_
				&& i * _picHeight >= height_top_ && (i + 1) * _picHeight < height_bottom_)
			{
				if(_mapSprites[i * bmCol + j])
				{
					//if((getChildByTag(i * 10 * bmCol + j)) == NULL)
					//if(_mapSprites[i * bmCol + j]->getParent() != this)
					if(!this->getChildByTag(i * 10 * bmCol + j))
					{
						addChild(_mapSprites[i * bmCol + j], -100, i * 10 * bmCol + j);
					}
					continue;
				}

				sprintf(p, rootPath.c_str(), j, i);

				//SyncStruct* data = new SyncStruct;
				//data->bmCol = bmCol;
				//data->i = i;
				//data->j = j;

				++m_needLoadCnt;
				//CCTextureCache::sharedTextureCache()->addImageAsync( p, this, callfuncOD_selector(BgBitmap::loadingCallBackND), data );
				//CCTextureCache::sharedTextureCache()->addImageAsync( p, this, callfuncO_selector(BgBitmap::loadingCallBack) );

				_mapSprites[i * bmCol + j] = CCSprite::spriteWithFile(p);
				//_mapSprites[i * bmCol + j] = 0;
				if (!_mapSprites[i * bmCol + j])
				{
					CCLog("loading bg map i:%d j:%d.\n", i, j);

					_mapSprites[i * bmCol + j] = /*new CCSprite;
					_mapSprites[i * bmCol + j]->init();*/
						CCSprite::spriteWithFile("assets/mapassets/scene/1002/front/14_8.jpg");
					_mapSprites[i * bmCol + j]->setIsVisible(false);
					//
				}

				//std::string pathKey = p;
				//CCFileUtils::removeSuffixFromFile(pathKey);
				//pathKey = CCFileUtils::fullPathFromRelativePath(pathKey.c_str());
				//CCTexture2D* pTexture = CCTextureCache::sharedTextureCache()->addImage( pathKey.c_str() );
				//_mapSprites[i * bmCol + j] = CCSprite::spriteWithTexture( pTexture );

				if(_mapSprites[i * bmCol + j])
				{
					int x = j * _picWidth + _picWidth / 2 - _totalWidth / 2;
					int y = _totalHeight / 2 - i * _picHeight - _picHeight / 2;
					_mapSprites[i * bmCol + j]->setPosition(ccp((float)x, (float)y));
					if(_mapSprites[i * bmCol + j]
					&&_mapSprites[i * bmCol + j]->getTexture())
					{
						_mapSprites[i * bmCol + j]->getTexture()->setAliasTexParameters();
					}

					if(_mapSprites[i * bmCol + j]->getParent() != this)
						addChild(_mapSprites[i * bmCol + j], -100 , i * 10 * bmCol + j);
					_totalTiles++;
				}
				//_totalTiles++;
			}
			else if(_mapSprites[i * bmCol + j])
			{
				if(_mapSprites[i * bmCol + j]->getParent() == this)
				{
					CCTexture2D* pTex = _mapSprites[i * bmCol + j]->getTexture();
					removeChild(_mapSprites[i * bmCol + j], true);
					_mapSprites[i * bmCol + j] = NULL;


#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
					CCTextureCache::sharedTextureCache()->removeTexture( pTex );
#endif
				}
				_totalTiles --;
			}
		}
	}
    
    //Doyang 20120715
    CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_Default);
}

//
//void BgBitmap::loadingCallBack( CCObject* pObject )
//{
//	if ( !pObject )
//	{
//		return;
//	}
//	
//	//CCTexture2D* tex = (CCTexture2D*)pObject;
//	++m_loadedCnt;
//
//	//if ( m_loadedCnt == m_needLoadCnt )
//	{
//		std::string rootPath = _rootPath + "%d_%d.jpg";
//		char p[50] = {0};
//
//		for(int i = 0; i < bmRow; ++i)// 15 * 15
//		{
//			for(int j = 0; j< bmCol; ++j)
//			{
//				if((i * bmCol + j) >= MAP_SPRITE_MAX)
//					break;
//
//				if(j * _picWidth  >= width_left_ && (j + 1) * _picWidth < width_right_
//					&& i * _picHeight >= height_top_ && (i + 1) * _picHeight < height_bottom_)
//				{
//					if(_mapSprites[i * bmCol + j])
//					{
//						if(_mapSprites[i * bmCol + j]->getParent() != this)
//						{
//							addChild(_mapSprites[i * bmCol + j], -100, i * 10 * bmCol + j);
//						}
//						continue;
//					}
//
//					sprintf(p, rootPath.c_str(), j, i);
//					//CCTexture2D* pTexture = CCTextureCache::sharedTextureCache()->addImage( p );
//					std::string pathKey = p;
//					CCFileUtils::removeSuffixFromFile(pathKey);
//					pathKey = CCFileUtils::fullPathFromRelativePath(pathKey.c_str());
//					CCTexture2D* pTexture = CCTextureCache::sharedTextureCache()->textureForKey( pathKey.c_str() );
//					if ( !pTexture )
//					{
//						continue;
//					}
//					_mapSprites[i * bmCol + j] = CCSprite::spriteWithTexture(pTexture);
//					//_mapSprites[i * bmCol + j] = CCSprite::spriteWithFile(p);
//					if(_mapSprites[i * bmCol + j])
//					{
//						int x = j * _picWidth + _picWidth / 2 - _totalWidth / 2;
//						int y = _totalHeight / 2 - i * _picHeight - _picHeight / 2;
//						_mapSprites[i * bmCol + j]->setPosition(ccp((float)x, (float)y));
//						if(_mapSprites[i * bmCol + j]
//						&&_mapSprites[i * bmCol + j]->getTexture())
//						{
//							_mapSprites[i * bmCol + j]->getTexture()->setAliasTexParameters();
//						}
//
//						if(_mapSprites[i * bmCol + j]->getParent() != this)
//							addChild(_mapSprites[i * bmCol + j], -100 , i * 10 * bmCol + j);
//					}
//				}	// if
//			} //for j
//		} // for i
//	}
//}

//void BgBitmap::loadingCallBackND( CCObject* pObject, void* pdata )
//{
//	//CCTexture2D* tex = (CCTexture2D*)pObject;
//	if ( pdata == 0 )
//	{
//		return;
//	}
//
//	++m_loadedCnt;
//
//	if ( m_loadedCnt == m_needLoadCnt )
//	{
//		std::string rootPath = _rootPath + "%d_%d.jpg";
//		char p[50] = {0};
//
//		for(int i = 0; i < bmRow; ++i)
//		{
//			for(int j = 0; j< bmCol; ++j)
//			{
//				if((i * bmCol + j) >= MAP_SPRITE_MAX)
//					break;
//
//				if(j * _picWidth  >= width_left_ && (j + 1) * _picWidth < width_right_
//					&& i * _picHeight >= height_top_ && (i + 1) * _picHeight < height_bottom_)
//				{
//					if(_mapSprites[i * bmCol + j])
//					{
//						if(_mapSprites[i * bmCol + j]->getParent() != this)
//						{
//							addChild(_mapSprites[i * bmCol + j], -100, i * 10 * bmCol + j);
//						}
//						continue;
//					}
//
//					sprintf(p, rootPath.c_str(), j, i);
//					CCTexture2D* pTexture = CCTextureCache::sharedTextureCache()->addImage( p );
//					_mapSprites[i * bmCol + j] = CCSprite::spriteWithTexture(pTexture);
//					if(_mapSprites[i * bmCol + j])
//					{
//						int x = j * _picWidth + _picWidth / 2 - _totalWidth / 2;
//						int y = _totalHeight / 2 - i * _picHeight - _picHeight / 2;
//						_mapSprites[i * bmCol + j]->setPosition(ccp((float)x, (float)y));
//						if(_mapSprites[i * bmCol + j]
//						&&_mapSprites[i * bmCol + j]->getTexture())
//						{
//							_mapSprites[i * bmCol + j]->getTexture()->setAliasTexParameters();
//						}
//
//						if(_mapSprites[i * bmCol + j]->getParent() != this)
//							addChild(_mapSprites[i * bmCol + j], -100 , i * 10 * bmCol + j);
//					}
//				}
//			}
//		}
//	}
//
//	SyncStruct* data = (SyncStruct*)pdata;
//
//	//int bmCol(data->bmCol), i(data->i), j(data->j);
//	CC_SAFE_DELETE( data );
//
//	//_mapSprites[i * bmCol + j] = CCSprite::spriteWithTexture(tex);
//	//if(_mapSprites[i * bmCol + j])
//	//{
//	//	int x = j * _picWidth + _picWidth / 2 - _totalWidth / 2;
//	//	int y = _totalHeight / 2 - i * _picHeight - _picHeight / 2;
//	//	_mapSprites[i * bmCol + j]->setPosition(ccp((float)x, (float)y));
//	//	if(_mapSprites[i * bmCol + j]
//	//	&&_mapSprites[i * bmCol + j]->getTexture())
//	//	{
//	//		_mapSprites[i * bmCol + j]->getTexture()->setAliasTexParameters();
//	//	}
//
//	//	if(_mapSprites[i * bmCol + j]->getParent() != this)
//	//		addChild(_mapSprites[i * bmCol + j], -100 , i * 10 * bmCol + j);
//	//	//_totalTiles++;
//	//}
//}

void BgBitmap::dispose()
{
//Begin kenfly 20121113 : modify
	std::string rootPath = _rootPath + "%d_%d.jpg";
	char p[50] = {0};

	for(int i = 0; i < bmRow; ++i)
	{
		for(int j = 0; j< bmCol; ++j)
		{
			if(_mapSprites[i * bmCol + j])
			{
				if(_mapSprites[i * bmCol + j]->getParent() == this)
					removeChild(_mapSprites[i * bmCol + j], true);
				_mapSprites[i * bmCol + j] = NULL;
			
				sprintf(p, rootPath.c_str(), j, i);
				SourceCacheManage::Instance()->removeBgMap(p);
			}
		}
	}

	for(int i = 0; i < MAP_SPRITE_MAX; ++i)
	{
		if(_mapSprites[i] && _mapSprites[i]->getParent() == this)
		{
			removeChild(_mapSprites[i], true);
		}
	}

	CC_SAFE_DELETE(_smallMap);

	m_callbackDic.clear();

	SourceCacheManage::Instance()->removeEventListener(Event::COMPLETE, this, callfuncND_selector(BgBitmap::loadCompleteHandler));
//old
//#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
//	CCTexture2D* pTexArray[MAP_SPRITE_MAX];
//	for(int i = 0; i < MAP_SPRITE_MAX; ++i)
//	{
//		if ( _mapSprites[i] )
//		{
//			pTexArray[i] = _mapSprites[i]->getTexture();
//		} 
//		else
//		{
//			pTexArray[i] = NULL;
//		}
//	}
//#endif
//
//	/*int bmCol = _totalWidth / _picWidth;
//	int bmRow = _totalHeight / _picHeight;*/
//	std::string rootPath = _rootPath + "%d_%d.jpg";
//	char p[50] = {0};
//
//	for(int i = 0; i < bmRow; ++i)
//	{
//		for(int j = 0; j< bmCol; ++j)
//		{
//			if(_mapSprites[i * bmCol + j])
//			{
//				if(_mapSprites[i * bmCol + j]->getParent() == this)
//					removeChild(_mapSprites[i * bmCol + j], true);
//				_mapSprites[i * bmCol + j] = NULL;
//				//_mapSprites[i * bmCol + j]->release();
//				//if(_mapSprites[i * bmCol + j])
//				//{
//				//	_mapSprites[i * bmCol + j]->release();
//				//}
//
//				//sprintf( p, rootPath.c_str(), j, i );
//				//CCTextureCache::sharedTextureCache()->removeTextureForKey( p );
//			}
//		}
//	}
//
//
//#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
//	for(int i = 0; i < MAP_SPRITE_MAX; ++i)
//	{
//		if ( pTexArray[i] )
//			CCTextureCache::sharedTextureCache()->removeTexture( pTexArray[i] );
//	}
//#endif  // CC_PLATFORM_ANDROID
//
//	for(int i = 0; i < MAP_SPRITE_MAX; ++i)
//	{
//		if(_mapSprites[i] && _mapSprites[i]->getParent() == this)
//		{
//			removeChild(_mapSprites[i], true);
//		}
//	}

//End Kenfly 20121113
}

CCPoint BgBitmap::getMapPos()
{
	return _mapPos;
}

CCSize BgBitmap::getMapSize()
{
	CCSize size;
	//size.width = _w - _offsetX * 2;
	//size.height = _h - _offsetY * 2;
	size.width = bmCol * _picWidth;
	size.height = bmRow * _picHeight;
	return size;
}

CCSize BgBitmap::getMapSizeV()
{
	return _mapSize;
}

void BgBitmap::setMapPos(CCPoint pos)
{
	//int bmCol = _w / _picWidth;
	//int bmRow = _h / _picHeight;

	for(int i = 0; i < bmRow; ++i)
	{
		for(int j = 0; j< bmCol; ++j)
		{
			if((i * bmCol + j) >= MAP_SPRITE_MAX)
				break;
			int x = i * _picWidth - _w / 2;
			int y = _h / 2 - j * _picHeight;
			if(_mapSprites[i * bmCol + j])
				_mapSprites[i * bmCol + j]->setPosition(ccp(pos.x + (float)x, pos.y + (float)y));
		}
	}
}

//Begin Kenfly 20121113 : loadAsync

void BgBitmap::load(CCLayer* layer, CCPoint pos, CCObject* target, SEL_CallFuncO selector)
{
	std::string rootPath = _rootPath + "%d_%d.jpg";
	char p[50] = {0};

	width_left_ = width_left - pos.x;
	width_right_ = width_right - pos.x;
	height_top_ = height_top + pos.y;
	height_bottom_ = height_bottom + pos.y;

	m_needLoadCnt = 0;
	m_loadedCnt = 0;

	for(int i = 0; i < bmRow; ++i)
	{
		for(int j = 0; j< bmCol; ++j)
		{
			if((i * bmCol + j) >= MAP_SPRITE_MAX)
				break;

			sprintf(p, rootPath.c_str(), j, i);
			int index = i * bmCol + j;

			if(j * _picWidth  >= width_left_ && (j + 1) * _picWidth < width_right_
				&& i * _picHeight >= height_top_ && (i + 1) * _picHeight < height_bottom_)
			{
				
				if(_mapSprites[index])
				{
					if(!this->getChildByTag(i * 10 * bmCol + j))
					{
						addChild(_mapSprites[index], -100, i * 10 * bmCol + j);
					}
					continue;
				}

				++m_needLoadCnt;

				CCTexture2D* texture = SourceCacheManage::Instance()->loadBgMap(p);
				if (NULL == texture)   //load small map
				{
					m_callbackDic[std::string(p)] = index;
					SourceCacheManage::Instance()->addEventListener(Event::COMPLETE, this, callfuncND_selector(BgBitmap::loadCompleteHandler));
					int offset = POSX(-128);
					float ofx = (_offsetX == offset ? 0 : _offsetX);
					float ofy = (_offsetY == offset ? 0 : _offsetY);

					float factorX = ((float)_totalWidth + ofx * 2) / (float)POSX(_smallMapSize.width);
					float factorY = ((float)_totalHeight + ofy * 2) / (float)POSX(_smallMapSize.height);

					float x = j * (_picWidth);
					float y = i * (_picHeight);

					x += (ofx);
					y += (ofy);
					if (_smallMap != NULL)
					{
						_mapSprites[index] = CCSprite::spriteWithTexture(_smallMap, CCRectMake(x / factorX, y / factorY, _picWidth / factorX, _picHeight / factorY));
						_mapSprites[index]->setScaleX(factorX);
						_mapSprites[index]->setScaleY(factorY);
					}
				}
				else
				{
					_mapSprites[index] = CCSprite::spriteWithTexture(texture);
				}

				if(_mapSprites[index])
				{
					int x = j * _picWidth + _picWidth / 2 - _totalWidth / 2;
					int y = _totalHeight / 2 - i * _picHeight - _picHeight / 2;
					_mapSprites[index]->setPosition(ccp((float)x, (float)y));
					if(_mapSprites[index]
					&&_mapSprites[index]->getTexture())
					{
						_mapSprites[index]->getTexture()->setAliasTexParameters();
					}

					if(_mapSprites[index]->getParent() != this)
						addChild(_mapSprites[index], -100 , i * 10 * bmCol + j);
					_totalTiles++;
				}
				//_totalTiles++;
			}
			else if(_mapSprites[index])
			{
				if(_mapSprites[index]->getParent() == this)
				{
					//CCTexture2D* pTex = _mapSprites[i * bmCol + j]->getTexture();
					removeChild(_mapSprites[index], true);
					_mapSprites[index] = NULL;
					SourceCacheManage::Instance()->removeBgMap(p);
				}
				_totalTiles --;
			}
		}
	}
}

void BgBitmap::loadCompleteHandler(CCNode* node, void* data)
{
	if (data == NULL)
		return;

	SourceCacheManage::EventInfo* pInfo = (SourceCacheManage::EventInfo*)data;
	std::map<std::string, int>::iterator ix = m_callbackDic.find(pInfo->data);
	if (ix != m_callbackDic.end())
	{
		int index = ix->second;
		int i = index / bmCol;
		int j = index % bmCol;

		CCTexture2D* texture = SourceCacheManage::Instance()->loadBgMap(pInfo->data.c_str());
		if (texture != NULL)
		{
			if (_mapSprites[index] && _mapSprites[index]->getParent() == this)
			{
				this->removeChild(_mapSprites[index], true);
			}

			{
				_mapSprites[index] = CCSprite::spriteWithTexture(texture);
				int x = j * _picWidth + _picWidth / 2 - _totalWidth / 2;
				int y = _totalHeight / 2 - i * _picHeight - _picHeight / 2;
				_mapSprites[index]->setPosition(ccp((float)x, (float)y));
				if(_mapSprites[index] && _mapSprites[index]->getTexture())
				{
					_mapSprites[index]->getTexture()->setAliasTexParameters();
				}

				if(_mapSprites[index]->getParent() != this)
					addChild(_mapSprites[index], -100 , i * 10 * bmCol + j);
			}
		}
		m_callbackDic.erase(ix);
	}
	if (m_callbackDic.empty())
	{
		SourceCacheManage::Instance()->removeEventListener(Event::COMPLETE, this, callfuncND_selector(BgBitmap::loadCompleteHandler));
	}
}

//End Kenfly 20121113 