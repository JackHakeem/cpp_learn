#include "BitmapMovieClip.h"
#include "utils/loader/KKAnimationFactory.h"
#include "effect/FightEffectGroup.h"
#include "ScaleUtil.h"
#include "model/com/ResourceManage.h"
#include "manager/SourceCacheManage.h"
#include "manager/GlobalManage.h"

const int TAG_PLAYER_SPRITE = 1001;
const int TAG_PLAYER_SPRITE_REPEAT = 1002;
const int g_direction[] = {0, 1, 2, 1, 4, 5, 4, 7, 8, 7};
const int g_index[] = {0, 0, 1, 0, 2, 0, 2, 3, 4, 3};

BitmapMovieClip::BitmapMovieClip()
{
	m_resId = -1;
	_x = 0.0f;
	_y = 0.0f;
	_alpha = 255;
	_delay = 0;
	m_bLoadAsNPC = true;

	for (int i = 0; i < ACTION_MAX; ++i)
	{
		for(int j = 0; j < 5; ++j)
		{
			m_animation[i][j] = 0;
		}
	}
	_currentAction = ACTION_MAX;
	_currentDirection = 0;

	normalAnimation = NULL;
	_runActionExDir = 0;

	CCLayer::init();
}

void BitmapMovieClip::setAlpha(int value)
{
	_alpha = value;
	//Doyang 20120714
	CCSprite *pPlayerSprite = (CCSprite *) this->getChildByTag(TAG_PLAYER_SPRITE);
	CC_ASSERT(pPlayerSprite);
	if(pPlayerSprite)
	{
		pPlayerSprite->setOpacity(_alpha);
	}
	/*if(playeSprite)
	playeSprite->setOpacity(_alpha);*/
}

void BitmapMovieClip::setData(float x, float y, CCAnimation* an)
{
	_x = x;
	_y = y;
}

void BitmapMovieClip::runActionEx(int actionNum, int dirState, bool repeat, CCSprite* sprite)
{
	CCSprite *pPlayerSprite = getPlayerSprite();
	if (! pPlayerSprite || actionNum < 0 || actionNum >= ACTION_MAX || dirState < 0 || dirState > 9)
	{
		if(!repeat)
		{
			FightEffectGroup::Instance()->completeOneAction();
		}
		return;
	}

	_currentAction = actionNum;
	_currentDirection = dirState;
	_bActionRepeat = repeat;

	float interval = 0.2f;
	_runActionExDir = dirState;
	bool turn = false;
	if (dirState == 3 || dirState == 6 || dirState == 9)
		turn = true;

	pPlayerSprite->stopAllActions();
	//remove the clicked effect
	CCActionInterval* pBrightAction = CCTintTo::actionWithDuration(0.01f, 255, 255, 255);
	if (pBrightAction)
		pPlayerSprite->runAction(pBrightAction);

	CCAnimation* pAnimation = m_animation[actionNum][g_index[dirState]];
	CCAnimate* animate = NULL;
	if (! pAnimation || ! (animate = CCAnimate::actionWithAnimation(pAnimation)))
	{
		pPlayerSprite->stopAllActions();
		pPlayerSprite->removeAllChildrenWithCleanup(true);
		pPlayerSprite->initWithFile("assets/res/default_sprite.png");

		if(!repeat)
		{
			FightEffectGroup::Instance()->completeOneAction();
		}
		return;
	}

	CCActionInterval* seq = NULL;

	pPlayerSprite->setOpacity(_alpha);
	pPlayerSprite->setIsVisible(true);

	ResourceVo* res = ResourceManage::Instance()->getRes( 1, m_resId );
	if (!res)
	{
		return;
	}
    
    if (m_resId == 1000)
    {
         pPlayerSprite->setPosition(ccp(-44, 176));
    }
    else
    {
        int G_DIR[8] = {1, 2, 3, 6, 9, 8, 7, 4};
        int dirIndex = -1;
        for (int i = 0; i < 8; i++)
        {
            if (G_DIR[i] == dirState)
            {
                dirIndex = i;
                break;
            }
        }
        
        if (dirIndex != -1)
        {
            ResVoPoint p = res->offset[dirIndex+actionNum*8];
            float x = (float)p.x;
            float y = (float)p.y;
            pPlayerSprite->setPosition(ccp(POSX(x), POSX(y)));
        }
        else
        {
            CCLog("error");
        }
    }

	if(repeat)
	{
		seq = (CCActionInterval*)(CCSequence::actions(CCFlipX::actionWithFlipX(turn), animate, NULL));
		pPlayerSprite->runAction(CCRepeatForever::actionWithAction(seq));
	}
	else
	{
		seq = (CCActionInterval*)(CCSequence::actions(CCFlipX::actionWithFlipX(turn), animate, 
			CCCallFunc::actionWithTarget(this, callfunc_selector(BitmapMovieClip::runActionExCallBack)), NULL));
		pPlayerSprite->runAction(seq);
	}
}

