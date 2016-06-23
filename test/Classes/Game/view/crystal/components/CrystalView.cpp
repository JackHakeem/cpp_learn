#include "CrystalView.h"
#include "manager/PopEventName.h"
#include "CCDirector.h"
#include "CCObject.h"
#include "CCPointExtension.h"
#include "CrystalUIPartialScrollView.h"
#include "BaseType.h"
#include "model/skill/SkillManager.h"
#include "manager/LayerManager.h"
#include "socket/network/GameServerSocket.h"
#include "socket/command/c18/CCMD184.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "CCLayer.h"
#include "Message.h"
#include "model/crystal/CrystalManager.h"
#include "utils/ValuesUtil.h"
#include "manager/GlobalManage.h"
#include "PopUIBg.h"
#include "utils/ScaleUtil.h"
#include "CCUIBackground.h"
#include "manager/CDManage.h"
#include "CrystalTimer.h"
#include "Confirm.h"
#include "model/player/RoleManage.h"
#include "MessageInfoBox.h"
#include "manager/TouchLayerEnum.h"
#include "model/newhand/vo/NewhandConst.h"
#include "CustomCD.h"
#include "manager/sound/SoundManager.h"

CrystalView::CrystalView()

{
	curSelectCrystalID = 35; // default click crystal
	_upgrade		= 0;
	_unName		= 0;
	_name		= 0;
	_level		= 0;
	_detail		= 0;
	_time		= 0;
	_BgPanel		= 0;
	scrollView	= 0;
	_container	= 0;
	_scrollLayer	= 0;
	_crystalCDList = 0;
	_adapter		= 0;
	_skillManager = 0;
	_crystalProxy = 0;
	_pCrysMediator = 0;
	_CDlistCount = 0;
	_upTime = 0;
	memset(_chCDType,0,sizeof(_chCDType));
	memset(_chCDTime,0,sizeof(_chCDTime));
	//memset(_pCryTimerList,0,sizeof(_pCryTimerList));
	if (!_skillManager)
	{
		_skillManager = SkillManager::Instance();
	}
	if (!_crystalProxy)
	{
		_crystalProxy = (CrystalProxy *)g_pFacade->retrieveProxy(AppFacade_CRYSTAL_PROXY_CHANGE);
	}
	if (!_pCrysMediator)
	{
		_pCrysMediator = (CrystalMediator *)g_pFacade->retrieveMediator(AppFacade_CRYSTAL_PROXY_CHANGE);
	}	

	initCrystalPos();
	initIDIndexMap();
}

void CrystalView::initIDIndexMap()
{
	IDIndexMap.insert(make_pair(35,1));
	IDIndexMap.insert(make_pair(32,9));
	IDIndexMap.insert(make_pair(36,11));
	IDIndexMap.insert(make_pair(33,15));
	IDIndexMap.insert(make_pair(34,17));
	IDIndexMap.insert(make_pair(37,36));
	IDIndexMap.insert(make_pair(44,40));
	IDIndexMap.insert(make_pair(41,42));
	IDIndexMap.insert(make_pair(43,45));
	IDIndexMap.insert(make_pair(39,50));
	IDIndexMap.insert(make_pair(38,55));
	IDIndexMap.insert(make_pair(45,101));
	IDIndexMap.insert(make_pair(42,102));
	IDIndexMap.insert(make_pair(40,105));
}

CrystalView::~CrystalView()
{
	//_itemsCrystal.clear();
}

// init pos
void CrystalView::initCrystalPos()
{
	for(int i = 0;i<CRYSTAL_ROW_NUM;i++)
	{
		for (int j=0;j<CRYSTAL_COLUMN_NUM;j++)
		{
			ccpCrystalPos[j+i*CRYSTAL_COLUMN_NUM] = ccp(POSX((j*2+1)*SCROLL_VIEW_WIDTH/(CRYSTAL_COLUMN_NUM*2)),
				POSX(500-(i*2+1)*SCROLL_VIEW_HEIGHT/(CRYSTAL_ROW_NUM*2)));
		}
	}
}

