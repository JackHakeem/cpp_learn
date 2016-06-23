#include "DailyTaskExView.h"
#include "UIListView/CCUIListView.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"
#include "CCUIBackground.h"
#include "manager/PopEventName.h"
#include "utils/ValuesUtil.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "socket/command/c42/CCMD420.h"
#include "socket/network/GameServerSocket.h"
#include "socket/command/c42/CCMD424.h"
#include "socket/command/c42/CCMD422.h"
#include "socket/command/c42/CCMD428.h"
#include "model/scene/MonsterManager.h"
#include "manager/LangManager.h"
#include "utils/ColorUtil.h"
#include "model/player/RoleManage.h"
#include "Confirm.h"
#include "model/scene/vo/FindVo.h"
#include "view/task/components/TaskType.h"
#include "socket/command/c42/CCMD42A.h"
#include "manager/VIPMgr.h"
#include "manager/VIPLimitConst.h"
#include "MessageInfoBox.h"

const int TAG_PARENT_LAYER = 1001;
const int TAG_LISTVIEW = 1002;
const int TAG_TASK_TITLE = 1003;
const int TAG_TASK_RANK = 1004;
const int TAG_TASK_CONTENT = 1005;
const int TAG_TASK_AWARD_ICON_POP = 1006;
const int TAG_TASK_AWARD_LABEL_PAT = 1007;
const int TAG_TASK_AWARD_LABEL_SILVER = 1008;
const int TAG_TASK_AWARD_LABEL_POP = 1009;
const int TAG_LABEL_REFRESH = 1010;
const int TAG_LABEL_ACTION = 1011;
const int TAG_LABEL_REMAIN_FREE_REFRESH = 1012;
const int TAG_LABEL_REMAIN_TASK_COUNT = 1013;
const int TAG_CELL_SELECT = 1014;
const int TAG_CELL_HIGHLIGHT = 1015;
const int TAG_BUTTON_REFRESH = 1016;
const int TAG_BUTTON_SELECT = 1017;
const int TAG_SPRITE_SELECT = 1018;
const int TAG_LABEL_SELECT = 1019;
const int TAG_LABEL_TIP = 1020;
const int TAG_TASK_AWARD_ICON_SILVER = 1021;

DailyTaskExView::DailyTaskExView()
{
	_pCurrentDailyTaskExVo = 0;
	key = PopEventName::DAILY_TASK_EX;
	_pDailyTaskExProxy = (DailyTaskExProxy *) g_pFacade->retrieveProxy(AppFacade_DAILY_TASK_EX_PROXY);
	_notifyGoldCost = true;
	_hasUnFinishTask = false;
	_allATaskSelect = false;
	_canShowAllATaskSelect = false;
}

