
#include "ArenaUI.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"
#include "manager/GlobalManage.h"
#include "manager/LayerManager.h"
#include "utils/ValuesUtil.h"
#include "Message.h"
#include "model/player/vo/AccountInfoVo.h"
#include "model/player/RoleManage.h"
#include "manager/TimerManage.h"
#include "socket/command/s36/SCMD361.h"
#include "socket/command/s28/SCMD285.h"
#include "InfoPanel.h"
#include "manager/CDManage.h"
#include "RankList.h"
#include "StarRecord.h"
#include "ReportList.h"
#include "RankingInfo.h"
#include "model/arena/ArenaManage.h"
#include "GiftPanel.h"
#include "manager/TouchLayerEnum.h"
#include "model/arena/ArenaConst.h"
#include "CardList.h"
#include "socket/command/s36/SCMD36E.h"
#include "manager/GlobalManage.h"
#include "manager/LangManager.h"
#include "utils/ScaleUtil.h"
#include "events/CDEvent.h"
#include "model/newhand/NewhandManager.h"
#include "manager/LevLimitConst.h"
#include "manager/ButtonIDConst.h"
#include "model/newhand/vo/NewhandConst.h"
#include "../ArenaMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "model/arena/ArenaProxy.h"
#include "manager/ViewManager.h"

ArenaUI::ArenaUI()
{
	_awardNum = 0;
	_meRank = 1000;
	_streak = 0;   
	_cdtime = 0;   
	_cdlock = 0;   
	_quota= 0;   
	_buyed= 0;   
	_rankList = 0;
	_infoPanel = 0;
	_starRecord = 0;
	_reportList = 0;
	_rankingInfo = 0;
	g_pGlobalManage->canOperate = true;
	_btnClose = 0;

	_cdManage = 0;
}

ArenaUI::~ArenaUI()
{
	ArenaMediator* pMeditor = (ArenaMediator*)g_pFacade->retrieveMediator(AppFacade_ARENA_MEDIATOR);
	pMeditor->_arenaUI = 0;
	ArenaProxy* proxy = (ArenaProxy*)g_pFacade->retrieveProxy(AppFacade_ARENA_PROXY);
	proxy->_arenaUI = 0;

	ViewManager::getInstance()->arenaUI = 0;

	CCObject* pGP = LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_rankReward);
	if (pGP)
	{
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_rankReward, true);
	}

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(
		"assets/ui/arena/res_arena_ic.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(
		"assets/icon/arena/res_arena.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(
		"assets/icon/arena/res_arena_close.plist");
	
	//CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/arena/res_arena_ic.pvr.ccz");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/icon/arena/res_arena.pvr.ccz");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/icon/arena/res_arena_close.pvr.ccz");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/arena/res_arena_bg.pvr.ccz");
}

void ArenaUI::handleCDEvent(CCNode* n, void* data)
{
	CDEvent e = *(CDEvent*)data;

	if(e.cdType == CDManage::ARENA_CD)
	{
		_cdtime = e.time/1000; 
		_cdlock = e.lock;   
	}
}

