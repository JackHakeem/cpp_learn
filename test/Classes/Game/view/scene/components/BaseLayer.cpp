//
//  BaseLayer.cpp
//  HLQS
//
//  Created by edward liu on 12-2-27.
//  Copyright (c) 2012 4399. All rights reserved.
//

#include "BaseLayer.h"
#include "BgBitmap.h"
#include "manager/ViewManager.h"

BaseLayer::BaseLayer() 
{
    this->m_cusPointByMapCells. x= -1;
    this->m_cusPointByMapCells. y= -1;
}

BaseLayer::~BaseLayer()
{
}

CCLayer * BaseLayer::newBaseLayer()
{
    BaseLayer * baseLayer = NULL;
    do
    {
        baseLayer = BaseLayer::node();
        CC_BREAK_IF(!baseLayer);
    }
    while(0);
    return baseLayer;
}


bool BaseLayer::init()
{
    if ( !CCLayer::init() )
	{
		return false;
	}
    
    
    
   
    this->setIsTouchEnabled(true);
	return true;
}

void BaseLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    if(pTouches->count())
    {
    }
    
    CCSetIterator iteratorTouch = pTouches->begin();
    CCTouch  * touchPoint = (cocos2d::CCTouch *)(* iteratorTouch);
    CCPoint pointLocation = touchPoint->locationInView(touchPoint->view());
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
}

void BaseLayer::moveStep(ccTime dt)
{
    CCLog("1--------------------------------");
    
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
}

void BaseLayer::setCusPointByScreenPixels(float x,float y)
{
    this->m_cusPointByScreenPixels.x = x;
    this->m_cusPointByScreenPixels.y = y;
}

CCPoint * BaseLayer::getCusPointByScreenPixels()
{
    return &m_cusPointByScreenPixels;
}

CCPoint * BaseLayer::getCusPointByMapPixels(CCPoint *cpScreen)
{
    return &m_cusPointByMapPixels;
}

CCPoint * BaseLayer::getCusPointByMapCells(CCPoint * cpPixels,int nTileW,int nTileH)
{
    if((0 == nTileW)||(0 == nTileH))
    {
        return cpPixels;
    }
    m_cusPointByMapCells.x =  cpPixels->x / nTileW;
    m_cusPointByMapCells.y =  cpPixels->y / nTileH;
    return &m_cusPointByMapCells;
}

CCPoint * BaseLayer::getCusPointByMapPixels()
{
    return &m_cusPointByMapPixels;
}

void BaseLayer::menuCloseCallback(CCObject* pSender)
{
	//if(ViewManager::getInstance()->_scene)
	//{
	//	//	delete _scene;
	//	ViewManager::getInstance()->_scene->dispose();
	//	ViewManager::getInstance()->_scene->removeFromParentAndCleanup(true);//jae
	//	ViewManager::getInstance()->_scene->release();
	//}

	CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

