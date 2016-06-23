#include "MineView.h"
#include "MinePanel.h"
#include "MineBg.h"
#include "model/silverMine/SilverConst.h"
#include "MineOpt.h"
#include "MineInfo.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "manager/LayerManager.h"
#include "MineRank.h"
#include "manager/ViewManager.h"
#include "view/chat/components/ChatBtnMenu.h"

MineView::MineView()
{
	_minePanel = 0;
	_pContainer = 0;
	_bgLayer = 0;
	_tokenType = -1;
	_btnReturn = 0;
	m_silver_forRank = 0;
}

MineView::~MineView()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/silvermine/res_silvermine1.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/silvermine/res_silvermine2.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/silvermine/res_silvermine3.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/silvermine/res_silvermine_icon5.plist");
}

bool MineView::init()
{
	if (!LayerNode::init())
		return false;

	CCTexture2D::setDefaultAlphaPixelFormat( kCCTexture2DPixelFormat_RGBA8888 );
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/silvermine/res_silvermine1.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/silvermine/res_silvermine2.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/silvermine/res_silvermine3.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/silvermine/res_silvermine_icon5.plist");
	CCTexture2D::setDefaultAlphaPixelFormat( kCCTexture2DPixelFormat_Default );

	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	//
	_pContainer = new LayerNode();
	_pContainer->init();
	this->addChild(_pContainer, 0);
	_pContainer->release();
	//
	/*_bgLayer = new LayerNode();
	_bgLayer->init();
	_pContainer->addChild(_bgLayer, Z_bgLayer, TAG_bgLayer);*/
	//
	_mineBg = new MineBg();
	_mineBg->init();
	_pContainer->addChild(_mineBg, Z_mineBg, TAG_mineBg);
	_mineBg->release();
	//
	_minePanel = new MinePanel();
	_minePanel->init(_mineBg, this);
	_pContainer->addChild(_minePanel, Z_minePanel, TAG_minePanel);
	_minePanel->release();
	//
	_mineOpt = new MineOpt();
	_mineOpt->init(this);
	_pContainer->addChild(_mineOpt, Z_mineOpt, TAG_mineOpt);
	_mineOpt->release();
	//
	_mineInfo = new MineInfo();
	_mineInfo->init(this);
	_pContainer->addChild(_mineInfo, Z_mineInfo, TAG_mineInfo);
	_mineInfo->release();
	//

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//title
	{
		SpriteNode* sp = new SpriteNode();
		sp->initWithSpriteFrameName("title.png");
		sp->setPosition(ccp(POSX(170), winSize.height-POSX(50)));
		_pContainer->addChild(sp, Z_title);
		sp->release();
	}	
	//
	//btn
	{
		CCSprite* p1 = CCSprite::spriteWithSpriteFrameName("mf_btnReturn_0.png");
		CCSprite* p2 = CCSprite::spriteWithSpriteFrameName("mf_btnReturn_1.png");
		CCSprite* p3 = CCSprite::spriteWithSpriteFrameName("mf_btnReturn_1.png");
		_btnReturn = CCMenuItemImage::itemFromNormalSprite(
			p1, 
			p2, 
			p3, 
			this, 
			menu_selector(MineView::onClose) );

		_btnReturn->setPosition(ccp(screenSize.width-_btnReturn->getContentSize().width/2, 
		screenSize.height-_btnReturn->getContentSize().height/2));

		_btnReturn->setTag(0);
		//_btnReturn->setScale(0.5f);

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btnReturn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::WindowLayer_guild-1);
		this->addChild(buttonMenu, 0, 10);	
	}

	loadChatMenu();
	return true;
}

// 更新我所挖银币数量 
void MineView::updateSilver(int silver)
{	
	m_silver_forRank = silver;
	MineRank* oldp = (MineRank*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_guild_silverMineRank);
	if (oldp)
	{
		oldp->updateSilver(silver);
	}
}

// 更新攻击加成 
void MineView::updateAttPlus(int plus)
{
	_mineInfo->updateAttPlus(plus);
}
		
// 更新防御加成
void MineView::updateDefPlus(int plus)
{
	_mineInfo->updateDefPlus(plus);
}
	

// 更新排行旁
void MineView::updateRank(std::list<SCMD367Node>& arr)
{
	m_arr.clear();
	m_arr = arr;

	MineRank* oldp = (MineRank*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_guild_silverMineRank);
	if (oldp)
	{
		oldp->updateRank(m_arr);
	}
}

int MineView::getMineIDByCamp(int campID)
{
	int mineID = -1;
	switch(campID){
	case SilverConst::CAMP_ZERO:
			mineID = 0;
			break;
	case SilverConst::CAMP_ONE:
			mineID = 27;
			break;
	case SilverConst::CAMP_TWO:
			mineID = 30;
			break;
	}
	return mineID;
}	

