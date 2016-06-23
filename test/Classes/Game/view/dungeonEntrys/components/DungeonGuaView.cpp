#include "DungeonGuaView.h"
#include "CCUIBackground.h"
#include "manager/PopManage.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"
#include "manager/LayerManager.h"
#include "utils/ValuesUtil.h"
#include "socket/command/c41/CCMD410.h"
#include "socket/network/GameServerSocket.h"
#include "manager/GlobalManage.h"

#include "model/scene/MonsterManager.h"
#include "socket/command/s13/SCMD13D.h"
#include "socket/command/s41/SCMD419.h"

#include "KKLabelTTF.h"
#include "model/player/RoleManage.h"
#include "manager/LangManager.h"
#include "DungeonGUAMsgItem.h"
#include "DungeonGUAMonsterInfoLayer.h"
#include "model/backpack/BagProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
/*
 //等待客户端可以开始挂机状态
 //可以点击开始挂机按钮进行挂机
 //
*/
#define w_bg1 POSX(928.0f)
#define h_bg1 POSX(562.0f)

#define w_bg2 POSX(910.0f)
#define h_bg2 POSX(524.0f)

DungeonGuaView::DungeonGuaView()
{
	m_pStartGUA = 0;
	m_pStopGUA = 0;
	m_iSelectMode = 0;
	m_timerGUA = 0.0f;

	m_iRoundCount = 0;
	m_iMaxRound = 0;
	_pShowChange[0] = 0;
	_pShowChange[1] = 0;
	aryRadioPNG[0] = ccp((513), (640-150));
	aryRadioPNG[1] = ccp((513), (640-207));
	aryRadioPNG[2] = ccp((513), (640-267));
}

DungeonGuaView::~DungeonGuaView()
{

}

