#ifndef _TowerMediator_H_
#define _TowerMediator_H_

#include "BaseType.h"
#include "mvc/Mediator.h"
#include "components/TowerView.h"
#include "socket/command/s3b/SCMD3B3.h"
#include "socket/command/s3c/SCMD3CF.h"
#include "socket/command/s3b/SCMD3B5.h"
#include "socket/command/s3b/SCMD3B7.h"
#include "socket/command/s3c/SCMD3CB.h"
#include "socket/command/s3a/SCMD3AE.h"
#include "model/tower/TowerProxy.h"
#include "socket/command/s3d/SCMD3DF.h"
#include "socket/command/s32/SCMD3C2.h"

class TowerRank;
class TowerPanel1Vo;
class TowerPanel2Vo;
class TowerRankListVo;

class TowerMediator:public Mediator
{
public:
	TowerMediator();
	enum
	{
		UPDATE_PANEL_1,
		UPDATE_PANEL_2,
		UPDATE_RANK_LIST,
		TOWER_FIGHT_END,
	};
public:
	void popHandler( CCNode* n, void* data );
	void openTowerView();
	void handleNotification( int M2Vcmd, char* data );

	void cmdInitTower( SCMD3B3* cmd );
	void updatePanel1( TowerPanel1Vo* vo );
	void cmdBoxTip( SCMD3CF* cmd );
	void cmdUpdateTowerInfo( SCMD3B5* cmd );
	void updatePanel2( TowerPanel2Vo* vo );
	void cmdTowerFightResult( SCMD3B7* cmd );
	void cmdTowerRanking( SCMD3CB* cmd );
	void updateRanking(TowerRankListVo* vo);
	void cmdInspire(SCMD3AE* cmd);
	void towerFightEnd(int battleType);

	void enterTowerFight(CCNode *pNode, void *pData);
	void onTowerInspire(CCNode *pNode, void *pData);
	void onTowerFight(CCNode *pNode, void *pData);
	void fightHideBoss(CCNode *pNode, void *pData);
	void towerFightEndCallback(CCNode *pNode, void *pData);
	void onLeaveTower(CCNode *pNode, void *pData);
	void onVisibleChange(CCNode *pNode, void *pData);
	void onTakeTowerAward(CCNode *pNode, void *pData);
	void onCrystalLevChange(CCNode *pNode, void *pData);
	void preTowerRank(CCNode *pNode, void *pData);
	void onPageChange(CCNode *pNode, void *pData);
	void rankMe(CCNode *pNode, void *pData);
	void onRankMeCallback(CCNode *pNode, void *pData);
	void openTowerRank();
	void startViewListener();
	void leaveTowerListener(SCMD3DF* cmd);
	void takeAwardListener( SCMD3C2* pPacket );
public:
	TowerView* _towerView;
	TowerRank* _towerRank;
	bool _isInTowerFightPanel;
	TowerProxy* _towerProxy;
};

extern TowerMediator* g_pTowerMediator;
#endif