// init view pics
bool CrystalView::initView() 
{
 	if(!CCLayer::init())
 	{
 		return false;
 	}
	//init key
	key = PopEventName::CRYSTAL;
	
	this->setIsTouchEnabled(true);

	//win pixs
	//CCSize winSizePixels = CCDirector::sharedDirector()->getWinSizeInPixels();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize(); // add by LH 0411

	setPopContentSize(winSize);
	setContentSize(winSize);

	//this->setPosition(ccp((POSX(winSize.width-w_bg1)/2),POSX((winSize.height-h_bg1)/2)));

	//bg layer
	if(!_container)
	{
		_container = new LayerNode();
		_container->init();// add by LH 6.30
		/*_container->setIsRelativeAnchorPoint(true);
		_container->setAnchorPoint(ccp(POSX(0),POSX(0)));*/
		_container->setPosition(POS(ccp(0, 12), ScaleUtil::CENTER_TOP));
		_container->setAnchorPoint(CCPointZero);

		/*CCLayerColor *pTestLayer = CCLayerColor::layerWithColorWidthHeight(ccc4(255, 0, 0, 128),
			winSize.width,
			winSize.height);
		pTestLayer->setAnchorPoint(CCPointZero);
		pTestLayer->setPosition(CCPointZero);
		_container->addChild(pTestLayer);*/
	}

	// bg panel
	/*_BgPanel = new LayerNode();
	_BgPanel->setContentSize(CCSizeMake(w_bg1,h_bg1));
	_BgPanel->setIsRelativeAnchorPoint(true);
	_BgPanel->setAnchorPoint(ccp(POSX(0),POSX(0)));
	_container->addChild(_BgPanel,Z_BG_PANEL);
	_viewSize = _BgPanel->getContentSize();*/

	// title
	


	// Close Button
	/*
	CCMenuItemImage *_btnClose = CCMenuItemImage::itemFromNormalImage(
		"assets/ui/crystal/btn_close_0.png", 
		"assets/ui/crystal/btn_close_1.png", 
		this, 
		menu_selector(CrystalView::clickCloseHandler));
	CCMenu * buttonMenuClose = CCMenu::menuWithItems(_btnClose, 0);
	buttonMenuClose->setPosition( ccp(POSX(0),POSX(0)) );
	_btnClose->setPosition(ccp(_viewSize.width-8, _viewSize.height - 50));
	_container->addChild(buttonMenuClose,Z_BG_ITEM);
	*/

	// Upgrade Button
	

	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			CCMenuItemSprite *_btnUpgrade = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this, 
				menu_selector(CrystalView::clickUpgradeHandler));
			_btnUpgrade->setPosition(ccp(POSX(796), POSX(40)));
			_btnUpgrade->setAnchorPoint(CCPointZero);
			_btnUpgrade->setTag(TAG_UPGRADE_BTN_IMG);
			CCMenu * buttonMenuUpgrade = CCMenu::menuWithItems(_btnUpgrade, 0);
			buttonMenuUpgrade->setPosition( CCPointZero );
			buttonMenuUpgrade->setTouchLayer(TLE::WindowLayer_CrystalView);
			buttonMenuUpgrade->setTag(TAG_UPGRADE_BTN);
			_container->addChild(buttonMenuUpgrade,Z_BG_ITEM);

			NewhandConst::Instance()->registerItem(NewhandConst::ITEM_CRYSTAL_UP, buttonMenuUpgrade);

			// Upgrade Button Text
			std::string _szUpgradeText = CrystalManager::Instance()->_cv->getString("CUB");
			_upgrade = CCLabelTTF::labelWithString(_szUpgradeText.c_str(),
				CCSizeMake(POSX(60), POSX(24)),
				CCTextAlignmentCenter,
				g_sSimHeiFont,
				POSX(g_CrystalFontSize+2));
			_upgrade->setColor(ccc3(255,240,0));
			CCSize ImgSize = _btnUpgrade->getContentSize();
			_upgrade->setPosition(ccp(POSX(796)+ImgSize.width/2, POSX(40)+ImgSize.height/2));
			_container->addChild(_upgrade,Z_TEXT);
		}
	}


	//

	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			CCMenuItemSprite *_btnBuyCDList = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this, 
				menu_selector(CrystalView::buyCrystalListHandle));
			_btnBuyCDList->setPosition(ccp(POSX(658), POSX(40)));
			_btnBuyCDList->setAnchorPoint(CCPointZero);
			CCMenu * buttonMenuBuyCDList = CCMenu::menuWithItems(_btnBuyCDList, 0);
			buttonMenuBuyCDList->setPosition( CCPointZero );
			buttonMenuBuyCDList->setTouchLayer(TLE::WindowLayer_CrystalView);
			_container->addChild(buttonMenuBuyCDList,Z_BG_ITEM,TAG_BUTTON_BUY_CD);
			// Buy CD list Button Text
			std::string _szBuyCDQueueText = ValuesUtil::Instance()->getString("CSL21");
			CCLabelTTF * pBuyCDListTxt = CCLabelTTF::labelWithString(_szBuyCDQueueText.c_str(), CCSizeMake(POSX(120), POSX(24)),CCTextAlignmentCenter,
				g_sSimHeiFont,POSX(g_CrystalFontSize+2));
			pBuyCDListTxt->setColor(ccc3(255,240,0));
			CCSize ImgSize = _btnBuyCDList->getContentSize();
			pBuyCDListTxt->setPosition(ccp(POSX(658)+ImgSize.width/2, POSX(40)+ImgSize.height/2));
			_container->addChild(pBuyCDListTxt,Z_TEXT,TAG_BUTTON_BUY_CDTXT);


			if (RoleManage::Instance()->_accountInfo._numCrystalCd > 5)
			{
				buttonMenuBuyCDList->setIsVisible(false);
				buttonMenuBuyCDList->setIsTouchEnabled(false);
				pBuyCDListTxt->setIsVisible(false);
				//_btnUpgrade->setPosition(ccp(POSX(720),POSX(40)));
				//_upgrade->setPosition(ccp(POSX(720)+ImgSize.width/2, POSX(40)+ImgSize.height/2));

				//_btnUpgrade->setPosition(ccp(POSX(710), POSX(/*_viewSize.height - 510*/130)));
				//_upgrade->setPosition(ccp(POSX(710),POSX(/*_viewSize.height - 510*/130)));

				CCSprite *pBuyAllListNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
				CCSprite *pBuyAllListPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
				CCSprite *pBuyAllListSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
				if(pBuyAllListNormalSprite && pBuyAllListPressedSprite && pBuyAllListSelectdSprite)
				{
					CCMenuItemSprite * pBuyAllListImg = CCMenuItemSprite::itemFromNormalSprite(
						pBuyAllListNormalSprite, 
						pBuyAllListPressedSprite, 
						pBuyAllListSelectdSprite, 
						this, 
						menu_selector(CrystalView::onClearAllCDConfirm));
					pBuyAllListImg->setPosition(ccp(POSX(658), POSX(40)));
					pBuyAllListImg->setAnchorPoint(CCPointZero);
					CCMenu * pBuyAllListMenu = CCMenu::menuWithItems(pBuyAllListImg, 0);
					pBuyAllListMenu->setPosition( CCPointZero );
					pBuyAllListMenu->setTouchLayer(TLE::WindowLayer_CrystalView);
					_container->addChild(pBuyAllListMenu,Z_BG_ITEM,TAG_BUTTON_BUY_CD + 1);

					CCLabelTTF * pBuyCDListTxt = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("CSL30").c_str(), CCSizeMake(POSX(120), POSX(24)),CCTextAlignmentCenter,
						g_sSimHeiFont,POSX(g_CrystalFontSize+2));
					pBuyCDListTxt->setColor(ccc3(255,240,0));
					ImgSize = _btnBuyCDList->getContentSize();
					pBuyCDListTxt->setPosition(ccp(POSX(658)+ImgSize.width/2, POSX(40)+ImgSize.height/2));
					_container->addChild(pBuyCDListTxt,Z_TEXT,TAG_BUTTON_BUY_CDTXT+1);
				}
				
			}
		}
	}

	
	// logo
	SpriteNode * pSpriteLogo = new SpriteNode;
	pSpriteLogo->initWithSpriteFrameName("crystal/logo.png");
	CCPoint pos = ccp(this->getContentSize().width/2,this->getContentSize().height-POSX(80));
	pSpriteLogo->setPosition(pos);
	this->addChild(pSpriteLogo,2);
	pSpriteLogo->release();

	// CD pannel
	CCUIBackground * pCDPanelBack = new CCUIBackground();
	if (pCDPanelBack)
	{
		pCDPanelBack->initWithSpriteFrame("ui2.png",CCPointZero,CCPointZero,CCSizeMake(POSX(260),POSX(250)));
		pCDPanelBack->setPosition(ccp(POSX(650),POSX(100)));
		if ( _container)
		{
			_container->addChild(pCDPanelBack,Z_BG_ITEM,TAG_CD_BG);

		}
	}
	pCDPanelBack->release();
	
	

	// CD List
	
	if (!_crystalCDList)
	{
		//_crystalCDList = CCUIListView::listViewWithCCRect(CCRectMake(POSX(640),POSX(124),POSX(274),POSX(120)),false);
		_crystalCDList = CCUIListView::listViewWithCCRect(CCRectMake(POSX(0),POSX(0),POSX(0),POSX(0)),false);
		_crystalCDList->setWorldSpaceLeftBottomPoint(ccpAdd(_crystalCDList->getPosition(), _container->getPosition()));
		_crystalCDList->setAnchorPoint(CCPointZero);
		_crystalCDList->setIsRelativeAnchorPoint(true);
		_crystalCDList->setOnItemActionListener(this);
		_crystalCDList->setSpacingVertical(POSX(20));
		_crystalCDList->setAdapter(this);
	}
	if ( _container && _crystalCDList )
	{
		_container->addChild(_crystalCDList,Z_BG_ITEM);
		_crystalCDList->release(); // Kenfly 20130125
	}
	

	// Set view position to Center
	//_container->setPosition(ccp((POSX(winSize.width-_viewSize.width)/2), POSX((winSize.height-_viewSize.height)/2-50)));

	addBackGround();

	showCrystalInfo(curSelectCrystalID); // default show crystal_main in right panel

	this->addChild(_container,Z_CONTAINER);
	_container->release();

	
	return true;
}