bool DungeonGuaView::init()
{
	if (!LayerNode::init())
		return false;

	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	LayerNode* pContainer = new LayerNode();
	pContainer->init();
	this->addChild(pContainer, 0);
	pContainer->release();	
	pContainer->setPosition(POS(ccp(0, 0), ScaleUtil::CENTER_TOP));

	for (int i = 0; i < 2; i++)
	{
		_pShowChange[i] = new LayerNode();
		_pShowChange[i]->init();
		pContainer->addChild(_pShowChange[i], 8);
		_pShowChange[i]->release();	
	}

	CCUIBackground* _bg0 = new CCUIBackground();
	_bg0->initWithSpriteFrame("ui2.png", CCPointZero,CCPointZero,screenSize);
	this->addChild(_bg0, 0);
	_bg0->release();

	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame("popuibg/bg1.png", ccp(POSX(16.0f), POSX(12.0f)), ccp(0,0), CCSizeMake(w_bg1, h_bg1));
	pContainer->addChild(_bg1, 1);
	_bg1->release();

	CCUIBackground* _bg2 = new CCUIBackground();
	_bg2->initWithSpriteFrame("popuibg/bg2.png", ccp(POSX(25.0f), POSX(32.0f)), ccp(0,0), CCSizeMake(w_bg2, h_bg2));
	pContainer->addChild(_bg2, 2);
	_bg2->release();

	//第N关底框
	{
		CCUIBackground* _bg = new CCUIBackground();
		_bg->initWithSpriteFrame("popuibg/bg2.png", ccp(POSX(500.0f), POSX(640-474)), ccp(0,0), CCSizeMake(POSX(910-500), POSX(454-280)));
		pContainer->addChild(_bg, 3);
		_bg->release();
	}

	//
	{
		CCUIBackground* _bg = new CCUIBackground();
		_bg->initWithSpriteFrame("popuibg/bg2.png", ccp(POSX(34.0f), POSX(640-600)), ccp(0,0), CCSizeMake(POSX(472-34), POSX(600-93)));
		pContainer->addChild(_bg, 3);
		_bg->release();
	}
	//
	{
		CCUIBackground* _bg = new CCUIBackground();
		_bg->initWithSpriteFrame("popuibg/bg2.png", ccp(POSX(487.0f), POSX(40.0f)), ccp(0,0), CCSizeMake(POSX(472-34), POSX(600-93)));
		pContainer->addChild(_bg, 3);
		_bg->release();
	}
	//X
	{
		CCSprite *pCloseNormalSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_normal.png");
		CCSprite *pClosePressedSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_pressed.png");
		CCMenuItemSprite *_btnX = CCMenuItemSprite::itemFromNormalSprite(
			pCloseNormalSprite,
			pClosePressedSprite,
			this, 
			menu_selector(DungeonGuaView::clickCloseHandler) );
		_btnX->setPosition(ccp(POSX(960)-_btnX->getContentSize().width/2, 
			POSX(640)-_btnX->getContentSize().height/2));


		CCMenu *buttonMenu = new CCMenu();
		buttonMenu->init();
		buttonMenu->addChild(_btnX, 0, 0);
		buttonMenu->setPosition(ccp(0, 0));
		buttonMenu->setTouchLayer(TLE::IntervalLayer_dunGUA-2);
		pContainer->addChild(buttonMenu, 5);
		buttonMenu->setIsVisible(true);
		buttonMenu->release();
	}
	//开始讨伐按钮
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			CCMenuItemSprite* _btnGUA = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this,
				menu_selector(DungeonGuaView::onTAOFABegin) );
			_btnGUA->setPosition( ccp(POSX(712), POSX(640-523)) );
			//_btnGUA->setAnchorPoint(ccp(0, 0));

			CCMenu* _btnMenu = CCMenu::menuWithItems(_btnGUA, 0);
			_btnMenu->setTouchLayer( TLE::IntervalLayer_dunGUA );
			_btnMenu->setPosition( CCPointZero );
			pContainer->addChild( _btnMenu, 5 );

			CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
				ValuesUtil::Instance()->getString( "GUA002" ).c_str(),
				CCSizeMake(POSX(120), POSX(30)), CCTextAlignmentCenter, g_sSimHeiFont, POSX(24) );
			txtLabel->setPosition( ccp(_btnGUA->getContentSize().width/2, _btnGUA->getContentSize().height/2+2.0f) );
			_btnGUA->addChild( txtLabel );

			m_pStartGUA = _btnGUA;
		}
	}	
	//停止讨伐按钮
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			CCMenuItemSprite* _btnGUA = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this,
				menu_selector(DungeonGuaView::onTAOFACancel) );
			_btnGUA->setPosition( ccp(POSX(712), POSX(640-523)) );
			//_btnGUA->setAnchorPoint(ccp(0, 0));

			CCMenu* _btnMenu = CCMenu::menuWithItems(_btnGUA, 0);
			_btnMenu->setTouchLayer( TLE::IntervalLayer_dunGUA );
			_btnMenu->setPosition( CCPointZero );
			pContainer->addChild( _btnMenu, 5 );

			CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
				ValuesUtil::Instance()->getString( "GUA003" ).c_str(),
				CCSizeMake(POSX(120), POSX(30)), CCTextAlignmentCenter, g_sSimHeiFont, POSX(24) );
			txtLabel->setPosition( ccp(_btnGUA->getContentSize().width/2, _btnGUA->getContentSize().height/2+2.0f) );

			_btnGUA->addChild( txtLabel );

			m_pStopGUA = _btnGUA;
		}
	}	
	//maintitle
	{
		SpriteNode* sp = new SpriteNode();
		sp->initWithFile("assets/ui/gua/title.png");
		pContainer->addChild( sp, 7 );
		sp->setPosition(ccp(POSX(480), POSX(640-72)));
		sp->release();
	}
	//title

	{
		CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString( "GUA009" ).c_str(),
			CCSizeMake(POSX(150), POSX(30)), CCTextAlignmentCenter, g_sSimHeiFont, POSX(24) );
		txtLabel->setPosition( ccp(POSX(712), POSX(640-106)) );
		_pShowChange[0]->addChild( txtLabel, 7 );
		txtLabel->setColor(ccc3(251, 206, 51));
	}
	//
	{
		CCMenu* pRadio = new CCMenu();
		pRadio->init();
		pRadio->setTouchLayer( TLE::IntervalLayer_dunGUA-20 );
		pRadio->setPosition( ccp(POSX(0), POSX(0)) );
		_pShowChange[0]->addChild( pRadio, 6 );	
		pRadio->release();
		for (int i = 0; i < 3; i++)
		{
			CCSprite* pNormal = CCSprite::spriteWithSpriteFrameName("train/radio.png");
			CCSprite* pPress = CCSprite::spriteWithSpriteFrameName("train/radio.png");
			CCMenuItemSprite *pItem = cocos2d::CCMenuItemImage::itemFromNormalSprite(
				pNormal,
				pPress,
				this,
				menu_selector(DungeonGuaView::clickRadio) );
			pItem->setPosition( ccp(POSX(aryRadioPNG[i].x), POSX(aryRadioPNG[i].y)) );
			pItem->setTag(i);
			pItem->setAnchorPoint(ccp(0, 0));

			pRadio->addChild(pItem, 1);
		}
	}
	//
	{
		CCSprite* sp = CCSprite::spriteWithSpriteFrameName( "train/radioSelected.png" );
		_pShowChange[0]->addChild(sp, 7, DungeonGuaViewTAG_radioSelect);
		sp->setAnchorPoint(ccp(0, 0));
		sp->setPosition(ccp(POSX(aryRadioPNG[m_iSelectMode].x+1), POSX(aryRadioPNG[m_iSelectMode].y+2)));
	}

	//本副本怪物组合列表建立
	{
		m_vMG.clear();
		m_vMGName.clear();
		//这里下面要做错误处理 停止挂机
		std::list<GMProgressVo*> array = MonsterManager::Instance()->getGroupMonsterByMapId(g_pGlobalManage->getDunMapId());
		if(array.size() == 0)
			return false;

		std::vector<int> proIdArray;
		for(std::list<GMProgressVo*>::iterator iter = array.begin(); iter != array.end(); ++iter)
		{
			if(!(*iter))
				continue;

			if((*iter)->mgId == 0)
			{
				continue;
			}

			NPCVo* npcVo = MonsterManager::Instance()->getMonsterGroup((*iter)->mgId);
			if(!npcVo)
				continue;
				
			int mgId = (*iter)->mgId;

			m_vMG.push_back(mgId);
			m_vMGName.push_back(npcVo->name);
		}
	}	
	//剩余全部精力
	{
		KKLabelTTF* pLabel = new KKLabelTTF();
		pLabel->init(23.f, 30.0f, CCSizeMake(350, 120));
        std::string tmpStr = ValuesUtil::Instance()->getString( "GUA004" );
		pLabel->add(tmpStr, ccc3(240, 240, 232));

		int curEnergy = RoleManage::Instance()->accountInfo()->energy() + RoleManage::Instance()->accountInfo()->vigourBuffCount();
		char str[40];
		sprintf(str, ValuesUtil::Instance()->getString( "GUA008" ).c_str(), curEnergy);
		std::string svalue = str;
		pLabel->add(svalue, ccc3(251, 206, 51));
		pLabel->setPosition(ccp(POSX(aryRadioPNG[0].x+40), POSX(aryRadioPNG[0].y)));
		_pShowChange[0]->addChild( pLabel, 7 );
		pLabel->release();
	}
	//8轮
	{
		KKLabelTTF* pLabel = new KKLabelTTF();
		pLabel->init(23.f, 30.0f, CCSizeMake(350, 120));
        std::string tmpStr = ValuesUtil::Instance()->getString( "GUA005" );
		pLabel->add(tmpStr, ccc3(240, 240, 232));
		char str[40];
		sprintf(str, ValuesUtil::Instance()->getString( "GUA032" ).c_str(), m_vMG.size()*8);
		std::string svalue = str;
		pLabel->add(svalue, ccc3(251, 206, 51));
		pLabel->setPosition(ccp(POSX(aryRadioPNG[1].x+40), POSX(aryRadioPNG[1].y)));
		_pShowChange[0]->addChild( pLabel, 7 );
		pLabel->release();
	}
	//4轮
	{
		KKLabelTTF* pLabel = new KKLabelTTF();
		pLabel->init(23.f, 30.0f, CCSizeMake(350, 120));
        std::string tmpStr = ValuesUtil::Instance()->getString( "GUA006" );
		pLabel->add(tmpStr, ccc3(240, 240, 232));
		char str[40];
		sprintf(str, ValuesUtil::Instance()->getString( "GUA032" ).c_str(), m_vMG.size()*4);
		std::string svalue = str;
		pLabel->add(svalue, ccc3(251, 206, 51));
		pLabel->setPosition(ccp(POSX(aryRadioPNG[2].x+40), POSX(aryRadioPNG[2].y)));
		_pShowChange[0]->addChild( pLabel, 7 );
		pLabel->release();
	}
	//剩余N轮
	{
		KKLabelTTF* pLabel = new KKLabelTTF();
		pLabel->init(46.f, 52.0f, CCSizeMake(350, 120));
        
        std::string tmpStr = ValuesUtil::Instance()->getString( "GUA019" );
		pLabel->add(tmpStr, ccc3(251, 206, 51));

		char str[40];
		sprintf(str, "%d", m_iRoundCount);
		std::string svalue = str;
		pLabel->add(svalue, ccc3(255,255,255));
        
        std::string tmpStr2 = ValuesUtil::Instance()->getString( "GUA020" );
		pLabel->add(tmpStr2, ccc3(251, 206, 51));

		pLabel->setPosition(ccp(POSX(600), POSX(640-222)));
		_pShowChange[1]->addChild( pLabel, 0, 0 );
		pLabel->release();		
	}
	//list 
	{
		_pKKListView = KKCCUIListView::listViewWithCCRect(CCRectMake(POSX(34.0f), POSX(640-600), POSX(472-34), 
			POSX(600-93)), 150);
		_pKKListView->setIsRelativeAnchorPoint(true);
		_pKKListView->m_pri = TLE::IntervalLayer_dunGUA;
		_pKKListView->setAnchorPoint(ccp(0,0));
		_pKKListView->setSpacingVertical(0);
		_pKKListView->setWorldSpaceLeftBottomPoint(ccpAdd(_pKKListView->getPosition(), pContainer->getPosition()));
		_pKKListView->setOnItemActionListener(this);
		pContainer->addChild(_pKKListView, 8);
		_pKKListView->release();
	}
	//DungeonGUAMonsterInfoLayer
	{
		DungeonGUAMonsterInfoLayer* monsterLayer = new DungeonGUAMonsterInfoLayer();
		monsterLayer->init(m_vMGName, pContainer->getPosition());
		pContainer->addChild(monsterLayer, 7);
		monsterLayer->release();
	}
	//
	m_pStartGUA->setIsVisible(true);
	m_pStopGUA->setIsVisible(false);
	_pShowChange[0]->setIsVisible(true);
	_pShowChange[1]->setIsVisible(false);

	m_iRoundCount = 0;


	//
	{
		char str[50];
		sprintf(str, "%s", ValuesUtil::Instance()->getString("GUA029").c_str());
		addStrRecords(str, ccc3(255, 215, 0));	
	}
	{
		char str[50];
		sprintf(str, "%s", ValuesUtil::Instance()->getString("GUA030").c_str());
		addStrRecords(str, ccc3(255, 215, 0));	
	}

	for (int i = 0 ; i<18; i++)
	{
		//empty 
		addStrRecords("  ", ccc3(255, 255, 255));
	}
	return true;
}