bool DailyTaskExView::init()
{
	if(!CCLayer::init())
	{
		return false;
	}

	ValuesUtil *pValueUtil = ValuesUtil::Instance();

	this->setPosition(CCPointZero);
	this->setContentSize(CCDirector::sharedDirector()->getWinSize());
	this->setPopContentSize(this->getContentSize());

	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/streng/res_streng.plist");

	CCLayer *pParentLayer = new CCLayer();
	if(!pParentLayer || !pParentLayer->init())
	{
		return false;
	}
	CCPoint innerLayerPosition = POS(ccp(16.0f, 12.0f), ScaleUtil::CENTER_TOP);
	pParentLayer->setAnchorPoint(CCPointZero);
	//pParentLayer->initWithColor(ccc4(255, 128, 128, 100));
	pParentLayer->setPosition(innerLayerPosition);
	pParentLayer->setIsRelativeAnchorPoint(true);
	pParentLayer->setContentSize(CCDirector::sharedDirector()->getWinSize());
	this->addChild(pParentLayer, 0, TAG_PARENT_LAYER);
	pParentLayer->release();

	// Add Left Background
	CCUIBackground *pLeftBackground = new CCUIBackground();
	pLeftBackground->initWithSpriteFrame("ui2.png", ccp(POSX(8), POSX(22)), CCPointZero, CCSizeMake(POSX(454),
		POSX(518)));
	pParentLayer->addChild(pLeftBackground);

	// Add Right Background
	CCUIBackground *pRightBackground = new CCUIBackground();
	pRightBackground->initWithSpriteFrame("ui2.png", ccp(POSX(466), POSX(160)), CCPointZero, CCSizeMake(POSX(454),
		POSX(380)));
	pParentLayer->addChild(pRightBackground);

	CCUIListView *pListView = CCUIListView::listViewWithCCRect(CCRectMake(
		POSX(27),
		POSX(24),
		POSX(450),
		POSX(520)), 
		false);
	pListView->setAnchorPoint(CCPointZero);
	pListView->setSpacingVertical(POSX(8));
	pListView->setHeaderSize(POSX(10));
	pListView->setFooterSize(POSX(10));
	pListView->setAdapter(this);
	pListView->setIsRelativeAnchorPoint(true);
	pListView->setOnItemActionListener(this);
	//pListView->setClipLayerRect(CCRECT_LIST_CLIP);
	pListView->setWorldSpaceLeftBottomPoint(ccp(this->getPosition().x + pParentLayer->getPosition().x + pListView->getPosition().x,
		this->getPosition().y + pParentLayer->getPosition().y + pListView->getPosition().y));
	pListView->m_pri = TLE::WindowLayer_PurchaseView;
	pParentLayer->addChild(pListView, 0, TAG_LISTVIEW);
	pListView->release();

	/*_pCurrentDailyTaskExVo = _pDailyTaskExProxy->getDailyTaskExList()[0];
	updateCurrentSelectTask();*/

	// Add Right Panel
	CCLabelTTF *pTaskTitleLabel = CCLabelTTF::labelWithString(pValueUtil->getString("DTE004").c_str(), CCSizeMake(POSX(400), POSX(26)), CCTextAlignmentCenter,
		"Arial", POSX(26));
	if(pTaskTitleLabel)
	{
		pTaskTitleLabel->setColor(ccc3(237, 220, 2));
		pTaskTitleLabel->setPosition(ccp(POSX(650-16+52), POSX(520)));
		pTaskTitleLabel->setAnchorPoint(ccp(0.5, 0.5));
		pParentLayer->addChild(pTaskTitleLabel, 0, TAG_TASK_TITLE);
	}

	CCLabelTTF *pTaskRankNameLabel = CCLabelTTF::labelWithString(pValueUtil->getString("DTE001").c_str(), CCSizeMake(POSX(400), POSX(26)), CCTextAlignmentLeft,
		"Arial", POSX(24));
	if(pTaskRankNameLabel)
	{
		pTaskRankNameLabel->setColor(ccc3(237, 220, 2));
		pTaskRankNameLabel->setPosition(ccp(POSX(493-16), POSX(640-173-12)));
		pTaskRankNameLabel->setAnchorPoint(CCPointZero);
		pParentLayer->addChild(pTaskRankNameLabel);
	}

	CCLabelTTF *pTaskRankLabel = CCLabelTTF::labelWithString("3", CCSizeMake(POSX(400), POSX(26)), CCTextAlignmentLeft,
		"Arial", POSX(24));
	if(pTaskRankLabel)
	{
		pTaskRankLabel->setColor(ccc3(255, 255, 255));
		pTaskRankLabel->setPosition(ccp(POSX(600-16), POSX(640-173-12)));
		pTaskRankLabel->setAnchorPoint(CCPointZero);
		pParentLayer->addChild(pTaskRankLabel, 0, TAG_TASK_RANK);
	}

	CCLabelTTF *pTaskContentNameLabel = CCLabelTTF::labelWithString(pValueUtil->getString("DTE002").c_str(), CCSizeMake(POSX(400), POSX(26)), CCTextAlignmentLeft,
		"Arial", POSX(24));
	if(pTaskContentNameLabel)
	{
		pTaskContentNameLabel->setColor(ccc3(237, 220, 2));
		pTaskContentNameLabel->setPosition(ccp(POSX(493-16), POSX(420-12)));
		pTaskContentNameLabel->setAnchorPoint(CCPointZero);
		pParentLayer->addChild(pTaskContentNameLabel);
	}

	CCLabelTTF *pTaskContentLabel = CCLabelTTF::labelWithString(pValueUtil->getString("CHT001").c_str(), CCSizeMake(POSX(400), POSX(100)), CCTextAlignmentLeft,
		"Arial", POSX(24));
	if(pTaskContentLabel)
	{
		pTaskContentLabel->setColor(ccc3(255, 255, 255));
		pTaskContentLabel->setPosition(ccp(POSX(493-16), POSX(420-12-10)));
		pTaskContentLabel->setAnchorPoint(ccp(0, 1));
		pParentLayer->addChild(pTaskContentLabel, 0, TAG_TASK_CONTENT);
	}

	CCLabelTTF *pTaskAwardNameLabel = CCLabelTTF::labelWithString(pValueUtil->getString("DTE003").c_str(), CCSizeMake(POSX(400), POSX(26)), CCTextAlignmentLeft,
		"Arial", POSX(24));
	if(pTaskAwardNameLabel)
	{
		pTaskAwardNameLabel->setColor(ccc3(237, 220, 2));
		pTaskAwardNameLabel->setPosition(ccp(POSX(493-16), POSX(310-12-50)));
		pTaskAwardNameLabel->setAnchorPoint(CCPointZero);
		pParentLayer->addChild(pTaskAwardNameLabel);
	}

	// Add awards
	CCSprite *pTaskAwardPatIcon = CCSprite::spriteWithFile("assets/icon/goods/3.png");
	if(pTaskAwardPatIcon)
	{
		pTaskAwardPatIcon->setScale(0.5f);
		pTaskAwardPatIcon->setAnchorPoint(CCPointZero);
		pTaskAwardPatIcon->setPosition(ccp(POSX(493-16), POSX(180)));
		pParentLayer->addChild(pTaskAwardPatIcon);
	}

	char pAwardPatChar[128]={0};
	sprintf(pAwardPatChar, "%d", 0);
	CCLabelTTF *pTaskAwardPatLabel = CCLabelTTF::labelWithString(pAwardPatChar, CCSizeMake(POSX(200), POSX(26)), CCTextAlignmentLeft,
		"Arial", POSX(24));
	if(pTaskAwardPatLabel)
	{
		pTaskAwardPatLabel->setColor(ccc3(255, 255, 255));
		pTaskAwardPatLabel->setPosition(ccp(POSX(493-16+50), POSX(180)));
		pTaskAwardPatLabel->setAnchorPoint(CCPointZero);
		pParentLayer->addChild(pTaskAwardPatLabel, 0, TAG_TASK_AWARD_LABEL_PAT);
	}

	CCSprite *pTaskAwardSilverIcon = CCSprite::spriteWithFile("assets/icon/goods/2.png");
	if(pTaskAwardSilverIcon)
	{
		pTaskAwardSilverIcon->setScale(0.5f);
		pTaskAwardSilverIcon->setAnchorPoint(CCPointZero);
		pTaskAwardSilverIcon->setPosition(ccp(POSX(493-16+142), POSX(180)));
		pParentLayer->addChild(pTaskAwardSilverIcon, 0, TAG_TASK_AWARD_ICON_SILVER);
	}
	char pAwardSilverChar[128]={0};
	sprintf(pAwardSilverChar, "%d", 0);
	CCLabelTTF *pTaskAwardSilverLabel = CCLabelTTF::labelWithString(pAwardSilverChar, CCSizeMake(POSX(200), POSX(26)), CCTextAlignmentLeft,
		"Arial", POSX(24));
	if(pTaskAwardSilverLabel)
	{
		pTaskAwardSilverLabel->setColor(ccc3(255, 255, 255));
		pTaskAwardSilverLabel->setPosition(ccp(POSX(493-16+142+50), POSX(180)));
		pTaskAwardSilverLabel->setAnchorPoint(CCPointZero);
		pParentLayer->addChild(pTaskAwardSilverLabel, 0, TAG_TASK_AWARD_LABEL_SILVER);
	}

	CCSprite *pTaskAwardPopularIcon = CCSprite::spriteWithFile("assets/icon/goods/4.png");
	if(pTaskAwardPopularIcon)
	{
		pTaskAwardPopularIcon->setScale(0.5f);
		pTaskAwardPopularIcon->setAnchorPoint(CCPointZero);
		pTaskAwardPopularIcon->setPosition(ccp(POSX(493-16+142+142), POSX(180)));
		pParentLayer->addChild(pTaskAwardPopularIcon, 0, TAG_TASK_AWARD_ICON_POP);
	}
	char pAwardPopChar[128]={0};
	sprintf(pAwardPopChar, "%d", 0);
	CCLabelTTF *pTaskAwardPopLabel = CCLabelTTF::labelWithString(pAwardPopChar, CCSizeMake(POSX(200), POSX(26)), CCTextAlignmentLeft,
		"Arial", POSX(24));
	if(pTaskAwardPopLabel)
	{
		pTaskAwardPopLabel->setColor(ccc3(255, 255, 255));
		pTaskAwardPopLabel->setPosition(ccp(POSX(493-16+142+142+50), POSX(180)));
		pTaskAwardPopLabel->setAnchorPoint(CCPointZero);
		pParentLayer->addChild(pTaskAwardPopLabel, 0, TAG_TASK_AWARD_LABEL_POP);
	}

	/*char pFreeCountChar[128]={0};
	sprintf(pFreeCountChar, pValueUtil->getString("DTE010").c_str(), 0);
	CCLabelTTF *pFreeCountLabel = CCLabelTTF::labelWithString(pFreeCountChar, CCSizeMake(POSX(300), POSX(26)), CCTextAlignmentCenter,
	"Arial", POSX(24));
	if(pFreeCountLabel)
	{
	pFreeCountLabel->setColor(ccc3(255, 255, 255));
	pFreeCountLabel->setPosition(ccp(POSX(550-16+60), POSX(80-12+25+48)));
	pParentLayer->addChild(pFreeCountLabel, 0, TAG_LABEL_REMAIN_FREE_REFRESH);
	}*/

	char pRemainTaskChar[128]={0};
	sprintf(pRemainTaskChar, pValueUtil->getString("DTE011").c_str(), 0);
	CCLabelTTF *pRemainTaskLabel = CCLabelTTF::labelWithString(pRemainTaskChar, CCSizeMake(POSX(300), POSX(22)), CCTextAlignmentCenter,
		"Arial", POSX(20));
	if(pRemainTaskLabel)
	{
		pRemainTaskLabel->setColor(ccc3(255, 255, 255));
		pRemainTaskLabel->setPosition(ccp(POSX(624-16+60), POSX(80-12+25+52)));
		pParentLayer->addChild(pRemainTaskLabel, 0, TAG_LABEL_REMAIN_TASK_COUNT);
	}

	//550,80
	CCSprite *pRefreshNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
	CCSprite *pRefreshPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
	if(pRefreshNormalSprite && pRefreshPressedSprite)
	{
		CCMenuItemSprite *pRefreshMenuItem = CCMenuItemSprite::itemFromNormalSprite(
			pRefreshNormalSprite,
			pRefreshPressedSprite,
			this,
			menu_selector(DailyTaskExView::onRefreshClick) );
		pRefreshMenuItem->setAnchorPoint(CCPointZero);
		pRefreshMenuItem->setTag(TAG_BUTTON_REFRESH);
		pRefreshMenuItem->setPosition( ccp(POSX(550-16), POSX(80-2)) );
		CCMenu* pRefreshMenu = CCMenu::menuWithItems(pRefreshMenuItem, NULL);
		pRefreshMenu->setPosition( CCPointZero );
		pRefreshMenu->setTouchLayer(TLE::WindowLayer_PurchaseView - 1);
		pParentLayer->addChild(pRefreshMenu, 0, TAG_BUTTON_REFRESH);

		CCLabelTTF *pRefreshLabel = CCLabelTTF::labelWithString(pValueUtil->getString("DTE005").c_str(), CCSizeMake(POSX(100), POSX(24)), CCTextAlignmentCenter,
			"Arial", POSX(24));
		if(pRefreshLabel)
		{
			pRefreshLabel->setColor(ccc3(255, 255, 255));
			pRefreshLabel->setPosition(ccp(POSX(550-16+60), POSX(80-12+35)));
			pParentLayer->addChild(pRefreshLabel, 0, TAG_LABEL_REFRESH);
		}
	}

	CCSprite *pTaskNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
	CCSprite *pTaskPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
	if(pTaskNormalSprite && pTaskPressedSprite)
	{
		CCMenuItemSprite *pTaskMenuItem = CCMenuItemSprite::itemFromNormalSprite(
			pTaskNormalSprite,
			pTaskPressedSprite,
			this,
			menu_selector(DailyTaskExView::onAcceptOrSubmitClick) );
		pTaskMenuItem->setAnchorPoint(CCPointZero);
		pTaskMenuItem->setPosition( ccp(POSX(744-16), POSX(80-2)) );
		CCMenu* pTaskMenu = CCMenu::menuWithItems(pTaskMenuItem, NULL);
		pTaskMenu->setPosition( CCPointZero );
		pTaskMenu->setTouchLayer(TLE::WindowLayer_PurchaseView - 1);
		pParentLayer->addChild(pTaskMenu);

		CCLabelTTF *pTaskLabel = CCLabelTTF::labelWithString(pValueUtil->getString("DTE006").c_str(), CCSizeMake(POSX(100), POSX(24)), CCTextAlignmentCenter,
			"Arial", POSX(24));
		if(pTaskLabel)
		{
			pTaskLabel->setColor(ccc3(255, 255, 255));
			pTaskLabel->setPosition(ccp(POSX(744-16+60), POSX(80-12+35)));
			pParentLayer->addChild(pTaskLabel, 0, TAG_LABEL_ACTION);
		}
	}

	CCLabelTTF *pTipLabel = CCLabelTTF::labelWithString("", CCSizeMake(POSX(100), POSX(24)), CCTextAlignmentCenter,
		"Arial", POSX(20));
	if(pTipLabel)
	{
		pTipLabel->setColor(ccc3(255, 255, 255));
		pTipLabel->setPosition(ccp(POSX(550-16+60), POSX(60)));
		pParentLayer->addChild(pTipLabel, 0, TAG_LABEL_TIP);
	}

	// add All ATask about
	RoleManage *pRoleManage = RoleManage::Instance();
	_canShowAllATaskSelect = pRoleManage->accountInfo()->vipLev() >= 6;
	{
		CCSprite* pNormal = CCSprite::spriteWithSpriteFrameName("streng/grid.png");
		CCSprite* pPress = CCSprite::spriteWithSpriteFrameName("streng/grid.png");
		CCMenuItemSprite *pSelectItem = cocos2d::CCMenuItemImage::itemFromNormalSprite(
			pNormal,
			pPress,
			this,
			menu_selector(DailyTaskExView::onAllATaskSelect) );
		pSelectItem->setPosition( ccp(POSX(480), POSX(22)) );
		pSelectItem->setAnchorPoint(CCPointZero);
		pSelectItem->setTag(TAG_BUTTON_SELECT);
		CCMenu *pSelectMenu = CCMenu::menuWithItems(pSelectItem, 0);
		pSelectMenu->setTouchLayer( TLE::WindowLayer_Common_btn );
		pSelectMenu->setAnchorPoint(CCPointZero);
		pSelectMenu->setPosition( CCPointZero );
		pSelectMenu->setIsVisible(_canShowAllATaskSelect);
		pParentLayer->addChild( pSelectMenu, 0, TAG_BUTTON_SELECT );

		CCSprite *pSelectSprite = new CCSprite();
		if (pSelectSprite && pSelectSprite->initWithSpriteFrameName("streng/select.png"))
		{
			pSelectSprite->setAnchorPoint(CCPointZero);
			pSelectSprite->setPosition(ccp(POSX(480), POSX(22)));
			pParentLayer->addChild(pSelectSprite, 1, TAG_SPRITE_SELECT);
			pSelectSprite->release();
			pSelectSprite->setIsVisible(false);
		}

		CCLabelTTF *pSelectLabel = CCLabelTTF::labelWithString(pValueUtil->getString("DTE026").c_str(), CCSizeMake(POSX(400), POSX(20)), CCTextAlignmentLeft,
			"Arial", POSX(20));
		if(pSelectLabel)
		{
			pSelectLabel->setColor(ccc3(255, 255, 255));
			pSelectLabel->setAnchorPoint(CCPointZero);
			pSelectLabel->setPosition(ccp(POSX(520), POSX(30)));
			pSelectLabel->setIsVisible(_canShowAllATaskSelect);
			pParentLayer->addChild(pSelectLabel, 0, TAG_LABEL_SELECT);
		}
	}


	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/streng/res_streng.plist");
	return true;
}