void BitmapMovieClip::runActionExCallBack() 
{
	FightEffectGroup::Instance()->completeOneAction();
	runActionEx(BitmapMovieClip::ACTION_STAND, _runActionExDir);
	//FightEffectGroup::Instance()->completeOneAction();
	//cocos2d::CCLog("---------------------------BitmapMovieClip::runActionExCallBack");
}

void BitmapMovieClip::runActionNormal(CCSprite* sprite)
{
	_currentAction = ACTION_NORMAL;
	_currentDirection = 0;
	_bActionRepeat = true;

	CCAnimation* pAnimation = m_animation[ACTION_NORMAL][0];
	if (! pAnimation)
	{
		return;
	}

	//Doyang 20120714
	CCSprite *pPlayerSprite = this->getPlayerSprite();
	pPlayerSprite->stopAllActions();
	pPlayerSprite->setOpacity(_alpha);
	pPlayerSprite->setIsVisible(true);
	pPlayerSprite->runAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(pAnimation)));
}

void BitmapMovieClip::runActionPvrNormal( int dirState, CCSprite* sprite )
{
	CCSprite *pPlayerSprite = this->getPlayerSprite();
	if (! pPlayerSprite || dirState < 0 || dirState > 9)
		return;

	_currentAction = ACTION_PVR_NORMAL;
	_currentDirection = dirState;
	_bActionRepeat = true;

	bool turn = false;

	if (dirState == 3 || dirState == 6 || dirState == 9)
		turn = true;

	CCAnimation* pAnimation = m_animation[ACTION_NORMAL][g_index[dirState]];
	CCAnimate* animate = NULL;
	if(! pAnimation || (animate = CCAnimate::actionWithAnimation(pAnimation)))
	{
		return;
	}

	pPlayerSprite->stopAllActions();

	CCActionInterval* seq = NULL;
	seq = (CCActionInterval*)(CCSequence::actions(CCFlipX::actionWithFlipX(turn), animate, NULL));
	pPlayerSprite->runAction(CCRepeatForever::actionWithAction(seq));
}

void BitmapMovieClip::stopActionEx()
{
	CCSprite *pPlayerSprite = this->getPlayerSprite();
	if(!pPlayerSprite)
	{
		return;
	}
	this->setPosition(0.0f, 0.0f);
	pPlayerSprite->stopAllActions();
}

void BitmapMovieClip::dispose(bool clean)
{
	if(clean)
	{
		//CC_SAFE_DELETE( normalAnimation );
		normalAnimation = 0;
		for (int i = 0; i < ACTION_MAX; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				CC_SAFE_RELEASE_NULL(m_animation[i][j]);
			}
		}
		//Doyang 20120714
		this->removeChildByTag(TAG_PLAYER_SPRITE, true);
	}

}

int BitmapMovieClip::load(std::string path, int frame_cnt, float interval /* = 0.1f */)
{
	return 0;
}

int BitmapMovieClip::loadNormal(std::string path, std::string frameName, int frame_cnt, float interval)
{
    
	if(normalAnimation)
		normalAnimation->release();

	if(g_pKKAnimationFactory)
		normalAnimation = g_pKKAnimationFactory->registAni(path.c_str(), frameName.c_str(), frame_cnt, interval);

	return 0;
}

CCSize BitmapMovieClip::getSize()
{
	//Begin Kenfly 20121024
	CCSize sz(100, 100);
	const float min = POSX(5.0f);
	const float max = POSX(400.0f);
	CCSprite* pSprite = (CCSprite*)this->getChildByTag(TAG_PLAYER_SPRITE);
	if (pSprite)
	{
		sz = pSprite->getTextureRect().size;
	}
	if (sz.width < min)
		sz.width = 50.0f;
	if (sz.width > max)
		sz.width = max;
	if (sz.height < min)
		sz.height = 100.0f;
	if (sz.height > max)
		sz.height = max;
	return sz;
	//End Kenfly 20121024
}