std::vector<LayerNode*>* DungeonGuaView::getViewList()
{
	return &_cacheNodes;
}


void DungeonGuaView::changeRound(int value)
{
	m_iRoundCount = value;

	if (!_pShowChange[1])
		return;

	KKLabelTTF* pOld = (KKLabelTTF*)_pShowChange[1]->getChildByTag(0);
	if (pOld)
		pOld->removeFromParentAndCleanup(true);
	

	//剩余N轮
	{
		KKLabelTTF* pLabel = new KKLabelTTF();
		pLabel->init(46.f, 52.0f, CCSizeMake(350, 120));
        
        std::string tmpStr = ValuesUtil::Instance()->getString( "GUA019" );
		pLabel->add(tmpStr, ccc3(251, 206, 51));

		char str[40];
		sprintf(str, "%02d", m_iRoundCount);
		std::string svalue = str;
		pLabel->add(svalue, ccc3(255,255,255));
        
        std::string tmpStr2 = ValuesUtil::Instance()->getString( "GUA020" );
		pLabel->add(tmpStr2, ccc3(251, 206, 51));

		pLabel->setPosition(ccp(POSX(580), POSX(640-222)));
		_pShowChange[1]->addChild( pLabel, 0, 0 );
		pLabel->release();		
	}


	//更新挂机面板ROUND数信息

	if (m_iRoundCount > 0)
		addRoundRecords();
	
}

