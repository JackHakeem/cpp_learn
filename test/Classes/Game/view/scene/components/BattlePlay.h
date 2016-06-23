//
//  BattlePlay.h
//  HLQS
//
//  Created by edward liu on 12-3-4.
//  Copyright (c) 2012 4399. All rights reserved.
//

#ifndef HLQS_BattlePlay_h
#define HLQS_BattlePlay_h
#include "cocos2d.h"
#include "socket/command/s13/SCMD133.h"
#include "socket/command/s13/SCMD131.h"

using namespace cocos2d;

class BattleLayer;
class BattlePlay : public CCSprite
{
public:
    BattlePlay();
    ~BattlePlay();
    
    static BattlePlay * getInstance();
    void runBattleAction();
    
    //CCSprite* sprite[18];
    CCSprite* m_battleSprite;
    
    void playBattleStart();
    void setBattleReady(bool ready);
    bool getBattleReady();
    void checkBattleReady();
    CCSprite* getBattleSprite();
    void showResult();
    
    void backReplayCallback(CCObject* pSender);
    void backCallback(CCObject* pSender);
    //static void setBattleLayer(CCLayer* ly);
    void checkBattleAction();
    void setCheckBattleAction(bool ready);
    
    void SetVictoryData( SCMD133* packet );

    void waitSCMD133Timeout(CCNode* pSender, void* data);

    BattleLayer* m_battleLayer;

    SCMD133 m_packet;
    
	
public:
    bool m_battleReady;
    bool m_battleAction;
    

	int32			a_BattleId;
	int32			b_GroupId;
	int16			c_formationId;
	int16			d_SCMD131NodeNum;
	std::list<SCMD131Node> d_SCMD131Node;
	int16			e_playerId;
};
#endif
