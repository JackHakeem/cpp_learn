#ifndef _ARENAUI_H_
#define _ARENAUI_H_

#include "PopContainer.h"
#include "model/arena/vo/ArenaReportVo.h"
#include "InfoPanel.h"

class RankList;
class GameDispatcher;
class SCMD361;
class SCMD285;
class CDManage;
class InfoPanel;
class StarRecord;
class ReportList;
class RankingInfo;
class GiftPanel;
class CardList;
class SCMD36E;
class ArenaUI:public PopContainer
{
public:
	
	enum
	{
		EXIT_CLICK = 0,
		GET_AWARD,
	};

	enum
	{
		RENDERZ_bg = 0,
		RENDERZ_InfoPanel,
		RENDERZ_RankList,
		RENDERZ_StarRecord,
		RENDERZ_ReportList,
		RENDERZ_RankingInfo,
		RENDERZ_buttonClose,
		RENDERZ_txtAwardNum,
		RENDERZ_cardList,
	};

	enum
	{
		RENDERTAG_bg = 0,
		RENDERTAG_InfoPanel,
		RENDERTAG_RankList,
		RENDERTAG_StarRecord,
		RENDERTAG_ReportList,
		RENDERTAG_RankingInfo,
		RENDERTAG_buttonClose,
		RENDERTAG_txtAwardNum,
		RENDERTAG_cardList,
	};

	ArenaUI();
	~ArenaUI();

	bool initView();
	void addCloseButton();
	bool initTxtAwardNum();
	void addPVPReportContainer();
	//void initBaseInfo();
	void initTxtCurrenGrade();
	void intAccountMoneyInfo();
	void showReportList(std::vector<ArenaReportVo*> report);
	void creatPVPreportObject(ArenaReportVo* arenaReportVo, int sitNum);

	void awardClickHandler(CCObject* pSender);
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	void updateAwardLabel(int awardNum);
	void updateInfo(SCMD361* param);
	std::string getRewardByRank(int rank);
	void setGiftOpt(bool canTake);
	void updatePackage(SCMD285* param);// 更新排名以及相关奖励
	void openGiftPanel();
	void clickClose(CCObject* pSender);
	void pkArena(int rank);
	void updateCard(SCMD36E* param);
	void handleCDEvent(CCNode* n, void* data);
	//Begin chenjian 20121019
	void reportArena(int battleId1, int battleId2);
	void reportWaitTime();
	//End chenjian 20121019

	CCNode * getNewHandItem(int id);

public:

	std::string _title;
	int32 _gold;
	int32 _silver;
	int32 _practice;
	int32 _popularity;


	SpriteNode* reportList;
	CCSize viewSize;
	GameDispatcher* _dispatcher;

	int32 _awardNum;

	cocos2d::CCLabelTTF* _txtAwardNum;
	char _szUpgradeText[100];
	CCMenuItemImage *_btnOpenAward;

	int32 _meRank;  // 记录当前排名 从0开始999
	int32 _streak;   // 连胜次数
	int32 _cdtime;   // CD时间 单位秒
	int32 _cdlock;   // cd是否锁定 0非锁定状态 1为锁定
	int32 _quota;   // 挑战次数(可购买)
	int32 _buyed;   // 今天已购买次数
	int32 _cdRefresh;//可以刷新竞技场挑战对手的CD时间 单位秒 hwj

	InfoPanel* _infoPanel;
	CDManage* _cdManage;

	RankList* _rankList; // 竞技场列表(以及竞技CD/购买按钮等)
	StarRecord* _starRecord;// 近5场战斗胜利记录 
	ReportList* _reportList; // 战报列表
	RankingInfo* _rankingInfo;  // 排名奖励信息
	GiftPanel* _giftPanel;
	CardList* _cardList;
	bool canOperate;  // 针对查看战报等过快的问题 
	CCMenuItemSprite *_btnClose;
};
#endif