void DungeonGuaView::addStrRecords(char* label, ccColor3B color)
{
	DungeonGUAMsgItem* newNode = DungeonGUAMsgItem::itemStrFactory(label, color);

	if (newNode)
	{
		_cacheNodes.push_back(newNode);	
	}

	if (_pKKListView && _pKKListView->add(this))
		clearCacheNodes();//把内容成功全部加进去，再CLEAR
}

void DungeonGuaView::addRoundRecords()
{

	//line
	DungeonGUAMsgItem* newNode = DungeonGUAMsgItem::lineFactory();
	if (newNode)
	{
		_cacheNodes.push_back(newNode);	
	}
	//round
	newNode = DungeonGUAMsgItem::itemRoundFactory(m_iMaxRound-m_iRoundCount+1);
	if (newNode)
	{
		_cacheNodes.push_back(newNode);	
	}
	//insert
	if (_pKKListView && _pKKListView->add(this))
		clearCacheNodes();//把内容成功全部加进去，再CLEAR
}

void DungeonGuaView::addRecords(SCMD419* pPacket)
{
	if (!pPacket)
		return;

	for (int i = 0; i < 3; i++)
	{
		if (i==0)
		{
			DungeonGUAMsgItem* newNodeLine = DungeonGUAMsgItem::lineFactory();
			if (newNodeLine)
			{
				_cacheNodes.push_back(newNodeLine);	
			}
		}

		DungeonGUAMsgItem* newNode = DungeonGUAMsgItem::itemFactory(pPacket, i, pPacket->_battleIndex);

		if (newNode)
		{
			_cacheNodes.push_back(newNode);	
		}
	}

	if (_pKKListView && _pKKListView->add(this))
		clearCacheNodes();//把内容成功全部加进去，再CLEAR
}