bool ArenaUI::initView()
{
	if (!CCLayer::init())
	{
		return false;
	}

	this->setIsTouchEnabled (true);
	_dispatcher = GameDispatcher::getInstance();
	CCSize winSizePixels = CCDirector::sharedDirector()->getWinSizeInPixels();
	this->key = 0;//PopEventName::ARENA;

	this->setIsNeedClose(false); // Kenfly 20121129
				
	_cdManage = CDManage::Instance();
	_cdManage->addEventListener(CDManage::CDCHANGED, this, callfuncND_selector(ArenaUI::handleCDEvent));
	/*
	_cdManage->addEventListener(CDManage.CDCHANGED, function(e:CDEvent):void{
//				new CDEvent(CDCHANGED, type, lock, time * 1000)
				if(e.cdType == CDManage.ARENA_CD){
					_cdtime = e.time/1000; 
					_cdlock = e.lock as int;   // lock==1Œ™À¯∂�?
				}
			});
			*/

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/arena/res_arena_ic.plist");

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/arena/res_arena.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/arena/res_arena_close.plist");

	//bg
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/arena/res_arena_bg.plist");
	SpriteNode* bg = new SpriteNode();
	bg->initWithSpriteFrameName("arena/bg.png");
	bg->setIsRelativeAnchorPoint(true);
	bg->setAnchorPoint(ccp(0,0));
	this->addChild(bg, RENDERZ_bg, RENDERTAG_bg);
	bg->release();
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/arena/res_arena_bg.plist");
	//
	//viewSize = bg->getTexture()->getContentSize();
	viewSize = CCSizeMake(POSX(960), POSX(640));
	this->setContentSize(viewSize);
	this->setPopContentSize(viewSize);

	this->setPosition(ccp(winSizePixels.width / 2.0f-viewSize.width/2, winSizePixels.height / 2.0f-viewSize.height/2));
	
	//
	_infoPanel = new InfoPanel();
	_infoPanel->initWithParam(this);
	this->addChild(_infoPanel, RENDERZ_InfoPanel, RENDERTAG_InfoPanel);
	_infoPanel->release();
	//
	_rankList = new RankList();
	_rankList->initWithParam(this);
	this->addChild(_rankList, RENDERZ_RankList, RENDERTAG_RankList);
	_rankList->release();
	//
	_starRecord = new StarRecord();
	_starRecord->initWithParam(this);
	this->addChild(_starRecord, RENDERZ_StarRecord, RENDERTAG_StarRecord);
	_starRecord->release();
	//
	_reportList = new ReportList();
	_reportList->initWithParam(this);
	this->addChild(_reportList, RENDERZ_ReportList, RENDERTAG_ReportList);
	_reportList->release();
	//
	_rankingInfo = new RankingInfo();
	_rankingInfo->initWithParam(this);
	this->addChild(_rankingInfo, RENDERZ_RankingInfo, RENDERTAG_RankingInfo);
	_rankingInfo->release();
	//
	_cardList = new CardList();
	_cardList->initWithParam(this);
	this->addChild(_cardList, RENDERZ_cardList, RENDERTAG_cardList);
	_cardList->release();
	//
	CCObject* pGP = LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_rankReward);
	if (pGP)
	{
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_rankReward, true);
	}	
	_giftPanel = new GiftPanel();
	_giftPanel->initWithParam(this);
	_giftPanel->setIsVisible(false);
	LayerManager::tipsLayer->addChild(_giftPanel, TipsLayer::TipsLayerZ_rankReward, TipsLayer::TipsLayerTAG_rankReward);
	_giftPanel->release();
	//closebtn
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_normal.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_pressed.png");
		_btnClose = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this, 
			menu_selector(ArenaUI::clickClose) );
		_btnClose->setPosition(ccp(POSX(960) - _btnClose->getContentSize().width / 2, POSX(640) - _btnClose->getContentSize().height / 2));

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btnClose, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::TipsLayer-1);
		this->addChild(buttonMenu, RENDERZ_buttonClose, RENDERTAG_buttonClose);		
	}
	
	return true;
}

void ArenaUI::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
}

bool ArenaUI::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
// 	if (g_pGlobalManage->getCurFocusGID() != LayerManager::windowLayer->getMyFocusGID())//µ±«∞–Ë“™windowLayerΩπµ�?
// 	{
// 		return false;
// 	}
	return true;
	//return _currentView->ccTouchBegan(touch, event);
}

void ArenaUI::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	//_currentView->ccTouchMoved(touch, event);
}

