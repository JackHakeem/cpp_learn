//
//  BattlePlay.cpp
//  HLQS
//
//  Created by edward liu on 12-3-4.
//  Copyright (c) 2012 4399. All rights reserved.
//

#include "BattlePlay.h"
#include "utils/loader/KKAnimationFactory.h"
#include "view/scene/layer/BattleLayer.h"
#include "view/scene/layer/FightLayer.h"
#include "../SceneListenerMediator.h"
#include "model/battle/FightProxy.h"
#include "events/GameDispatcher.h"
#include "model/scene/vo/SceneConst.h"
#include "manager/ViewManager.h"
#include "manager/GlobalManage.h"
#include "view/battle/SceneFightMediator.h"
#include "manager/CDManage.h"
static BattlePlay * m_pBattlePlayInstance;
extern CCSprite * sp[];

BattlePlay::BattlePlay()
{
    m_battleReady = false;
    m_battleAction = false;
	m_battleSprite = NULL;

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//m_battleSprite = CCSprite::spriteWithFile("scene/battle/icon/3.png");
	//m_battleSprite->setPosition(ccp(size.width / 2.0f, size.height / 2.0f));
	//m_battleSprite->setIsVisible(false);

	m_battleSprite = new CCSprite();
	m_battleSprite->init();
	m_battleSprite->setContentSize(CCSizeMake(50, 150));
	m_battleSprite->setPosition(ccp(size.width / 2.0f, size.height / 2.0f));
	m_battleSprite->setIsVisible(false);
}

BattlePlay::~BattlePlay()
{
}

BattlePlay * BattlePlay::getInstance()
{
    static bool isCreat = false;
    if((false == isCreat )&&(!m_pBattlePlayInstance))
    {
        isCreat = true;
        m_pBattlePlayInstance = new BattlePlay();
    }
    
    return m_pBattlePlayInstance;
}

void BattlePlay::playBattleStart()
{
	// add by LH
	g_pGlobalManage->_isInFight = true;
	g_pGlobalManage->showAllUI(false);

	GameDispatcher::getInstance()->dispatchEvent(SceneConst::WALK_COMPLETE,0);
	Scene * scene = ViewManager::getInstance()->_scene;
	if (scene)
	{
		scene->setIsTouchEnabled(false);
		scene->_movingLayer->setIsTouchEnabled(false);
		if(scene->_role && scene->_role->poseState)
		{
			scene->_role->poseState->state(SceneConst::STAND);
		}
	}

	CCLog("-------------Play Battle start now");
	CCTexture2D* p = CCTextureCache::sharedTextureCache()->textureForKey("scene/battle/animation/battle-start.plist");
    CCAnimation* startAnimation =  g_pKKAnimationFactory->registAni("scene/battle/animation/battle-start.plist", "battle-start-%d.png", 10, 0.1f);
    
	CCAction* action = cocos2d::CCSequence::actions(//CCSpawn
                                           CCAnimate::actionWithAnimation(startAnimation/*, false*/),
                                           CCCallFunc::actionWithTarget(this,
										   callfunc_selector(BattlePlay::checkBattleReady)),
                                           NULL);
	if(m_battleSprite/* && action*/)
	{
		m_battleSprite->setIsVisible(true);
		m_battleSprite->runAction(action);
	}
	//this->checkBattleReady();
}

void BattlePlay::checkBattleReady()
{

	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("scene/battle/animation/battle-start.plist");//kevinshit

	//if (CCTextureCache::sharedTextureCache()->textureForKey("scene/battle/animation/battle-start.pvr.ccz"))
	//{
	//	CCTextureCache::sharedTextureCache()->removeTextureForKey("scene/battle/animation/battle-start.pvr.ccz");
	//}



	if (m_battleSprite)
	{
		m_battleSprite->stopAllActions();
		m_battleSprite->setIsVisible(false);
	}

	g_pKKAnimationFactory->removeUnusedTextureForKey("scene/battle/animation/battle-start");
	
	FightProxy* _fightProxy = (FightProxy*)g_pFacade->retrieveProxy(AppFacade_FIGHT_PROXY_CHANGE);
	if(_fightProxy)
	{
		_fightProxy->setFightLayer();
	}
}

