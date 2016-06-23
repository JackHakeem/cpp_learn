#ifndef HLQS_SourceCacheManage_H_
#define HLQS_SourceCacheManage_H_
#include "utils/BitmapMovieClip.h"
#include "utils/Singleton.h"
#include "utils/flash/CCIEventDispatcher.h"
#include "cocos2d.h"
#include "BaseType.h"

class SourceCacheManage: public Singleton<SourceCacheManage>, public CCIEventDispatcher, public CCObject
{
public:
	SourceCacheManage();
	~SourceCacheManage();
	void put(std::string str, BitmapMovieClip& obj, bool overWrite = false);
	void remove(std::string, bool clean = false);
	BitmapMovieClip* getObject(std::string);
	bool has(const std::string& str);
	int count();
	BitmapMovieClip* load(std::string path, int frame_cnt, float interval = 0.1f, bool overWrite = false);
	BitmapMovieClip* loadNormal(std::string path, std::string frame, int frame_cnt, float interval = 0.1f, bool overWrite = false);
	BitmapMovieClip* loadPvrNormal(std::string path, int resId, int actionType, int direction = 1,
		float interval = 0.1f, bool overWrite = false, bool bLoadAsNPC = false );
	BitmapMovieClip* loadModel(std::string path, int num, float interval = 0.1f, bool overWrite = false, bool bLoadAsNPC = false );
	BitmapMovieClip* loadPVRCommon(int resid, int frame_cnt, float interval = 0.1f, bool overWrite = false);

	void dispose();
	void disposeSkillEffect();
	void reLoadModel( BitmapMovieClip* bit, std::string path, int num, float interval );

	//Begin Kenfly 20121102
	struct EventInfo
	{
		std::string data;
	};

	/*it will get animation from animation cache, but not load from file.*/
	CCAnimation* getAnimation(const char* aniName);
	/*it will load from file sync*/
	CCAnimation* registerAnimation(const char* aniName, const char* frameName, int frameCount, float interval);

	/*****load animation async*****/
	CCAnimation* loadModelAnimation(const char* aniName, const char* frameName, int frameCount, float interval);
	CCAnimation* loadEffectAnimation(int resId, int frameCount, float interval);
	CCTexture2D* loadBgMap(const char* file);

	void removeBgMap(const char* file);
	void disposeAsyncResource();
	void disposeEffect();
	void disposeModel();
	void disposeBgMap();
private:
	std::set<std::string> m_animationContainer;
	std::set<std::string> m_bgMapContainer;
	std::set<std::string> m_loadingSet;

	std::set<int> m_effectResIdContainer;

	void loadModelAnimationCallback(CCObject* object, void* data);
	void loadEffectAnimationCallback(CCObject* object, void* data);
	void loadBgMapCallback(CCObject* object, void* data);
	bool isLoading(const std::string& file);
	//End Kenfly 20121102
public:
	std::map<std::string, BitmapMovieClip> _cacheDic;
	//std::map<std::string, BitmapMovieClip> _skillCacheDic;
	std::vector< int > m_skillResIdContainer;
};

#endif
