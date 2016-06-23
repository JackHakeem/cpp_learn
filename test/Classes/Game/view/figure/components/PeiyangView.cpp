#include "PeiyangView.h"
#include "manager/PopEventName.h"
#include "CCTouchDispatcher.h"
#include "FigureCreate.h"
#include "model/player/RoleManage.h"
#include "utils/ValuesUtil.h"
#include "model/player/FigureBaseManage.h"
#include "socket/network/GameServerSocket.h"
#include "CCGeometry.h"
#include "Message.h"
#include "mvc/Facade.h"
#include "PopUIBg.h"
#include "utils/ColorUtil.h"
#include "manager/GlobalManage.h"
#include "CCUIBackground.h"
#include "manager/TouchLayerEnum.h"
#include "manager/ViewManager.h"
#include "MessageInfoBox.h"
#include "model/newhand/NewhandManager.h"
#include "manager/LevLimitConst.h"

PeiyangView::PeiyangView()
{
	_figureMediator = (FigureMediator *)g_pFacade->retrieveMediator(AppFacade_FIGURE_MEDIATOR);
	_peiyangLayer = 0;
	_washText = 0;
	_acceptText = 0;
	_cancelText = 0;
	_rebornButton = 0;
	_washButton = 0;
	_acceptButton = 0;
	_cancelButton = 0;
	_CurScreen = 0;
	_curID = 0;
	_curAccount = 0;
	_type = 0;
	_useItem = 0;
	_baseStrength = 0;
	_baseIntellect = 0;
	_baseStamina = 0;
	_fullValue = 0;
	_practiceNeed = 0;
	_goldNeed = 0;
	_washType = 0;
	_price = 4;
	_vipLev = 0;
	_starLev = 0;
	_reBornNeedLev = 51;
	_caStrength = 0;
	_caStamina = 0;
	_caIntelect = 0;
	for (int i = 0;i<MAX_ROLE_NUM;i++)
	{
		_sigSelect[i] = 3;
	}
	SELECTPOS[0] = ccp(POSX(43), POSX(368));
	SELECTPOS[1] = ccp(POSX(245), POSX(368));
	SELECTPOS[2] = ccp(POSX(44), POSX(326));
	SELECTPOS[3] = ccp(POSX(245), POSX(326));
	SELECTPOS[4] = ccp(POSX(44), POSX(286));
	SELECTPOS[5] = ccp(POSX(245), POSX(286));
	SELECTPOS[6] = ccp(POSX(57), POSX(201));
	SELECTPOS[7] = ccp(POSX(57), POSX(150));
	SELECTPOS[8] = ccp(POSX(57), POSX(96));

	memset(IsWashed,0,sizeof(IsWashed));
	memset(_mulSelect1,0,sizeof(_mulSelect1));
	memset(_mulSelect2,0,sizeof(_mulSelect2));
	memset(_mulSelect3,0,sizeof(_mulSelect3));
	memset(_isRecommend,0,sizeof(_isRecommend));
	initHeadMap();
	init();
}

PeiyangView::~PeiyangView()
{

}

void PeiyangView::initHeadMap()
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

bool PeiyangView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	this->key = PopEventName::PEIYANG;
	this->setIsTouchEnabled(true);

	CCSize popContainerSize = CCSizeMake(POSX(448), /*POSX(628)*/CCDirector::sharedDirector()->getWinSize().height);

	g_pGlobalManage->setCurFocusGID(LayerManager::windowLayer->getMyFocusGID());

	if (ViewManager::getInstance()->figureView&&ViewManager::getInstance()->figureView->_figureV&&ViewManager::getInstance()->figureView->_figureV->_attrLayer)
	{
		ViewManager::getInstance()->figureView->_figureV->_attrLayer->setIsVisible(false);
	}

	setPopContentSize(popContainerSize);

	CCUIBackground * _peiyangContainer = new CCUIBackground();
	_peiyangContainer->initWithSpriteFrame("ui2.png", 
		ccp(POSX(2), POSX(28)),
		ccp(0,0),
		CCSizeMake(POSX(444),POSX(504)));

	if (!_peiyangLayer)
	{
		_peiyangLayer = new LayerNode();
		_peiyangLayer->setAnchorPoint(CCPointZero);
		_peiyangLayer->setIsRelativeAnchorPoint(true);
		_peiyangLayer->setPosition(POS(ccp(0, 12), ScaleUtil::TOP_LEFT));
		_peiyangLayer->setContentSize(popContainerSize);
	}
	_peiyangLayer->addChild(_peiyangContainer);
	

	this->addChild(_peiyangLayer,Z_PY+1);

	_viewSize = popContainerSize;
	loadItems(false);
	_peiyangContainer->release();
	return true;
}

void PeiyangView::moveBy(CCPoint pos)
{

}

void PeiyangView::loadSelectItems()
{
	if (!_peiyangLayer)
	{
		return;
	}
	// add code here
	for (int i = 0;i<6;i++)
	{
		SpriteNode * pSpriteSingle = new SpriteNode();
		if (pSpriteSingle)
		{
			if (pSpriteSingle->initWithSpriteFrameName("peiyang/bg_circle.png"))
			{
				pSpriteSingle->setScale(1.0);
				pSpriteSingle->setPosition(SELECTPOS[i]);
				_peiyangLayer->addChild(pSpriteSingle,0);
			}
			pSpriteSingle->release(); //LH0712LEAK
		}
		
		
	}
	for (int i = 6;i<9;i++)
	{
  		SpriteNode * pSpriteMulti = new SpriteNode();
		if (pSpriteMulti)
		{
			if (pSpriteMulti->initWithSpriteFrameName("peiyang/bg_kuang.png"))
			{
				pSpriteMulti->setPosition(ccp(SELECTPOS[i].x-POSX(10),SELECTPOS[i].y));
				_peiyangLayer->addChild(pSpriteMulti,0);
			}
			pSpriteMulti->release(); //LH0712LEAK
		}
		
 		

		CCUIBackground * pSpriteAttr = new CCUIBackground();
		if (pSpriteAttr)
		{
			pSpriteAttr->initWithSpriteFrame("peiyang/bg_kuang2.png",CCPointZero,CCPointZero,CCSizeMake(POSX(300), POSX(50)));
			pSpriteAttr->setPosition(ccp(SELECTPOS[i].x+POSX(30),SELECTPOS[i].y-POSX(25)));
			_peiyangLayer->addChild(pSpriteAttr,0);
			pSpriteAttr->release(); //LH0712LEAK
		}
		
		
	}	
}