void DungeonGuaView::addRecords(SCMD13D* pPacket)
{
	if (!pPacket)
		return;

	for (int i = 0; i < 3; i++)
	{
		if (i==0)
		{
			DungeonGUAMsgItem* newNodeLine = DungeonGUAMsgItem::lineFactory();
			if (newNodeLine)
			{
				_cacheNodes.push_back(newNodeLine);	
			}
		}

		DungeonGUAMsgItem* newNode = DungeonGUAMsgItem::itemFactory(pPacket, i, 5);

		if (newNode)
		{
			_cacheNodes.push_back(newNode);	
		}
	}

	if (_pKKListView && _pKKListView->add(this))
		clearCacheNodes();//把内容成功全部加进去，再CLEAR
}

void DungeonGuaView::clearCacheNodes()
{
	for (int i = 0; i < _cacheNodes.size(); i++)
	{
		_cacheNodes[i]->release();
	}
	_cacheNodes.clear();
}

void DungeonGuaView::clickRadio(CCObject* pSender)
{
	if (g_pGlobalManage->getDunGUA() != 0)
		return;//挂机期间不允许选择

	int tag = ((CCMenuItemSprite*)pSender)->getTag();
	if (m_iSelectMode == tag)
		return;
	else
	{
		if (tag == 0)
		{//all
			int curEnergy = RoleManage::Instance()->accountInfo()->energy() + RoleManage::Instance()->accountInfo()->vigourBuffCount();
			if (curEnergy <= 0)
			{
				LangManager::msgShow("GUA011");
				return;
			}
		}
		else if (tag == 1)
		{//8
			int curEnergy = RoleManage::Instance()->accountInfo()->energy() + RoleManage::Instance()->accountInfo()->vigourBuffCount();
			if (m_vMG.size()*8 > curEnergy)
			{
				LangManager::msgShow("GUA011");
				return;
			}
		}
		else if (tag == 2)
		{//4
			int curEnergy = RoleManage::Instance()->accountInfo()->energy() + RoleManage::Instance()->accountInfo()->vigourBuffCount();
			if (m_vMG.size()*4 > curEnergy)
			{
				LangManager::msgShow("GUA011");
				return;
			}
		}
		m_iSelectMode = tag;
	}

	CCNode* selected = _pShowChange[0]->getChildByTag(DungeonGuaViewTAG_radioSelect);
	if (selected)
	{
		selected->setPosition(ccp(POSX(aryRadioPNG[m_iSelectMode].x), POSX(aryRadioPNG[m_iSelectMode].y)));
	}
}


void DungeonGuaView::onTAOFABegin(CCObject* pSender)
{
	//精力判断
	int curEnergy = RoleManage::Instance()->accountInfo()->energy() + RoleManage::Instance()->accountInfo()->vigourBuffCount();
	if (curEnergy <= 0)
	{
		LangManager::msgShow("GUA011");
		return;
	}

	if (g_pGlobalManage->getDunGUA() != 0)
	{
		LangManager::msgShow("GUA016");
		return;
	}


	//设置挂机轮数
	m_iMaxRound = 0;
	switch(m_iSelectMode)
	{
	case 0:
		m_iMaxRound = ceil((float)curEnergy/m_vMG.size());break;
	case 1:
		m_iMaxRound = 8;break;
	case 2:
		m_iMaxRound = 4;break;
	default:
		m_iMaxRound = 0;
	}
	changeRound(m_iMaxRound);
	//


	//这里需要同步
//	LayerManager::loadingPic->socketWait( WMSG_DUNGEON_GUA, 0, 0);

	m_pStartGUA->setIsVisible(false);
	m_pStopGUA->setIsVisible(true);
	_pShowChange[0]->setIsVisible(false);
	_pShowChange[1]->setIsVisible(true);


	g_pGlobalManage->setDunGUA(1); 
	schedule (schedule_selector (DungeonGuaView::stepGUA));
}