// Jae judge file exist or not
bool BitmapMovieClip::isFileExist( std::string filePath )
{
	CCFileUtils::removeSuffixFromFile(filePath);

	//Doyang 20120924
	// For SDCard
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	FILE *fp = fopen( CCFileUtils::fullPathFromSDCard( filePath.c_str() ), "r" );
#else
	FILE *fp = fopen( CCFileUtils::fullPathFromRelativePath( filePath.c_str() ), "r" );
#endif
	bool bRet = false;

	if (fp)
	{
		bRet = true;
		fclose(fp);
	}

	return bRet;
}

// path �� resId�� action type like stand�� direciton
int BitmapMovieClip::loadPvrNormal( std::string path1, int resId, int actionType, int direction /*= 1*/, float interval /*= 0.1f*/ )
{
	m_resId = resId;

	int dirState = direction;
	if(dirState == 1)
		direction = 1;
	else if(dirState == 2)
		direction = 2;
	else if(dirState == 4)
		direction = 4;
	else if(dirState == 7)
		direction = 7;
	else if(dirState == 8)
		direction = 8;
	else if(dirState == 3)
	{
		direction = 1;
	}
	else if(dirState == 6)
	{
		direction = 4;
	}
	else if(dirState == 9)
	{
		direction = 7;
	}

	int frame_cnt = 25;
	char path[128] = {0};
	//int directionArray[5] = {1, 2, 4, 7, 8};
	std::string frameName;

	//sprintf( path, "/model-%d.plist", resId );
	//std::string filePath = path1 + path;
	std::string filePath;

	//if ( !isFileExist( filePath ) )
	//{
	//	return -1;
	//}

	if(normalAnimation)
		normalAnimation->release();

	switch ( actionType )
	{
	case ACTION_STAND:
		sprintf( path, "/stand-%d.plist", direction );
		filePath = path1 + path;
		sprintf( path, "%d/stand-%d", resId, direction );	// 1/stand-8-9.png
		frameName = std::string(path) + "-000%d.png";
		break;
	case ACTION_WALK:
		sprintf( path, "/walk-%d.plist", direction );
		filePath = path1 + path;
		sprintf( path, "%d/walk-%d", resId, direction );
		frameName = std::string(path) + "-000%d.png";
		break;
	case ACTION_HIT:
		sprintf( path, "/hit-%d.plist", direction );
		filePath = path1 + path;
		sprintf( path, "%d/hit-%d", resId, direction );
		frameName = std::string(path) + "-000%d.png";
		break;
	case ACTION_ATTACK:
		sprintf( path, "/attack-%d.plist", direction );
		filePath = path1 + path;
		sprintf( path, "%d/attack-%d", resId, direction );
		frameName = std::string(path) + "-000%d.png";
		break;
	}

	//animationStand[0] = g_pKKAnimationFactory->registModelAnimation( filePath.c_str(), frameName.c_str(), frame_cnt, interval );
	mCurrentAnimation = g_pKKAnimationFactory->registModelAnimation( filePath.c_str(), frameName.c_str(), frame_cnt, interval );
	//mCurrentAnimation = g_pKKAnimationFactory->registModelAnimationAsync( filePath.c_str(), frameName.c_str(), frame_cnt, interval );
	//mCurrentAnimation = SourceCacheManage::Instance()->loadModelAnimation( filePath.c_str(), frameName.c_str(), frame_cnt, interval ); //Kenfly 20121112
	if (!mCurrentAnimation)
	{
		return -1;
	}

	return 0;
}

int BitmapMovieClip::loadPVRCommon( std::string path, std::string frameName, int frame_cnt, float interval )
{
	/*
	if ( !isFileExist( path ) )//kevinchange0813
	{
		return -1;
	}
	*/
	//normalAnimation = 0;
	if(normalAnimation)
		normalAnimation->release();

	if(g_pKKAnimationFactory)
		normalAnimation = g_pKKAnimationFactory->registModelAnimation(path.c_str(), frameName.c_str(), frame_cnt, interval);//SourceCacheManage::Instance()->loadModelAnimation(path.c_str(), frameName.c_str(), frame_cnt, interval);//interval kevine, modified kenfly

	if (!normalAnimation)
		return -1;
	
	return 0;
}

