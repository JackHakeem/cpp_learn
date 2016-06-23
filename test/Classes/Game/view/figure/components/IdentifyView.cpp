#include "IdentifyView.h"
#include "CCUIBackground.h"
#include "utils/ScaleUtil.h"
#include "../FigureMediator.h"
#include "model/player/RoleManage.h"
#include "model/player/vo/PlayerInfoVo.h"
#include "manager/PopEventName.h"
#include "manager/GlobalManage.h"
#include "socket/command/s2a/SCMD2A3.h"
#include "utils/ValuesUtil.h"
#include "socket/command/s2a/SCMD2A5.h"

IdentifyView::IdentifyView()
{
	_CurScreen = 0;
	_type = ItemType_Gold;
}

IdentifyView::~IdentifyView()
{

}

bool IdentifyView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	_winSize = CCDirector::sharedDirector()->getWinSize();

	this->key = PopEventName::IDENTIFY;
	this->setIsTouchEnabled(true);

	CCSize popContainerSize = CCSizeMake(POSX(448), CCDirector::sharedDirector()->getWinSize().height);

	g_pGlobalManage->setCurFocusGID(LayerManager::windowLayer->getMyFocusGID());
	
	setPopContentSize(popContainerSize);

	initHeadMap();
	loadItems();

}

void IdentifyView::initHeadMap()
{
	headMap.insert(make_pair(11,1));
	headMap.insert(make_pair(21,2));
	headMap.insert(make_pair(12,3));
	headMap.insert(make_pair(22,4));
	headMap.insert(make_pair(14,1));
	headMap.insert(make_pair(24,2));
	headMap.insert(make_pair(18,5));
	headMap.insert(make_pair(28,6));
	headMap.insert(make_pair(26,7));
	headMap.insert(make_pair(36,8));
	headMap.insert(make_pair(42,9));
	headMap.insert(make_pair(52,10));
	headMap.insert(make_pair(74,10));
	headMap.insert(make_pair(84,10));
}

void IdentifyView::loadItems()
{

	CCUIBackground * _peiyangContainer = new CCUIBackground();
	_peiyangContainer->initWithFile("assets/ui/ui2.png", 
		ccp(POSX(2), POSX(28)),
		ccp(0,0),
		CCSizeMake(POSX(444),POSX(504)));
	//_peiyangContainer->setPosition(ccp(POSX(0) , POSX(12)));
	this->addChild(_peiyangContainer , 0);

	updateRoleInfoLayer();
	updateDiffLayer(0);
	updateCurrentIdentifyLayer(0);
	updateNewIdentifyLayer(0);
	updateSelectedOptionsLayer(0);
	updateIdentifyButtons(false);
}

void IdentifyView::updateRoleInfoLayer()
{
	CCLayer * pRoleInfoLayer = (CCLayer *)this->getChildByTag(Tag_RoleInfoLayer);
	if (!pRoleInfoLayer)
	{
		pRoleInfoLayer = new CCLayer();
		pRoleInfoLayer->init();
		pRoleInfoLayer->setTag(Tag_RoleInfoLayer);
		pRoleInfoLayer->setContentSize(CCSizeMake(POSX(404) , POSX(100)));
		pRoleInfoLayer->setPosition(ccp(POSX(0) , POSX(300)));
		this->addChild(pRoleInfoLayer);
		pRoleInfoLayer->release();
		// head icon
		CCSprite * pHeadBg = new CCSprite();
		if (!pHeadBg)		{	return;		}
		bool var = pHeadBg->initWithFile("assets/ui/figure/peiyang/headbg.png");
		if (!var)		{	return;		}
		pRoleInfoLayer->addChild(pHeadBg,0);
		pHeadBg->release();

		if (!g_pFigureScrollView)		{			return;		}
		int nCurScreen = g_pFigureScrollView->currentScreen;
		_CurScreen = nCurScreen;
		int count = nCurScreen;
		//std::map<int ,PlayerInfoVo>* list = RoleManage::Instance()->mercList();
		//std::map<int, PlayerInfoVo>::iterator iter = list->begin();
		std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* list = RoleManage::Instance()->mercListEx();  // LH20121019listorder
		std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>::iterator iter = list->begin();
		while (count-1)
		{
			++iter;
			--count;
		}
		if (iter != list->end())
		{
			// head
			CCSprite * pHead = new CCSprite();
			char path[128] = {0};
			memset(path,0,sizeof(path));
			sprintf(path,"assets/icon/head/%d.png",iter->second.playerBaseInfo.cloth);
			if (pHead->initWithFile(path))
			{
				pHead->setPosition(ccp(pHeadBg->getContentSize().width/2,pHeadBg->getContentSize().height/2));
				pHead->setScale((float)pHeadBg->getContentSize().width/pHead->getContentSize().width);
				pHeadBg->addChild(pHead,0,0);
				pHead->release();
			}

			// name
			//CCLabelTTF * pName = new CCLabelTTF();
			//pName->initWithString("")
		}
	}
	else
	{

	}
}

