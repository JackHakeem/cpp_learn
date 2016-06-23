#include "SourceCacheManage.h"
#include "utils/loader/KKAnimationFactory.h"
#include "model/com/ResourceManage.h"
#include "manager/GlobalManage.h"

SourceCacheManage::SourceCacheManage()
{
}

void SourceCacheManage::put(std::string str, BitmapMovieClip& obj, bool overWrite)
{
	std::map<std::string, BitmapMovieClip>::iterator iter = _cacheDic.find(str);
	if(iter == _cacheDic.end())
	{
		_cacheDic.insert(make_pair(str, obj));
	}
	else if(overWrite)
	{
		iter->second.dispose();

		iter->second = obj;
	}
}

void SourceCacheManage::remove(std::string str, bool clean)
{
	std::map<std::string, BitmapMovieClip>::iterator iter = _cacheDic.find(str);
	if(iter != _cacheDic.end())
	{
		iter->second.dispose(clean);
		_cacheDic.erase(iter);
	}
}
BitmapMovieClip* SourceCacheManage::getObject(std::string str)
{
	std::map<std::string, BitmapMovieClip>::iterator iter = _cacheDic.find(str);
	if(iter != _cacheDic.end())
		return &(iter->second);

	return NULL;
}
bool SourceCacheManage::has(const std::string& str)
{
	std::map<std::string, BitmapMovieClip>::iterator iter = _cacheDic.find(str);
	if(iter != _cacheDic.end())
		return true;

	return false;

	//return _cacheDic.find(str) !=  _cacheDic.end();
}
int SourceCacheManage::count()
{
	return _cacheDic.size();
}

BitmapMovieClip* SourceCacheManage::load(std::string path, int num, float interval, bool overWrite)
{
	//CCAnimation* an = g_pKKAnimationFactory->registAni(path.c_str(), frame.c_str(), frame_cnt, interval);
	BitmapMovieClip* bit = new BitmapMovieClip();
	int result = bit->load(path, num, interval);
	//int result = bit->loadModel(path, num, interval);
	if(result == 0)
	{
		put(path, *bit, overWrite);
		return bit;
	}
	return NULL;
}

BitmapMovieClip* SourceCacheManage::loadModel(std::string path, int num, float interval, bool overWrite, bool bLoadAsNPC/* = false */)
{
	//BitmapMovieClip* bit =  new BitmapMovieClip();
	//std::map<std::string, BitmapMovieClip>::iterator iter = _cacheDic.find(path);
	//if(iter == _cacheDic.end())
	//{
	//	int result = bit->loadModel(path, num, interval);
	//	if(result == 0)
	//	{
	//		put(path, *bit, overWrite);
	//		return bit;
	//	}
	//}
	//else
	//{
	//	BitmapMovieClip* bitCache = &iter->second;
	//	if ( bitCache->m_bLoadAsNPC && !bLoadAsNPC )
	//	{
	//		int result = bit->loadModel(path, num, interval);
	//		if(result == 0)
	//		{
	//			put(path, *bit, true);//over write
	//		}
	//	}
	//	else
	//	{
	//		bitCache->copyToMovieClip( bit );
	//	}
	//	return bit;
	//}

	//bit->dispose(true);
	//CC_SAFE_DELETE( bit );
	return 0;
}


void SourceCacheManage::reLoadModel( BitmapMovieClip* bit, std::string path, int num, float interval )
{
	std::map<std::string, BitmapMovieClip>::iterator iter = _cacheDic.find(path);
	if(iter == _cacheDic.end())
	{
		return;
	}
	else
	{
		//int result = bit->loadModel(path, num, interval);
		//if(result == 0)
		//{
		//	put(path, *bit, true);//over write
		//}
	}
}

BitmapMovieClip* SourceCacheManage::loadNormal(std::string path, std::string frame, int frame_cnt, float interval, bool overWrite)
{
	//CCAnimation* an = g_pKKAnimationFactory->registAni(path.c_str(), frame.c_str(), frame_cnt, interval);
	BitmapMovieClip* bit = new BitmapMovieClip();
	int result = bit->loadNormal(path, frame, frame_cnt, interval);
	if(result == 0)
	{
		put(path, *bit, overWrite);
		return bit;
	}

	bit->dispose(true);
	CC_SAFE_DELETE( bit );
	return NULL;
}