void ArenaUI::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	//_currentView->ccTouchEnded(touch, event);
}
/*
void ArenaUI::initBaseInfo()
{
	intAccountMoneyInfo();
}

void ArenaUI::intAccountMoneyInfo()
{
	AccountInfoVo* accountInfoVo = RoleManage::Instance()->accountInfo();
	if(!accountInfoVo)
		return;
	_gold = accountInfoVo->_gold;
	_silver = accountInfoVo->_silver;
	_practice = accountInfoVo->_practice;
	_popularity = accountInfoVo->_popularity;

	_title = ValuesUtil::Instance()->getString("ARENA08");
	if(accountInfoVo->_crystalLev > 40 && accountInfoVo->_crystalLev <= 60)
		_title = ValuesUtil::Instance()->getString("ARENA09");
	else if(accountInfoVo->_crystalLev > 60 && accountInfoVo->_crystalLev <= 80)
		_title = ValuesUtil::Instance()->getString("ARENA10");
	else if(accountInfoVo->_crystalLev > 80 && accountInfoVo->_crystalLev <= 100)
		_title = ValuesUtil::Instance()->getString("ARENA11");
	else if(accountInfoVo->_crystalLev > 100 && accountInfoVo->_crystalLev <= 120)
		_title = ValuesUtil::Instance()->getString("ARENA12");

// 	var repvo:ReputationVo = ReputationManage.getInstance().getCurrentData(accountInfo.popularity);
// 	__skin["_txtTitle"].htmlText = repvo?repvo.repName:"<font color='#ffffff'>Œ¥ªÒµ√≥∆∫�?/font>";
// 	__skin["_btnReputation"].visible = repvo?true:fals
}
*/
void ArenaUI::initTxtCurrenGrade()
{
	/*
	char _currentGradeText[100];
	sprintf(_currentGradeText, ValuesUtil::Instance()->getString("ARENA13").c_str(), _title.c_str());
	cocos2d::CCLabelTTF* _text = CCLabelTTF::labelWithString(_currentGradeText, CCSizeMake(400,20), CCTextAlignmentCenter,
		g_sSimHeiFont,(float)g_RoleFontSize);
	_text->setColor(ccc3(255,240,0));
	_text->setPosition(ccp(500, viewSize.height-50));
	if (arenaContainer)
	{
		arenaContainer->addChild(_text, RENDERZ_txtAwardNum);	
	}
	*/
}

void ArenaUI::addCloseButton()
{
	CCMenuItemSprite *_btnClose = CCMenuItemImage::itemFromNormalSprite(
		CCSprite::spriteWithSpriteFrameName("close1.png"), 
		CCSprite::spriteWithSpriteFrameName("close2.png"), 
		this, 
		menu_selector(ArenaUI::clickCloseHandler));

	CCMenu *buttonMenu = CCMenu::menuWithItems(_btnClose, NULL);
	_btnClose->setPosition(CCPointZero);
	buttonMenu->setPosition(ccp(viewSize.width - POSX(15), viewSize.height - POSX(55)));
	this->addChild(buttonMenu, RENDERZ_buttonClose);
}

void ArenaUI::addPVPReportContainer()
{

}

void ArenaUI::awardClickHandler(CCObject* pSender)
{
	dispatchEvent(GET_AWARD, NULL);
}

void ArenaUI::updateAwardLabel(int awardNum)
{
	_awardNum = awardNum > 0 ? awardNum : 0;

	sprintf(_szUpgradeText, ValuesUtil::Instance()->getString("ARENA07").c_str(), awardNum);
	_txtAwardNum->setString(_szUpgradeText);
	
	if(_awardNum <= 0)
	{
		_btnOpenAward->setIsEnabled(false);
	}
	else
	{
		_btnOpenAward->setIsEnabled(true);
	}
}

bool ArenaUI::initTxtAwardNum()
{
	sprintf(_szUpgradeText, ValuesUtil::Instance()->getString("ARENA07").c_str(), 0);
	_txtAwardNum = CCLabelTTF::labelWithString(_szUpgradeText, CCSizeMake(POSX(400), POSX(20)), CCTextAlignmentCenter,
		g_sSimHeiFont,POSX(g_RoleFontSize));
	_txtAwardNum->setColor(ccc3(255,240,0));
	_txtAwardNum->setPosition(ccp(POSX(500), viewSize.height - POSX(100)));
	/*
	if (arenaContainer)
	{
		arenaContainer->addChild(_txtAwardNum,RENDERZ_txtAwardNum);	
	}
	*/
	return true;
}

void ArenaUI::showReportList(std::vector<ArenaReportVo*> report)
{

	std::vector<ArenaReportVo*>::iterator it;

	for (int i = 0; i < report.size(); i++)
	{
		creatPVPreportObject(report[i], i);
	}

}