void IdentifyView::updateDiffLayer(char * data)
{
	CCLayer * pDiffLayer = (CCLayer *)this->getChildByTag(Tag_DiffLayer);
	if (!pDiffLayer)
	{
		pDiffLayer = new CCLayer();
		pDiffLayer->init();
		pDiffLayer->setTag(Tag_DiffLayer);
		this->addChild(pDiffLayer);
		pDiffLayer->release();
		//
		CCUIBackground * pBack = new CCUIBackground();
		pBack->initWithFile("assets/ui/ui2.png", 
			ccp(POSX(0), POSX(0)),
			ccp(0,0),
			CCSizeMake(POSX(140),POSX(54)));

	}
	else
	{

	}
}

void IdentifyView::updateCurrentIdentifyLayer(char * data)
{
	if (!data)	{return;	}
	SCMD2A3 * scmd = (SCMD2A3 * )data;
	int num = scmd->a_gridNum;

	CCLayer * pCurIdentifyLayer = (CCLayer *)this->getChildByTag(Tag_CurrentIdentifyLayer);
	if (!pCurIdentifyLayer)
	{
		pCurIdentifyLayer = new CCLayer();
		pCurIdentifyLayer->init();
		pCurIdentifyLayer->setTag(Tag_CurrentIdentifyLayer);
		this->addChild(pCurIdentifyLayer);
		pCurIdentifyLayer->release();

		//
		std::list<SCMD2A3::SCMD2A3Node1> listNode1 = scmd->b_MercArr;
		std::list<SCMD2A3::SCMD2A3Node1>::iterator iter = listNode1.begin();
		std::list<SCMD2A3::SCMD2A3Node2> listNode2;
		for (iter ; iter != listNode1.end() ; iter++)
		{
			if (iter->a_mercId == getCurMerchId())
			{
				listNode2 = iter->c_statArr;
				break;
			}
		}
		// grids
		std::list<SCMD2A3::SCMD2A3Node2>::iterator it = listNode2.begin();
		int cnt = 0;
		for (it ; it != listNode2.end() ; it++)
		{
			// back
			CCUIBackground * pBack = new CCUIBackground();
			bool var = pBack->initWithFile("assets/ui/ui2.png" , CCPointZero , CCPointZero , CCSizeMake(POSX(120) , POSX(30)) , 255);
			if (var)
			{
				pBack->setPosition(ccp(POSX(0) , POSX((-1) * cnt * 30)));
				pCurIdentifyLayer->addChild(pBack,0);
				pBack->release();
			}

			// Text
			char key[32] = {0};
			sprintf(key , "IDT00%d", it->a_statsType+1);
			char path[32] = {0};
			sprintf(path , ValuesUtil::Instance()->getString(key).c_str() , it->b_statsLv);
			CCLabelTTF * pText = new CCLabelTTF();
			var = pText->initWithString(path ,CCSizeMake(POSX(120) , POSX(30)) , CCTextAlignmentLeft , "Arial" , POSX(24));
			if (var)
			{
				pText->setPosition(ccp(POSX(0) , POSX((-1) * cnt * 30)));
				pCurIdentifyLayer->addChild(pBack,1);
				pText->release();
			}
			++cnt;
		}
	}
	else
	{

	}
}