void BattlePlay::checkBattleAction()
{
    int cnt = 0;
    while(!m_battleAction)
    {
        //sleep(100);
        cnt++;
        CCLog("-------------Check Battle ready in while %d", cnt);
    }
    
    CCLog("-------------Check Battle ready, Play now");
    
    runBattleAction();
}
void BattlePlay::runBattleAction()
{
    //sleep(100);
    std::list<CCAnimation *> *animationList = BattleLayer::getInstance()->getAnimationList();
    std::list<AnimationPara> *animationParaList = BattleLayer::getInstance()->getAnimationParaList();
    
    CCLog("Start run Battle action in BattlePlay, animation size:%d, para size:%d", animationList->size(), animationParaList->size());
    
    for(std::list<AnimationPara>::iterator it = animationParaList->begin();
        it != animationParaList->end(); ++it)
    {
        CCLog("pos:%d, skill: %d, hp: %d",it->pos,it->skill, it->hp);
    }
    //int ssize = BattleLayer::m_AnimationList.size();
    int ssize = animationList->size();
    int psize = animationParaList->size();
    if (ssize == 0|| psize == 0)
    {
        return;
    }
    //CCAnimation * animate = BattleLayer::m_AnimationList.front();
    CCAnimation * animate = animationList->front();
    CCAnimate *aniAction  = 0;
    if (animate)
    {
        aniAction = CCAnimate::actionWithAnimation(animate);
        
    }
    if (!aniAction)
    {
        return;
    }
    //int pos = BattleLayer::m_AnimationParaList.front().pos;
    int pos = animationParaList->front().pos;
    CCCallFunc * func = CCCallFunc::actionWithTarget(BattlePlay::getInstance(), callfunc_selector(BattlePlay::runBattleAction));
    CCFiniteTimeAction * seq = CCSequence::actions(aniAction, func, NULL);
    
//    
    if (sp[pos])
	{
        CCLog("Run action now----------------------");
        sp[pos]->runAction(seq);
    }
    else
    {
        CCLog("sp[%d] is null, return", pos);
        return;
    }

    animationList->pop_front();
    animationParaList->pop_front();
    
    
    showResult();
}

void BattlePlay::setBattleReady(bool ready)
{
    m_battleReady = ready;
}

bool BattlePlay::getBattleReady()
{
    return m_battleReady;
}

CCSprite* BattlePlay::getBattleSprite()
{
    //m_battleSprite = CCSprite::spriteWithFile("scene/battle/icon/3.png");
    //CCSize size = CCDirector::sharedDirector()->getWinSize();
    //m_battleSprite->setPosition(ccp(size.width / 2.0f, size.height / 2.0f));
    //m_battleSprite->setIsVisible(false);
    return m_battleSprite;
}

void BattlePlay::SetVictoryData( SCMD133* packet )
{
	memcpy((void*)&m_packet, (void*)packet, sizeof(m_packet));
}