void PeiyangView::loadItems(bool isSaved)
{
	if (!_peiyangLayer)
	{
		return;
	}

	_peiyangLayer->removeAllChildrenWithCleanup(true);

	loadSelectItems();

	if (!g_pFigureScrollView)
	{
		return;
	}
	int nCurScreen = g_pFigureScrollView->currentScreen;
	_CurScreen = nCurScreen;
	int count = nCurScreen;
	//std::map<int ,PlayerInfoVo>* list = RoleManage::Instance()->mercList();
	//std::map<int, PlayerInfoVo>::iterator iter = list->begin();
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* list = RoleManage::Instance()->mercListEx();  // LH20121019listorder
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>::iterator iter = list->begin();
	_vipLev = RoleManage::Instance()->_accountInfo._vipLev;
	while (count-1)
	{
		++iter;
		--count;
	}
	if (iter != list->end())
	{

		_fullValue = iter->second.playerBaseInfo._lev + 20;
		_practiceNeed = iter->second.playerBaseInfo._lev * 5 + 10;
		_curID = iter->second.figureBaseInfo.mercId;
		_curAccount = iter->first.id;
		_starLev = iter->second.figureBaseInfo.rebornNum;
		_reBornNeedLev = 51 + _starLev * 5;

		char path[64];
		// load head icon
		SpriteNode * headbg = new SpriteNode();
		headbg->initWithSpriteFrameName("peiyang/headbg.png");
		headbg->setPosition(ccp(POSX(67), POSX(463)));
		_peiyangLayer->addChild(headbg,0,0);
		SpriteNode * head = new SpriteNode();
		memset(path,0,sizeof(path));
		//sprintf(path,"head/%d.png",iter->second.playerBaseInfo.cloth);
		sprintf(path,"assets/icon/head/%d.png",iter->second.playerBaseInfo.cloth);
		if (head->initWithFile(path))
		{
			head->setPosition(ccp(headbg->getContentSize().width/2,headbg->getContentSize().height/2));
			head->setScale((float)headbg->getContentSize().width/head->getContentSize().width);
			headbg->addChild(head,0,0);
		}
		head->release();
		headbg->release(); // LH0712LEAK
		

		// name
		CCLabelTTF * _roleName = CCLabelTTF::labelWithString(iter->second.playerBaseInfo.name.c_str(),
			CCSizeMake(POSX(160), POSX(22)),
			CCTextAlignmentLeft,
			g_sSimHeiFont,
			POSX(20));
		_roleName->setAnchorPoint(CCPointZero);
		_roleName->setColor(ColorUtil::getMerchColor(iter->second.playerBaseInfo.color));
		_roleName->setPosition(ccp(POSX(125), POSX(482)));
		_peiyangLayer->addChild(_roleName,0,1);
		// star text
//		CCLabelTTF * _starText = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("PY1").c_str(),
//			CCSizeMake(POSX(80), POSX(20)),
//			CCTextAlignmentLeft,
//			g_sSimHeiFont,
//			POSX(16));
//		_starText->setAnchorPoint(CCPointZero);
//		_starText->setColor(ccc3(240,240,240));
//		_starText->setPosition(ccp(POSX(125), POSX(452)));
//		_peiyangLayer->addChild(_starText,0,2);
		// star icon
//		loadStarIcon(_starLev);

		// gold txt
		{
			char path[128] = {0};
			memset(path,0,sizeof(path));
			sprintf(path,ValuesUtil::Instance()->getString("ROL100").c_str(),RoleManage::Instance()->accountInfo()->gold());
			CCLabelTTF * pGoldText = CCLabelTTF::labelWithString(
				path,
				CCSizeMake(POSX(210), POSX(20)),
				CCTextAlignmentLeft,
				g_sSimHeiFont,
				POSX(16));
			pGoldText->setAnchorPoint(CCPointZero);
			pGoldText->setColor(ccc3(233,133,25));
			pGoldText->setPosition(ccp(POSX(125), POSX(452)));
			_peiyangLayer->addChild(pGoldText,0,2);
		}		

		// practice txt
		{
			char path[128] = {0};
			memset(path,0,sizeof(path));
			sprintf(path ,ValuesUtil::Instance()->getString("ROL101").c_str() , RoleManage::Instance()->accountInfo()->practice());
			CCLabelTTF * pPracText = CCLabelTTF::labelWithString(
				path,
				CCSizeMake(POSX(200), POSX(20)),
				CCTextAlignmentLeft,
				g_sSimHeiFont,
				POSX(16));
			pPracText->setAnchorPoint(CCPointZero);
			pPracText->setColor(ccc3(12,133,233));
			pPracText->setIsVisible(true);
			pPracText->setPosition(ccp(POSX(125), POSX(422)));
			_peiyangLayer->addChild(pPracText,0,4);
		}

		// reborn text
// 		memset(path,0,sizeof(path));
// 		sprintf(path,ValuesUtil::Instance()->getString("PY2").c_str(),_reBornNeedLev);
// 		std::string sReBornText(path);
// 		CCLabelTTF * _reBornText = CCLabelTTF::labelWithString(sReBornText.c_str(),
// 			CCSizeMake(POSX(200), POSX(20)),
// 			CCTextAlignmentLeft,
// 			g_sSimHeiFont,
// 			POSX(16));
// 		_reBornText->setAnchorPoint(CCPointZero);
// 		_reBornText->setColor(ccc3(240,133,25));
// 		_reBornText->setIsVisible(false);
// 		_reBornText->setPosition(ccp(POSX(125), POSX(422)));
// 		_peiyangLayer->addChild(_reBornText,0,4);

		// reborn button
		CCLabelTTF * _reBornButtonText = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("PY24").c_str(),
			CCSizeMake(POSX(60), POSX(20)),
			CCTextAlignmentCenter,
			g_sSimHeiFont,
			POSX(18));
		_reBornButtonText->setAnchorPoint(CCPointZero);
		_reBornButtonText->setColor(ccc3(240,240,220));
		_reBornButtonText->setPosition(ccp(POSX(300), POSX(420)));
		_reBornButtonText->setIsVisible(false);
		_peiyangLayer->addChild(_reBornButtonText,1,21);
		
		{
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
			if(pNormalSprite && pPressedSprite && pSelectdSprite)
			{
				CCMenuItemSprite *_buttonRebornImg = CCMenuItemSprite::itemFromNormalSprite(
					pNormalSprite,
					pPressedSprite,
					pSelectdSprite,
					this,menu_selector(PeiyangView::clickRebornHandler));
				_rebornButton = CCMenu::menuWithItem(_buttonRebornImg);
				_rebornButton->setPosition(ccp(POSX(330), POSX(430)));
				_rebornButton->setAnchorPoint(CCPointZero);
				_rebornButton->setScaleX(0.6);
				_rebornButton->setScaleY(0.6);
				_rebornButton->setTouchLayer(TLE::WindowLayer_Peiyang);
				_rebornButton->setIsVisible(false);
				_peiyangLayer->addChild(_rebornButton,0,22);
			}
		}			

		// load select texts
		CCLabelTTF * _selectText0 = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("PY3").c_str(),
			CCSizeMake(POSX(200), POSX(20)),
			CCTextAlignmentLeft,
			g_sSimHeiFont,
			POSX(18));
		_selectText0->setAnchorPoint(CCPointZero);
		_selectText0->setColor(ccc3(100,100,100));
		_selectText0->setPosition(ccp(POSX(70), POSX(358)));
		_peiyangLayer->addChild(_selectText0,0,5);
		CCLabelTTF * _selectText1 = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("PY4").c_str(),
			CCSizeMake(POSX(200), POSX(20)),
			CCTextAlignmentLeft,
			g_sSimHeiFont,
			POSX(18));
		_selectText1->setAnchorPoint(CCPointZero);
		_selectText1->setColor(ccc3(100,100,100));
		_selectText1->setPosition(ccp(POSX(270), POSX(358)));
		_peiyangLayer->addChild(_selectText1,0,6);		
		memset(path,0,sizeof(path));
		sprintf(path,ValuesUtil::Instance()->getString("PY5").c_str(),_practiceNeed);
		CCLabelTTF * _selectText2 = CCLabelTTF::labelWithString(path,
			CCSizeMake(POSX(200), POSX(20)),
			CCTextAlignmentLeft,
			g_sSimHeiFont,
			POSX(18));
		_selectText2->setAnchorPoint(CCPointZero);
		_selectText2->setColor(ccc3(255,215,0));
		_selectText2->setPosition(ccp(POSX(70), POSX(316)));
		_peiyangLayer->addChild(_selectText2,0,7);
		memset(path,0,sizeof(path));
		sprintf(path,ValuesUtil::Instance()->getString("PY6").c_str(),2);
		CCLabelTTF * _selectText3 = CCLabelTTF::labelWithString(path,
			CCSizeMake(POSX(200), POSX(20)),
			CCTextAlignmentLeft,
			g_sSimHeiFont,
			POSX(18));
		_selectText3->setAnchorPoint(CCPointZero);
		_selectText3->setColor(ccc3(255,215,0));
		_selectText3->setPosition(ccp(POSX(270), POSX(316)));
		_peiyangLayer->addChild(_selectText3,0,8);
		memset(path,0,sizeof(path));
		sprintf(path,ValuesUtil::Instance()->getString("PY7").c_str(),_price);
		CCLabelTTF * _selectText4 = CCLabelTTF::labelWithString(path,
			CCSizeMake(POSX(200), POSX(20)),
			CCTextAlignmentLeft,
			g_sSimHeiFont,
			POSX(18));
		_selectText4->setTag(TAG_Price_Labtxt);
		_selectText4->setAnchorPoint(CCPointZero);
		_selectText4->setColor((RoleManage::Instance()->accountInfo()->_vipLev >= 3) ? ccc3(255,215,0) : ccc3(100,100,100));
		_selectText4->setPosition(ccp(POSX(70), POSX(275)));
		_peiyangLayer->addChild(_selectText4,0);
		CCLabelTTF * _selectText5 = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("PY8").c_str(),
			CCSizeMake(POSX(200), POSX(20)),
			CCTextAlignmentLeft,
			g_sSimHeiFont,
			POSX(18));
		_selectText5->setAnchorPoint(CCPointZero);
		_selectText5->setColor((RoleManage::Instance()->accountInfo()->_vipLev >= 7) ? ccc3(255,215,0) : ccc3(100,100,100));
		_selectText5->setPosition(ccp(POSX(270), POSX(275)));
		_peiyangLayer->addChild(_selectText5,0,10);

		// load single/mult select icon
		loadSelectIcon(_sigSelect[_CurScreen],_mulSelect1[_CurScreen],_mulSelect2[_CurScreen],_mulSelect3[_CurScreen]);

		// priority // recommend
		std::string s1 = ValuesUtil::Instance()->getString("stamina");
		std::string s2 = ValuesUtil::Instance()->getString("strength");
		std::string s3 = ValuesUtil::Instance()->getString("intelligence");
		std::string strArr[3] = {s1,s2,s3};
		int recommendArr[3] = {0};
		FigureCfgBaseVo *pBaseVo = FigureBaseManage::Instance()->getMercBase(iter->second.figureBaseInfo.mercId);
		if (pBaseVo)
		{
			int i = 0;
			std::vector<int>::iterator iter = pBaseVo->recommend.begin();
			for (;iter != pBaseVo->recommend.end();iter++)
			{
				recommendArr[i] = *iter;
				++i;
			}
			memset(path,0,sizeof(path));
			sprintf(path,ValuesUtil::Instance()->getString("PY9").c_str(),strArr[recommendArr[0]-1].c_str(),strArr[recommendArr[1]-1].c_str(),strArr[recommendArr[2]-1].c_str()); // should vary depends
			std::string sPriText(path);
			CCLabelTTF * _priText = CCLabelTTF::labelWithString(sPriText.c_str(),
				CCSizeMake(POSX(300), POSX(20)),
				CCTextAlignmentLeft,
				g_sSimHeiFont,
				POSX(18));
			_priText->setAnchorPoint(CCPointZero);
			_priText->setColor(ccc3(240,240,240));
			_priText->setPosition(ccp(POSX(100), POSX(240)));
			_peiyangLayer->addChild(_priText,0,11);
		}

		// selected
		// skip this

		// property
		FigureCfgBaseVo * fv = FigureBaseManage::Instance()->getMercBase(iter->second.figureBaseInfo.mercId);
		if (fv)
		{
			_baseStrength = fv->strength;
			_baseIntellect = fv->intellect;
			_baseStamina = fv->stamina;
		}
		int _exStrength = iter->second.figureBaseInfo.strength-_baseStrength;
		int _exIntellect = iter->second.figureBaseInfo.intellect-_baseIntellect;
		int _exStamina = iter->second.figureBaseInfo.stamina-_baseStamina;
		std::string str("");
		str = (_exStrength < _fullValue) ? "PY15" : "PY26";
		memset(path,0,sizeof(path));
		sprintf(path,ValuesUtil::Instance()->getString(str.c_str()).c_str(),_baseStrength,_exStrength);
		std::string sProText0(path);
		CCLabelTTF * _proText0 = CCLabelTTF::labelWithString(sProText0.c_str(),
			CCSizeMake(POSX(260), POSX(30)),
			CCTextAlignmentLeft,
			g_sSimHeiFont,
			POSX(24));
		_proText0->setAnchorPoint(CCPointZero);
		_proText0->setColor(ccc3(255,0,0));
		_proText0->setPosition(ccp(POSX(100), POSX(188)));
		_peiyangLayer->addChild(_proText0,0,12);

		memset(path,0,sizeof(path));
		str = (_exStamina < _fullValue) ? "PY16" : "PY27";
		sprintf(path,ValuesUtil::Instance()->getString(str.c_str()).c_str(),_baseStamina,_exStamina);
		std::string sProText1(path);
		CCLabelTTF * _priText1 = CCLabelTTF::labelWithString(sProText1.c_str(),
			CCSizeMake(POSX(260), POSX(30)),
			CCTextAlignmentLeft,
			g_sSimHeiFont,
			POSX(24));
		_priText1->setAnchorPoint(CCPointZero);
		_priText1->setColor(ccc3(12,233,25));
		_priText1->setPosition(ccp(POSX(100), POSX(136)));
		_peiyangLayer->addChild(_priText1,0,13);

		memset(path,0,sizeof(path));
		str = (_exIntellect < _fullValue) ? "PY17" : "PY28";
		sprintf(path,ValuesUtil::Instance()->getString(str.c_str()).c_str(),_baseIntellect,_exIntellect);
		std::string sProText2(path);
		CCLabelTTF * _priText2 = CCLabelTTF::labelWithString(sProText2.c_str(),
			CCSizeMake(POSX(260), POSX(30)),
			CCTextAlignmentLeft,
			g_sSimHeiFont,
			POSX(24));
		_priText2->setAnchorPoint(CCPointZero);
		_priText2->setColor(ccc3(28,129,233));
		_priText2->setPosition(ccp(POSX(100), POSX(81)));
		_peiyangLayer->addChild(_priText2,0,14);

		// Recommend


		// wash button		
		_washText = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("PY10").c_str(),
			CCSizeMake(POSX(100), POSX(20)),
			CCTextAlignmentCenter,
			g_sSimHeiFont,
			POSX(20));
		_washText->setColor(ccc3(255,215,0));
		_washText->setPosition(ccp(POSX(205), POSX(46)));
		_washText->setIsVisible(!IsWashed[_CurScreen]);
		_peiyangLayer->addChild(_washText,1,15);
		
		{
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
			if(pNormalSprite && pPressedSprite && pSelectdSprite)
			{
				CCMenuItemSprite *_ButtonImg = CCMenuItemSprite::itemFromNormalSprite(
					pNormalSprite,
					pPressedSprite,
					pSelectdSprite,
					this,menu_selector(PeiyangView::clickWashHandler));
				_washButton = CCMenu::menuWithItem(_ButtonImg);
				_washButton->setPosition(ccp(POSX(205), POSX(46)));
				_washButton->setTouchLayer(TLE::WindowLayer_Peiyang);
				_peiyangLayer->addChild(_washButton,0,16);
				_washButton->setIsVisible(!IsWashed[_CurScreen]);
				_washButton->setIsTouchEnabled(!IsWashed[_CurScreen]);
			}
		}

		// accept and cancel button
		_acceptText = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("PY13").c_str(),
			CCSizeMake(POSX(100), POSX(20)),
			CCTextAlignmentCenter,
			g_sSimHeiFont,
			POSX(20));
		_acceptText->setColor(ccc3(255,215,0));
		_acceptText->setPosition(ccp(POSX(87), POSX(42)));
		_acceptText->setIsVisible(IsWashed[_CurScreen]);
		_peiyangLayer->addChild(_acceptText,1,17);

		{
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
			if(pNormalSprite && pPressedSprite && pSelectdSprite)
			{
				CCMenuItemSprite *_ButtonImg1 = CCMenuItemSprite::itemFromNormalSprite(
					pNormalSprite,
					pPressedSprite,
					pSelectdSprite,
					this,menu_selector(PeiyangView::clickAcceptHandler));
				_acceptButton = CCMenu::menuWithItem(_ButtonImg1);
				_acceptButton->setPosition(ccp(POSX(87), POSX(42)));
				_acceptButton->setIsVisible(IsWashed[_CurScreen]);
				_acceptButton->setIsTouchEnabled(IsWashed[_CurScreen]);
				_acceptButton->setTouchLayer(TLE::WindowLayer_Peiyang);
				_peiyangLayer->addChild(_acceptButton,0,18);
			}

		}
		
		_cancelText = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("PY14").c_str(),
			CCSizeMake(POSX(100), POSX(20)),
			CCTextAlignmentCenter,
			g_sSimHeiFont,
			POSX(20));
		_cancelText->setColor(ccc3(255,215,0));
		_cancelText->setPosition(ccp(POSX(323), POSX(42)));
		_cancelText->setIsVisible(IsWashed[_CurScreen]);
		_peiyangLayer->addChild(_cancelText,1,19);

		{
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
			if(pNormalSprite && pPressedSprite && pSelectdSprite)
			{
				CCMenuItemSprite *_ButtonImg2 = CCMenuItemSprite::itemFromNormalSprite(
					pNormalSprite,
					pPressedSprite,
					pSelectdSprite,
					this,menu_selector(PeiyangView::clickCancelHandler));
				_cancelButton = CCMenu::menuWithItem(_ButtonImg2);
				_cancelButton->setPosition(ccp(POSX(323), POSX(42)));
				_cancelButton->setIsVisible(IsWashed[_CurScreen]);
				_cancelButton->setIsTouchEnabled(IsWashed[_CurScreen]);
				_cancelButton->setTouchLayer(TLE::WindowLayer_Peiyang);
				_peiyangLayer->addChild(_cancelButton,0,20);
			}
		}

		if (isSaved)
		{
			loadTipsItems();
		}
	}
	
}