void ArenaUI::creatPVPreportObject(ArenaReportVo* arenaReportVo, int sitNum)
{
	std::string str = TimerManage::formatServerTimeToDate(arenaReportVo->fightTime);

	char tmpName[100];
	if(arenaReportVo->isChallenge == 1)
	{
		sprintf(tmpName, ValuesUtil::Instance()->getString("ARENA14").c_str(), arenaReportVo->enemyName.c_str() );
	} 
	else
	{
		sprintf(tmpName, ValuesUtil::Instance()->getString("ARENA15").c_str(), arenaReportVo->enemyName.c_str());
	}

	str.append(tmpName);
	char tmpSuc[20];

	if(arenaReportVo->isSuccess == 1)
	{
		sprintf(tmpSuc, "%s", ValuesUtil::Instance()->getString("ARENA16").c_str());
	}
	else
	{
		sprintf(tmpSuc, "%s",ValuesUtil::Instance()->getString("ARENA17").c_str());
	}

	str.append(tmpSuc);
	char tmpRank[20];

	if(arenaReportVo->rank == 0)
	{
		sprintf(tmpRank, "%s",ValuesUtil::Instance()->getString("ARENA18").c_str());
	}
	else if(arenaReportVo->rank > 0)
	{
		sprintf(tmpRank, "%s",ValuesUtil::Instance()->getString("ARENA19").c_str());
	}
	else
	{
		sprintf(tmpRank, "%s",ValuesUtil::Instance()->getString("ARENA20").c_str());
	}

	str.append(tmpRank);
	//to be continued...

	
}

// ∏¸–¬æ∫ºº≥°–≈œ¢ 
void ArenaUI::updateInfo(SCMD361* param)
{
	if (!param)
		return;
	_rankingInfo = (RankingInfo*)this->getChildByTag(RENDERTAG_RankingInfo);
	if (!_rankingInfo)
	{
		return;
	}

	_cdManage = CDManage::Instance();

	_meRank = param->b_rank;  //   º¥ ±≈≈√�?
	_streak = param->d_winstreak;  //  §¿˚¥Œ ˝
	_quota = param->f_quota ; // ÃÙ’Ω¥Œ �?
	_buyed = param->h_buyed;   // “—π∫¬Ú¥Œ �?
	
	_cdtime = param->e_cd;   // CD
	_cdRefresh = param->l_refreshcd; //hwj
	Number st = _cdManage->getServerTime();
	long int pst = _cdtime - 30*60;//_cdtime*1000 - 30*60*1000;
	if (pst < 0) pst = 0;
	Number st2 = pst*1000;
	_cdlock= st < st2? 1:0;
			
	
	_rankingInfo->updateRanking(param->b_rank);
	
	if(param->a_state == 0)
	{
		_rankList->update(param);
				
		_cardList->setIsVisible(false);
		_rankList->setIsVisible(true);
	}
	else
	{
		//_rankList.visible = false;
		//_cardList.visible = true;
		_cardList->setIsVisible(true);
		_rankList->setIsVisible(false);
		//dispatchEvent();new ParamEvent(ArenaConst.TAKE_AWARD)
	}
	_infoPanel->update(param);
	_starRecord->update(param->j_resultArr);
	_reportList->update(param->k_reportArr);
}



// ∏˘æ›≈≈√˚ªÒ»°∂‘”¶Ω±¿�?
std::string ArenaUI::getRewardByRank(int rank)
{
	std::string rewardStr = "";
	CfgRankVo* vo = ArenaManage::Instance()->getCfgRank(rank);
	if (vo)
	{
		char str[100];
		sprintf(str, ValuesUtil::Instance()->getString("JJC026").c_str(), vo->silver, vo->pop);
		rewardStr = str;
	}
	else
	{
		char str[100];
		sprintf(str, ValuesUtil::Instance()->getString("JJC026").c_str(), 0, 0);
		rewardStr = str;		
	}

	return rewardStr;
}

void ArenaUI::setGiftOpt(bool canTake)
{
	_giftPanel->setGiftOpt(canTake);
}