void CrystalView::addBackGround()
{
	CCUIBackground * _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame("crystal/select_bg.png",
		ccp(POSX(30),POSX(28)),
		ccp(POSX(0),POSX(0)),
		CCSizeMake(/*_viewSize.width*3/5+10,_viewSize.height-50*/POSX(610), POSX(510)));
	/*_bg1->setAnchorPoint(CCPointZero);
	_bg1->setIsRelativeAnchorPoint(true);*/
	_container->addChild(_bg1,Z_BG);
	_bg1->release();

	CCUIBackground * _bg2 = new CCUIBackground();
	_bg2->initWithSpriteFrame("crystal/select_bg.png",
		ccp(POSX(644),POSX(28)),
		ccp(POSX(0),POSX(0)),
		CCSizeMake(/*_viewSize.width*2/5-50,_viewSize.height-50*/POSX(286), POSX(510)));
	/*_bg2->setAnchorPoint(CCPointZero);
	_bg2->setIsRelativeAnchorPoint(true);*/
	_container->addChild(_bg2,Z_BG);
	_bg2->release();
}

void CrystalView::showCDPannel()
{
	if(!_container){return;}

//	CCUIBackground * pCDPanelBack = (CCUIBackground *)_container->getChildByTag(TAG_CD_BG);
//	if(!pCDPanelBack){return;}
	int count = RoleManage::Instance()->_accountInfo._numCrystalCd;
	int begin = CDManage::CRYSTAL_0;
	for (int i = begin;i < begin+count ; i++)
	{
		if (_container->getChildByTag(TAG_CDITEM_1+i-begin))
		{
			if (CDManage::Instance()->getCustomCD(i))
			{
				CDManage::Instance()->deleteCustomCD(i);
			}			
			_container->removeChildByTag(TAG_CDITEM_1+i-begin,true);
		}

		if (!_container->getChildByTag(TAG_CDITEM_ZERO+i-begin))
		{
			CCLabelTTF * pLabText = new CCLabelTTF();
			pLabText->initWithString(
				ValuesUtil::Instance()->getString("CSL28").c_str(),
				CCSizeMake(POSX(240),POSX(24)),
				CCTextAlignmentLeft,
				"Arial",
				POSX(24));
			pLabText->setAnchorPoint(CCPointZero);
			pLabText->setColor(ccc3(12,233,25));
			pLabText->setPosition(ccp(POSX(660),POSX(315 - (i-begin)*40)));
			_container->addChild(pLabText,11,TAG_CDITEM_ZERO+i-begin);
			pLabText->release();
		}
		CCLabelTTF * pLabText = (CCLabelTTF *)_container->getChildByTag(TAG_CDITEM_ZERO+i-begin);
		bool isReady = CDManage::Instance()->getCDReady(i);
		if (isReady)
		{
			pLabText->setIsVisible(true);
		}
		else
		{
			pLabText->setIsVisible(false);
		}		

		CustomCD * pCustomCD = new CustomCD(i);
		if (pCustomCD)
		{			
			pCustomCD->setPosition(ccp(POSX(620),POSX(315 - (i-begin)*40)));
			_container->addChild(pCustomCD,10,TAG_CDITEM_1+i-begin);

			pCustomCD->reinit();

			pCustomCD->release();
		}
	}

	//
	bool bIsInCD = isInCD();
	if (bIsInCD)
	{
		EnableUpgradeButton(false);
	}
	else
	{
		EnableUpgradeButton(false);
		CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(CrystalView::upgradeTimer),this,0.2f,false);
	}
	
}