BitmapMovieClip* SourceCacheManage::loadPvrNormal(std::string path, int resId, int actionType, int direction /*= 1*/,
	float interval, bool overWrite, bool bLoadAsNPC/* = false*/ )
{
	BitmapMovieClip* bit =  new BitmapMovieClip();
	std::map<std::string, BitmapMovieClip>::iterator iter = _cacheDic.find(path);
	if(iter == _cacheDic.end())
	{
		int result = bit->loadPvrNormal( path, resId, actionType, direction, interval );
		if(result == 0)
		{
			bit->m_bLoadAsNPC = bLoadAsNPC;
			put(path, *bit, overWrite);
			return bit;
		}
	}
	else
	{
		BitmapMovieClip* bitCache = &iter->second;
		if ( bitCache->m_bLoadAsNPC && !bLoadAsNPC )
		{
			int result = bit->loadPvrNormal( path, resId, actionType, direction, interval );
			if(result == 0)
			{
				put(path, *bit, true);//over write
			}
		}
		else
		{
			bitCache->copyToMovieClip( bit );
		}
		return bit;
	}

	bit->dispose(true);
	CC_SAFE_DELETE( bit );
	return 0;
}

BitmapMovieClip* SourceCacheManage::loadPVRCommon( int resid, int frame_cnt, float interval /*= 0.1f*/, bool overWrite /*= false*/ )
{
	string _assetURL = ResourceManage::Instance()->skillUrl();

	char fmt[54];
	sprintf( fmt, "/effect-%d.plist", /*pListId*/resid );
	string path = _assetURL + fmt;

	sprintf( fmt, "%d/image0", resid );
	string frame =  std::string(fmt) + "%d.png";

	BitmapMovieClip* bit =  new BitmapMovieClip();
	std::map<std::string, BitmapMovieClip>::iterator iter = _cacheDic.find(frame);
	if(iter == _cacheDic.end())
	{
		int result = bit->loadPVRCommon(path, frame, frame_cnt, interval);
		if(result == 0)
		{
			put(frame, *bit, overWrite);

			m_skillResIdContainer.push_back( resid );
			return bit;
		}
	}
	else
	{
		BitmapMovieClip* bitCache = &iter->second;
		bitCache->copyToMovieClip( bit );
		return bit;
	}

	bit->dispose(true);
	//CC_SAFE_DELETE( bit );
	bit->release(); // LH0714
	return 0;
}

void SourceCacheManage::dispose()
{
	//std::map<std::string, BitmapMovieClip>::iterator iter;
	//for ( iter = _cacheDic.begin(); iter != _cacheDic.end(); iter++ )
	//{
	//	iter->second.dispose(true);
	//}
	_cacheDic.clear();

	//Begin Kenfly 20121116
	disposeAsyncResource();
	//End Kenfly 20121116
}

SourceCacheManage::~SourceCacheManage()
{
	dispose();
}

void SourceCacheManage::disposeSkillEffect()
{
	//jae: remove spriteFrame & animation & texture.
	string resUrl = ResourceManage::Instance()->skillUrl();
	string _assetURL = "";//plist url
	char fmt[54];
	for( std::vector<int>::iterator iter = m_skillResIdContainer.begin();
		iter != m_skillResIdContainer.end();
		iter++ )
	{
		int resid = *iter;
		sprintf( fmt, "/effect-%d.plist", /*pListId*/resid );
		_assetURL = resUrl + fmt;

		sprintf( fmt, "%d/image0", resid );
		string frame =  std::string(fmt) + "%d.png";

		//frame
		CCAnimationCache::sharedAnimationCache()->removeAnimationByName( frame.c_str() );
		//sprite frame
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile( _assetURL.c_str() );

		sprintf( fmt, "/effect-%d.png", resid );
		std::string pathKey = resUrl + fmt;
		CCFileUtils::removeSuffixFromFile(pathKey);
		pathKey = CCFileUtils::fullPathFromRelativePath(pathKey.c_str());
		CCTextureCache::sharedTextureCache()->removeTextureForKey(pathKey.c_str());

		SourceCacheManage::Instance()->remove( frame, true );
	}
}

//Begin Kenfly 20121109

CCAnimation* SourceCacheManage::getAnimation(const char* aniName)
{
	return CCAnimationCache::sharedAnimationCache()->animationByName(aniName);
}