CCSprite* BitmapMovieClip::runActionPVRCommon( cocos2d::CCCallFunc *callBack )
{
	_currentAction = ACTION_COMMON;
	_currentDirection = 0;
	_bActionRepeat = false;
	CCSprite *pPlayerSprite = this->getPlayerSprite();
	CCAnimation* pAnimation = m_animation[ACTION_COMMON][0];
	if (!pAnimation || ! pPlayerSprite)
	{
		if (callBack)
			callBack->execute();
		return 0;
	}
	
	pPlayerSprite->stopAllActions();
	pPlayerSprite->setOpacity(_alpha);
	pPlayerSprite->setIsVisible(true);
	pPlayerSprite->setRotation(0);//keviny

	if ( GlobalScale::Instance()->getStandardWidth()== 480 )
		pPlayerSprite->setScale(2.0f);
	cocos2d::CCFiniteTimeAction *action = cocos2d::CCSequence::actions(
		cocos2d::CCAnimate::actionWithAnimation(pAnimation), 
		callBack, 
		NULL );
	pPlayerSprite->runAction( action );
	return pPlayerSprite;
}

CCSprite* BitmapMovieClip::runActionPVRCommonRepeat()
{
	_currentAction = ACTION_COMMON;
	_currentDirection = 0;
	_bActionRepeat = true;
	CCAnimation* pAnimation = m_animation[ACTION_COMMON][0];
	if (! pAnimation)
	{
		return 0;
	}

	CCSprite *pPlayerSprite = (CCSprite *) this->getChildByTag(TAG_PLAYER_SPRITE_REPEAT);
	if(!pPlayerSprite)
	{
		pPlayerSprite = new CCSprite();
		pPlayerSprite->init();
		this->addChild(pPlayerSprite, 0, TAG_PLAYER_SPRITE_REPEAT);
		pPlayerSprite->release();
	}

	pPlayerSprite->stopAllActions();
	pPlayerSprite->setOpacity(_alpha);
	pPlayerSprite->setIsVisible(true);
	pPlayerSprite->setRotation(0);
	if ( GlobalScale::Instance()->getStandardWidth()== 480 )
		pPlayerSprite->setScale(2.0f);
	pPlayerSprite->runAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(pAnimation)));

	return pPlayerSprite;
}

void BitmapMovieClip::copyToMovieClip( BitmapMovieClip* pBitmapMovieClip )
{
	if ( pBitmapMovieClip )
	{
		pBitmapMovieClip->normalAnimation = normalAnimation;
		pBitmapMovieClip->m_resId = m_resId;
	}
}

BitmapMovieClip::~BitmapMovieClip()
{
	//Begin Kenfly 20121108
	SourceCacheManage::Instance()->removeEventListener(Event::COMPLETE, this, callfuncND_selector(BitmapMovieClip::loadCompleteHandler));
	dispose(true);
	//End Kenfly 20121108
}

CCSprite * BitmapMovieClip::getPlayerSprite()
{
	CCSprite *pPlayerSprite = (CCSprite *)this->getChildByTag(TAG_PLAYER_SPRITE);
	if(! pPlayerSprite)
	{
		pPlayerSprite = new CCSprite();
		pPlayerSprite->init();
		this->addChild(pPlayerSprite, 0, TAG_PLAYER_SPRITE);
		pPlayerSprite->release();
	}
	return pPlayerSprite;
}

void BitmapMovieClip::endHandler( CCNode* pnode)
{
	if (!this->getParent())
	{
		CCLog("BUG void BitmapMovieClip::endHandler( CCNode* pnode, void* data)");
		return;
	}
	this->dispose(true);
	this->removeFromParentAndCleanup(true);
}