int DailyTaskExView::getCount()
{
	return _pDailyTaskExProxy->getDailyTaskExList().size();
}

LayerNode * DailyTaskExView::getView( int position )
{
	LayerNode *pNode = new LayerNode();
	pNode->setContentSize(CCSizeMake(POSX(408), POSX(92)));
	pNode->setvisibleSize(CCSizeMake(POSX(408), POSX(92)));

	// Add Background
	CCUIBackground *pLeftBackground = new CCUIBackground();
	pLeftBackground->initWithSpriteFrame("ui2.png", CCPointZero, CCPointZero, CCSizeMake(POSX(408),
		POSX(92)));
	pNode->addChild(pLeftBackground);

	DailyTaskExVo *pTaskVo = _pDailyTaskExProxy->getDailyTaskExList()[position];
	if(!pTaskVo)
	{
		return pNode;
	}

	if(position == 0 || pTaskVo->hasAccepted == 1)
	{
		_pCurrentDailyTaskExVo = pTaskVo;
		updateCurrentSelectTask();
	}

	// Add Title
	// 日常任务（新）
	// 序号     种类         需要完成的次数
	//  1.    剧情副本         [1, 6]
	//  2.    挑战副本         [1, 4]
	//  3.    竞技场           [1, 5]
	//  4.    装备强化         [1, 5]
	//  5.    金币消耗         [1, 4]
	//  6.    佣兵训练         [1, 3]
	//  7.    训练突飞         [1, 5]
	//  8.    进行培养         [1, 5]
	//  9.    淘宝             [1, 5]
	// 10.    赏金领取         [1, 5]
	// 11.    添加好友         [1, 3]
	int id = pTaskVo->type + 100;
	char titleStr[128]={0};
	sprintf(titleStr, "DTE%d", id);
	ValuesUtil *pValueUtil = ValuesUtil::Instance();
	CCLabelTTF *pTitleLabel = CCLabelTTF::labelWithString(pValueUtil->getString(titleStr).c_str(), CCSizeMake(POSX(400), POSX(26)), CCTextAlignmentLeft,
		"Arial", POSX(26));
	if(pTitleLabel)
	{
		pTitleLabel->setColor(ColorUtil::getGoodColor(pTaskVo->quailty + 1));
		pTitleLabel->setPosition(ccp(POSX(10), POSX(54)));
		pTitleLabel->setAnchorPoint(CCPointZero);
		pNode->addChild(pTitleLabel);
	}

	// Add Content
	id += 200;
	char contentStr[20]={0};
	sprintf(contentStr, "DTE%d", id);
	char pContentChars[128]={0};
	/*if(pTaskVo->type == 1)
	{
		NPCVo* pNpc = MonsterManager::Instance()->getMonsterGroup(pTaskVo->monsterGroup);
		char pMonsterName[20]={0};
		if(pNpc)
		{
			sprintf(pMonsterName, "%s", pNpc->name.c_str());
		}
		else
		{
			sprintf(pMonsterName, "ID:%d", pTaskVo->monsterGroup);
		}
		sprintf(pContentChars, pValueUtil->getString(contentStr).c_str(), pMonsterName, pTaskVo->finishCount, pTaskVo->count);
	}
	else
	{
		sprintf(pContentChars, pValueUtil->getString(contentStr).c_str(), pTaskVo->finishCount, pTaskVo->count);
	}*/
	sprintf(pContentChars, pValueUtil->getString(contentStr).c_str(), pTaskVo->finishCount, pTaskVo->count);
	CCLabelTTF *pContentLabel = CCLabelTTF::labelWithString(pContentChars, CCSizeMake(POSX(400), POSX(22)), CCTextAlignmentLeft,
		"Arial", POSX(20));
	if(pContentLabel)
	{
		pContentLabel->setColor(ccc3(224, 175, 4));
		pContentLabel->setPosition(ccp(POSX(10), POSX(22)));
		pContentLabel->setAnchorPoint(CCPointZero);
		pNode->addChild(pContentLabel);
	}

	// Add select
	CCLayer *pSelectLayer = new CCLayer();
	pSelectLayer->setPosition(ccp(POSX(360), POSX(48)));
	pSelectLayer->setAnchorPoint(CCPointZero);
	CCSprite *pFrameSprite = CCSprite::spriteWithSpriteFrameName("peiyang/bg_kuang.png");
	if(pFrameSprite)
	{
		pFrameSprite->setAnchorPoint(CCPointZero);
		pFrameSprite->setPosition(CCPointZero);
		pSelectLayer->addChild(pFrameSprite);
	}
	CCSprite *pIconSprite = CCSprite::spriteWithSpriteFrameName("peiyang/gou1.png");
	if(pIconSprite)
	{
		pIconSprite->setAnchorPoint(CCPointZero);
		pIconSprite->setPosition(CCPointZero);
		pSelectLayer->addChild(pIconSprite);
	}
	if(pTaskVo->hasAccepted == 1)
	{
		pSelectLayer->setIsVisible(true);
	}
	else
	{
		pSelectLayer->setIsVisible(false);
	}
	pNode->addChild(pSelectLayer, 0, TAG_CELL_SELECT);
	pSelectLayer->release();


	CCUIBackground *pHighLightSprite = new CCUIBackground();
	pHighLightSprite->initWithSpriteFrame( "train/gold_back.png",
		ccp(0, POSX(2)), CCPointZero, CCSizeMake( POSX(408), POSX(92) ) );
	pHighLightSprite->setIsVisible(pTaskVo->hasAccepted == 1);
	pNode->addChild( pHighLightSprite, 0, TAG_CELL_HIGHLIGHT );
	pHighLightSprite->release();


	return pNode;
}