void DungeonGuaView::onTAOFACancel(CCObject* pSender)
{
	m_pStartGUA->setIsVisible(true);
	m_pStopGUA->setIsVisible(false);
	_pShowChange[0]->setIsVisible(true);
	_pShowChange[1]->setIsVisible(false);

	m_iMaxRound = 0;
	m_iRoundCount = 0;
	//changeRound(0);

	g_pGlobalManage->setDunGUA(0); 
	this->unschedule(schedule_selector(DungeonGuaView::stepGUA));

}

void DungeonGuaView::clickCloseHandler(CCObject* pSender)
{
	g_pGlobalManage->setDunGUA(0); 
	this->unschedule(schedule_selector(DungeonGuaView::stepGUA));
	//

	DungeonGuaView* guaView = (DungeonGuaView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_dungeonGua);
	if (guaView)
	{
		guaView->removeFromParentAndCleanup(true);

	}
}

void DungeonGuaView::stepGUA(float dt)
{
	if (g_pGlobalManage->getDunGUA() == 0)
	{
		 //等待客户端可以开始挂机状态
		 //可以点击开始挂机按钮进行挂机
		
	}
	else if (g_pGlobalManage->getDunGUA() == 9)
	{
		char str[50];
		std::string strvalue = ValuesUtil::Instance()->getString("GUA025");
		sprintf(str, "%s", strvalue.c_str());
		addStrRecords(str, ccc3(255, 255, 255));

		onTAOFACancel(0);
	}
	else if (g_pGlobalManage->getDunGUA() == 1)
	{
		//bag
		BagProxy* bagProxy = (BagProxy*)g_pFacade->retrieveProxy(AppFacade_BAG_PROXY_CHANGE);
		if (bagProxy && bagProxy->getSpaceGridNum()<=0)
		{
			LangManager::msgShow("TOWR072");
			onTAOFACancel(0);
			return;
		}

		int curEnergy = RoleManage::Instance()->accountInfo()->energy() + RoleManage::Instance()->accountInfo()->vigourBuffCount();
		if (m_vMG.size() == 0 || m_iRoundCount == 0 || curEnergy <= 0)
		{//处理
			//over挂机异常结束
			onTAOFACancel(0);
			LangManager::msgShow("GUA012");
			return;
		}

		CCMD410 cmd;
		cmd.a_dunId = g_pGlobalManage->getDunMapId();
		GameServerSocket::getInstance()->sendMessage(&cmd);
		//LayerManager::loadingPic->socketWait( WMSG_DUNGEON_GUA, 0, 0);

		g_pGlobalManage->setDunGUA(2);
	}
	else if (g_pGlobalManage->getDunGUA() == 2)
	{
	
	}
	else if (g_pGlobalManage->getDunGUA() == 3)
	{
		//冷却时间
		m_timerGUA+=dt;
		if (m_timerGUA >= 1.0f)//20秒
		{
			m_timerGUA = 0.0f;


			
			
			int curEnergy = RoleManage::Instance()->accountInfo()->energy() + RoleManage::Instance()->accountInfo()->vigourBuffCount();
			if (curEnergy <= 0)
			{
				//over挂机结束 精力用完
				char str[50];
				sprintf(str, "%s ", ValuesUtil::Instance()->getString("GUA014").c_str());
				addStrRecords(str, ccc3(255, 255, 255));

				onTAOFACancel(0);	
				return;
			}

			changeRound(m_iRoundCount-1);				
			if (m_iRoundCount <= 0)
			{
				//over挂机结束 回合过了
				char str[50];
				sprintf(str, "%s", ValuesUtil::Instance()->getString("GUA013").c_str());
				addStrRecords(str, ccc3(255, 255, 255));

				onTAOFACancel(0);
			}
			else
			{
				LangManager::msgShow("GUA015");
				g_pGlobalManage->setDunGUA(1);

			}
		}
	}
}

