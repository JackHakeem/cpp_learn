//
//  Npc.cpp
//  HLQS
//
//  Created by edward liu on 12-3-5.
//  Copyright (c) 2012年 4399. All rights reserved.
//


//
//  Player.cpp
//  HLQS
//
//  Created by edward liu on 12-3-4.
//  Copyright (c) 2012 4399. All rights reserved.
//

#include "Npc.h"
#include "utils/loader/KKAnimationFactory.h"
#include "model/scene/vo/NPCVo.h"

Npc::Npc()
{
	walkAnimationNpc = NULL;
    standAnimationNpc = NULL;
    m_action = NULL;
    
    roleAnimation = NULL;
}

Npc::~Npc()
{
}

CCSprite * Npc::getNpcSprite()
{
    return m_baseSprite;
}

CCSprite * Npc::loadNpc()
{
    standAnimationNpc = new CCAnimation*[1];
        
    standAnimationNpc[0] = g_pKKAnimationFactory->registAni("role/npc/fushihun-stand-1.plist", "fushihun-stand-1-%d.png", 8, 0.1f);
    
    
    CCSprite * npcSprite = CCSprite::spriteWithSpriteFrame(standAnimationNpc[0]->getFrames()->getObjectAtIndex(0));
    if(npcSprite == NULL)
    {
        CCLog("Create NPC sprite failed");
        return NULL;
    }
	m_baseSprite = npcSprite;
	
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    m_baseSprite->setPosition(ccp(s.width/2, s.height/2));
    
    m_baseSprite->runAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(standAnimationNpc[0])));
    return m_baseSprite;
}

void Npc::playAnimation()
{
    return;
    
}

void Npc::stopAnimation()
{
    return;
}

void Npc::npcMove(char** map_desc, int &h, int &w)
{
    return;
}
