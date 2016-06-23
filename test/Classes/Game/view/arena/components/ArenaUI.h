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
	void updatePackage(SCMD285* param);// ���������Լ���ؽ���
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

	int32 _meRank;  // ��¼��ǰ���� ��0��ʼ999
	int32 _streak;   // ��ʤ����
	int32 _cdtime;   // CDʱ�� ��λ��
	int32 _cdlock;   // cd�Ƿ����� 0������״̬ 1Ϊ����
	int32 _quota;   // ��ս����(�ɹ���)
	int32 _buyed;   // �����ѹ������
	int32 _cdRefresh;//����ˢ�¾�������ս���ֵ�CDʱ�� ��λ�� hwj

	InfoPanel* _infoPanel;
	CDManage* _cdManage;

	RankList* _rankList; // �������б�(�Լ�����CD/����ť��)
	StarRecord* _starRecord;// ��5��ս��ʤ����¼ 
	ReportList* _reportList; // ս���б�
	RankingInfo* _rankingInfo;  // ����������Ϣ
	GiftPanel* _giftPanel;
	CardList* _cardList;
	bool canOperate;  // ��Բ鿴ս���ȹ�������� 
	CCMenuItemSprite *_btnClose;
};
#endif