void DailyTaskExView::onRefreshClick( CCObject* pSender )
{
	if(_hasUnFinishTask && 1 == _pCurrentDailyTaskExVo->hasAccepted)
	{
		/*
		if(RoleManage::Instance()->accountInfo()->vipLev() < 4)
		{
			LangManager::msgShow("DTE029");
			return;
		}
		*/
		if (!VIPMgr::Instance()->hasVIPFunc(VIPLimitConst::VIP_GoldFinishTask , RoleManage::Instance()->accountInfo()->vipLev()))
		{
			char path[128] = {0};
			sprintf(path , ValuesUtil::Instance()->getString("WLC010").c_str() , VIPLimitConst::VIP_GoldFinishTask);
			MessageInfoBox::Instance()->show(path,ccc3(12,233,25));
			return;
		}
		else
		{
			if(RoleManage::Instance()->accountInfo()->_gold < 10)
			{
				LangManager::msgShow("S3");
				return;
			}

			GameServerSocket *pGameServerSocket = GameServerSocket::getInstance();
			CCMD424 *pCCMD424 = new CCMD424(_pCurrentDailyTaskExVo->taskId,
				_pCurrentDailyTaskExVo->type, 1);
			pGameServerSocket->sendMessage(pCCMD424);
			CC_SAFE_DELETE(pCCMD424);
			return;
		}
	}
	if(_pDailyTaskExProxy->getRemainTaskCount() <= 0)
	{
		LangManager::msgShow("DTE014");
		return;
	}
	bool hasALevelTask = false;
	std::vector<DailyTaskExVo *>::const_iterator taskIter = _pDailyTaskExProxy->getDailyTaskExList().begin();
	for(; taskIter != _pDailyTaskExProxy->getDailyTaskExList().end(); ++taskIter)
	{
		if((*taskIter)->hasAccepted == 1)
		{
			LangManager::msgShow("DTE013");
			return;
		}
		if((*taskIter)->quailty == 5)
		{
			hasALevelTask = true;
		}
	}

	if(hasALevelTask)
	{
		Confirm* pConfirm = new Confirm();
		pConfirm->initWithParam(ValuesUtil::Instance()->getString("DTE024"), this, menu_selector(DailyTaskExView::onATaskConfirmOk),
			menu_selector(DailyTaskExView::onATaskConfirmCancel));
		LayerManager::tipsLayer->addChild(pConfirm,TipsLayer::TipsLayerZ_confirmFrame, TipsLayer::TipsLayerTAG_confirmFrame);
		pConfirm->release();
		return;
	}

	if(_pDailyTaskExProxy->getRemainFreeRefreshCount() <= 0)
	{
//		if(RoleManage::Instance()->accountInfo()->_vipLev < 3)
//		{
//			LangManager::msgShow("DTE015");
//			return;
//		}

		int cost = _allATaskSelect ? 100 : 5;
		if(RoleManage::Instance()->accountInfo()->_gold < cost)
		{
			LangManager::msgShow("S3");
			return;
		}
		
		if(_notifyGoldCost)
		{
			Confirm* pConfirm = new Confirm();
			char pTipChar[128] = {0};
			sprintf(pTipChar, ValuesUtil::Instance()->getString("DTE017").c_str(), cost);
			pConfirm->initWithParam(pTipChar, this, menu_selector(DailyTaskExView::onGoldConfirmOk),
				menu_selector(DailyTaskExView::onGoldConfirmCancel));
			LayerManager::tipsLayer->addChild(pConfirm,TipsLayer::TipsLayerZ_confirmFrame, TipsLayer::TipsLayerTAG_confirmFrame);
			pConfirm->release();
			return;
		}
	}
	int type = _allATaskSelect ? 1 : 0;
	CCMD428 *ccmd428 = new CCMD428(type);
	GameServerSocket *pGameServerSocket = GameServerSocket::getInstance();
	if(pGameServerSocket)
	{
		pGameServerSocket->sendMessage(ccmd428);
	}
	CC_SAFE_DELETE(ccmd428);
}