// init items
bool CrystalView::initItemsInScrollView()
{
	// init clip layer
	if(!initCrystalScrollView())
	{
		CCLog("Crystal:init ScrollView failed");
		return false;
	}
	// add clip layer into vector
	g_pCrystalScrollView->setIsRelativeAnchorPoint(true);
	g_pCrystalScrollView->setAnchorPoint(CCPointZero);
	g_pCrystalScrollView->setPosition(ccp(POSX(34),POSX(30)));
	if(!_container)
	{
		_container = new LayerNode();
		_container->init();  // LH0710
		_container->addChild(g_pCrystalScrollView,Z_BG_ITEM,TAG_SCROLLVIEW);
	}
	else if (!_container->getChildByTag(TAG_SCROLLVIEW))
	{
		_container->addChild(g_pCrystalScrollView,Z_BG_ITEM,TAG_SCROLLVIEW);
	}

	// left background cycle pics
	for(int _idto = 0;_idto < CrystalType::CRYSTAL_NUM;_idto++)
	{

		std::map<int,CrystalInfo*>::iterator iter = _crystalProxy->_idToVos.find(CRYSTALS[_idto]);
		if (iter == _crystalProxy->_idToVos.end())
		{
			continue;
		}
		if ((iter->second->id == CrystalType::CRYSTAL_SHANG)
			||(iter->second->id == CrystalType::CRYSTAL_KUANG)
			||iter->second->id == CrystalType::CRYSTAL_YOU)
		{
			continue;
		}
		
 		if(0 == _idto%(CRYSTAL_ROW_NUM * CRYSTAL_COLUMN_NUM))
 		{
			CCLog("Crystal:get scroll layer tag: %d",_idto/(CRYSTAL_ROW_NUM * CRYSTAL_COLUMN_NUM));
			_scrollLayer = g_pCrystalScrollView->getLayerByTag(_idto/(CRYSTAL_ROW_NUM * CRYSTAL_COLUMN_NUM));
		}

		if(_scrollLayer)
		{
			int posIndex = _idto%(CRYSTAL_ROW_NUM * CRYSTAL_COLUMN_NUM);

			SpriteNode * spriteBgCircle = new SpriteNode();
 			_scrollLayer->setIsRelativeAnchorPoint(true);
 			_scrollLayer->setAnchorPoint(CCPointZero);
			spriteBgCircle->initWithSpriteFrameName("crystal/bg_cycle.png");
			spriteBgCircle->setPosition(this->ccpCrystalPos[posIndex]);
			if (_scrollLayer->getChildByTag(TAG_BGCIRCLE+_idto))
			{
				_scrollLayer->removeChildByTag(TAG_BGCIRCLE+_idto,true);
			}
			_scrollLayer->addChild(spriteBgCircle,Z_TEXT,TAG_BGCIRCLE+_idto);
			spriteBgCircle->release();

			// left crystal picture
			SpriteNode * spriteCrystal = new SpriteNode();
			char path[64];
			if(_crystalProxy->_idToVos.find(CRYSTALS[_idto])!=_crystalProxy->_idToVos.end())
			{
				memset(path,0,sizeof(path));
				sprintf(path,"crystal/%d.png",CRYSTALS[_idto]);
				spriteCrystal->initWithSpriteFrameName(path); // different pictures depends on crystal type
			}
			else
			{
				spriteCrystal->initWithSpriteFrameName("crystal/crystal_unactivated.png"); // different pictures depends on crystal type
			}
			spriteCrystal->setPosition(ccp(this->ccpCrystalPos[posIndex].x,this->ccpCrystalPos[posIndex].y+10));
			int tagCrystalPic = TAG_CRYSTAL+_idto + (g_pCrystalScrollView->currentScreen-1)*(CRYSTAL_ROW_NUM * CRYSTAL_COLUMN_NUM);
			if (_scrollLayer->getChildByTag(tagCrystalPic))
			{
				_scrollLayer->removeChildByTag(tagCrystalPic,true);
			}			
			_scrollLayer->addChild(spriteCrystal,Z_TEXT+1,tagCrystalPic);
			spriteCrystal->release();

			// left crystal info
			std::string sz;
			char tmp[40]={0};
			sprintf(tmp,"CSL%d",_idto+1);
			sz.clear();
			sz.assign(CrystalManager::Instance()->_cv->getString(tmp));
			int level = iter->second->level;
// 			if(_crystalProxy->_idToVos.find(CRYSTALS[_idto])!=_crystalProxy->_idToVos.end())
// 			{
// 
// 				CrystalInfo* info = _crystalProxy->_idToVos.find(CRYSTALS[_idto])->second;
// 				level = info->level;
// 			}
			
			char chLevel[12];
			sprintf(chLevel,sz.c_str(),level);
			sz.clear();
			sz.assign(chLevel);
			UTF8(sz);
			_unName = CCLabelTTF::labelWithString(sz.c_str(),
				CCSizeMake(POSX(100), POSX(20)),
				CCTextAlignmentCenter,
				g_sSimHeiFont,
				POSX(g_CrystalFontSize));
			_unName->setColor(ccc3(255,240,180));
			_unName->setPosition(ccp(this->ccpCrystalPos[posIndex].x, this->ccpCrystalPos[posIndex].y-POSX(60)));
			if(_scrollLayer->getChildByTag(TAG_DESCRIBE+_idto))
			{
				_scrollLayer->removeChildByTag(TAG_DESCRIBE+_idto,true);
			}
			_scrollLayer->addChild(_unName,Z_TEXT+1,TAG_DESCRIBE+_idto);

			g_pCrystalScrollView->addHightLightFocusImage(g_pCrystalScrollView->_nPreFocusPos);

		}
		else
		{
			return false;
		}		
	}
	return true;
}


