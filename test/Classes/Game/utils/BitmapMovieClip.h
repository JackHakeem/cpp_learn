#ifndef HLQS_BitmapMovieClip_H_
#define HLQS_BitmapMovieClip_H_
#include "cocos2d.h"

USING_NS_CC;

class BitmapMovieClip: public CCLayer
{
public:
	BitmapMovieClip();
	~BitmapMovieClip();
	void setData(float x, float y, CCAnimation* an);
	void runActionEx(int actionNum, int dirState, bool repeat = true, CCSprite* sprite = NULL);
	void runActionNormal(CCSprite* sprite = NULL);
	void runActionPvrNormal( int dirState, CCSprite* sprite );
	void stopActionEx();
	void dispose(bool clean = false);

	int load(std::string path, int frame_cnt, float interval = 0.1f);
	int loadNormal(std::string path, std::string frameName, int frame_cnt, float interval);

	void setAlpha(int value);
	CCSize getSize();

	static bool isFileExist( std::string filePath );

	//int loadModel(std::string path, int resId, float interval = 0.1f);
	int loadPvrNormal( std::string path1, int resId, int actionType, int direction /*= 1*/, float interval /*= 0.1f*/ );
	int loadPVRCommon( std::string path, std::string frameName, int frame_cnt, float interval );
	CCSprite* runActionPVRCommon( cocos2d::CCCallFunc *callBack );
	CCSprite* runActionPVRCommonRepeat();
	void runActionExCallBack();

	void copyToMovieClip( BitmapMovieClip* pBitmapMovieClip );
	void endHandler( CCNode* pnode);
	CCSprite *getPlayerSprite();
	void runActionNormal(int actionNum, int dirState, bool repeat = true, CCSprite* sprite = NULL);
	
	//Begin Kenlfy 20121102

	int loadPvrNormalAsync(std::string path, int resId, int actionType, int direction, float interval, CCObject* target = NULL, SEL_CallFuncOD selector = NULL, void* pData = NULL);
	void loadModelAsync(std::string path, int resId, float interval = 0.1f, CCObject* target = NULL, SEL_CallFuncOD selector = NULL, void* pData = NULL);
	int loadPvrCommonAsync(int resId, int frame_cnt, float interval);
	int loadNormalAsync(std::string path, std::string frameName, int frame_cnt, float interval, CCObject* target = NULL, SEL_CallFuncOD selector = NULL, void* pData = NULL);
private:
	void loadCompleteHandler(CCNode* node, void* pData);

	typedef struct _CallbackInfo 
	{
		_CallbackInfo(CCObject* o = NULL, SEL_CallFuncOD s = NULL, void* d = NULL, int at = ACTION_MAX, int dir = 0)
			: target(o), selector(s), data(d), actionType(at), direction(dir) {} 
		CCObject* target;
		SEL_CallFuncOD selector;
		void* data;
		int actionType;
		int direction;
	}CallbackInfo;
	std::map<std::string, CallbackInfo> m_callbackDic;
	//End Kenfly 20121102
public:

	enum
	{
		ACTION_STAND = 0,
		ACTION_WALK,
		ACTION_HIT,
		ACTION_ATTACK,
		ACTION_NORMAL,
		ACTION_PVR_NORMAL,
		ACTION_COMMON,
		ACTION_MAX,
	};
	//CCSprite * playeSprite;

	float _x;
	float _y;
	int _alpha;
	int _delay;
	int _runActionExDir;
	CCAnimation* normalAnimation;
	bool m_bLoadAsNPC;
	int m_resId;
	CCAnimation* mCurrentAnimation;

private:
	CCAnimation* m_animation[ACTION_MAX][5];
	int _currentAction;
	int _currentDirection;
	bool _bActionRepeat;
};



#endif