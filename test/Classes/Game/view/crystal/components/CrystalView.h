#ifndef _CRYSTALVIEW_H_
#define _CRYSTALVIEW_H_

#include "model/crystal/vo/CrystalType.h"
#include "model/crystal/vo/CrystalInfo.h"
#include "CCLabelTTF.h"
#include "PopContainer.h"
#include "FocusNode.h"
#include "view/crystal/CrystalMediator.h"
#include "CCUIPartialScrollView.h"
#include "UIListView/CCUIListView.h"
#include "UIListView/CCUIListViewAdapter.h"
#include "model/crystal/CrystalProxy.h"
#include "socket/command/s19/SCMD19F.h"

USING_NS_CC;

#define MAX_CRYSTAL_NUM			(CrystalType::CRYSTAL_NUM)	// max crystal type 

#define CRYSTAL_ROW_NUM			(3)							// crystal num in each row
#define CRYSTAL_COLUMN_NUM		(4)							// crystal num in each column

#define SCROLL_VIEW_WIDTH		(600)						// scroll view width
#define SCROLL_VIEW_HEIGHT		(500)						// scroll view height

#define TAG_SCROLLLAYER_CRYSTAL_UNDER		(20)
#define TAG_BGPANEL_DETAIL_INFO			(20)

class SkillManager;
class CrystalTimer;

class CrystalView : public PopContainer,public CCUIListViewAdapter,public CCUIListViewItemActionListener
{
public:
	CrystalView();
	~CrystalView();
public:
	enum CrystalZPrioEnum								// Z 
	{
		Z_BG = 0,
		Z_CONTAINER	,
		Z_BG_PANEL	,
		Z_BG_ITEM	,
		Z_CRYSTAL	,
		Z_TEXT	
	};

	enum
	{	
		TAG_BGCIRCLE = 0,
		TAG_CRYSTAL = 20,
		TAG_DESCRIBE = 40,
		TAG_FOCUS = 60,
		TAG_SCROLLVIEW = 100,
		TAG_BUTTON_BUY_CD = 110,
		TAG_BUTTON_BUY_CDTXT = 120,
		TAG_CD_BG = 130,
		TAG_UPGRADE_BTN_IMG = 201,
		TAG_UPGRADE_BTN = 301,
	};

	enum
	{	
		TAG_CDITEM_1 = 1801,
		TAG_CDITEM_2,
		TAG_CDITEM_3,
		TAG_CDITEM_4,
		TAG_CDITEM_5,
		TAG_CDITEM_6,
		TAG_CDITEM_ZERO = 1851,
	};
	cocos2d::CCPoint ccpCrystalPos[MAX_CRYSTAL_NUM];		// crystal pos
	cocos2d::CCLabelTTF * _upgrade;						// "upgrade" Text
	cocos2d::CCLabelTTF * _unName;
	cocos2d::CCLabelTTF * _name;						// crystal name
	cocos2d::CCLabelTTF * _level;						// crystal level
	cocos2d::CCLabelTTF * _detail;						// crystal detail info
	cocos2d::CCLabelTTF * _time;						// upgrade time
 	//std::map <int,CrystalInfo *> _itemsCrystal;			// crystal object
 	string _itemsLev[MAX_CRYSTAL_NUM];					// left panel Text
	std::map<int,int> IDIndexMap;
public:
	void initCrystalPos();								// init crystal pos
	void initIDIndexMap();
 	bool initView();									// init crystal view
 	bool initItemsInScrollView();						// init items in scroll view
	bool initCrystalScrollView();						// init scroll view
	bool initCrystalView();								// init Crystal View
	void addBackGround();
	void showCDPannel();
//	void showCrystal();								// show left panel info
	void showCrystalInfo(uint32 id);						// show right panel info
	void updateCDList(int type ,int id ,uint time);					// update CD list view
	void clearCD(char * pPacket);						// request money for clear cd
	void clearCDOK(CCObject * pSender);					// confirm to clear CD time
	void onClearAllCDConfirm(CCObject * pSender);
	void onClearAllCDOK(CCObject * pSender);					// clear  All CD time

	void buyCrystalCDList(int nValue,int listNum);			// buy cd list response

	int32 getTouchPosIndex( CCPoint point );

	virtual int getCount();

	virtual LayerNode * getView( int position );

	void clickUpgradeHandler(CCObject* pSender);

	void clickCloseHandler(CCObject* pSender);

	void clickCancel(CCObject * pSender);

	virtual void onItemClickListener(LayerNode *itemCell, int position);

	void buyCrystalListHandle(CCObject * pSender);

	void clickReqRecharge(CCObject * pSender);

	void clickCDReqRecharge(CCObject * pSender);

	void EnableUpgradeButton(bool var);

	bool isInCD();

	bool isMaxLev();

	void upgradeTimer(ccTime dt);

	CCNode * getNewHandItem(int id);
	//virtual void onItemTouchListener(LayerNode *itemCell, int position);
	//virtual void onItemTouchCancelListener(LayerNode *itemCell, int position);
	//string formatData( Number serTimer );

public:
	LayerNode * _container;
	cocos2d::CCSize _viewSize;
	LayerNode * _BgPanel;
	CCLayer * _scrollLayer;
	SkillManager * _skillManager;
	CrystalProxy * _crystalProxy;
	CCUIListView * _crystalCDList;
	CCUIListViewAdapter * _adapter;
	CCUIPartialScrollView *scrollView;
	int curSelectCrystalID;
	//std::map<int/*id*/,Number/*time*/> serverTimeMap;
	//std::map<int/*id*/,CrystalTimer/*Timer*/> TimerMap;
	uint _CDlistCount;
	CrystalMediator * _pCrysMediator;
	SCMD19F _cmd19fCopy;
	int _chCDType[16];
	uint _chCDTime[16];
	int _curCDType;
	uint _curCDtime;

	int _upTime;
	//LayerNode * _pCryTimerList[10];
	std::map<int/*id*/,CrystalTimer *> _pCryTimerListMap; 
};

#endif