// ∏¸–¬≈≈√˚“‘º∞œ‡πÿΩ±¿¯
void ArenaUI::updatePackage(SCMD285* param)
{
	GiftPanel* pGP = (GiftPanel*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_rankReward);
	if (pGP)
		pGP->update(param, this);
			
	_rankingInfo->updatePackage(param);
}

// ¥Úø™¿Ò∞¸√Ê∞Â
void ArenaUI::openGiftPanel()
{
	GiftPanel* pGP = (GiftPanel*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_rankReward);
	if (pGP)
	{
		pGP->setIsVisible(true);
	}	
}

void ArenaUI::clickClose(CCObject* pSender)
{
	//clickCloseHandler(0);
	PopContainer::close();

	// new hand
	if (NewhandManager::Instance()->getNewHandStateByType(LevLimitConst::Limit_Arena) == NewhandManager::Flag_New)
	{
		//NewhandManager::Instance()->touchNextScript("addBtn" , ButtonIDConst::ButtonID_Arena);
	}
	else if (NewhandManager::Instance()->getNewHandStateByType(LevLimitConst::Limit_Arena) == NewhandManager::Flag_Done)
	{
		NewhandManager::Instance()->setNewHandStateByType(LevLimitConst::Limit_Arena , NewhandManager::Flag_Close);
		NewhandManager::Instance()->touchNextEvent(NewhandConst::EVENT_ARENA_OVER);
		NewhandManager::Instance()->doTaskFollow();
	}
}

void ArenaUI::pkArena(int rank)
{
	if(!g_pGlobalManage->canOperate)
	{
		LangManager::msgShow("JJC043");
		return;
	}
	
	g_pGlobalManage->canOperate = false;

	//�ӳ�5��
	CCMoveBy *pwaitAction = cocos2d::CCMoveBy::actionWithDuration(5.0f, ccp(0, 0));
	CCCallFunc *pWaitActionDo = CCCallFunc::actionWithTarget(LayerManager::windowLayer, callfunc_selector(WindowLayer::arenaWaitTime));
	CCAction *pAction = cocos2d::CCSequence::actions(pwaitAction, pWaitActionDo, 0);
	LayerManager::windowLayer->runAction(pAction);

	//
	dispatchEvent(ArenaConst::PK_ARENA, &rank);
}



void ArenaUI::updateCard(SCMD36E* param)
{
	_cardList->update(param);
}

//Begin chenijan 20121019
void ArenaUI::reportArena(int battleId1, int battleId2)
{
	if(g_pGlobalManage && (g_pGlobalManage->isReport || g_pGlobalManage->getisInFight()))
	{
		LangManager::msgShow("RPO040");
		//�ӳ�5�� �ָ�
		CCDelayTime* pWaitAction = CCDelayTime::actionWithDuration(5.0);
		CCCallFunc *pWaitActionDo = CCCallFunc::actionWithTarget(this, callfunc_selector(ArenaUI::reportWaitTime));
		CCAction *pAction = cocos2d::CCSequence::actions(pWaitAction, pWaitActionDo, 0);
		this->runAction(pAction);
		return;
	}
	if (g_pGlobalManage)
		g_pGlobalManage->isReport = true;


	struct sdata
	{
		uint32 a_battleId1;
		uint32 b_battleId2;
	}battleId;
	battleId.a_battleId1 = battleId1;
	battleId.b_battleId2 = battleId2;

	dispatchEvent(ArenaConst::REPORT_ARENA, (char*)&battleId);
}

void ArenaUI::reportWaitTime()
{
	if (g_pGlobalManage)
		g_pGlobalManage->isReport = false;
}
//End chenjian 20121019

CCNode * ArenaUI::getNewHandItem(int id)
{
	switch (id)
	{
	case 100:
		{
			int len = _rankList->_itemDic.size();
			if (_rankList && (len > 0))
			{
				return (CCNode *)_rankList->_itemDic[(len > 5 ? 4 : (len-1) )];
			}
		}
		break;
	case 101:
		{

		}
		break;
	case 103:
		{
			return _btnClose;
		}
		break;
	default:
		break;
	}
	return 0;	
}