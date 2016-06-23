
#include "TouchMapNode.h"
#include "CCUIBackground.h"
#include "../DungeonEntrysMediator.h"
#include "utils/Timer.h"
#include "manager/GlobalManage.h"
#include "manager/LayerManager.h"
#include "socket/command/c37/CCMD37D.h"
#include "socket/network/GateServerSocket.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"
#include "manager/sound/SoundManager.h"
#include "utils/ValuesUtil.h"
#include "DungeonGuaView.h"
#include "ChallengeGuaView.h"
#include "model/player/RoleManage.h"
#include "model/scene/SceneProxy.h"
#include "socket/command/c41/CCMD413.h"
#include "manager/LevLimitConst.h"

TouchMapNode::TouchMapNode()
{
	_rowId = 0;
	_colId = 0;
	_copyType = 0;
	CCSize size;
	sp = NULL;
	_pBeganTouch = NULL;
	_spClicked = false;
	//POSX edwardliu
	size.height = POSX(122);
	size.width = POSX(122);
	//this->initWithColor(ccc4(255, 128, 128, 255));
	setContentSize(size);
	_isNoTongGuan = false;
	_btnGUA = 0;
	
	//setColor(ccc3(255, 128, 128));
	//this->setIsTouchEnabled(true);

	/*CCLayerColor *pTestLayer = CCLayerColor::layerWithColorWidthHeight(ccc4(255, 255, 0, 128),
	CCDirector::sharedDirector()->getWinSize().width,
	CCDirector::sharedDirector()->getWinSize().height);
	pTestLayer->setAnchorPoint(CCPointZero);
	pTestLayer->setPosition(CCPointZero);

	this->addChild(pTestLayer, -100);*/
	//CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer_CopyMap, true);
}

TouchMapNode::TouchMapNode(std::map<int, MapData>& list)
{
	_rowId = 0;
	_colId = 0;
	_nodeList = list;
}

TouchMapNode::~TouchMapNode()
{

}

void TouchMapNode::setNoTongGuan()
{
	if (_btnGUA)
	{
		_btnGUA->setIsVisible(false);
	}
}

void TouchMapNode::onTAOFA(CCObject* pSender)
{
	g_pGlobalManage->setDunMapId(_mapData._id);


	if (_copyType == 0)
	{
		DungeonGuaView* guaView = (DungeonGuaView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_dungeonGua);
		if (!guaView)
		{
			DungeonGuaView* newNode = new DungeonGuaView();
			newNode->init();
			LayerManager::intervalLayer->addChild(newNode, IntervalLayer::IntervalLayerZ_dungeonGua, IntervalLayer::IntervalLayerTAG_dungeonGua);
			newNode->release();
		}	
	}
	else if (_copyType == 1)
	{
		ChallengeGuaView* guaView = (ChallengeGuaView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_dungeonGua);
		if (!guaView)
		{
			ChallengeGuaView* newNode = new ChallengeGuaView();
			newNode->init();
			LayerManager::intervalLayer->addChild(newNode, IntervalLayer::IntervalLayerZ_dungeonGua, IntervalLayer::IntervalLayerTAG_dungeonGua);
			newNode->release();

			//申请3样需要精力==>消耗次数
			CCMD413 cmd;
			//cmd.a_lunType = 0;
			//cmd.b_lunType = 8;
			//cmd.c_lunType = 4;
			//cmd.d_lunType = 1;
			GameServerSocket* pSocket = GameServerSocket::getInstance();
			if (pSocket)
				pSocket->sendMessage(&cmd);

			//这里需要同步414
			LayerManager::loadingPic->socketWait( WMSG_CHALLENAGE_VIGOUR_GET, 0, 0);
		}		
	}



}