void PeiyangView::loadStarIcon(int starLev)
{
	int starlev = (starLev < 0) ? 0 : starLev;
	int sun = starlev/25;
	int moon = (starlev - sun*25)/5;
	int star = starlev - sun*25 - moon*5;
	
	if (!_peiyangLayer)
	{
		return;
	}
	for (int i =0;i<10;i++) 
	{
		SpriteNode * s1 = new SpriteNode();
		if (s1)
		{
			if (s1->initWithSpriteFrameName("peiyang/sun.png"))
			{
				s1->setPosition(ccp(POSX(183+i*25), POSX(464)));
				s1->setIsVisible(false);
				if (_peiyangLayer->getChildByTag(30+i))
				{
					_peiyangLayer->removeChildByTag(30+i,true);
				}
				_peiyangLayer->addChild(s1,0,30+i);
			}
			s1->release(); // LH0712LEAK
		}
		
		
		

		SpriteNode * s2 = new SpriteNode();
		if (s2)
		{
			if (s2->initWithSpriteFrameName("peiyang/moon.png"))
			{
				s2->setPosition(ccp(POSX(183+i*25), POSX(464)));
				s2->setIsVisible(false);
				if (_peiyangLayer->getChildByTag(40+i))
				{
					_peiyangLayer->removeChildByTag(40+i,true);
				}
				_peiyangLayer->addChild(s2,0,40+i);
			}
			s2->release(); // LH0712LEAK			
		}
		
		
		

		SpriteNode * s3 = new SpriteNode();
		if (s3)
		{
			if (s3->initWithSpriteFrameName("peiyang/star.png"))
			{
				s3->setPosition(ccp(POSX(183+i*25), POSX(464)));
				s3->setIsVisible(false);
				if (_peiyangLayer->getChildByTag(50+i))
				{
					_peiyangLayer->removeChildByTag(50+i,true);
				}
				_peiyangLayer->addChild(s3,0,50+i);
			}
			s3->release(); // LH0712LEAK
		}		
	}	
	if (starLev)
	{
		for (int i =0;i<sun;i++)
		{
			_peiyangLayer->getChildByTag(30+i)->setIsVisible(true);
		}
		for (int i =sun;i<moon+sun;i++)
		{
			_peiyangLayer->getChildByTag(40+i)->setIsVisible(true);
		}
		for (int i =moon+sun;i<moon+sun+star;i++)
		{
			_peiyangLayer->getChildByTag(50+i)->setIsVisible(true);
		}
	}
	else
	{
		CCLabelTTF * _labText = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("PY23").c_str(),
			CCSizeMake(POSX(140), POSX(20)),
			CCTextAlignmentLeft,
			g_sSimHeiFont,
			POSX(16));
		_labText->setAnchorPoint(CCPointZero);
		_labText->setColor(ccc3(240,240,240));
		_labText->setPosition(ccp(POSX(170), POSX(450)));
		if (_peiyangLayer->getChildByTag(3))
		{
			_peiyangLayer->removeChildByTag(3,true);
		}
		_peiyangLayer->addChild(_labText,0,3);
	}
}