void DailyTaskExView::onAcceptOrSubmitClick( CCObject* pSender )
{
	GameServerSocket *pGameServerSocket = GameServerSocket::getInstance();
	if(!_pCurrentDailyTaskExVo || !pGameServerSocket)
	{
		return;
	}

	if(_pCurrentDailyTaskExVo->hasAccepted == 1)
	{
		// Submit task
		if(_pCurrentDailyTaskExVo->count == _pCurrentDailyTaskExVo->finishCount)
		{
			CCMD424 *pCCMD424 = new CCMD424(_pCurrentDailyTaskExVo->taskId,
				_pCurrentDailyTaskExVo->type, 0);
			pGameServerSocket->sendMessage(pCCMD424);
			CC_SAFE_DELETE(pCCMD424);
		}
		else
		{
			Confirm* pConfirm = new Confirm();
			pConfirm->initWithParam(ValuesUtil::Instance()->getString("DTE020"), this, menu_selector(DailyTaskExView::onGiveUpConfirmOk),
				menu_selector(DailyTaskExView::onGiveUpConfirmCancel));
			LayerManager::tipsLayer->addChild(pConfirm,TipsLayer::TipsLayerZ_confirmFrame, TipsLayer::TipsLayerTAG_confirmFrame);
			pConfirm->release();
			return;
		}
	}
	else
	{
		bool hasAcceptedTask = false;
		std::vector<DailyTaskExVo *>::const_iterator taskIter = _pDailyTaskExProxy->getDailyTaskExList().begin();
		for(; taskIter != _pDailyTaskExProxy->getDailyTaskExList().end(); ++taskIter)
		{
			if((*taskIter)->hasAccepted == 1)
			{
				hasAcceptedTask = true;
				break;
			}
		}
		if(hasAcceptedTask)
		{
			Confirm* pConfirm = new Confirm();
			pConfirm->initWithParam(ValuesUtil::Instance()->getString("DTE019"), this, menu_selector(DailyTaskExView::onAcceptConfirmOk),
				menu_selector(DailyTaskExView::onAcceptConfirmCancel));
			LayerManager::tipsLayer->addChild(pConfirm,TipsLayer::TipsLayerZ_confirmFrame, TipsLayer::TipsLayerTAG_confirmFrame);
			pConfirm->release();
			return;
		}
		if(_pDailyTaskExProxy->getRemainTaskCount() <= 0)
		{
			LangManager::msgShow("DTE014");
			return;
		}
		// Accept task
		CCMD422 *pCCMD422 = new CCMD422(_pCurrentDailyTaskExVo->taskId,
			_pCurrentDailyTaskExVo->type);
		pGameServerSocket->sendMessage(pCCMD422);
		CC_SAFE_DELETE(pCCMD422);
	}
}

void DailyTaskExView::onItemTouchListener( LayerNode *itemCell, int position )
{

	_pCurrentDailyTaskExVo = _pDailyTaskExProxy->getDailyTaskExList()[position];

	CCNode *pParentLayer = this->getChildByTag(TAG_PARENT_LAYER);
	if(!pParentLayer || !_pCurrentDailyTaskExVo)
	{
		return;
	}

	// set highlight
	CCUIListView *pListView = (CCUIListView *) pParentLayer->getChildByTag(TAG_LISTVIEW);
	if(!pListView)
	{
		return;
	}

	CCMutableArray<LayerNode *> * pLayerItems = pListView->getChilds();
	CCMutableArray<LayerNode *>::CCMutableArrayIterator it = pLayerItems->begin();
	int itemIndex = 0;
	for (it;it != pLayerItems->end();it++)
	{
		CCNode *pSelectLayer = (*it)->getChildByTag(TAG_CELL_HIGHLIGHT);
		if (pSelectLayer)
		{
			pSelectLayer->setIsVisible(itemIndex == position);
		}
		itemIndex ++;
	}
	updateCurrentSelectTask();
}