void IdentifyView::updateNewIdentifyLayer(char * data)
{
	if (!data)	{return;	}
	SCMD2A5 * scmd = (SCMD2A5 * )data;

	CCLayer * pNewIdentifyLayer = (CCLayer *)this->getChildByTag(Tag_NewIdentifyLayer);
	if (!pNewIdentifyLayer)
	{
		pNewIdentifyLayer = new CCLayer();
		pNewIdentifyLayer->init();
		pNewIdentifyLayer->setTag(Tag_NewIdentifyLayer);
		this->addChild(pNewIdentifyLayer);
		pNewIdentifyLayer->release();

		//
		std::list<SCMD2A5::SCMD2A5Node> listNode = scmd->c_statsArr;
		std::list<SCMD2A5::SCMD2A5Node>::iterator iter = listNode.begin();
		// grids
		int cnt = 0;
		for (iter ; iter != listNode.end() ; iter++)
		{
			CCUIBackground * pBack = new CCUIBackground();
			bool var = pBack->initWithFile("assets/ui/ui2.png" , CCPointZero , CCPointZero , CCSizeMake(POSX(120) , POSX(30)) , 255);
			if (var)
			{
				pBack->setPosition(ccp(POSX(0) , POSX((-1) * cnt * 30)));
				pNewIdentifyLayer->addChild(pBack,0); 
				pBack->release();
			}

			// Text
			char key[32] = {0};
			sprintf(key , "IDT00%d", iter->a_statsType+1);
			char path[32] = {0};
			sprintf(path , ValuesUtil::Instance()->getString(key).c_str() , iter->b_statsLv);
			CCLabelTTF * pText = new CCLabelTTF();
			var = pText->initWithString("" ,CCSizeMake(POSX(120) , POSX(30)) , CCTextAlignmentLeft , "Arial" , POSX(24));
			if (var)
			{
				pText->setPosition(ccp(POSX(0) , POSX((-1) * cnt * 30)));
				pNewIdentifyLayer->addChild(pText,1);
				pText->release();
			}
			++cnt;
		}
	}
	else
	{

	}
}

void IdentifyView::updateSelectedOptionsLayer(int type)
{
	CCLayer * pSelectedOptionsLayer = (CCLayer *)this->getChildByTag(Tag_SelectedOptionsLayer);
	if (!pSelectedOptionsLayer)
	{
		pSelectedOptionsLayer = new CCLayer();
		pSelectedOptionsLayer->init();
		pSelectedOptionsLayer->setTag(Tag_SelectedOptionsLayer);
		this->addChild(pSelectedOptionsLayer);
		pSelectedOptionsLayer->release();
	}
	else
	{

	}
}