void PeiyangView::loadSelectIcon(int sigSelect,int mulSelect1,int mulSelect2,int mulSelect3)
{
	if (!_peiyangLayer)
	{
		return;
	}
	for (int i = 0;i <6;i++)
	{
		if (!_peiyangLayer->getChildByTag(TAG_SELECT+i+1))
		{
			SpriteNode * circle = new SpriteNode();
			if (circle)
			{
				if (circle->initWithSpriteFrameName("peiyang/circle.png"))
				{
					circle->setPosition(SELECTPOS[i]);
					circle->setIsVisible(false);
					if (!_peiyangLayer->getChildByTag(TAG_SELECT+i+1))
					{
						_peiyangLayer->addChild(circle,1,TAG_SELECT+i+1);
					}
				}
				circle->release(); // LH0712LEAK
			}
		}
	}
	for (int i = 6;i <9;i++)
	{
		if (!_peiyangLayer->getChildByTag(TAG_SELECT+i+1))
		{
			SpriteNode * gou = new SpriteNode();
			if (gou)
			{
				if (gou->initWithSpriteFrameName("peiyang/gou.png"))
				{
					gou->setPosition(SELECTPOS[i]);
					gou->setIsVisible(false);
					if (!_peiyangLayer->getChildByTag(TAG_SELECT+i+1))
					{
						_peiyangLayer->addChild(gou,1,TAG_SELECT+i+1);
					}
				}
				gou->release(); // LH0712LEAK
			}			
		}
	}
	// load single select icon
	if(_sigSelect[_CurScreen])
	{
		for (int i = 0;i <6;i++)
		{
			if (_peiyangLayer->getChildByTag(TAG_SELECT+i+1))
			{
				if (_peiyangLayer->getChildByTag(TAG_SELECT+i+1)->getIsVisible())
				{
					_peiyangLayer->getChildByTag(TAG_SELECT+i+1)->setIsVisible(false);
				}
			}
		}
		// 		SpriteNode * circle = new SpriteNode();
		// 		circle->initWithFile("assets/ui/figure/peiyang/circle.png");
		// 		circle->setPosition(SELECTPOS[_sigSelect[_CurScreen]-1]);
		if (_peiyangLayer->getChildByTag(TAG_SELECT+_sigSelect[_CurScreen]))
		{
			_peiyangLayer->getChildByTag(TAG_SELECT+_sigSelect[_CurScreen])->setIsVisible(true);
		}
	}

	// load multi select icon
	if(_mulSelect1[_CurScreen])
	{
		if (_peiyangLayer->getChildByTag(TAG_SELECT+7))
		{
			_peiyangLayer->getChildByTag(TAG_SELECT+7)->setIsVisible(true);
		}
	}
	else
	{
		if (_peiyangLayer->getChildByTag(TAG_SELECT+7))
		{
			_peiyangLayer->getChildByTag(TAG_SELECT+7)->setIsVisible(false);
		}
	}
	if(_mulSelect2[_CurScreen])
	{
		if (_peiyangLayer->getChildByTag(TAG_SELECT+8))
		{
			_peiyangLayer->getChildByTag(TAG_SELECT+8)->setIsVisible(true);
		}
	}
	else
	{
		if (_peiyangLayer->getChildByTag(TAG_SELECT+8))
		{
			_peiyangLayer->getChildByTag(TAG_SELECT+8)->setIsVisible(false);
		}
	}
	if(_mulSelect3[_CurScreen])
	{
		if (_peiyangLayer->getChildByTag(TAG_SELECT+9))
		{
			_peiyangLayer->getChildByTag(TAG_SELECT+9)->setIsVisible(true);
		}
	}
	else
	{
		if (_peiyangLayer->getChildByTag(TAG_SELECT+9))
		{
			_peiyangLayer->getChildByTag(TAG_SELECT+9)->setIsVisible(false);
		}
	}
}