// load crystal clip vector
bool CrystalView::initCrystalScrollView()
{
	if(!g_pCrystalScrollView)
	{
		CrystalUIPartialScrollView * pScrollView = CrystalUIPartialScrollView::crystalScrollViewWithCCRect(CCRectMake(POSX(28),POSX(30),POSX(SCROLL_VIEW_WIDTH),POSX(SCROLL_VIEW_HEIGHT)));
		int nPageCount = (int)ceil((double)MAX_CRYSTAL_NUM/(CRYSTAL_ROW_NUM * CRYSTAL_COLUMN_NUM));
		
		CCLog("Crystal:nPageCount = %d",nPageCount);
		int page = 0;
		while((page<nPageCount)&&(pScrollView))
		{
			CCLog("Crystal:add scroll layer tag: %d",page);
			pScrollView->addLayerByTag(page);
			++page;
		}
		g_pCrystalScrollView = pScrollView;
		if(!g_pCrystalScrollView)
		{
			return false;
		}
	}
	return true;
}



// show left panel info
// void CrystalView::showCrystal()
// {
// 	std::string sz;
// 	for (int i=0;i<MAX_CRYSTAL_NUM;i++)
// 	{
// 		char tmp[40]={0};
// 		sprintf(tmp,"CSL%d",i+1);
// 		sz.clear();
// 		sz.assign(CrystalManager::Instance()->_cv->getString(tmp));
// 		int level = 0;
// 		if(_crystalProxy->idToVo.find(CRYSTALS[i])!=_crystalProxy->idToVo.end())
// 		{
// 			CrystalInfo* info = _crystalProxy->idToVo.find(CRYSTALS[i])->second;
// 			level = info->level;
// 		}
// 		 
// 		char chLevel[12];
// 		sprintf(chLevel,sz.c_str(),level);
// 		sz.clear();
// 		sz.assign(chLevel);
// 		UTF8(sz);
// 		_unName = CCLabelTTF::labelWithString(sz.c_str(),CCSizeMake(100,20),CCTextAlignmentCenter,g_sSimHeiFont,(float)g_CrystalFontSize);
// 		_unName->setColor(ccc3(255,240,180));
// 		_unName->setPosition(ccp(this->ccpCrystalPos[i].x,this->ccpCrystalPos[i].y-60));
// 
// 		_scrollLayer = g_pCrystalScrollView->getLayerByTag(i);
// 
// 		if(_scrollLayer->getChildByTag(TAG_SCROLLLAYER_CRYSTAL_UNDER+i))
// 		{
// 			_scrollLayer->removeChildByTag(TAG_SCROLLLAYER_CRYSTAL_UNDER+i,true);
// 		}
// 		_scrollLayer->addChild(_unName,Z_TEXT+1,TAG_SCROLLLAYER_CRYSTAL_UNDER+i);
// 	}
// }

// click to show right info
void CrystalView::showCrystalInfo(uint32 id)
{
	if (!id)
	{
		return;
	}

	// right cicle
	SpriteNode * spriteBgCircle = new SpriteNode();
	spriteBgCircle->initWithSpriteFrameName("crystal/bg_cycle.png");
	spriteBgCircle->setPosition(ccp(POSX(672), POSX(406)));
	spriteBgCircle->setAnchorPoint(CCPointZero);
	if (_container) 
	{
		_container->addChild(spriteBgCircle,Z_BG_ITEM);
	}
	spriteBgCircle->release();

	// crystal pics
	SpriteNode * spriteCrystal = new SpriteNode();
	//	spriteCrystal->autorelease();
	char path[64];
	memset(path,0,sizeof(path));
	sprintf(path,"crystal/%d.png",id);
	spriteCrystal->initWithSpriteFrameName(path); // should differ depends on type
	//spriteCrystal->setPosition(ccp(POSX(742), POSX(386)));
	spriteCrystal->setPosition(ccp(POSX(672), POSX(416)));
	spriteCrystal->setAnchorPoint(CCPointZero);
	if (_container) 
	{
		if (_container->getChildByTag(TAG_BGPANEL_DETAIL_INFO))
		{
			_container->removeChildByTag(TAG_BGPANEL_DETAIL_INFO,true);
		}
		_container->addChild(spriteCrystal,Z_BG_ITEM+1,TAG_BGPANEL_DETAIL_INFO);

		spriteCrystal->release();
	}
	CrystalInfo* info = NULL;
	if(_crystalProxy->_idToVos.find(id)!=_crystalProxy->_idToVos.end())
	{
		info = _crystalProxy->_idToVos.find(id)->second;
	}

	// name
	std::string szName;
	SkillVo* skillVo = SkillManager::Instance()->getSkill(id);
	if(skillVo)
		szName = skillVo->name;

	UTF8(szName);
	_name = CCLabelTTF::labelWithString(szName.c_str(), 
		CCSizeMake(POSX(120), POSX(26)),
		CCTextAlignmentCenter,
		g_sSimHeiFont,
		POSX(g_CrystalFontSize+2));
	_name->setColor(ccc3(255,240,0));
	//_name->setPosition(ccp(POSX(688), POSX(346)));
	_name->setPosition(ccp(POSX(750), POSX(500)));
	_name->setAnchorPoint(CCPointZero);
	if (_container)
	{
		if (_container->getChildByTag(TAG_BGPANEL_DETAIL_INFO+1))
		{
			_container->removeChildByTag(TAG_BGPANEL_DETAIL_INFO+1,true);
		}
		_container->addChild(_name,Z_TEXT,TAG_BGPANEL_DETAIL_INFO+1);
	}

 	int level = 0;
    if(info)
        level = info->level; 
	char chLevelAll[16];
	std::string szLevel = "";
	szLevel = CrystalManager::Instance()->_cv->getString("CSL15");
	sprintf(chLevelAll,szLevel.c_str(),level);
	szLevel.clear();
	szLevel.assign(chLevelAll);
	UTF8(szLevel);
	_level = CCLabelTTF::labelWithString(szLevel.c_str(), 
		CCSizeMake(POSX(100), POSX(20)),
		CCTextAlignmentLeft,
		g_sSimHeiFont,
		POSX(g_CrystalFontSize));
	_level->setColor(ccc3(255,255,250));
	_level->setPosition(ccp(POSX(688+110), POSX(460)));
	_level->setAnchorPoint(CCPointZero);
	if (_container)
	{
		if (_container->getChildByTag(TAG_BGPANEL_DETAIL_INFO+2))
		{
			_container->removeChildByTag(TAG_BGPANEL_DETAIL_INFO+2,true);
		}
		_container->addChild(_level,Z_TEXT,TAG_BGPANEL_DETAIL_INFO+2);
	}
	//
	char chTimeAll[24];
	std::string szTime = "";
	int time = info->time;
	if(time < 0) time = 0; // here are to debug why time changed to -85673827 when upgrade once 
	szTime = ValuesUtil::Instance()->getString("CSL16");
	sprintf(chTimeAll,szTime.c_str(),time/60);
	szTime.clear();
	szTime.assign(chTimeAll);	// upgrade time
	UTF8(szTime);

	_time = CCLabelTTF::labelWithString(szTime.c_str(), 
		CCSizeMake(POSX(200), POSX(20)),
		CCTextAlignmentCenter,
		g_sSimHeiFont, 
		POSX(g_CrystalFontSize));
	_time->setColor(ccc3(255,133,25));
	_time->setPosition(ccp(POSX(688+60), POSX(420)));
	_time->setAnchorPoint(CCPointZero);
	if (_container)
	{
		if (_container->getChildByTag(TAG_BGPANEL_DETAIL_INFO+3))
		{
			_container->removeChildByTag(TAG_BGPANEL_DETAIL_INFO+3,true);
		}
		_container->addChild(_time,Z_TEXT,TAG_BGPANEL_DETAIL_INFO+3);
	}
	//
	std::string szDetail = SkillManager::Instance()->getSkill(id)->des; // detail 
	UTF8(szDetail);
	_detail = CCLabelTTF::labelWithString(szDetail.c_str(),
		CCSizeMake(POSX(200), POSX(60)),
		CCTextAlignmentLeft,
		g_sSimHeiFont, 
		POSX(g_CrystalFontSize));
	_detail->setColor(ccc3(255,240,180));
	_detail->setPosition(ccp(POSX(688), POSX(346)));
	_detail->setAnchorPoint(CCPointZero);
	if (_container)
	{
		if (_container->getChildByTag(TAG_BGPANEL_DETAIL_INFO+4))
		{
			_container->removeChildByTag(TAG_BGPANEL_DETAIL_INFO+4,true);
		}
		_container->addChild(_detail,Z_TEXT,TAG_BGPANEL_DETAIL_INFO+4);
	}
}