void DailyTaskExView::updateCurrentSelectTask()
{
	CCNode *pParentLayer = this->getChildByTag(TAG_PARENT_LAYER);
	if(!pParentLayer || !_pCurrentDailyTaskExVo)
	{
		return;
	}

	int id = _pCurrentDailyTaskExVo->type + 100;
	ValuesUtil *pValueUtil = ValuesUtil::Instance();

	char titleStr[128]={0};
	sprintf(titleStr, "DTE%d", id);
	CCLabelTTF *pTaskTitleabel = (CCLabelTTF *) pParentLayer->getChildByTag(TAG_TASK_TITLE);
	if(pTaskTitleabel)
	{
		pTaskTitleabel->setString(pValueUtil->getString(titleStr).c_str());
		pTaskTitleabel->setColor(ColorUtil::getGoodColor(_pCurrentDailyTaskExVo->quailty + 1));
	}

	CCLabelTTF *pTaskRankLabel = (CCLabelTTF *) pParentLayer->getChildByTag(TAG_TASK_RANK);
	if(pTaskRankLabel)
	{
		char pRankChars[128] = {0};
		switch(_pCurrentDailyTaskExVo->quailty)
		{
		case 1:
			sprintf(pRankChars, "E");
			break;
		case 2:
			sprintf(pRankChars, "D");
			break;
		case 3:
			sprintf(pRankChars, "C");
			break;
		case 4:
			sprintf(pRankChars, "B");
			break;
		case 5:
			sprintf(pRankChars, "A");
			break;
		default:
			sprintf(pRankChars, "E");
			break;
		}
		pTaskRankLabel->setString(pRankChars);
		pTaskRankLabel->setColor(ColorUtil::getGoodColor(_pCurrentDailyTaskExVo->quailty + 1));
	}

	CCLabelTTF *pTaskContentLabel = (CCLabelTTF *) pParentLayer->getChildByTag(TAG_TASK_CONTENT);
	if(pTaskContentLabel)
	{
		id += 200;
		char contentStr[128]={0};
		sprintf(contentStr, "DTE%d", id);
		char pContentChars[128]={0};
		/*if(_pCurrentDailyTaskExVo->type == 1)
		{
		NPCVo* pNpc = MonsterManager::Instance()->getMonsterGroup(_pCurrentDailyTaskExVo->monsterGroup);
		char pMonsterName[20]={0};
		if(pNpc)
		{
		sprintf(pMonsterName, "%s", pNpc->name.c_str());
		}
		else
		{
		sprintf(pMonsterName, "Unknown");
		}
		sprintf(pContentChars, pValueUtil->getString(contentStr).c_str(), pMonsterName, _pCurrentDailyTaskExVo->finishCount, _pCurrentDailyTaskExVo->count);
		}
		else
		{
		sprintf(pContentChars, pValueUtil->getString(contentStr).c_str(), _pCurrentDailyTaskExVo->finishCount, _pCurrentDailyTaskExVo->count);
		}*/
		sprintf(pContentChars, pValueUtil->getString(contentStr).c_str(), _pCurrentDailyTaskExVo->finishCount, _pCurrentDailyTaskExVo->count);
		pTaskContentLabel->setString(pContentChars);
	}

	// Add reward
	//#define SILVER_ITEM_ID 2
	//#define PRACTICE_ITEM_ID 3
	//#define POPULARITY_ITEM_ID 4
	int awardSilver = 0, awardPractice = 0, awardPopularity = 0;
	std::vector<std::pair<int, int> >::iterator iter = _pCurrentDailyTaskExVo->awardList.begin();
	for(; iter != _pCurrentDailyTaskExVo->awardList.end(); ++iter)
	{
		if(iter->first == 2)
		{
			//silver
			awardSilver = iter->second;
		}
		else if (iter->first == 3)
		{
			//practice
			awardPractice = iter->second;
		}
		else if (iter->first == 4)
		{
			//popularity
			awardPopularity = iter->second;
		}
	}
	CCLabelTTF *pTaskAwardSilverLabel = (CCLabelTTF *) pParentLayer->getChildByTag(TAG_TASK_AWARD_LABEL_SILVER);
	CCSprite *pTaskAwardSilverIcon = (CCSprite *) pParentLayer->getChildByTag(TAG_TASK_AWARD_ICON_SILVER);
	if(pTaskAwardSilverLabel)
	{
		if(awardSilver > 0)
		{
			pTaskAwardSilverLabel->setIsVisible(true);
			pTaskAwardSilverIcon->setIsVisible(true);
			char pAwardSilverChar[128]={0};
			sprintf(pAwardSilverChar, "%d", awardSilver);
			pTaskAwardSilverLabel->setString(pAwardSilverChar);
		}
		else
		{
			pTaskAwardSilverIcon->setIsVisible(false);
			pTaskAwardSilverLabel->setIsVisible(false);
		}
	}
	CCLabelTTF *pTaskAwardPatLabel = (CCLabelTTF *) pParentLayer->getChildByTag(TAG_TASK_AWARD_LABEL_PAT);
	if(pTaskAwardPatLabel)
	{
		char pAwardPatChar[128]={0};
		sprintf(pAwardPatChar, "%d", awardPractice);
		pTaskAwardPatLabel->setString(pAwardPatChar);
	}
	CCLabelTTF *pTaskAwardPopLabel = (CCLabelTTF *) pParentLayer->getChildByTag(TAG_TASK_AWARD_LABEL_POP);
	CCSprite *pTaskAwardPopIcon = (CCSprite *) pParentLayer->getChildByTag(TAG_TASK_AWARD_ICON_POP);
	if(pTaskAwardPopLabel && pTaskAwardPopIcon)
	{
		if(awardPopularity > 0)
		{
			pTaskAwardPopIcon->setIsVisible(true);
			pTaskAwardPopLabel->setIsVisible(true);
			char pAwardPopChar[128]={0};
			sprintf(pAwardPopChar, "%d", awardPopularity);
			pTaskAwardPopLabel->setString(pAwardPopChar);
		}
		else
		{
			pTaskAwardPopIcon->setIsVisible(false);
			pTaskAwardPopLabel->setIsVisible(false);
		}
	}

	// UPDATE label
	CCLabelTTF *pRemainFreeLabel = (CCLabelTTF *) pParentLayer->getChildByTag(TAG_LABEL_REMAIN_FREE_REFRESH);
	if(pRemainFreeLabel)
	{
		char pFreeCountChar[128]={0};
		sprintf(pFreeCountChar, pValueUtil->getString("DTE010").c_str(), _pDailyTaskExProxy->getRemainFreeRefreshCount());
		pRemainFreeLabel->setString(pFreeCountChar);
	}
	CCLabelTTF *pRemainTaskLabel = (CCLabelTTF *) pParentLayer->getChildByTag(TAG_LABEL_REMAIN_TASK_COUNT);
	if(pRemainTaskLabel)
	{
		char pTaskChar[128]={0};
		sprintf(pTaskChar, pValueUtil->getString("DTE011").c_str(), _pDailyTaskExProxy->getRemainTaskCount());
		pRemainTaskLabel->setString(pTaskChar);
	}

	// UPDATE BUTTON
	CCLabelTTF *pActionLabel = (CCLabelTTF *) pParentLayer->getChildByTag(TAG_LABEL_ACTION);
	if(pActionLabel)
	{
		if(_pCurrentDailyTaskExVo->hasAccepted == 1)
		{
			if (_pCurrentDailyTaskExVo->finishCount == _pCurrentDailyTaskExVo->count)
			{
				pActionLabel->setString(pValueUtil->getString("DTE007").c_str());
			}
			else
			{
				pActionLabel->setString(pValueUtil->getString("DTE023").c_str());
			}
		}
		else
		{
			pActionLabel->setString(pValueUtil->getString("DTE006").c_str());
		}
	}
	CCLabelTTF *pRefreshLabel = (CCLabelTTF *) pParentLayer->getChildByTag(TAG_LABEL_REFRESH);
	CCLabelTTF *pTipLabel = (CCLabelTTF *) pParentLayer->getChildByTag(TAG_LABEL_TIP);
	bool hasAccepted = 1 == _pCurrentDailyTaskExVo->hasAccepted;
	if(pRefreshLabel && pTipLabel)
	{
		char pTipChar[64] = {0};

		if(hasAccepted)
		{
			pRefreshLabel->setString(pValueUtil->getString("DTE025").c_str());
			sprintf(pTipChar, pValueUtil->getString("DTE027").c_str(), 10);
			pTipLabel->setString(pTipChar);
		}
		else
		{
			if(_pDailyTaskExProxy->getRemainFreeRefreshCount() > 0)
			{
				pRefreshLabel->setString(pValueUtil->getString("DTE005").c_str());
				sprintf(pTipChar, pValueUtil->getString("DTE028").c_str(), _pDailyTaskExProxy->getRemainFreeRefreshCount());
				pTipLabel->setString(pTipChar);
			}
			else
			{
				int cost = _allATaskSelect ? 100 : 5;
				pRefreshLabel->setString(pValueUtil->getString("DTE008").c_str());
				sprintf(pTipChar, pValueUtil->getString("DTE027").c_str(), cost);
				pTipLabel->setString(pTipChar);
			}
		}

	}

	bool isFreeRefresh = _pDailyTaskExProxy->getRemainFreeRefreshCount() > 0;
	CCNode *pAllASelect = pParentLayer->getChildByTag(TAG_BUTTON_SELECT);
	CCNode *pAllASelectLabel = pParentLayer->getChildByTag(TAG_LABEL_SELECT);
	if(pAllASelectLabel)
	{
		pAllASelectLabel->setIsVisible((!isFreeRefresh && _canShowAllATaskSelect) && !hasAccepted);
	}
	if(pAllASelect)
	{
		pAllASelect->setIsVisible((!isFreeRefresh && _canShowAllATaskSelect) && !hasAccepted);
	}
}

void DailyTaskExView::refresh()
{
	CCNode *pParentLayer = this->getChildByTag(TAG_PARENT_LAYER);
	if(!pParentLayer)
	{
		return;
	}

	CCUIListView *pListView = (CCUIListView *) pParentLayer->getChildByTag(TAG_LISTVIEW);
	if(!pListView)
	{
		return;
	}
	_hasUnFinishTask = _pDailyTaskExProxy->getHasUnFinishTask();
	pListView->setAdapter(this);
}

void DailyTaskExView::onOpenFinished()
{
	// If not data, request
	if(_pDailyTaskExProxy->getDailyTaskExList().size() == 0)
	{
		CCMD420 cCMD420;
		GameServerSocket *pGameServerSocket = GameServerSocket::getInstance();
		if(pGameServerSocket)
		{
			pGameServerSocket->sendMessage(&cCMD420);
		}
	}
    
    refresh();
}