void PeiyangView::loadTipsItems()
{
	if (!_peiyangLayer)
	{
		return;
	}
	int count = _CurScreen;
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
		char tmp[64] = {0};
		_caStrength = _cache[_CurScreen-1].washVo->strength;
		_caStamina = _cache[_CurScreen-1].washVo->stamina;
		_caIntelect = _cache[_CurScreen-1].washVo->intellect;
		int subStrength = iter->second.figureBaseInfo.strength - (_caStrength + _baseStrength);
		int subStamina = iter->second.figureBaseInfo.stamina - (_caStamina + _baseStamina);
		int subIntelect = iter->second.figureBaseInfo.intellect - (_caIntelect + _baseIntellect);
		int subSum = 0;
		bool isNotSelect = false;
		if ((!_mulSelect1[_CurScreen])&&(!_mulSelect2[_CurScreen])&&(!_mulSelect3[_CurScreen]))
		{
			subSum = subStrength + subStamina + subIntelect;
			isNotSelect = true;
		}
		else
		{
			subSum = subStrength * _mulSelect1[_CurScreen] + subStamina * _mulSelect2[_CurScreen] + subIntelect * _mulSelect3[_CurScreen];
		}
		
		if (subSum < 0)
		{
			_isRecommend[_CurScreen] = true;
		}
		else
		{
			_isRecommend[_CurScreen] = false;
		}
		if (IsWashed[_CurScreen])
		{
			// strength
			SpriteNode * s1 = new SpriteNode();
			if (s1)
			{
				if (subStrength < 0 ? s1->initWithSpriteFrameName("peiyang/up.png") : s1->initWithSpriteFrameName("peiyang/down.png"))
				{
					s1->setAnchorPoint(CCPointZero);
					s1->setPosition(ccp(POSX(305), POSX(185)));
					if (!_peiyangLayer->getChildByTag(60))
					{
						_peiyangLayer->addChild(s1,0,60);
					}
				}
				s1->release(); // LH0712LEAK
			}
			
			
			memset(tmp,0,sizeof(tmp));
			sprintf(tmp,"%d",subStrength<0?((-1)*subStrength):subStrength);
			CCLabelTTF * c1 = CCLabelTTF::labelWithString(tmp,
				CCSizeMake(POSX(60), POSX(30)),
				CCTextAlignmentCenter,
				g_sSimHeiFont,
				POSX(24));
			subStrength < 0 ? c1->setColor(ccc3(12,233,25)) : c1->setColor(ccc3(255,0,0));
			c1->setAnchorPoint(CCPointZero);
			c1->setPosition(ccp(POSX(340), POSX(188)));
			if (!_peiyangLayer->getChildByTag(61))
			{
				_peiyangLayer->addChild(c1,0,61);
			}
			// stamina
			SpriteNode * s2 = new SpriteNode();
			if (s2)
			{
				if (subStamina < 0 ? s2->initWithSpriteFrameName("peiyang/up.png") : s2->initWithSpriteFrameName("peiyang/down.png"))
				{
					s2->setAnchorPoint(CCPointZero);
					s2->setPosition(ccp(POSX(305), POSX(133)));
					if (!_peiyangLayer->getChildByTag(62))
					{
						_peiyangLayer->addChild(s2,0,62);
					}
				}
				s2->release(); // LH712LEAK
			}
			
			
			memset(tmp,0,sizeof(tmp));
			sprintf(tmp,"%d",subStamina<0?((-1)*subStamina):subStamina);
			CCLabelTTF * c2 = CCLabelTTF::labelWithString(tmp,
				CCSizeMake(POSX(60), POSX(30)),
				CCTextAlignmentCenter,
				g_sSimHeiFont,
				POSX(24));
			subStamina < 0 ? c2->setColor(ccc3(12,233,25)) : c2->setColor(ccc3(255,0,0));
			c2->setAnchorPoint(CCPointZero);
			c2->setPosition(ccp(POSX(340), POSX(136)));
			if (!_peiyangLayer->getChildByTag(63))
			{
				_peiyangLayer->addChild(c2,0,63);
			}
			// intelect
			SpriteNode * s3 = new SpriteNode();
			if (s3)
			{
				if (subIntelect < 0 ? s3->initWithSpriteFrameName("peiyang/up.png") : s3->initWithSpriteFrameName("peiyang/down.png"))
				{
					s3->setAnchorPoint(CCPointZero);
					s3->setPosition(ccp(POSX(305), POSX(78)));
					if (!_peiyangLayer->getChildByTag(64))
					{
						_peiyangLayer->addChild(s3,0,64);
					}
				}
				s3->release(); // LH712LEAK
			}
			
			
			memset(tmp,0,sizeof(tmp));
			sprintf(tmp,"%d",subIntelect<0?((-1)*subIntelect):subIntelect);
			CCLabelTTF * c3 = CCLabelTTF::labelWithString(tmp,
				CCSizeMake(POSX(60), POSX(30)),
				CCTextAlignmentCenter,
				g_sSimHeiFont,
				POSX(24));
			subIntelect < 0 ? c3->setColor(ccc3(12,233,25)) : c3->setColor(ccc3(255,0,0));
			c3->setAnchorPoint(CCPointZero);
			c3->setPosition(ccp(POSX(340), POSX(81)));
			if (!_peiyangLayer->getChildByTag(65))
			{
				_peiyangLayer->addChild(c3,0,65);
			}
			// recommend
			SpriteNode * s4 = new SpriteNode();
			if (s4)
			{
				if (subSum < 0 ? s4->initWithSpriteFrameName("peiyang/gou1.png") : s4->initWithSpriteFrameName("peiyang/cha.png"))
				{
					s4->setPosition(ccp(POSX(175), POSX(42)));
					if (!_peiyangLayer->getChildByTag(66))
					{
						_peiyangLayer->addChild(s4,0,66);
					}
				}

				if (isNotSelect)
				{
					s4->setIsVisible(false);
				}

				s4->release(); // LH712LEAK
			}
			
			
			std::string sRecom = subSum < 0 ? ValuesUtil::Instance()->getString("PY11") : ValuesUtil::Instance()->getString("PY12");
			CCLabelTTF * c4 = CCLabelTTF::labelWithString(sRecom.c_str(),
				CCSizeMake(POSX(60), POSX(20)),
				CCTextAlignmentCenter,
				g_sSimHeiFont,
				POSX(20));
			subSum < 0 ? c4->setColor(ccc3(12,233,25)) : c4->setColor(ccc3(255,0,0));
			c4->setPosition(ccp(POSX(225), POSX(42)));
			if (isNotSelect)
			{
				c4->setIsVisible(false);
			}
			if (!_peiyangLayer->getChildByTag(67))
			{
				_peiyangLayer->addChild(c4,0,67);
			}
		}
		else
		{
			//remove
			for (int i = 60;i<68;i++)
			{
				if (_peiyangLayer->getChildByTag(i))
				{
					_peiyangLayer->removeChildByTag(i,true);
				}
			}

		}
	}
}

