#ifndef _TowerView_H_
#define _TowerView_H_

#include "PopContainer.h"
#include "EnterPanel.h"
#include "FightPanel.h"
#include "cocos2d.h"
#include "socket/command/s3c/SCMD3CF.h"
#include "model/tower/vo/TowerPanel1Vo.h"
#include "model/tower/vo/TowerPanel2Vo.h"
#include "socket/command/s3a/SCMD3AE.h"
#include "control/tower/TowerCommand.h"

class SCMD3B7;
class KKLabelTTF;

USING_NS_CC;

class TowerView : public PopContainer
{
public:
	TowerView();

	~TowerView();
	enum
	{
		OPEN_TOWER_RANK,
		ENTER_TOWER_FIGHT,
		ON_TOWER_INSPIRE, 
		ON_TOWER_FIGHT,
		FIGHT_HIDE_BOSS,
		ON_LEAVE_TOWER,
		ON_VISIBLE_CHANGE,
		ON_TAKE_AWARD,
	};
public:
	bool init();
	virtual void clickCloseHandler(CCObject* pSender);
	void updateBoxTip( std::list<SCMD3CF::SCMD3CFNode>& a_rewards );
	void updatePanel1( TowerPanel1Vo* vo );
	void updatePanel2(TowerPanel2Vo* vo);
	void updateInspire(SCMD3AE* cmd);
	void openTowerRank(CCObject* obj);
	void enterTowerFight1(CCObject* obj);
	void enterTowerFight2();
	void onTowerInspire(CCObject* obj);
	void onTowerFight(CCObject* obj);
	void fightHideBoss(CCObject* obj);
	void onLeaveTower(CCObject* obj);
	void onVisibleChange(CCObject* obj);
	void shureToLeave(CCObject* obj);
	void cancelToLeave(CCObject* obj);
	void okFunctionFightIn(CCObject* obj);
	void updatePanelGUA(SCMD3B7* cmd);
	TypeObject getRewardType(int id);
	void cleanLayerGUA();
public:
	CCLayer* pInnerLayer;
	EnterPanel* _panelEnter;
	FightPanel* _panelFight;
	LayerNode* m_pLayerGUA;
	int m_enterNeedGold; 
	KKLabelTTF* arrayGUAInfo[5];
	int GUARoundArray[5];
};
#endif