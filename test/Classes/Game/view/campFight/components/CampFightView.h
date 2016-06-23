#ifndef _CAMPFIGHTVIEW_H_
#define _CAMPFIGHTVIEW_H_
#include "PopContainer.h"
#include "CCUIBackground.h"
#include "CampFightPlayerListView.h"
#include "CampFightMsgListView.h"
#include "model/campFight/vo/campFightVo.h"
#include "model/campFight/campFightProxy.h"

class CampFightView : public PopContainer
{
public:
	CampFightView();
	~CampFightView();

	void UpdateCampFightSceneInfo();
	void UpdateMyInfo();
	virtual bool init();
	virtual void clickCloseHandler(CCObject* pSender);
	void closeView(int ApplyRes);
	bool InitDivede();
	bool InitLable();
	bool InitLsView();
	bool InitBtn();
	void onClose(CCObject* pSender);
	void onFight(CCObject* pSender);
	void onCancel(CCObject* pSender);
	void onInspireByGold(CCObject* pSender);
	void onInspireByPratice(CCObject* pSender);
private:
	CampFightProxy* m_pCampFightProxy;
	CCLayer* m_pContainer;

	CCFPlayerListView* m_plsIcePlayers;
	CCFPlayerListView* m_plsFirePlayers;

	CCFMsgListView*    m_plsMsg;

	CCUIBackground* m_pbg;
	CCUIBackground* m_pLeftBg;
	CCUIBackground* m_pMidBg;
	CCUIBackground* m_pRightBg;
	CCMenu* m_ptnClose;

	CCLabelTTF* m_pIceCityText;
	CCLabelTTF* m_pIceCityScore;

	CCLabelTTF* m_pFireCityText;
	CCLabelTTF* m_pFireCityScore;

	CCLabelTTF* m_pTimeTips;
	CCLabelTTF* m_pTimeContext;

	CCLabelTTF* m_pIcePlayerName;
	CCLabelTTF* m_pIcePlayerContiWinTms;
	CCLabelTTF* m_pFirePlayerName;
	CCLabelTTF* m_pFirePlayerContiWinTms;

	CCLabelTTF* m_pPlayerScore;
	CCLabelTTF* m_pPlayerHisContiWinTms;
	CCLabelTTF* m_pPlayerAward;
	CCLabelTTF* m_pMyCamp;

	CCLayerColor *divide1;
	CCLayerColor *divide2;
	CCLayerColor *divide3;

	CCLayerColor *divide4;
	CCLayerColor *divide5;
	CCLayerColor *divide6;
	
	CCLabelTTF* m_pFightLable;
	CCMenu*     m_pBtnIFightMenu;
	CCMenuItemSprite* m_pBtnFightSpr;
	
	CCMenu*     m_pBtnCancelMenu;
	CCMenuItemSprite* m_pBtnCancelSpr;

	CCLabelTTF* m_myScoreLabel;
	CCLabelTTF* m_myHisConWinTmsLabel;
	CCLabelTTF* m_myTotalAwardLabel;
	CCLabelTTF* m_attackAddLabel;
	CCLabelTTF* m_lifeAddLabel;

	enum
	{
		CAMPFIGHT_LAYER = 0,
		CAMPFIGHT_CONTAINER1,
		CAMPFIGHT_CONTAINER2,
		CAMPFIGHT_MONITOR,
	};
private:
	bool SetMyScore(uint16 score, ccColor3B color = ccc3(0xff, 0xc6, 0x00));
	bool SetMyHisContiWinTms(uint16 wins, ccColor3B color = ccc3(0xff, 0xc6, 0x00));
	bool SetMyTotalAwards(uint16 pop, uint32 silver, ccColor3B color = ccc3(0xff, 0xc6, 0x00));
	bool SetAttackAddStr(int16 per, ccColor3B color = ccc3(0xff, 0xc6, 0x00));
	bool SetLifeAddStr(int16 per, ccColor3B color = ccc3(0xff, 0xc6, 0x00));

	void TestListView();
};
#endif