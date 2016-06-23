//
//  BattleLayer.h
//  HLQS_IPAD
//
//  Created by hui long on 12-2-27.
//  Copyright (c) 2012 4399. All rights reserved.
//

#ifndef HLQS_IPAD_BattleLayer_h
#define HLQS_IPAD_BattleLayer_h

#include "cocos2d.h"
#include <list>
using namespace cocos2d;

static CCPoint formationPos[18];


typedef struct _AnimationPara
{
    int pos;
    int skill;
    int hp;
    // add code here
}AnimationPara;

//static std::list<CCAnimation *>	 AnimationList;
//static std::list<AnimationPara> AnimationParaList;

class BattleLayer : public cocos2d::CCLayer
{
private:
    virtual ~BattleLayer();
public:
    BattleLayer();
    bool init();
    void menuCloseCallback(CCObject* pSender);
    static BattleLayer* getInstance();
    
    static void generateFormationPos();
    static CCPoint *getFormationPos()
    {
        return formationPos;
    }
    
    std::list<CCAnimation *>* getAnimationList();
    
    std::list<AnimationPara>* getAnimationParaList();
    
    void startBattleAnimation();
    static void endBattleAnimation();
    
    static void loadBgAnimation();
    static void loadSpriteAnimation();
    
    static void play();
    
    static void playStartAnimation();
    
    CCSprite* getSprites();
    
    std::list<CCAnimation *> m_AnimationList;
    std::list<AnimationPara> m_AnimationParaList;
    
    //static CCSprite* sp[18];
    //static CCSprite * sp[18];
    
//    void loadBattleFormation(int nFormaitionIndex,int);
    // void loadPlayer()
    
    LAYER_NODE_FUNC(BattleLayer);
};

#endif