CCAnimation* SourceCacheManage::registerAnimation(const char* aniName, const char* frameName, int frameCount, float interval)
{
	CCAnimation* animation = g_pKKAnimationFactory->registAni(aniName, frameName, frameCount, interval);
	if (animation)
		m_animationContainer.insert(std::string(frameName));
	else
		m_animationContainer.erase(std::string(frameName));

	return animation;
}

CCAnimation* SourceCacheManage::loadModelAnimation(const char* aniName, const char* frameName, int frameCount, float interval)
{
	if (isLoading(aniName))
		return 0;

	typedef struct _LoadModelCallback
	{
		std::string aniName;
	} LoadModelCallback;
	LoadModelCallback* pInfo = new LoadModelCallback();

	pInfo->aniName = std::string(aniName);
	CCAnimation* ani = g_pKKAnimationFactory->registAnimationAsync(aniName, frameName, frameCount, interval, this, callfuncOD_selector(SourceCacheManage::loadModelAnimationCallback), (void*)pInfo);
	if (ani != NULL)
	{
		CC_SAFE_DELETE(pInfo);
		return ani;
	}

	m_loadingSet.insert(std::string(aniName));

	return 0;
}

CCAnimation* SourceCacheManage::loadEffectAnimation(int resId, int frameCount, float interval)
{
	string _assetURL = ResourceManage::Instance()->skillUrl();

	char fmt[54];
	sprintf( fmt, "/effect-%d.plist", resId );
	string path = _assetURL + fmt;

	sprintf( fmt, "%d/image0", resId );
	string frame =  std::string(fmt) + "%d.png";

	if (isLoading(path))
		return 0;

	typedef struct _LoadEffectCallback
	{
		int resId;
		std::string aniName;
	} LoadEffectCallback;
	LoadEffectCallback* pInfo = new LoadEffectCallback();

	pInfo->resId = resId;
	pInfo->aniName = path;
	CCAnimation* ani = g_pKKAnimationFactory->registAnimationAsync(path.c_str(), frame.c_str(), frameCount, interval, this, callfuncOD_selector(SourceCacheManage::loadEffectAnimationCallback), (void*)pInfo);
	if (ani != NULL)   //return back sync
	{
		CC_SAFE_DELETE(pInfo);
		return ani;
	}

	m_loadingSet.insert(path);

	return 0;
}

CCTexture2D* SourceCacheManage::loadBgMap(const char* file)
{
	if (m_bgMapContainer.find(file) != m_bgMapContainer.end())
	{
		CCTexture2D* texture = NULL;
		texture = CCTextureCache::sharedTextureCache()->addImage(file);
		if (texture != NULL)
			return texture;
	}

	if (isLoading(file))
		return 0;

	m_loadingSet.insert(std::string(file));

	typedef struct 
	{
		std::string fileName;
	} LoadBgMapCallback;
	LoadBgMapCallback* pData = new LoadBgMapCallback();

	pData->fileName = file;
	CCTextureCache::sharedTextureCache()->addImageAsync(file, this, callfuncOD_selector(SourceCacheManage::loadBgMapCallback), (void*)pData);
	return 0;
}

void SourceCacheManage::loadModelAnimationCallback(CCObject* object, void* data)
{
	if (NULL == data)
		return;

	typedef struct 
	{
		std::string aniName;
	} LoadModelCallback;
	LoadModelCallback* pCallback = (LoadModelCallback*)data;

	m_loadingSet.erase(pCallback->aniName);

	if (NULL == object) //load fail
	{
		CC_SAFE_DELETE(pCallback);
		return;
	}

	m_animationContainer.insert(pCallback->aniName);

	EventInfo * pInfo = new EventInfo();
	pInfo->data = pCallback->aniName;
	
	SourceCacheManage::Instance()->dispatchEvent(Event::COMPLETE, (void*)pInfo);

	CC_SAFE_DELETE(pCallback);
	CC_SAFE_DELETE(pInfo);
}

void SourceCacheManage::loadEffectAnimationCallback(CCObject* object, void* data)
{
	typedef struct _LoadEffectCallback
	{
		int resId;
		std::string aniName;
	} LoadEffectCallback;
	LoadEffectCallback* pCallback = (LoadEffectCallback*)data;

	m_loadingSet.erase(pCallback->aniName);

	if (NULL == object)
	{
		CC_SAFE_DELETE(pCallback);
		return;
	}

	m_effectResIdContainer.insert(pCallback->resId);

	CC_SAFE_DELETE(pCallback);
	if (! g_pGlobalManage->getisInFight())
	{
		disposeEffect();
	}
}