int PeiyangView::calcPractice()
{
	if (_practiceNeed > RoleManage::Instance()->_accountInfo._practice)
	{
		return -1;
	}
	return 0;
}

int PeiyangView::calcGold(int type)
{
	switch(type)
	{
	case 1:
		_goldNeed = 2;
		break;
	case 2:
		_goldNeed = _price;
		break;
	case 3:
		_goldNeed = 70;
		break;
	default:
		break;
	}
	if (_goldNeed > RoleManage::Instance()->_accountInfo._gold)
	{
		return -1;
	}
	return _goldNeed;
}

void PeiyangView::setPrice(int price)
{
	_price = price;
}

void PeiyangView::clickWashHandler(CCObject * pSender)
{
	// new hand
	if (NewhandManager::Instance()->getNewHandStateByType(LevLimitConst::Limit_Peiyang) == NewhandManager::Flag_New)
	{
		NewhandManager::Instance()->touchNextEvent(801);
	}

	// add limit conditions
	switch(_sigSelect[_CurScreen])
	{
	case 1:
		_washType = 2;
		_useItem = 1;
		break;
	case 2:
		_washType = 3;
		_useItem = 1;
		break;
	case 3:
		_washType = 0;
		break;
	case 4:
		_washType = 1;
		_washButton->setIsTouchEnabled(false);
		break;
	case 5:
		_washType = 2;
		break;
	case 6:
		_washType = 3;
		break;
	default:
		_washType = 0;
		break;
	}

	Message * msg = Message::Instance(); // LH0713
	if ((0 == _washType)&&(-1 == calcPractice()))
	{
		msg->show(ValuesUtil::Instance()->getString("PY18"),ccc3(222,23,42),1);
		return;
	}
	else if ((1 == _washType)&&(calcGold(_washType) > RoleManage::Instance()->_accountInfo._gold))
	{
		msg->show(ValuesUtil::Instance()->getString("PY19"),ccc3(222,23,42),1);
		return;
	}
	else if (2 == _washType)
	{
		if ((_sigSelect[_CurScreen] == 5)&&((RoleManage::Instance()->_accountInfo._vipLev < 3)/*||(!RoleManage::Instance()->_accountInfo._trialVip)*/))
		{
			msg->show(ValuesUtil::Instance()->getString("PY29"),ccc3(222,23,42),1);
			return;
		}
		if (calcGold(_washType) > RoleManage::Instance()->_accountInfo._gold)
		{
			msg->show(ValuesUtil::Instance()->getString("PY19"),ccc3(222,23,42),1);
			return;
		}
	}
	else if (3 == _washType)
	{
		if ((_sigSelect[_CurScreen] == 6)&&(RoleManage::Instance()->_accountInfo._vipLev < 7))
		{
			msg->show(ValuesUtil::Instance()->getString("PY30"),ccc3(222,23,42),1);
			return;
		}
		if (calcGold(_washType) > RoleManage::Instance()->_accountInfo._gold)
		{
			msg->show(ValuesUtil::Instance()->getString("PY19"),ccc3(222,23,42),1);
			return;
		}
	}
	//UseItemID = 52,53 ?
	//add code here
	sendWashRequest(_curAccount,_washType,_useItem); // should be modified depends
}