void MineView::onClose(CCObject* pSender)
{
	dispatchEvent(SilverConst::EXIT_MINE_VIEW, 0);
}

void MineView::updateMinePanel(std::list<SilverMineVo>& mines)
{
	_minePanel->updateMinePanel(mines);
}

/*更新所在矿区信息*/
void MineView::updateMineInfo(int mineId, int onMine)
{
//	debug("ID:",mineId, " online:",onMine);
 	_mineOpt->updateMineInfo(mineId, onMine);
}

/*更新挖矿CD*/
void MineView::updateDigCD(uint digCD, bool inCD)
{
	_mineInfo->updateDigCD(digCD, inCD);
}

/*设置挖矿btn*/
void MineView::setDigEnable(bool value)
{
	if( whichCampHome(getcurMineID()) == SilverConst::NON_CAMP )
	{
		_mineOpt->setDigBtnEnable(value);
	}
}

int MineView::whichCampHome(int mineID)
{
	int campID = SilverConst::NON_CAMP;
	switch(mineID){
		case 0:
			campID = SilverConst::CAMP_ZERO;
			break;
		case 27:
			campID = SilverConst::CAMP_ONE;
			break;
		case 30:
			campID = SilverConst::CAMP_TWO;
			break;
	}
	return campID;
}	

int MineView::getcurCampID()
{
	return _minePanel->getcurCampID();
}

// 更新历练奖励显示的tips
void MineView::updatePracInsTips(int cost)
{
	//_mineInfo.updatePrasInsTips(cost);
}

void MineView::setMyCamp(int campID)
{
	if(_minePanel && _minePanel->getcurCampID() != campID){
		_minePanel->setMyCamp(campID);
	}
}
		
// 设置自己所在矿ID
void MineView::setMyMine(int mineID)
{
	if(_minePanel)
		_minePanel->setMyMine(mineID);
}

int MineView::getTokenType()
{
	return _tokenType;
}

/*更新行动CD*/
void MineView::updateMoveCD(uint moveCD, bool inCD)
{
	_mineInfo->updateMoveCD(moveCD, inCD); 
}
		
void MineView::setTokenType(int value)
{
	_tokenType = value;
	if(_tokenType == -1){
		setMyMine(getcurMineID());
	}
	else{
		_minePanel->useToken(_tokenType);
	}
}

int MineView::getcurMineID()
{
	return _minePanel->getcurMineID();
}


void MineView::loadChatMenu()
{
	//CCSize _winSize = CCDirector::sharedDirector()->getWinSize();
	//// chat menu
	//CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("chat/chat_1.png");
	//CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("chat/chat_1.png");
	//CCSprite *pSelectedSprite = CCSprite::spriteWithSpriteFrameName("chat/chat_1.png");
	//CCMenuItemSprite *pChatMenuImg = CCMenuItemSprite::itemFromNormalSprite(
	//	pNormalSprite,
	//	pPressedSprite,
	//	pSelectedSprite,
	//	this,
	//	menu_selector(MineView::onClickChat));

	//CCMenu * pChatMenu = CCMenu::menuWithItem(pChatMenuImg);
	//pChatMenu->setTouchLayer(TLE::SceneUILayer_MainNavigateTAG_menubtn);
	////pChatMenu->setTag(TAG_Chat_Menu);
	//pChatMenu->setPosition(ccp(POSX(45) , POSX(45)));
	//this->addChild(pChatMenu, 100);

	//_pContainer->setIsVisible(false);


	//{
	//	CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("chat/chat_1.png");
	//	CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("chat/chat_1.png");
	//	CCMenuItemSprite *_button = CCMenuItemSprite::itemFromNormalSprite(
	//		pNormalSprite,
	//		pPressedSprite,
	//		this,
	//		menu_selector(MineView::onClickChat));

	//	if(_button)
	//	{
	//		ChatBtnMenu*_btnChatBtnMenu = ChatBtnMenu::menuWithItems(_button, 0);
	//		if(_btnChatBtnMenu)
	//		{
	//			_btnChatBtnMenu->setPosition(CCPointZero);
	//			_button->setPosition(POS(ccp(44, 45), ScaleUtil::BOTTOM_LEFT));
	//			_btnChatBtnMenu->setTouchLayer(TLE::SceneUILayer_MainNavigateTAG_menubtn);
	//			addChild(_btnChatBtnMenu, 0, 14);
	//			//_button->release();
	//		}
	//	}	
	//}
}

void MineView::onClickChat(CCObject * pSender)
{
	if (ViewManager::getInstance()->_secNavigate)
	{
		ViewManager::getInstance()->_secNavigate->popUIHandlerChatOpen(0);
	}
}