void DailyTaskExView::updateAccpetTask( int taskId )
{
	_hasUnFinishTask = true;

	refresh();

	CCNode *pParentLayer = this->getChildByTag(TAG_PARENT_LAYER);
	if(!pParentLayer)
	{
		return;
	}

	ValuesUtil *pValueUtil = ValuesUtil::Instance();
	CCLabelTTF *pRefreshLabel = (CCLabelTTF *) pParentLayer->getChildByTag(TAG_LABEL_REFRESH);
	CCLabelTTF *pTipLabel = (CCLabelTTF *) pParentLayer->getChildByTag(TAG_LABEL_TIP);
	if(pRefreshLabel && pTipLabel)
	{
		char pTipChar[64] = {0};
		pRefreshLabel->setString(pValueUtil->getString("DTE025").c_str());
		sprintf(pTipChar, pValueUtil->getString("DTE027").c_str(), 10);
		pTipLabel->setString(pTipChar);
	}


	//int index = 0;

	//std::vector<DailyTaskExVo *>::const_iterator taskIter = _pDailyTaskExProxy->getDailyTaskExList().begin();
	//for(; taskIter != _pDailyTaskExProxy->getDailyTaskExList().end(); ++taskIter)
	//{
	//	if((*taskIter)->taskId == taskId)
	//	{
	//		_pCurrentDailyTaskExVo = (DailyTaskExVo *)(*taskIter);
	//		updateCurrentSelectTask();
	//		break;
	//	}
	//	index ++;
	//}
	//
	//CCNode *pParentLayer = this->getChildByTag(TAG_PARENT_LAYER);
	//if(!pParentLayer || !_pCurrentDailyTaskExVo)
	//{
	//	return;
	//}

	//// Clear All Status
	//CCUIListView *pListView = (CCUIListView *) pParentLayer->getChildByTag(TAG_LISTVIEW);
	//if(!pListView)
	//{
	//	return;
	//}

	//CCMutableArray<LayerNode *> * pLayerItems = pListView->getChilds();
	//CCMutableArray<LayerNode *>::CCMutableArrayIterator it = pLayerItems->begin();
	//int itemIndex = 0;
	//for (it;it != pLayerItems->end();it++)
	//{
	//	CCNode *pSelectLayer = (*it)->getChildByTag(TAG_CELL_SELECT);
	//	if (pSelectLayer)
	//	{
	//		pSelectLayer->setIsVisible(itemIndex == index);
	//	}
	//	itemIndex ++;
	//}
}

void DailyTaskExView::onGoldConfirmOk( CCObject* pSender )
{
	_notifyGoldCost = false;
	int type = _allATaskSelect ? 1 : 0;
	CCMD428 *ccmd428 = new CCMD428(type);
	GameServerSocket *pGameServerSocket = GameServerSocket::getInstance();
	if(pGameServerSocket)
	{
		pGameServerSocket->sendMessage(ccmd428);
	}
	CC_SAFE_DELETE(ccmd428);
	CCNode* pSell = LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pSell)
		pSell->removeFromParentAndCleanup(true);
}

void DailyTaskExView::onGoldConfirmCancel( CCObject* pSender )
{
	CCNode* pSell = LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pSell)
		pSell->removeFromParentAndCleanup(true);
}

void DailyTaskExView::onAcceptConfirmOk( CCObject* pSender )
{
	GameServerSocket *pGameServerSocket = GameServerSocket::getInstance();
	CCMD422 *pCCMD422 = new CCMD422(_pCurrentDailyTaskExVo->taskId,
		_pCurrentDailyTaskExVo->type);
	pGameServerSocket->sendMessage(pCCMD422);
	CC_SAFE_DELETE(pCCMD422);
	CCNode* pSell = LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pSell)
		pSell->removeFromParentAndCleanup(true);
}

void DailyTaskExView::onAcceptConfirmCancel( CCObject* pSender )
{
	CCNode* pSell = LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pSell)
		pSell->removeFromParentAndCleanup(true);
}

void DailyTaskExView::onGiveUpConfirmOk( CCObject* pSender )
{
	GameServerSocket *pGameServerSocket = GameServerSocket::getInstance();
	CCMD42A *pCCMD42A = new CCMD42A(_pCurrentDailyTaskExVo->taskId,
		_pCurrentDailyTaskExVo->type);
	pGameServerSocket->sendMessage(pCCMD42A);
	CC_SAFE_DELETE(pCCMD42A);
	CCNode* pSell = LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pSell)
		pSell->removeFromParentAndCleanup(true);
}

void DailyTaskExView::onGiveUpConfirmCancel( CCObject* pSender )
{
	CCNode* pSell = LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pSell)
		pSell->removeFromParentAndCleanup(true);
}

void DailyTaskExView::onATaskConfirmOk( CCObject* pSender )
{
	CCNode* pSell = LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pSell)
		pSell->removeFromParentAndCleanup(true);
	if(_pDailyTaskExProxy->getRemainFreeRefreshCount() <= 0)
	{
//		if(RoleManage::Instance()->accountInfo()->_vipLev < 3)
//		{
//			LangManager::msgShow("DTE015");
//			return;
//		}

		int cost = _allATaskSelect ? 100 : 5;
		if(RoleManage::Instance()->accountInfo()->_gold < cost)
		{
			LangManager::msgShow("S3");
			return;
		}

		if(_notifyGoldCost)
		{
			Confirm* pConfirm = new Confirm();
			char pTipChar[128] = {0};
			sprintf(pTipChar, ValuesUtil::Instance()->getString("DTE017").c_str(), cost);
			pConfirm->initWithParam(pTipChar, this, menu_selector(DailyTaskExView::onGoldConfirmOk),
				menu_selector(DailyTaskExView::onGoldConfirmCancel));
			LayerManager::tipsLayer->addChild(pConfirm,TipsLayer::TipsLayerZ_confirmFrame, TipsLayer::TipsLayerTAG_confirmFrame);
			pConfirm->release();
			return;
		}
	}
	_notifyGoldCost = false;
	int type = _allATaskSelect ? 1 : 0;
	CCMD428 *ccmd428 = new CCMD428(type);
	GameServerSocket *pGameServerSocket = GameServerSocket::getInstance();
	if(pGameServerSocket)
	{
		pGameServerSocket->sendMessage(ccmd428);
	}
	CC_SAFE_DELETE(ccmd428);
}

void DailyTaskExView::onATaskConfirmCancel( CCObject* pSender )
{
	CCNode* pSell = LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pSell)
		pSell->removeFromParentAndCleanup(true);
}

void DailyTaskExView::updateGiveupTask()
{
	_hasUnFinishTask = false;

	refresh();

	CCNode *pParentLayer = this->getChildByTag(TAG_PARENT_LAYER);
	if(!pParentLayer)
	{
		return;
	}

	ValuesUtil *pValueUtil = ValuesUtil::Instance();

	CCLabelTTF *pRefreshLabel = (CCLabelTTF *) pParentLayer->getChildByTag(TAG_LABEL_REFRESH);
	CCLabelTTF *pTipLabel = (CCLabelTTF *) pParentLayer->getChildByTag(TAG_LABEL_TIP);
	if(pRefreshLabel)
	{
		char pTipChar[64] = {0};
		if(_pDailyTaskExProxy->getRemainFreeRefreshCount() > 0)
		{
			pRefreshLabel->setString(pValueUtil->getString("DTE005").c_str());
			sprintf(pTipChar, pValueUtil->getString("DTE028").c_str(), _pDailyTaskExProxy->getRemainFreeRefreshCount());
			pTipLabel->setString(pTipChar);
			CCNode *pSelectButton = pParentLayer->getChildByTag(TAG_BUTTON_SELECT);
			CCNode *pSelectLabel = pParentLayer->getChildByTag(TAG_LABEL_SELECT);
			CCNode *pSelectSprite = pParentLayer->getChildByTag(TAG_SPRITE_SELECT);
			if(pSelectButton)
			{
				pSelectButton->setIsVisible(false);
			}
			if(pSelectLabel)
			{
				pSelectLabel->setIsVisible(false);
			}
			if(pSelectSprite)
			{
				pSelectSprite->setIsVisible(false);
			}
		}
		else
		{
			pRefreshLabel->setString(pValueUtil->getString("DTE008").c_str());
			sprintf(pTipChar, pValueUtil->getString("DTE027").c_str(), 5);
			pTipLabel->setString(pTipChar);
		}
	}
}