void SourceCacheManage::loadBgMapCallback(CCObject* object, void* data)
{
	if (NULL == data)
		return;

	typedef struct 
	{
		std::string fileName;
	}BgMapInfo;
	BgMapInfo* pData = (BgMapInfo*)data;
	
	m_loadingSet.erase(pData->fileName);
	if (NULL == object)
	{
		CC_SAFE_DELETE(pData);
		return;
	}
	m_bgMapContainer.insert(pData->fileName);

	EventInfo* pInfo = new EventInfo();
	pInfo->data = pData->fileName;
	
	dispatchEvent(Event::COMPLETE, (void*)pInfo);

	CC_SAFE_DELETE(pData);
	CC_SAFE_DELETE(pInfo);
}

bool SourceCacheManage::isLoading(const std::string& file)
{
	return m_loadingSet.find(file) != m_loadingSet.end();
}

void SourceCacheManage::removeBgMap(const char* file)
{
	std::set<std::string>::iterator ix = m_bgMapContainer.find(std::string(file));
	if (ix != m_bgMapContainer.end())
	{
		std::string pathKey = file;
		CCFileUtils::removeSuffixFromFile(pathKey);

		pathKey = CCFileUtils::fullPathFromRelativePath(pathKey.c_str());
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->textureForKey(pathKey.c_str());
		if (texture && texture->retainCount() == 1)
		{
			CCTextureCache::sharedTextureCache()->removeTextureForKey(pathKey.c_str());
			m_bgMapContainer.erase(ix);
		}
	}
}

void SourceCacheManage::disposeEffect()
{
	string _assetURL = ResourceManage::Instance()->skillUrl();

	char fmt[100];

	string path = _assetURL + "/effect-%d.plist";

	std::vector<int> delVec;
	for( std::set<int>::iterator iter = m_effectResIdContainer.begin(); iter != m_effectResIdContainer.end(); iter++ )
	{
		int resid = *iter;
		sprintf(fmt, path.c_str(), resid);
		CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName(fmt);
		
		if (animation && animation->retainCount() == 1)
		{
			CCAnimationCache::sharedAnimationCache()->removeAnimationByName(fmt);
			delVec.push_back(resid);
		}
	}
	for (std::vector<int>::iterator ix = delVec.begin(); ix != delVec.end(); ++ix)
	{
		m_effectResIdContainer.erase(*ix);
	}
	delVec.clear();
}

void SourceCacheManage::disposeModel()
{
	std::vector<std::string> delVec;
	std::set<std::string>::iterator iter;
	for (iter = m_animationContainer.begin(); iter != m_animationContainer.end(); ++iter)
	{
		CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName(iter->c_str());
		if (animation && animation->retainCount() == 1)
		{
			CCAnimationCache::sharedAnimationCache()->removeAnimationByName(iter->c_str());
			delVec.push_back(*iter);
		}
	}
	std::vector<std::string>::iterator ix;
	for (ix = delVec.begin(); ix != delVec.end(); ++ix)
	{
		m_animationContainer.erase(*ix);
	}
	delVec.clear();
}

void SourceCacheManage::disposeBgMap()
{
	std::vector<std::string> delVec;
	std::set<std::string>::iterator ix;
	for (ix = m_bgMapContainer.begin(); ix != m_bgMapContainer.end(); ++ix)
	{
		std::string pathKey = *ix;
		CCFileUtils::removeSuffixFromFile(pathKey);

		pathKey = CCFileUtils::fullPathFromRelativePath(pathKey.c_str());
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->textureForKey(pathKey.c_str());
		if (texture && texture->retainCount() == 1)
		{
			CCTextureCache::sharedTextureCache()->removeTextureForKey(pathKey.c_str());
			delVec.push_back(*ix);
		}
	}
	std::vector<std::string>::iterator iter;
	for (iter = delVec.begin(); iter != delVec.end(); ++iter)
	{
		m_bgMapContainer.erase(*iter);
	}
	delVec.clear();
}

void SourceCacheManage::disposeAsyncResource()
{
	disposeEffect();
	disposeModel();
	disposeBgMap();
	//CCTextureCache::sharedTextureCache()->removeUnusedTextures();
	//CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
	//CCTextureCache::sharedTextureCache()->description();
}
//End Kenfly 20121109