// init crystal
bool CrystalView::initCrystalView()
{
	return (initView()&&initItemsInScrollView());
}

// upgrade button event
void CrystalView::clickUpgradeHandler(CCObject* pSender)
{
	if(_crystalProxy->_idToVos.find(curSelectCrystalID)!=_crystalProxy->_idToVos.end())
	{
		CrystalInfo* info = _crystalProxy->_idToVos.find(CRYSTALS[0])->second; // main crystal
		if(info->level < LEVEL[IDIndexMap.find(curSelectCrystalID)->second])
		{
			//CCLog("main level:%d,least level:%d",info->level,LEVEL[curSelectCrystalID]);
			//Message * m = new Message();
			//m->show(_crystalProxy->idToVo.find(curSelectCrystalID)->second->tip,ccc3(255,133,25),1);
			//return;
		}
		else
		{
			if (_crystalProxy->_idToVos.find(curSelectCrystalID)->second->time>0)
			{
				// add code here // CD time is 0 or not?
			}
		}
	}
	else{ return;}
	
	bool bIsInCD = isInCD();
	
	if (bIsInCD)
	{
		Message::Instance()->show(ValuesUtil::Instance()->getString("CSL26"),ccc3(12,233,25),1);

		EnableUpgradeButton(false);
	}
	else
	{
		//EnableUpgradeButton(true);
		EnableUpgradeButton(false);
		CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(CrystalView::upgradeTimer),this,0.2f,false);
	}

	CCMD184* s = new CCMD184();
	if (s)
	{
		s->a_id = uint8(this->curSelectCrystalID);
		GameServerSocket* pSocket = GameServerSocket::getInstance();
		if (pSocket)
		{
			pSocket->sendMessage(s);
		}
		cocos2d::CCLog("Crystal:Crystal Upgrade Request:CCMD184"); 
	}
	SAFE_DELETE(s);

	SoundManager::Instance()->playButtonEffectSound();
} 