void DailyTaskExView::updateProgress(bool canSubmit)
{
	refresh();

	showLeftButtonsAndLables(!canSubmit);
	if(canSubmit)
	{
		CCNode *pParentLayer = this->getChildByTag(TAG_PARENT_LAYER);
		if(!pParentLayer)
		{
			return;
		}
		CCLabelTTF *pTipLabel = (CCLabelTTF *) pParentLayer->getChildByTag(TAG_LABEL_TIP);
		if(pTipLabel)
		{
			pTipLabel->setIsVisible(false);
		}
	}
}

void DailyTaskExView::updateSubmitTask()
{
	_hasUnFinishTask = false;
	_allATaskSelect = false;
	refresh();

	showLeftButtonsAndLables(true);

	CCNode *pParentLayer = this->getChildByTag(TAG_PARENT_LAYER);
	if(!pParentLayer)
	{
		return;
	}
	CCLabelTTF *pTipLabel = (CCLabelTTF *) pParentLayer->getChildByTag(TAG_LABEL_TIP);
	if(pTipLabel)
	{
		pTipLabel->setIsVisible(true);
	}
}

void DailyTaskExView::updateRefreshTask( bool canSubmit )
{
	_hasUnFinishTask = false;
	_allATaskSelect = false;
	refresh();
	showLeftButtonsAndLables(!canSubmit);
}

void DailyTaskExView::onAllATaskSelect( CCObject* pSender )
{
	CCNode *pParentLayer = this->getChildByTag(TAG_PARENT_LAYER);
	if(!pParentLayer)
	{
		return;
	}
	/*CCNode *pButton = pParentLayer->getChildByTag(TAG_BUTTON_SELECT);
	if(pButton)
	{
	pButton->setIsVisible(!pButton->getIsVisible());
	_allATaskSelect = !pButton->getIsVisible();
	}*/
	_allATaskSelect = !_allATaskSelect;
	CCNode *pSelectSprite = pParentLayer->getChildByTag(TAG_SPRITE_SELECT);
	if(pSelectSprite)
	{
		pSelectSprite->setIsVisible(_allATaskSelect && _canShowAllATaskSelect);
	}

	char pTipChar[64] = {0};
	ValuesUtil *pValueUtil = ValuesUtil::Instance();
	CCLabelTTF *pTipLabel = (CCLabelTTF *) pParentLayer->getChildByTag(TAG_LABEL_TIP);
	if(_allATaskSelect)
	{
		sprintf(pTipChar, pValueUtil->getString("DTE027").c_str(), 100);
		pTipLabel->setString(pTipChar);
	}
	else
	{
		sprintf(pTipChar, pValueUtil->getString("DTE027").c_str(), 5);
		pTipLabel->setString(pTipChar);
	}
}

void DailyTaskExView::showLeftButtonsAndLables( bool isShow )
{
	CCNode *pParentLayer = this->getChildByTag(TAG_PARENT_LAYER);
	if(!pParentLayer)
	{
		return;
	}
	CCNode *pButton = pParentLayer->getChildByTag(TAG_BUTTON_REFRESH);
	CCLabelTTF *pRefreshLabel = (CCLabelTTF *) pParentLayer->getChildByTag(TAG_LABEL_REFRESH);
	CCLabelTTF *pTipLabel = (CCLabelTTF *) pParentLayer->getChildByTag(TAG_LABEL_TIP);

	ValuesUtil *pValueUtil = ValuesUtil::Instance();

	CCNode *pSelectButton = pParentLayer->getChildByTag(TAG_BUTTON_SELECT);
	CCNode *pSelectLabel = pParentLayer->getChildByTag(TAG_LABEL_SELECT);
	CCNode *pSelectSprite = pParentLayer->getChildByTag(TAG_SPRITE_SELECT);


	if(pButton)
	{
		pButton->setIsVisible(isShow);
	}
	if(pRefreshLabel)
	{
		pRefreshLabel->setIsVisible(isShow);
	}
	if(pSelectButton)
	{
		pSelectButton->setIsVisible(isShow && _canShowAllATaskSelect);
	}
	if(pSelectLabel)
	{
		pSelectLabel->setIsVisible(isShow && _canShowAllATaskSelect);
	}
	if(pSelectSprite)
	{
		pSelectSprite->setIsVisible(_allATaskSelect && isShow && _canShowAllATaskSelect);
	}

	if(!isShow)
	{
		_hasUnFinishTask = false;
	}
	else
	{
		if(pRefreshLabel && pTipLabel)
		{
			char pTipChar[64] = {0};
			if(_pDailyTaskExProxy->getRemainFreeRefreshCount() > 0)
			{
				pRefreshLabel->setString(pValueUtil->getString("DTE005").c_str());
				sprintf(pTipChar, pValueUtil->getString("DTE028").c_str(), _pDailyTaskExProxy->getRemainFreeRefreshCount());
				pTipLabel->setString(pTipChar);
				if(pSelectButton)
				{
					pSelectButton->setIsVisible(false);
				}
				if(pSelectLabel)
				{
					pSelectLabel->setIsVisible(false);
				}
				if(pSelectSprite)
				{
					pSelectSprite->setIsVisible(false);
				}
			}
			else
			{
				pRefreshLabel->setString(pValueUtil->getString("DTE008").c_str());
				sprintf(pTipChar, pValueUtil->getString("DTE027").c_str(), 5);
				pTipLabel->setString(pTipChar);
			}
		}
	}
}

void DailyTaskExView::onVipChanged()
{
	RoleManage *pRoleManage = RoleManage::Instance();
	_canShowAllATaskSelect = pRoleManage->accountInfo()->vipLev() >= VIPLimitConst::VIP_Daily_A;


	CCNode *pParentLayer = this->getChildByTag(TAG_PARENT_LAYER);
	if(!pParentLayer)
	{
		return;
	}
	CCNode *pSelectButton = pParentLayer->getChildByTag(TAG_BUTTON_SELECT);
	CCNode *pSelectLabel = pParentLayer->getChildByTag(TAG_LABEL_SELECT);
	CCNode *pSelectSprite = pParentLayer->getChildByTag(TAG_SPRITE_SELECT);
	if(pSelectButton)
	{
		pSelectButton->setIsVisible(pSelectButton->getIsVisible() && _canShowAllATaskSelect);
	}
	if(pSelectLabel)
	{
		pSelectLabel->setIsVisible(pSelectLabel->getIsVisible() && _canShowAllATaskSelect);
	}
	if(pSelectSprite)
	{
		pSelectSprite->setIsVisible(pSelectSprite->getIsVisible() && _canShowAllATaskSelect);
	}
}

DailyTaskExView::~DailyTaskExView()
{

}