void BitmapMovieClip::runActionNormal( int actionNum, int dirState, bool repeat /*= true*/, CCSprite* sprite /*= NULL*/ )
{
	CCSprite *pPlayerSprite = this->getPlayerSprite();
	if (! pPlayerSprite || actionNum < 0 || actionNum > ACTION_MAX || dirState < 0 || dirState > 9)
	{
		if(!repeat)
		{
			FightEffectGroup::Instance()->completeOneAction();
		}
		return;
	}

	_runActionExDir = dirState;
	_currentAction = actionNum;
	_currentDirection = dirState;

	CCAnimation* pAnimation = m_animation[actionNum][g_index[dirState]];

	bool turn = false;

	if (dirState == 3 || dirState == 6 || dirState == 9)
		turn = true;

	CCAnimate* animate = NULL;
	if (!pAnimation || !(animate = CCAnimate::actionWithAnimation(pAnimation)))
	{
		pPlayerSprite->stopAllActions();
		pPlayerSprite->removeAllChildrenWithCleanup(true);
		pPlayerSprite->initWithFile("assets/res/default_sprite.png");

		if(!repeat)
		{
			FightEffectGroup::Instance()->completeOneAction();
		}
		return;
	}

	CCActionInterval* seq = NULL;

	pPlayerSprite->setOpacity(_alpha);
	pPlayerSprite->setIsVisible(true);

	ResourceVo* res = ResourceManage::Instance()->getRes( 1, m_resId );
	if (!res)
	{
		return;
	}
    
    if (m_resId == 1000)
    {
         pPlayerSprite->setPosition(ccp(-44, 176));
    }
    else
    {
        int G_DIR[8] = {1, 2, 3, 6, 9, 8, 7, 4};
        int dirIndex = -1;
        for (int i = 0; i < 8; i++)
        {
            if (G_DIR[i] == dirState)
            {
                dirIndex = i;
                break;
            }
        }
        
        if (dirIndex != -1)
        {
            ResVoPoint p = res->offset[dirIndex+actionNum*8];
            float x = (float)p.x;
            float y = (float)p.y;
            pPlayerSprite->setPosition(ccp(x, y));
        }
        else
        {
            CCLog("error");
        }
    }

	if(repeat)
	{
		seq = (CCActionInterval*)(CCSequence::actions(CCFlipX::actionWithFlipX(turn), animate, NULL));
		pPlayerSprite->runAction(CCRepeatForever::actionWithAction(seq));
	}
	else
	{
		seq = (CCActionInterval*)(CCSequence::actions(CCFlipX::actionWithFlipX(turn), animate, 
			CCCallFunc::actionWithTarget(this, callfunc_selector(BitmapMovieClip::runActionExCallBack)), NULL));
		pPlayerSprite->runAction(seq);
	}
}


//Begin Kenfly 20121102
void BitmapMovieClip::loadModelAsync(std::string path, int resId, float interval, CCObject* target, SEL_CallFuncOD selector, void* pData)
{
	m_resId = resId;
	int frame_cnt = 25;
	const int direction[5] = {1, 2, 4, 7, 8};

	//ResourceVo* res = ResourceManage::Instance()->getRes(1, resId);
	//if (NULL == res)
	//	return;
	interval = 0.125;

	// stand 
	for ( int i = 0; i < 5; i++ )
	{
		loadPvrNormalAsync(path.c_str(), m_resId, ACTION_STAND, direction[i], 0.3f, target, selector, pData);
	}

	// walk 
	for ( int i = 0; i < 5; i++ )
	{
		loadPvrNormalAsync(path.c_str(), m_resId, ACTION_WALK, direction[i], interval, target, selector, pData);
	}

	//// hit 
	for ( int i = 0; i < 5; i++ )
	{
		loadPvrNormalAsync(path.c_str(), m_resId, ACTION_HIT, direction[i], 0.25f, target, selector, pData);
	}

	// attack 
	for ( int i = 0; i < 5; i++ )
	{
		if ( resId == 6 )//Ů��ʿ 10
		{
			interval = 1.0f/10.0f;
		}
		else if ( (resId == 4)|| (resId==9) )//��Ůħ�� 6
		{
			interval = 1.0f/6.0f;
		}
		else
		{
			interval = 0.125;
		}

		loadPvrNormalAsync(path.c_str(), m_resId, ACTION_ATTACK, direction[i], interval, target, selector, pData);
	}
}

int BitmapMovieClip::loadPvrNormalAsync(std::string path1, int resId, int actionType, int direction, float interval, CCObject* target, SEL_CallFuncOD selector, void* pData)
{
	if (actionType < 0 || actionType >= ACTION_MAX || direction < 0 || direction > 9)
	{
		return -1;
	}

	m_resId = resId;

	direction = g_direction[direction];

	int frame_cnt = 25;
	char path[128] = {0};
	std::string frameName = "";

	std::string filePath = "";

	switch ( actionType )
	{
	case ACTION_STAND:
		sprintf( path, "/stand-%d.plist", direction );
		filePath = path1 + path;
		sprintf( path, "%d/stand-%d", resId, direction );	// 1/stand-8-9.png
		frameName = std::string(path) + "-000%d.png";
		break;
	case ACTION_WALK:
		sprintf( path, "/walk-%d.plist", direction );
		filePath = path1 + path;
		sprintf( path, "%d/walk-%d", resId, direction );
		frameName = std::string(path) + "-000%d.png";
		break;
	case ACTION_HIT:
		sprintf( path, "/hit-%d.plist", direction );
		filePath = path1 + path;
		sprintf( path, "%d/hit-%d", resId, direction );
		frameName = std::string(path) + "-000%d.png";
		break;
	case ACTION_ATTACK:
		sprintf( path, "/attack-%d.plist", direction );
		filePath = path1 + path;
		sprintf( path, "%d/attack-%d", resId, direction );
		frameName = std::string(path) + "-000%d.png";
		break;
	}

	CCAnimation*& animation = m_animation[actionType][g_index[direction]];
	CC_SAFE_RELEASE_NULL(animation);
	animation = SourceCacheManage::Instance()->loadModelAnimation(filePath.c_str(), frameName.c_str(), frame_cnt, interval);
	if (animation)
	{
		animation->retain();
		if (target && selector)
			(target->*selector)(NULL, pData);
		return 0;
	}
	else
	{
		m_callbackDic[filePath] = CallbackInfo(target, selector, pData, actionType, direction);
		SourceCacheManage::Instance()->addEventListener(Event::COMPLETE, this, callfuncND_selector(BitmapMovieClip::loadCompleteHandler));
		return -1;
	}
	return 0;
}