bool CrystalView::isMaxLev()
{
	if (!g_pCrystalScrollView)
	{
		return false;
	}	
	int nPosIndex = g_pCrystalScrollView->_nPosIndex;
	if (nPosIndex >= 0)
	{
		std::map<int,CrystalInfo *>::iterator iter = _crystalProxy->_idToVos.find(CRYSTALS[nPosIndex]);
		if(iter == _crystalProxy->_idToVos.end())		{		return false;	}
		if (iter->second->level >= RoleManage::Instance()->roleInfo()->playerBaseInfo._lev)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

void CrystalView::upgradeTimer(ccTime dt)
{
	if (_upTime>=1)
	{
		CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(CrystalView::upgradeTimer),this);

		bool bIsInCD = isInCD();
		if (bIsInCD)
		{
			EnableUpgradeButton(false);
		}
		else
		{
			if (isMaxLev())
			{
				EnableUpgradeButton(false);
			}
			else
			{
				EnableUpgradeButton(true);
			}
		}

		_upTime = 0;
	}
	++_upTime;
}

// update Crystal CD list 
void CrystalView::updateCDList(int type,int incd,uint time)
{
	if (!_crystalCDList) return;

	if (type != _chCDType[type])
	{
		if (_CDlistCount>= RoleManage::Instance()->_accountInfo._numCrystalCd) {return;}
		++_CDlistCount;
		_chCDType[type] = type;
	}
	_chCDTime[type] = time;
	_curCDType = type;
	_curCDtime = time;
	
	//Doyang 20120711
	
	CCMutableArray<LayerNode *>* listChilds = _crystalCDList->getChilds();
	CCMutableArray<LayerNode *>::CCMutableArrayIterator it;
	for(it = listChilds->begin();
		it != listChilds->end();
		++ it)
	{
		LayerNode *pChildLayer = (LayerNode *) *it;
		if(!pChildLayer)
			continue;

		pChildLayer->removeFromParentAndCleanup(true);
		pChildLayer->release();
	}
	
	_crystalCDList->setAdapter(this);
	
}

// get crystal index from touch pos
int32 CrystalView::getTouchPosIndex( CCPoint point )
{
	int curPage = 0; 
	if (!g_pCrystalScrollView)
	{
		return -1;		
	}
	curPage = g_pCrystalScrollView->currentScreen;	
	int nStart = CRYSTAL_ROW_NUM*CRYSTAL_COLUMN_NUM*(curPage-1);
	int nMax = (CRYSTAL_ROW_NUM*CRYSTAL_COLUMN_NUM*curPage);
	int nEnd = nMax<MAX_CRYSTAL_NUM ? nMax:MAX_CRYSTAL_NUM;
	for(int i=nStart; i<nEnd; i++)
	{
		CCRect _crystalRect = CCRectMake(this->ccpCrystalPos[i].x,this->ccpCrystalPos[i].y,POSX(50), POSX(50));
		
		if(CCRect::CCRectContainsPoint(_crystalRect, point))
		{
			return i;
		}
	}
	return (-1);
}

int CrystalView::getCount()
{
	
	return _CDlistCount;
}

LayerNode * CrystalView::getView( int position )
{
	/*
	
	CrystalInfo info;
	info.time = _chCDTime[position+CDManage::CRYSTAL_0]*1000;


	CrystalTimer *pTimer = 0;
	std::map <int,CrystalTimer *>::iterator iter = _pCryTimerListMap.find(position+CDManage::CRYSTAL_0);
	if (iter != _pCryTimerListMap.end())
	{
		*pTimer = *iter->second;
		pTimer->update(&info);
	}
	else
	{
		pTimer = CrystalTimer::CrystalTimerWithCrystalInfo(&info);
		pTimer->update(&info);
		//pTimer->setAnchorPoint(ccp(POSX(0),POSX(0)));
		//pTimer->setPosition(ccp(POSX(130),POSX(10)));
		pTimer->setContentSize(CCSizeMake(POSX(100), POSX(40)));
		_pCryTimerListMap.insert(make_pair(position+CDManage::CRYSTAL_0,pTimer));
	}
	//CDItem* item = new CDItem( position+CDManage::CRYSTAL_0 );
	LayerNode * pLayer = (LayerNode *)pTimer;
	*/
	return 0;
}

void CrystalView::clickCloseHandler(CCObject* pSender)
{
	setisPop(false);
	g_pGlobalManage->setCurFocusGID(LayerManager::sceneLayer->getMyFocusGID());
}

void CrystalView::onItemClickListener(LayerNode *itemCell, int position)
{
	if (!_chCDTime[position + CDManage::CRYSTAL_0])
	{
		Message::Instance()->show(ValuesUtil::Instance()->getString("CSL20"),ccc3(12,233,25));
		return;
	}
	
	if (!_pCrysMediator) return;
	int type = position + CDManage::CRYSTAL_0;
	_pCrysMediator->reqMoney(type);
}

void CrystalView::clearCD(char * pPacket)
{
	SCMD19F * cmd = (SCMD19F *)pPacket;
	if (!cmd) return;
	memcpy((void *)&_cmd19fCopy,(void*)cmd,sizeof(_cmd19fCopy));

	Confirm * _confirmBuy = new Confirm();
	char str[64];
	sprintf(str,ValuesUtil::Instance()->getString("CSL19").c_str(),cmd->b_cost);
	_confirmBuy->initWithParam(
		str,
		this,
		menu_selector(CrystalView::clearCDOK),
		menu_selector(CrystalView::clickCancel));
	if (LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame))
	{
		LayerManager::windowLayer->removeChildByTag(WindowLayer::WindowLayerTAG_confirmFrame,true);
	}
	LayerManager::windowLayer->addChild(_confirmBuy,WindowLayer::WindowLayerZ_confirmFrame,WindowLayer::WindowLayerTAG_confirmFrame);
	_confirmBuy->release();
}

void CrystalView::clearCDOK(CCObject * pSender)
{
	clickCancel(0);
	if (_cmd19fCopy.b_cost > RoleManage::Instance()->_accountInfo._gold)
	{
		Message::Instance()->show(ValuesUtil::Instance()->getString("PY19"),ccc3(233,12,12),1);
		return;
	}
	if (!_pCrysMediator) return;
	_pCrysMediator->reqClearCD(_cmd19fCopy.a_type,_cmd19fCopy.b_cost);
}

void CrystalView::onClearAllCDConfirm(CCObject * pSender)
{
	Confirm * _confirmBuy = new Confirm();
	char str[128];
	sprintf(str,ValuesUtil::Instance()->getString("CSL29").c_str());
	_confirmBuy->initWithParam(
		str,
		this,
		menu_selector(CrystalView::onClearAllCDOK),
		menu_selector(CrystalView::clickCancel));
	if (LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame))
	{
		LayerManager::windowLayer->removeChildByTag(WindowLayer::WindowLayerTAG_confirmFrame,true);
	}
	LayerManager::windowLayer->addChild(_confirmBuy,WindowLayer::WindowLayerZ_confirmFrame,WindowLayer::WindowLayerTAG_confirmFrame);
	_confirmBuy->release();
}

void CrystalView::onClearAllCDOK(CCObject * pSender)
{
	clickCancel(0);
	if (!_pCrysMediator) return;
	int nCurNum = RoleManage::Instance()->_accountInfo._numCrystalCd;
	int nType = CDManage::CRYSTAL_0;
	for (nType ; nType < CDManage::CRYSTAL_0 + nCurNum ; nType++)
	{
		_pCrysMediator->reqClearCD(nType , 0);
	}	
}