void IdentifyView::updateIdentifyButtons(bool bVar)
{
	CCLayer * pIdentifyButtonsLayer = (CCLayer *)this->getChildByTag(Tag_IdentifyButtons);
	if (!pIdentifyButtonsLayer)
	{
		pIdentifyButtonsLayer = new CCLayer();
		pIdentifyButtonsLayer->init();
		pIdentifyButtonsLayer->setTag(Tag_IdentifyButtons);
		this->addChild(pIdentifyButtonsLayer);
		pIdentifyButtonsLayer->release();

		// buttons
		CCMenuItemImage * pIdentifyImg = CCMenuItemImage::itemFromNormalImage(
			"assets/ui/button3.png",
			"assets/ui/button3_0.png",
			"assets/ui/button3_1.png",
			this,
			menu_selector(IdentifyView::onIdentifyHandler));
		pIdentifyImg->setTag(0);
		pIdentifyImg->setIsVisible(!bVar);

		CCMenuItemImage * pSaveImg = CCMenuItemImage::itemFromNormalImage(
			"assets/ui/button3.png",
			"assets/ui/button3_0.png",
			"assets/ui/button3_1.png",
			this,
			menu_selector(IdentifyView::onSaveHandler));
		pSaveImg->setTag(1);
		pSaveImg->setIsVisible(bVar);

		CCMenuItemImage * pCancelImg = CCMenuItemImage::itemFromNormalImage(
			"assets/ui/button3.png",
			"assets/ui/button3_0.png",
			"assets/ui/button3_1.png",
			this,
			menu_selector(IdentifyView::onCancelHandler));
		pCancelImg->setTag(2);
		pCancelImg->setIsVisible(bVar);

		CCMenu * pMenuIdentify = CCMenu::menuWithItems(pIdentifyImg , pSaveImg , pCancelImg , 0);
		pMenuIdentify->setTag(0);
		pIdentifyButtonsLayer->addChild(pMenuIdentify,0);
	}
	else
	{
		if (pIdentifyButtonsLayer->getChildByTag(0))
		{
			if (pIdentifyButtonsLayer->getChildByTag(0)->getChildByTag(0))
			{
				pIdentifyButtonsLayer->getChildByTag(0)->getChildByTag(0)->setIsVisible(!bVar);
			}
			if (pIdentifyButtonsLayer->getChildByTag(0)->getChildByTag(1))
			{
				pIdentifyButtonsLayer->getChildByTag(0)->getChildByTag(1)->setIsVisible(bVar);
			}
			if (pIdentifyButtonsLayer->getChildByTag(0)->getChildByTag(2))
			{
				pIdentifyButtonsLayer->getChildByTag(0)->getChildByTag(2)->setIsVisible(bVar);
			}
		}		
	}
}

void IdentifyView::registerWithTouchDispatcher()
{

}

void IdentifyView::onIdentifyHandler(CCObject * pSender)
{
	FigureMediator * pFigureMediator = (FigureMediator *)g_pFacade->retrieveMediator(AppFacade_FIGHT_PROXY_CHANGE);
	if (pFigureMediator)
	{
		int account = getCurMerchId();
		pFigureMediator->sendIdentifyRequest(account , _type);
	}
}

void IdentifyView::onSaveHandler(CCObject * pSender)
{
	FigureMediator * pFigureMediator = (FigureMediator *)g_pFacade->retrieveMediator(AppFacade_FIGHT_PROXY_CHANGE);
	if (pFigureMediator)
	{
		pFigureMediator->sendSaveIdentifyRequest();
	}
}

void IdentifyView::onCancelHandler(CCObject * pSender)
{
	
}

void IdentifyView::onBuyGridHandler(CCObject * pSender)
{
	FigureMediator * pFigureMediator = (FigureMediator *)g_pFacade->retrieveMediator(AppFacade_FIGHT_PROXY_CHANGE);
	if (pFigureMediator)
	{
		int account = getCurMerchId();
		pFigureMediator->sendBuyGridRequest();
	}
}

int IdentifyView::getCurMerchId()
{
	if (!g_pFigureScrollView)		{			return 0;		}
	int nCurScreen = g_pFigureScrollView->currentScreen;
	_CurScreen = nCurScreen;
	int count = nCurScreen;
	//std::map<int ,PlayerInfoVo>* list = RoleManage::Instance()->mercList();
	//std::map<int, PlayerInfoVo>::iterator iter = list->begin();
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* list = RoleManage::Instance()->mercListEx();  // LH20121019listorder
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>::iterator iter = list->begin();
	while (count-1)
	{
		++iter;
		--count;
	}

	if (iter != list->end())
	{
		return iter->first.id;
	}
	return 0;	
}

bool IdentifyView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return false;
}