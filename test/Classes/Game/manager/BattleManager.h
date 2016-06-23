
#ifndef HLQS_IPAD_BattleManager_h
#define HLQS_IPAD_BattleManager_h

#include "cocos2d.h"
using namespace cocos2d;
class BattleManager
{
public:
	BattleManager();
	~BattleManager();
    
public:
    void sendBattleRequestHandler(); // Combat request

    void sendBattleStopHandler(int type); // The end of combat

    
public:
	
};

extern BattleManager* g_pBattleManager;


#endif
