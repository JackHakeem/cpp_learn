#include "ZXDuiView.h"
#include "manager/LangManager.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "CCUIBackground.h"
#include "manager/TouchLayerEnum.h"
#include "manager/LayerManager.h"
#include "control/AppFacade.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"
#include "CCUIBackground.h"
#include "manager/ViewManager.h"
#include "Confirm.h"
#include "view/zx/ZXMediator.h"
#include "XHView.h"
#include "ZXView.h"
#include "socket/command/c46/CCMD46C.h"

ZXDuiView::ZXDuiView()
{
	_pContainer = 0;
	_pListView = 0;
}

ZXDuiView::~ZXDuiView()
{}

bool ZXDuiView::init()
{
	if (!LayerNode::init())
	{
		return false;
	}

	{
		//
		_pContainer = new LayerNode();
		_pContainer->init();
		_pContainer->setPosition(POS(ccp(0, 0), ScaleUtil::CENTER));
		this->addChild(_pContainer, 1);
		_pContainer->release();
	}

	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	CCUIBackground* _bg0 = new CCUIBackground();
	_bg0->initWithSpriteFrame("ui2.png", CCPointZero,CCPointZero,screenSize);
	this->addChild(_bg0, 0);
	_bg0->release();


	{
		CCUIBackground* _bg2 = new CCUIBackground();
		_bg2->initWithSpriteFrame("popuibg/bg1.png", ccp(POSX(96.0f), POSX(33.0f)), ccp(0,0), CCSizeMake(POSX(768), POSX(507)));
		_pContainer->addChild(_bg2, 1);
		_bg2->release();
	}
	{
		CCUIBackground* _bg2 = new CCUIBackground();
		_bg2->initWithSpriteFrame("popuibg/bg2.png", ccp(POSX(108.0f), POSX(48.0f)), ccp(0,0), CCSizeMake(POSX(744), POSX(438)));
		_pContainer->addChild(_bg2, 2);
		_bg2->release();
	}

	//X
	{
		CCSprite *pCloseNormalSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_normal.png");
		CCSprite *pClosePressedSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_pressed.png");
		CCMenuItemSprite *_btnX = CCMenuItemSprite::itemFromNormalSprite(
			pCloseNormalSprite,
			pClosePressedSprite,
			this, 
			menu_selector(ZXDuiView::clickClose) );
		_btnX->setPosition(ccp(screenSize.width-_btnX->getContentSize().width/2, 
			screenSize.height-_btnX->getContentSize().height/2));


		CCMenu *buttonMenu = new CCMenu();
		buttonMenu->init();
		buttonMenu->addChild(_btnX, 0, 0);
		buttonMenu->setPosition(ccp(0, 0));
		buttonMenu->setTouchLayer(TLE::TipsLayer_zx-1);
		this->addChild(buttonMenu, 5);
		buttonMenu->release();
	}
	{//返回占星面板
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this, 
			menu_selector(ZXDuiView::clickBackZX) );
		_btn->setPosition(ccp(POSX(780), POSX(640-549)));


		CCMenu *buttonMenu = new CCMenu();
		buttonMenu->init();
		buttonMenu->addChild(_btn, 0, 0);
		buttonMenu->setPosition(ccp(0, 0));
		buttonMenu->setTouchLayer(TLE::TipsLayer_zx-10);
		_pContainer->addChild(buttonMenu, 5);
		buttonMenu->release();

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString( "ZX021" ).c_str(), CCSizeMake(POSX(200), POSX(28)), CCTextAlignmentCenter, "Arial", POSX(24));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(251, 216, 0));
	}	
	//title
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString( "ZX014" ).c_str(), CCSizeMake(POSX(200), POSX(50)), CCTextAlignmentCenter, "Arial", POSX(40));
		pLabel->setPosition(ccp(POSX(476), POSX(640-128)));
		_pContainer->addChild(pLabel, 3);
		pLabel->setColor(ccc3(247, 191, 23));
	}
	//积分
	{	
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString( "ZX010" ).c_str(), CCSizeMake(POSX(100), POSX(28)), CCTextAlignmentLeft, "Arial", POSX(24));
		pLabel->setAnchorPoint(ccp(0,0));
		pLabel->setPosition(ccp(POSX(141), POSX(640-569)));
		_pContainer->addChild(pLabel, 5);
		pLabel->setColor(ccc3(255, 217, 27));
	}
	//
	std::map<int8, XHConfVo>& dic = XHConfManager::Instance()->_XHConfDic;
	for (std::map<int8, XHConfVo>::iterator it = dic.begin(); it != dic.end(); it++)
	{
		if (it->second.score > 0)
			_dataConf.push_back(it->second);
	}
	
	//
	{
		_pListView = CCUIListView::listViewWithCCRect(CCRectMake(POSX(118.0f),
			POSX(48.0f+70.0f),
			POSX(724),
			POSX(360)), 
			false);
		_pListView->setAnchorPoint(CCPointZero);
		//_pListView->setSpacingVertical(POSX(10));
		//_pListView->setHeaderSize(POSX(10));
		//_pListView->setFooterSize(POSX(10));
		_pListView->setAdapter(this);
		_pListView->setIsRelativeAnchorPoint(true);
		_pListView->setWorldSpaceLeftBottomPoint(ccp(this->getPosition().x + _pContainer->getPosition().x + _pListView->getPosition().x,
			this->getPosition().y + _pContainer->getPosition().y + _pListView->getPosition().y));
		_pListView->m_pri = TLE::TipsLayer_zx-1;
		_pContainer->addChild(_pListView, 6);
		_pListView->release();
	}
	return true;
}

