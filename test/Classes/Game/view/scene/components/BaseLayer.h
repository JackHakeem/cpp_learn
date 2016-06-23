//
//  BaseLayer.h
//  HLQS
//
//  Created by edward liu on 12-2-27.
//  Copyright (c) 2012 4399. All rights reserved.
//

#ifndef HLQS_BaseLayer_h
#define HLQS_BaseLayer_h

#include "cocos2d.h"

using namespace cocos2d;

class BaseLayer : public cocos2d::CCLayer
{
private:

    CCPoint m_cusPointByScreenPixels;
    
    CCPoint m_cusPointByMapPixels;
    CCPoint m_cusPointByMapCells;
    
public:
    BaseLayer();
    ~BaseLayer();
    virtual bool init();
    static CCLayer * newBaseLayer();
    
    void moveStep(ccTime dt);
    void setCusPointByScreenPixels(float x,float y);
    CCPoint * getCusPointByScreenPixels();
    
    CCPoint * getCusPointByMapPixels(CCPoint *cpScreen);
    CCPoint * getCusPointByMapCells(CCPoint *cpPixels,int nTileW,int nTileH);
    CCPoint * getCusPointByMapPixels();
    CCPoint * pixelsToCells(CCPoint *cpPixels);
    
    virtual void menuCloseCallback(CCObject* pSender);
    //    void OnNext();
    //    void OnBack();
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    //    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    //    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    //    virtual void ccTouchesCancelled(cocos2d::CCSet*pTouches,cocos2d::CCEvent *pEvent);
    
    int m_mapWidth;
    int m_mapHeight;
    
    CCPoint m_map_pos_start;
    float m_distance_x;
    float m_distance_y;
    
    LAYER_NODE_FUNC(BaseLayer);
};

#endif