int BitmapMovieClip::loadPvrCommonAsync(int resId, int frame_cnt, float interval)
{
	CCAnimation*& pAnimation = m_animation[ACTION_COMMON][0];
	CC_SAFE_RELEASE(pAnimation);

	pAnimation = SourceCacheManage::Instance()->loadEffectAnimation(resId, frame_cnt, interval);//interval kevine, modified kenfly
	if (pAnimation)
	{
		pAnimation->retain();
		return 0;
	}
	else
		return -1;
}

int BitmapMovieClip::loadNormalAsync(std::string path, std::string frameName, int frame_cnt, float interval, CCObject* target, SEL_CallFuncOD selector, void* pData)
{
	CCAnimation*& pAnimation = m_animation[ACTION_PVR_NORMAL][0];
	CC_SAFE_RELEASE_NULL(pAnimation);

	pAnimation = SourceCacheManage::Instance()->loadModelAnimation(path.c_str(), frameName.c_str(), frame_cnt, interval);

	if (pAnimation)
	{
		pAnimation->retain();
		if (target && selector)
			(target->*selector)(NULL, pData);
		runActionNormal();
		return 0;
	}
	else
	{
		m_callbackDic[path] = CallbackInfo(target, selector, pData, ACTION_NORMAL, 0);
		SourceCacheManage::Instance()->addEventListener(Event::COMPLETE, this, callfuncND_selector(BitmapMovieClip::loadCompleteHandler));
		return -1;
	}
}

void BitmapMovieClip::loadCompleteHandler(CCNode* node, void* pData)
{
	SourceCacheManage::EventInfo* pInfo = (SourceCacheManage::EventInfo*)pData;

	std::map<std::string, CallbackInfo>::iterator ix = m_callbackDic.find(pInfo->data);
	if (ix != m_callbackDic.end())
	{
		CCObject* target = ix->second.target;
		SEL_CallFuncOD selector = ix->second.selector;
		void* data = ix->second.data;
		int actionType = ix->second.actionType;
		int direction = ix->second.direction;

		if (target && selector)
			(target->*selector)(NULL, data);
		m_callbackDic.erase(ix);

		if (actionType >= 0 && actionType < ACTION_MAX && direction >= 0 && direction < 10)
		{
			CCAnimation*& animation = m_animation[actionType][g_index[direction]];
			CC_SAFE_RELEASE_NULL(animation);
			animation = SourceCacheManage::Instance()->getAnimation(pInfo->data.c_str());
			if (animation)
			{
				animation->retain();
				if (actionType == _currentAction && g_index[direction] == g_index[_currentDirection])
				{
					switch(actionType)
					{
					case ACTION_STAND : 
					case ACTION_WALK :
					case ACTION_HIT :
					case ACTION_ATTACK :
						runActionEx(_currentAction, _currentDirection, _bActionRepeat);
						break;
					case ACTION_NORMAL:
						runActionNormal();
						break;
					case ACTION_PVR_NORMAL:
						runActionNormal(_currentAction, _currentDirection, _bActionRepeat);
						break;
					case ACTION_COMMON :
						if (_bActionRepeat)
							runActionPVRCommonRepeat();
						//runActionPVRCommon();
						break;
					}
				}
			}
				
		}
	}
	if (m_callbackDic.empty())
	{
		SourceCacheManage::Instance()->removeEventListener(Event::COMPLETE, this, callfuncND_selector(BitmapMovieClip::loadCompleteHandler));
	}
}


//End Kenfly 20121102