void PeiyangView::showWashResult()
{
	_washButton->setIsTouchEnabled(true);

	IsWashed[_CurScreen] = true;
	_washText->setIsVisible(false);
	_washButton->setIsVisible(false);
	_washButton->setIsTouchEnabled(false);
	_acceptText->setIsVisible(true);
	_acceptButton->setIsVisible(true);
	_acceptButton->setIsTouchEnabled(true);
	_cancelText->setIsVisible(true);
	_cancelButton->setIsVisible(true);
	_cancelButton->setIsTouchEnabled(true);

	loadItems(true);
}

void PeiyangView::clickRebornHandler(CCObject * pSender)
{

	//std::map<int ,PlayerInfoVo>* list = RoleManage::Instance()->mercList();
	//std::map<int, PlayerInfoVo>::iterator iter = list->begin();
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* list = RoleManage::Instance()->mercListEx();  // LH20121019listorder
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>::iterator iter = list->begin();

	while ((iter->first.id != _curAccount)&&(iter!=list->end()))
	{
		++iter;
	}

	_starLev = iter->second.figureBaseInfo.rebornNum;
	_reBornNeedLev = 51 + _starLev * 5;

	if ((iter->second.playerBaseInfo._lev < _reBornNeedLev))
	{
		char path[128] = {0};
		sprintf(path,ValuesUtil::Instance()->getString("PY25").c_str(),_reBornNeedLev);
		Message::Instance()->show(path,ccc3(233,12,25),2.0f);
		return;
	}
	else if (iter->second.playerBaseInfo.adLv != 0)
	{
		Message::Instance()->show(ValuesUtil::Instance()->getString("PY32").c_str(),ccc3(233,12,25),2.0f);
		return;
	}
	
	sendRebornRequest(_curAccount);
}