void ZXDuiView::clickBackZX(CCObject* pSender)
{
	if (this->getParent())
	{
		ZXMediator * pZXMediator = (ZXMediator *)g_pFacade->retrieveMediator(AppFacade_ZX);
		if (pZXMediator)
		{
			ZXView* pZXView = (ZXView*)LayerManager::intervalLayer->getChildByTag( IntervalLayer::IntervalLayerTAG_ZX);
			if (pZXView)
				pZXView->setIsVisible(true);
		}	

		this->removeFromParentAndCleanup(true);
	}
}

int ZXDuiView::getCount()
{
	return ceil(_dataConf.size()/2.0f);
}

LayerNode * ZXDuiView::getView( int position )
{
	return createListItem(position*2, position*2+1);
}


LayerNode * ZXDuiView::createListItem(int indexL, int indexR)
{

	int datasize = _dataConf.size();
	if (indexL >= datasize)
	{
		return 0;
	}

	LayerNode *pContainer = new LayerNode();
	if(!pContainer || !pContainer->init())
	{
		return NULL;
	}
	pContainer->setContentSize(CCSizeMake(POSX(724), POSX(120)));
	pContainer->setvisibleSize(CCSizeMake(POSX(724), POSX(120)));

	CCMenu *buttonMenu = new CCMenu();
	buttonMenu->init();
	buttonMenu->setPosition(ccp(POSX(0), POSX(0)));
	buttonMenu->setTouchLayer(TLE::TipsLayer_zx-1);
	pContainer->addChild(buttonMenu, 5);	
	buttonMenu->release();

	//
	{
		CCUIBackground* bg = new CCUIBackground();
		bg->initWithSpriteFrame("popuibg/bg2.png", ccp(POSX(0), POSX(5)), ccp(0,0), CCSizeMake(POSX(714/2-5), POSX(110)));
		pContainer->addChild(bg, 0);
		bg->release();
	}
	//
	{
		SpriteNode* sp = new SpriteNode();
		sp->initWithFile("assets/ui/zx/cellbg.png");
		pContainer->addChild(sp, 1);
		sp->release();
		sp->setPosition(ccp(POSX(46), POSX(55)));
	}
	//
	{
		char picpath[50];
		sprintf(picpath, "assets/ui/zx/xh%02d.png", _dataConf[indexL].type);
		SpriteNode* pPic = new SpriteNode();
		pPic->initWithFile(picpath);
		pContainer->addChild(pPic, 2);
		pPic->release();	
		pPic->setPosition(ccp(POSX(46), POSX(55)));
	}
	//name
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(_dataConf[indexL].name.c_str(), CCSizeMake(POSX(200), POSX(28)), CCTextAlignmentLeft, "Arial", POSX(24));
		pLabel->setPosition(ccp(POSX(90), POSX(70)));
		pLabel->setAnchorPoint(ccp(0, 0));
		pContainer->addChild(pLabel, 2);
		switch (_dataConf[indexL].color)
		{
		case 0: pLabel->setColor(ccc3(192, 192, 192)); break;//hui
		case 1: pLabel->setColor(ccc3(33, 255, 33)); break;//green
		case 2: pLabel->setColor(ccc3(74, 74, 255)); break;//blue
		case 3: pLabel->setColor(ccc3(202, 60, 177)); break;//purple
		case 4: pLabel->setColor(ccc3(254, 147, 39)); break;//orange
		case 5: pLabel->setColor(ccc3(247, 51, 40)); break;//red
		default:
			break;
		}
	}
	//buy btn
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this, 
			menu_selector(ZXDuiView::clickBuy) );
		_btn->setPosition(ccp(POSX(280), POSX(35)));
		_btn->setTag(_dataConf[indexL].type);
		_btn->setScale(0.8f);

		buttonMenu->addChild(_btn, 0);

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString( "ZX018" ).c_str(), CCSizeMake(POSX(100), POSX(28)), CCTextAlignmentCenter, "Arial", POSX(24));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(251, 216, 0));
		pLabel->setScale(1.2f);
	}
	//积分
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString( "ZX017" ).c_str(), CCSizeMake(POSX(200), POSX(28)), CCTextAlignmentLeft, "Arial", POSX(24));
		pLabel->setPosition(ccp(POSX(290), POSX(70)));
		pLabel->setAnchorPoint(ccp(0, 0));
		pContainer->addChild(pLabel, 2);
		pLabel->setColor(ccc3(251, 216, 255));
	}
	//need score
	{
		char numstr[10];
		sprintf(numstr, "%d", _dataConf[indexL].score);
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(numstr, CCSizeMake(POSX(100), POSX(28)), CCTextAlignmentRight, "Arial", POSX(20));
		pLabel->setPosition(ccp(POSX(190), POSX(70)));
		pLabel->setAnchorPoint(ccp(0, 0));
		pContainer->addChild(pLabel, 2);
		pLabel->setColor(ccc3(255, 255, 255));
	}
	//intro
	{
		char introstr[30];
		char nameeffect[30];
		sprintf(nameeffect, "ZXEFFECT0%02d", _dataConf[indexL].effecttype);
		if (_dataConf[indexR].lv[0] < 1.0f)
			sprintf(introstr, "%s+%d%%", ValuesUtil::Instance()->getString( nameeffect ).c_str(), (int)(_dataConf[indexL].lv[0]*100));
		else
			sprintf(introstr, "%s+%d", ValuesUtil::Instance()->getString( nameeffect ).c_str(), (int)(_dataConf[indexL].lv[0]));

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(introstr, CCSizeMake(POSX(120), POSX(28)), CCTextAlignmentLeft, "Arial", POSX(20));
		pLabel->setPosition(ccp(POSX(90), POSX(20)));
		pLabel->setAnchorPoint(ccp(0, 0));
		pContainer->addChild(pLabel, 2);
		pLabel->setColor(ccc3(255, 255, 255));
	}

	/*------------------------------------------second----------------------------------------------------*/
	if (indexR >= datasize)
	{
		return pContainer;
	}
	//
	{
		CCUIBackground* bg = new CCUIBackground();
		bg->initWithSpriteFrame("popuibg/bg2.png", ccp(POSX(714/2+10), POSX(5)), ccp(0,0), CCSizeMake(POSX(714/2-5), POSX(110)));
		pContainer->addChild(bg, 0);
		bg->release();
	}
	//
	{
		SpriteNode* sp = new SpriteNode();
		sp->initWithFile("assets/ui/zx/cellbg.png");
		pContainer->addChild(sp, 1);
		sp->release();
		sp->setPosition(ccp(POSX(46 + 714/2+10), POSX(55)));
	}
	
	//
	{
		char picpath[50];
		sprintf(picpath, "assets/ui/zx/xh%02d.png", _dataConf[indexR].type);
		SpriteNode* pPic = new SpriteNode();
		pPic->initWithFile(picpath);
		pContainer->addChild(pPic, 2);
		pPic->release();	
		pPic->setPosition(ccp(POSX(46 + 714/2+10), POSX(55)));
	}
	//name
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(_dataConf[indexR].name.c_str(), CCSizeMake(POSX(200), POSX(28)), CCTextAlignmentLeft, "Arial", POSX(24));
		pLabel->setPosition(ccp(POSX(90 + 714/2+10), POSX(70)));
		pLabel->setAnchorPoint(ccp(0, 0));
		pContainer->addChild(pLabel, 2);
		switch (_dataConf[indexL].color)
		{
		case 0: pLabel->setColor(ccc3(192, 192, 192)); break;//hui
		case 1: pLabel->setColor(ccc3(33, 255, 33)); break;//green
		case 2: pLabel->setColor(ccc3(74, 74, 255)); break;//blue
		case 3: pLabel->setColor(ccc3(202, 60, 177)); break;//purple
		case 4: pLabel->setColor(ccc3(254, 147, 39)); break;//orange
		case 5: pLabel->setColor(ccc3(247, 51, 40)); break;//red
		default:
			break;
		}
	}
	//buy btn
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this, 
			menu_selector(ZXDuiView::clickBuy) );
		_btn->setPosition(ccp(POSX(280 + 714/2+10), POSX(35)));
		_btn->setTag(_dataConf[indexR].type);
		_btn->setScale(0.8f);

		buttonMenu->addChild(_btn, 0);

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString( "ZX018" ).c_str(), CCSizeMake(POSX(100), POSX(28)), CCTextAlignmentCenter, "Arial", POSX(24));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(251, 216, 0));
		pLabel->setScale(1.2f);
	}
	//积分
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString( "ZX017" ).c_str(), CCSizeMake(POSX(200), POSX(28)), CCTextAlignmentLeft, "Arial", POSX(24));
		pLabel->setPosition(ccp(POSX(290 + 714/2+10), POSX(70)));
		pLabel->setAnchorPoint(ccp(0, 0));
		pContainer->addChild(pLabel, 2);
		pLabel->setColor(ccc3(251, 216, 255));
	}
	//
	ZXMediator * pZXMediator = (ZXMediator *)g_pFacade->retrieveMediator(AppFacade_ZX);
	if (pZXMediator)
		updateScore(pZXMediator->m_iScore);
	//need score
	{
		char numstr[10];
		sprintf(numstr, "%d", _dataConf[indexR].score);
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(numstr, CCSizeMake(POSX(100), POSX(28)), CCTextAlignmentRight, "Arial", POSX(20));
		pLabel->setPosition(ccp(POSX(190 + 714/2+10), POSX(70)));
		pLabel->setAnchorPoint(ccp(0, 0));
		pContainer->addChild(pLabel, 2);
		pLabel->setColor(ccc3(255, 255, 255));
	}
	//intro
	{
		char introstr[30];
		char nameeffect[30];
		sprintf(nameeffect, "ZXEFFECT0%02d", _dataConf[indexR].effecttype);
		if (_dataConf[indexR].lv[0] < 1.0f)
			sprintf(introstr, "%s+%d%%", ValuesUtil::Instance()->getString( nameeffect ).c_str(), (int)(_dataConf[indexR].lv[0]*100));
		else
			sprintf(introstr, "%s+%d", ValuesUtil::Instance()->getString( nameeffect ).c_str(), (int)(_dataConf[indexR].lv[0]));

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(introstr, CCSizeMake(POSX(120), POSX(28)), CCTextAlignmentLeft, "Arial", POSX(20));
		pLabel->setPosition(ccp(POSX(90 + 714/2+10), POSX(20)));
		pLabel->setAnchorPoint(ccp(0, 0));
		pContainer->addChild(pLabel, 2);
		pLabel->setColor(ccc3(255, 255, 255));
	}
    return pContainer;
}