void BattlePlay::showResult()
{
    CCLog("Begin to show result now");
    char p[100];
	sprintf(  p, "a_BattleId:%d, Battle type:b_type:%d, c_win:%d, d_damage:%d, e_round:%d ", 
            m_packet.a_BattleId,
            m_packet.b_type,
            m_packet.c_win,
            m_packet.d_damage,
            m_packet.e_round
            );
	//WCHAR wszBuf[100] = {0};
	//MultiByteToWideChar(CP_UTF8, 0, p, -1, wszBuf, sizeof(wszBuf));
	//OutputDebugStringW(wszBuf);
	//OutputDebugStringA("\n");
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	int iLayer( 0 );
	
    // victory
	CCSprite* pSprite = CCSprite::spriteWithFile("scene/battle/icon/1.png");
    // position the sprite on the center of the screen
	pSprite->setPosition( ccp(size.width/2, size.height/2) );
    // add the sprite as a child to this layer
	m_battleLayer->addChild(pSprite, ++iLayer);
    
    
	// Victory Font
	pSprite = CCSprite::spriteWithFile("scene/battle/icon/2.png");
	pSprite->setPosition( ccp(size.width/2, size.height/2 + 130 ) );
	m_battleLayer->addChild(pSprite, ++iLayer);
    
	// head
	for ( int i = 0; i < 1; i++ )
	{
		pSprite = CCSprite::spriteWithFile("scene/battle/icon/head1.PNG");
		pSprite->setPosition( ccp(size.width/2- 150 + i*70 , size.height/2 + 60) );
		m_battleLayer->addChild(pSprite, iLayer);
	}
    
	// Star
	for ( int i = 0; i < 3; i++ )
	{
		pSprite = CCSprite::spriteWithFile("scene/battle/icon/3.png");
		pSprite->setPosition( ccp(size.width/2 - 98 + i*40, size.height/2 - 44) );
		m_battleLayer->addChild(pSprite, iLayer);
	}
    
    
	//pSprite = CCSprite::spriteWithFile("Victory/save.PNG");
	//pSprite->setPosition( ccp(size.width/2, size.height/2 - 100 ) );
	//this->addChild(pSprite, iLayer);
    
	// copy
	pSprite = CCSprite::spriteWithFile("scene/battle/icon/10.png");
	pSprite->setPosition( ccp(size.width/2 - 160 , size.height/2 -120 ) );
	m_battleLayer->addChild(pSprite, iLayer);
    
	// replay
	pSprite = CCSprite::spriteWithFile("scene/battle/icon/7.png");
	pSprite->setPosition( ccp(size.width/2 - 130 , size.height/2 - 120 ) );
	m_battleLayer->addChild(pSprite, iLayer);
    
	// Name
	char sExp[20];
	//sprintf( sExp, "Danfan", m_packet.d_damage/800 );
	CCLabelTTF* label = CCLabelTTF::labelWithString(/*title().c_str()*/sExp, "Arial", 15);
	m_battleLayer->addChild(label, iLayer);
	label->setPosition( ccp(size.width/2 - 150 , size.height/2 + 22 ) );

	label = CCLabelTTF::labelWithString(/*title().c_str()*/sExp, "Arial", 15);
	m_battleLayer->addChild(label, iLayer);
	label->setPosition( ccp(size.width/2 - 150 , size.height/2 ) );
    
	label = CCLabelTTF::labelWithString(/*title().c_str()*/sExp, "Arial", 15);
	m_battleLayer->addChild(label, iLayer);
	label->setPosition( ccp(size.width/2 + 95 , size.height/2 - 42 ) );
    
    
	// Confirm
	char sCon[20];
	sprintf( sCon, "Comfirm" );
	CCLabelTTF* labelC = CCLabelTTF::labelWithString(sCon, "Arial", 15);
	m_battleLayer->addChild(labelC, iLayer);
	labelC->setPosition( ccp(size.width/2 , size.height/2 - 100 ) );
    
	CCMenuItemImage *pCloseItem = CCMenuItemImage::itemFromNormalImage(
                                                                       "scene/battle/icon/4.png",
                                                                       "scene/battle/icon/5.png",
                                                                       m_battleLayer,
                                                                       menu_selector(BattlePlay::backCallback) );
	pCloseItem->setPosition( ccp(size.width/2 , size.height/2 - 100 ) );
    
	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::menuWithItems(pCloseItem, NULL);
	pMenu->setPosition( CCPointZero );
	m_battleLayer->addChild(pMenu, iLayer);
}

void BattlePlay::backReplayCallback(CCObject* pSender)
{
	//m_battleLayer->setIsVisible( false );
	//LayerBattleResult* pLayerBattleResult = new LayerBattleResult();
	//pLayerBattleResult->autorelease();
    
	//CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
	//BattleLayer * pLayer = new BattleLayer();
	//pLayer->SetVictoryData( &m_packet );
	//pScene->addChild( pLayer, 2 );
	//pLayer->autorelease();
} 

void BattlePlay::backCallback(CCObject* pSender)
{
	this->setIsVisible( false );
} 

//void BattlePlay::setBattleLayer(CCLayer* ly)
//{
//    m_battleLayer = ly;
//}

void BattlePlay::setCheckBattleAction(bool ready)
{
    m_battleAction = ready;
}

void BattlePlay::waitSCMD133Timeout(CCNode* pSender, void* data)
{
	SceneFightMediator* m = (SceneFightMediator*)g_pFacade->retrieveMediator(AppFacade_FIGHT_PROXY_CHANGE);
	if(m)
	{
		m->fightOutHandler(0, 0);
	}
	FightProxy *pFightProxy = (FightProxy *) g_pFacade->retrieveProxy(AppFacade_FIGHT_PROXY_CHANGE);
	if(pFightProxy)
		pFightProxy->fightExit();	
}