void PeiyangView::clickAcceptHandler(CCObject * pSender)
{
	// new hand
	if (NewhandManager::Instance()->getNewHandStateByType(LevLimitConst::Limit_Peiyang) == NewhandManager::Flag_New)
	{
		NewhandManager::Instance()->setNewHandStateByType(LevLimitConst::Limit_Peiyang , NewhandManager::Flag_Done);
		NewhandManager::Instance()->touchNextEvent(802);
	}
	

	IsWashed[_CurScreen] = false;
	_washText->setIsVisible(true);
	_washButton->setIsVisible(true);
	_washButton->setIsTouchEnabled(true);
	_acceptText->setIsVisible(false);
	_acceptButton->setIsVisible(false);
	_acceptButton->setIsTouchEnabled(false);
	_cancelText->setIsVisible(false);
	_cancelButton->setIsVisible(false);
	_cancelButton->setIsTouchEnabled(false);
	loadItems(false);
	// send save request
	// property changed
	sendSaveRequest(_curAccount);
}


void PeiyangView::clickCancelHandler(CCObject * pSender)
{
	IsWashed[_CurScreen] = false;
	_washText->setIsVisible(true);
	_washButton->setIsVisible(true);
	_washButton->setIsTouchEnabled(true);
	_acceptText->setIsVisible(false);
	_acceptButton->setIsVisible(false);
	_acceptButton->setIsTouchEnabled(false);
	_cancelText->setIsVisible(false);
	_cancelButton->setIsVisible(false);
	_cancelButton->setIsTouchEnabled(false);
	loadItems(false);
}

void PeiyangView::sendRebornRequest(uint32 figureID)
{
	if (!_figureMediator)
	{
		return;
	}
	_figureMediator->sendRebornRequest(figureID);
}

void PeiyangView::sendWashRequest(uint32 figureID,uint8 type,uint8 useItem)
{
	if (!_figureMediator)
	{
		return;
	}
	_figureMediator->sendWashRequest(figureID,type,useItem);
}

void PeiyangView::sendSaveRequest(uint32 figureID)
{
	if (!_figureMediator)
	{
		return;
	}
	_figureMediator->sendSaveRequest(figureID);
}

void PeiyangView::getPrice(int type)
{
	if (!_figureMediator)
	{
		return;
	}
	_figureMediator->sendPriceRequest(type);
}

void PeiyangView::updatePrice(int price)
{
	_price = price;
	if (_peiyangLayer)
	{
		char path[32] = {0};
		sprintf(path,ValuesUtil::Instance()->getString("PY7").c_str(),price);
		CCLabelTTF * pPriceLab = (CCLabelTTF *)_peiyangLayer->getChildByTag(TAG_Price_Labtxt);
		if (pPriceLab)
		{
			pPriceLab->setString(path);
		}
	}
}

void PeiyangView::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer_Peiyang, true);
}

bool PeiyangView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	this->setIsTouchEnabled(true);
	CCPoint locationInView = pTouch->locationInView(pTouch->view());
	CCPoint preTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
	CCLog("Peiyang:touch position(%f,%f)",preTouchPoint.x,preTouchPoint.y);
	CCRect rect;
	if (!_peiyangLayer)
	{
		return false;
	}
	for (int i = 0;i<sizeof(SELECTPOS);i++)
	{
		CCNode * s = _peiyangLayer->getChildByTag(TAG_SELECT+i+1);
		if (!s)
		{
			return false;
		}
		CCPoint p = getScreenPos(s);
		CCLog("Peiyang:screen pos is(%f,%f)",p.x,p.y);
		rect = CCRect(p.x-POSX(16),p.y-POSX(16), POSX(35), POSX(35));
		if (CCRect::CCRectContainsPoint(rect,preTouchPoint))
		{
			if ((i>=2)&&(i<6)) // 0£¬1 will open later,not now
			{
				_sigSelect[_CurScreen] = i+1;

				if (( i==4 )&&(RoleManage::Instance()->accountInfo()->_vipLev < 3))
				{
					_sigSelect[_CurScreen] = 0;
				}
				if (( i==5 )&&(RoleManage::Instance()->accountInfo()->_vipLev < 7))
				{
					_sigSelect[_CurScreen] = 0;
				}
			}
			bool bVar;
			switch (i)
			{
			case 6:
				bVar = _mulSelect1[_CurScreen];
				_mulSelect1[_CurScreen] = bVar ? false : true;
				break;
			case 7:
				bVar = _mulSelect2[_CurScreen];
				_mulSelect2[_CurScreen] = bVar ? false : true;
				break;
			case 8:
				bVar = _mulSelect3[_CurScreen];
				_mulSelect3[_CurScreen] = bVar ? false : true;
				break;
			default:
				break;
			}
			loadSelectIcon(_sigSelect[_CurScreen],_mulSelect1[_CurScreen],_mulSelect2[_CurScreen],_mulSelect3[_CurScreen]);
			return true;
		}	
	}
	return false;
}

void PeiyangView::updatePractice()
{
	if (_peiyangLayer)
	{
		CCLabelTTF * pTxt = (CCLabelTTF *)_peiyangLayer->getChildByTag(2);
		if (pTxt)
		{
			std::string str = ""+RoleManage::Instance()->accountInfo()->practice();
			pTxt->setString(str.c_str());
		}		
	}
}

void PeiyangView::updateGold()
{
	if (_peiyangLayer)
	{
		CCLabelTTF * pTxt = (CCLabelTTF *)_peiyangLayer->getChildByTag(4);
		if (pTxt)
		{
			std::string str = ""+RoleManage::Instance()->accountInfo()->gold();
			pTxt->setString(str.c_str());
		}		
	}
}

void PeiyangView::removeDataObjectChild()
{
	ViewManager::getInstance()->_peiyangView = 0;

	if (ViewManager::getInstance()->figureView
		&& ViewManager::getInstance()->figureView->_figureV
		&& ViewManager::getInstance()->figureView->_figureV->_peiyangV)
	{
		ViewManager::getInstance()->figureView->_figureV->_peiyangV = 0;
	}
}