void TouchMapNode::setSpriteIcon(bool open)
{
	SceneProxy* _sceneProxy = (SceneProxy*)g_pFacade->retrieveProxy(AppFacade_SCENE_PROXY);

	if ( 
		(
		_copyType == 0 &&//是剧情副本
		RoleManage::Instance()->roleLev() >= LevLimitConst::Limit_Gua  &&
		_sceneProxy->isSceneOpened(_mapData._id) && 
		!_isNoTongGuan
		)
		||
		(_copyType == 1 &&//是挑战副本
		_sceneProxy->getSceneStatus(1065) > 0 &&
		RoleManage::Instance()->roleLev() >= LevLimitConst::Limit_Gua &&
		_mapData._star == 5 
		)
	   )
	{

		// 挂机 btn

		//CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		//CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		//CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		//if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			_btnGUA = CCMenuItemImage::itemFromNormalImage(
				"assets/ui/gua/button1.png",
				"assets/ui/gua/button0.png",
				"assets/ui/gua/button0.png",
				this,
				menu_selector(TouchMapNode::onTAOFA) );
			if (_btnGUA)
			{
				_btnGUA->setPosition( ccp(POSX(15), POSX(-60)) );
				_btnGUA->setAnchorPoint(ccp(0, 0));

				CCMenu* _btnMenu = CCMenu::menuWithItems(_btnGUA, 0);
				_btnMenu->setTouchLayer( TLE::WindowLayer_Common_btn );
				_btnMenu->setPosition( CCPointZero );
				this->addChild( _btnMenu );

				CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
					ValuesUtil::Instance()->getString( "GUA001" ).c_str(),
					CCSizeMake(POSX(80), POSX(30)), CCTextAlignmentCenter, g_sSimHeiFont, POSX(24) );
				txtLabel->setPosition( ccp(_btnGUA->getContentSize().width/2, _btnGUA->getContentSize().height/2+2.0f) );
				_btnGUA->addChild( txtLabel );
			}
		}
	}	



	if(_mapData._star == 4)
	{
		/*std::string s = "assets/ui/crystal/btn_close_0.png";
		CCSprite* bt = CCSprite::spriteWithFile(s.c_str());
		if(bt)
		{
			addChild(bt, 1);
			bt->setAnchorPoint(CCPointZero);
			bt->setPosition(ccp(30, 30));
		}*/
		sp = new CCSprite();//CCSprite::spriteWithFile("assets/ui/entrance/copyMap2.png");
		sp->initWithSpriteFrameName("entrance/copyMap2.png");
		if(sp)
		{
			addChild(sp, 0, 0);
			sp->release();
			sp->setAnchorPoint(CCPointZero);
		}
	}
	else// if (_mapData._star == 3 || _mapData._star == 5)
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("entrance/copyMap_normal.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("entrance/copyMap_pressed.png");
		CCMenuItemSprite *pItemImage = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this,
			menu_selector(TouchMapNode::handleClickEvent));
		pItemImage->setPosition(CCPointZero);
		pItemImage->setAnchorPoint(CCPointZero);
		CCMenu *pMenu = CCMenu::menuWithItem(pItemImage);
		pMenu->setPosition(CCPointZero);
		pMenu->setTouchLayer(TLE::WindowLayer_Map);
		this->addChild(pMenu, 0, 0);
		/*sp = CCSprite::spriteWithFile("assets/ui/entrance/copyMap.png");
		if(sp)
		{
			addChild(sp, 0, 0);
			sp->setAnchorPoint(CCPointZero);
		}*/

		char tmp[64] = {0};
		std::string s = "entrance/entranceIcon/%d.png";
		sprintf(tmp, s.c_str(), _mapData._id);

		/*CCMenuItemImage *mainBtn = new CCMenuItemImage();
		if (mainBtn)
			mainBtn->initFromNormalImage(tmp, tmp, 
			                             0, this, menu_selector(TouchMapNode::handleClickEvent));*/
		CCSprite* bt = new CCSprite;
		bt->initWithSpriteFrameName(tmp);
		/*if(mainBtn)
		{
			mainBtn->setAnchorPoint(CCPointZero);
			addChild(mainBtn, 1, 1);
			//CCSize size = bt->getContentSize();
			//bt->setPosition(ccp(113 - size.width / 2, 56 - size.height / 2));
		}*/
		if(bt)
		{
			bt->setAnchorPoint(CCPointZero);
			//CCSize size = bt->getContentSize();
			//bt->setPosition(ccp(113 - size.width / 2, 56 - size.height / 2));
			addChild(bt, 1);
			bt->release();
		}

		CCLabelTTF* label = CCLabelTTF::labelWithString(_mapData._name.c_str(), "Arial", POSX(20));
		if(label)
		{
			addChild(label, 100);
			label->setAnchorPoint(CCPointZero);
			label->setPosition(ccp(POSX(0), 0));
		}
	}
}

void TouchMapNode::handleClickEvent(CCObject* pSender)
{
	//CCLog("Clicked map button %d, %s, %d", _mapData._id, _mapData._name.c_str(), _mapData._star);
	//CCLog("-------------------send 116: %d",  Timer::millisecondNow());
	if(_copyType == 0)
	{
		DungeonEntrysMediator* m = (DungeonEntrysMediator*)g_pFacade->retrieveMediator(AppFacade_DungeonEntrysMediator);
		if(m)
			m->onClickStoryMapIcon(NULL, (void*)(&(_mapData._id)));
	}
	else if(_copyType == 1)
	{
		CCMD37D ccmd37d;
		ccmd37d.a_operationType = (int8)4;
		ccmd37d.b_mapId = _mapData._id;
		ccmd37d.c_roomId = 0;
		GameServerSocket* pSocket = GameServerSocket::getInstance();
		if (pSocket)
			pSocket->sendMessage(&ccmd37d);
	}
}