void ZXDuiView::clickClose(CCObject* pSender)
{
	if (this->getParent())
	{
		ZXMediator * pZXMediator = (ZXMediator *)g_pFacade->retrieveMediator(AppFacade_ZX);
		if (pZXMediator)
		{
			pZXMediator->m_pXHView->clickClose(0);
			pZXMediator->m_pXHView = 0;
		}	
	}
}

void ZXDuiView::clickBuy(CCObject* pSender)
{
	int tag = ((CCNode*)pSender)->getTag();

	CCMD46C cmd;
	cmd.a_xhtype = tag;
	GameServerSocket::getInstance()->sendMessage( &cmd );
}

void ZXDuiView::updateScore(int32 val)
{
	//score
	CCLabelTTF* pLabel = (CCLabelTTF*)_pContainer->getChildByTag(1000);
	if (!pLabel)
	{
		char numstr[20]; 
		sprintf(numstr, "%d", val);
		pLabel = CCLabelTTF::labelWithString(numstr, CCSizeMake(POSX(100), POSX(28)), CCTextAlignmentLeft, "Arial", POSX(24));
		pLabel->setAnchorPoint(ccp(0,0));
		pLabel->setPosition(ccp(POSX(141+90), POSX(640-569)));
		_pContainer->addChild(pLabel, 5, 1000);
		pLabel->setColor(ccc3(255, 255, 255));
	}
	else
	{
		char numstr[20]; 
		sprintf(numstr, "%d", val);
		pLabel->setString(numstr);
	}
}