void CrystalView::clickCancel(CCObject * pSender)
{
	Confirm * _confirmBuy = (Confirm *)LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame);
	if (_confirmBuy&&_confirmBuy->getParent())
	{
		_confirmBuy->getParent()->removeChildByTag(WindowLayer::WindowLayerTAG_confirmFrame,true);
	}  
}

void CrystalView::buyCrystalListHandle(CCObject * pSender)
{
	SoundManager::Instance()->playButtonEffectSound();

	int nCurNum = RoleManage::Instance()->_accountInfo._numCrystalCd;
	if (nCurNum>=2 && nCurNum<=5)
	{
		int nNeedVIP = CDManage::BUY_LIST_VIPLEV[nCurNum];
		int nNeedGold = CDManage::BUY_LIST_GOLD[nCurNum];
		if (nNeedVIP > RoleManage::Instance()->_accountInfo._vipLev)
		{
			Confirm * _confirmBuy = new Confirm();
			char str[128];
			sprintf(str,ValuesUtil::Instance()->getString("CSL22").c_str(),nNeedVIP);
			_confirmBuy->initWithParam(
				str,
				this,
 				menu_selector(CrystalView::clickReqRecharge),
 				menu_selector(CrystalView::clickCancel));
			if (LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame))
			{
				LayerManager::windowLayer->removeChildByTag(WindowLayer::WindowLayerTAG_confirmFrame,true);
			}
			LayerManager::windowLayer->addChild(_confirmBuy,WindowLayer::WindowLayerZ_confirmFrame,WindowLayer::WindowLayerTAG_confirmFrame);
			_confirmBuy->release();
		}
		else
		{
			if (nNeedGold == 0)
			{
				//_dispatcher.dispatchEvent(new ParamEvent(GameDispatcher.SHOW_UI_VIP));
			}
			else
			{
				if (nNeedGold > RoleManage::Instance()->_accountInfo._gold)
				{
					Message::Instance()->show(ValuesUtil::Instance()->getString("PY19"),ccc3(233,12,25),1);
					return;
				}
				else
				{
					{
						Confirm * _confirmBuy = new Confirm();
						char str[128];
						sprintf(str,ValuesUtil::Instance()->getString("CSL27").c_str(),nNeedGold);
						_confirmBuy->initWithParam(
							str,
							this,
							menu_selector(CrystalView::clickCDReqRecharge),
							menu_selector(CrystalView::clickCancel));
						if (LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame))
						{
							LayerManager::windowLayer->removeChildByTag(WindowLayer::WindowLayerTAG_confirmFrame,true);
						}
						LayerManager::windowLayer->addChild(_confirmBuy,WindowLayer::WindowLayerZ_confirmFrame,WindowLayer::WindowLayerTAG_confirmFrame);
						_confirmBuy->release();
					}
				}
			}
			
		}
		
	}
	
}

void CrystalView::clickReqRecharge(CCObject * pSender)
{
	// Recharge Handler
	clickCancel(0);
	// add code here
}

void CrystalView::clickCDReqRecharge(CCObject * pSender)
{
	int nCurNum = RoleManage::Instance()->_accountInfo._numCrystalCd;
	if (nCurNum>=2 && nCurNum<=5)
	{
		int type = CDManage::CRYSTAL_0 + nCurNum;
		if (_pCrysMediator)
		{
			_pCrysMediator->sendBuyCDListReq(type);
		}
	}
	clickCancel(0);
}

void CrystalView::buyCrystalCDList(int nValue,int listNum)
{
	switch (nValue)
	{
	case 0:
		Message::Instance()->show(ValuesUtil::Instance()->getString("CSL23"),ccc3(233,23,23),1);
		break;
	case 1:
		Message::Instance()->show(ValuesUtil::Instance()->getString("PY19"),ccc3(233,23,23),1);
		break;
	case 2:
		Message::Instance()->show(ValuesUtil::Instance()->getString("CSL24"),ccc3(12,233,25),1);
		break;
	default:
		break;
	}
	
	// update CD pannel
	showCDPannel(); // LH0809
}

void CrystalView::EnableUpgradeButton(bool var)
{
	if (_container)
	{
		CCMenu * pUpgradeBtn = (CCMenu *)_container->getChildByTag(TAG_UPGRADE_BTN);
		if (pUpgradeBtn)
		{
			CCMenuItemImage* pBtnImage = (CCMenuItemImage*)pUpgradeBtn->getChildByTag( TAG_UPGRADE_BTN_IMG );
			if(pBtnImage)
			{
				pBtnImage->setIsEnabled(var);
			}
		}
	}
}

bool CrystalView::isInCD()
{
	if (!_container){return false;}
	int count = RoleManage::Instance()->_accountInfo._numCrystalCd;
	int begin = CDManage::CRYSTAL_0;
	bool isInCD = false;
	for (int i = begin;i < begin+count ; i++)
	{
		CustomCD * pCustomCD = (CustomCD *)_container->getChildByTag(TAG_CDITEM_1+i-begin);
		if (pCustomCD)
		{
			if (pCustomCD->getIsLock())
			{
				isInCD = true;
			}
			else
			{
				isInCD = false;
				break;
			}
		}
	}
	return isInCD;
}

CCNode * CrystalView::getNewHandItem( int id )
{
	if(id == 10) // upgrade button
	{
		if (_container && _container->getChildByTag(TAG_UPGRADE_BTN))
		{
			return _container->getChildByTag(TAG_UPGRADE_BTN)->getChildByTag(TAG_UPGRADE_BTN_IMG);
		}
	}
	else if (id == 11)
	{
		if ( g_pCrystalScrollView && g_pCrystalScrollView->getLayerByTag(0) && g_pCrystalScrollView->getLayerByTag(0)->getChildByTag(TAG_CRYSTAL + 1))
		{
			return g_pCrystalScrollView->getLayerByTag(0)->getChildByTag(TAG_CRYSTAL + 1);
		}
	}	

	return NULL;
}

// void onItemTouchListener(LayerNode *itemCell, int position)
// {
// 
// }
// void onItemTouchCancelListener(LayerNode *itemCell, int position)
// {
// 
// }
