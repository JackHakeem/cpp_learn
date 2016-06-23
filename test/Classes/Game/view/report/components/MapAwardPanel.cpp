#include "manager/PopEventName.h"
#include "utils/ValuesUtil.h"
#include "Message.h"
#include "events/GameDispatcher.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "MapAwardPanel.h"
#include "model/player/vo/LevyInfoVo.h"
#include "events/CDEvent.h"
#include "manager/CDManage.h"
#include "utils/Utils.h"
#include "utils/ScaleUtil.h"
#include "manager/LangManager.h"
#include "model/player/RoleManage.h"
#include "CCUIBackground.h"
#include "model/backpack/GoodsManager.h"
#include "utils/ColorUtil.h"
#include "socket/network/GameServerSocket.h"
#include "view/honor/HonorMediator.h"
#include "manager/TouchLayerEnum.h"
#include "model/newhand/NewhandManager.h"
#include "model/newhand/vo/NewhandConst.h"
#include "model/scene/NPCManager.h"
#include "view/task/components/TaskType.h"
#include "manager/sound/SoundManager.h"
#include "Confirm.h"
#include "view/figure/FigureMediator.h"
#include "bear/manager/DisplayObjectManager.h"
#include "model/honor/HonorProxy.h"

#if (CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM)
#include "jni/slcq/JniManager.h"
#endif

MapAwardPanel::MapAwardPanel()
{
	for ( int i = 0; i < 3; i++ )
	{
		_pic[i] = 0;
		_picGoods[i] = 0;
		_txtGoods[i] = 0;
	}
}

bool MapAwardPanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	// initial key
	key = PopEventName::MAP_AWARD;
	setNeedBg(NeedBg_NO);

	CCSize screenSize( CCDirector::sharedDirector()->getWinSize() );
	CCSize cs( POSX(428), POSX(487) );
	this->setPopContentSize( cs );
	this->setContentSize( cs );

	CCLayer* pContentLayer = new CCLayer;
	pContentLayer->init();
	pContentLayer->setContentSize( cs );
	//pContentLayer->setPosition( screenSize.width/2-cs.width/2, screenSize.height/2-cs.height/2 );
	this->addChild( pContentLayer, RENDERZ_Container );

	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame(  "popuibg/bg1.png", 
		ccp( POSX(0), POSX(0) ), CCPointZero, CCSizeMake( POSX(393), POSX(450) )  );
	pContentLayer->addChild(_bg1);
	_bg1->release(); // LH0709

	CCUIBackground* _bg2 = new CCUIBackground();
	_bg2->initWithSpriteFrame(  "popuibg/bg2.png",
		ccp( POSX(16), POSX(99) ), CCPointZero, CCSizeMake( POSX(362), POSX(326) )  );
	pContentLayer->addChild(_bg2);
	_bg2->release(); // LH0709
	
	_pic[0] = new CCUIBackground();
	_pic[0]->initWithSpriteFrame( "ui.png",
		ccp(POSX(27), POSX(320)), ccp(POSX(0),POSX(0)), CCSizeMake( POSX(100), POSX(100) ) );
	pContentLayer->addChild( _pic[0] );
	_pic[0]->release(); // LH0709

	_pic[1] = new CCUIBackground();
	_pic[1]->initWithSpriteFrame( "ui.png",
		ccp(POSX(27), POSX(215)), ccp(POSX(0),POSX(0)), CCSizeMake( POSX(100), POSX(100) ) );
	pContentLayer->addChild( _pic[1] );
	_pic[1]->release(); // LH0709

	_pic[2] = new CCUIBackground();
	_pic[2]->initWithSpriteFrame( "ui.png",
		ccp(POSX(27), POSX(102)), ccp(POSX(0),POSX(0)), CCSizeMake( POSX(100), POSX(100) ) );
	pContentLayer->addChild( _pic[2] );
	_pic[2]->release(); // LH0709
	
	float fFont(29.5);
	// gold ttf
	_txtGoods[0] = CCLabelTTF::labelWithString( "",
		CCSizeMake( POSX(320), POSX(47) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(fFont) );
	_txtGoods[0]->setPosition( ccp( POSX(133), POSX(350) ) );
	_txtGoods[0]->setAnchorPoint( CCPointZero );
	pContentLayer->addChild( _txtGoods[0] );

	// silver ttf
	_txtGoods[1] = CCLabelTTF::labelWithString( "",
		CCSizeMake( POSX(320), POSX(fFont) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(fFont) );
	_txtGoods[1]->setPosition( ccp( POSX(133), POSX(245) ) );
	_txtGoods[1]->setAnchorPoint( CCPointZero );
	pContentLayer->addChild( _txtGoods[1] );

	// goods ttf
	_txtGoods[2] = CCLabelTTF::labelWithString( "",
		CCSizeMake( POSX(320), POSX(fFont) ), CCTextAlignmentLeft, g_sSimHeiFont, POSX(fFont) );
	_txtGoods[2]->setPosition( ccp( POSX(133), POSX(140) ) );
	_txtGoods[2]->setAnchorPoint( CCPointZero );
	pContentLayer->addChild( _txtGoods[2] );

	CCSize size = this->getContentSize();
	CCSize csBt( POSX(121), POSX(49) );
	// get btn
	CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
	CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
	if(!pNormalSprite || !pPressedSprite)
	{
		return true;
	}


	CCMenuItemSprite *pItem = CCMenuItemSprite::itemFromNormalSprite(
		pNormalSprite,
		pPressedSprite,
		this,
		menu_selector(MapAwardPanel::defClickHandler )
		);
	pItem->setPosition( ccp( POSX(125+121/2), POSX(23+79/2) ) );
	CCMenu* pGetMenu = CCMenu::menuWithItems(pItem, 0);
	pGetMenu->setTouchLayer( TLE::WindowLayer_Common_btn );
	pGetMenu->setPosition( CCPointZero );
	pContentLayer->addChild( pGetMenu );


	//NewhandConst.registerItem(NewhandConst.ITEM_COM_WIN, _panel);
	NewhandConst::Instance()->registerItem(NewhandConst::ITEM_MAP_AWARD_BTN, pItem);

	string txt = ValuesUtil::Instance()->getString( "pass_gift" );
	CCLabelTTF* txtLabel = CCLabelTTF::labelWithString( txt.c_str(), csBt, CCTextAlignmentCenter, g_sSimHeiFont, POSX(fFont) );
	txtLabel->setPosition( ccp( csBt.width/2, csBt.height/2 ) );
	pItem->addChild( txtLabel );

	// close btn
	pNormalSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_normal.png");
	pPressedSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_pressed.png");
	CCMenuItemSprite *_btnX = CCMenuItemSprite::itemFromNormalSprite(
		pNormalSprite,
		pPressedSprite,
	this, 
	menu_selector(MapAwardPanel::clickCloseHandler) );
	_btnX->setPosition(  ccp( POSX(396), POSX(451) )  );
	_buttonMenuX = new CCMenu();
	_buttonMenuX->init();
	_buttonMenuX->setTouchLayer( TLE::WindowLayer_Common_btn );
	_buttonMenuX->addChild(_btnX, 0, 0);
	_buttonMenuX->setPosition(CCPointZero);
	pContentLayer->addChild(_buttonMenuX);
	_buttonMenuX->release();
	_buttonMenuX->setIsVisible(false);
	//_buttonMenuX->setIsTouchEnabled(false);

	//this->setIsTouchEnabled( true );
	pContentLayer->release();
	return true;
}

void MapAwardPanel::clickCloseHandler(CCObject* obj)
{
	DisplayObjectManager::getInstance()->showAwardEffect();

	PopContainer::clickCloseHandler(obj);
}

/**
* 初始化奖励内容，通关奖励是由成就配置的
* @param honorGoods 成就配置vo
* 
*/
void MapAwardPanel::init( HonorGoodVo* honorGoods )
{
	clearItems();

	_honorId = honorGoods->honorsid;
	_taskId = honorGoods->taskId;
	vector<AwardThing> awards = honorGoods->goods;
	for ( int i = 0; i < awards.size(); i++ )
	{
		createItem( i, awards[i].type, awards[i].numbers );
	}
	if ( !getisPop() )
	{
		this->setisPop( true );
	}
	//_panel["_btnGetAll"].addEventListener(MouseEvent.CLICK,onClickGetItem);
			
	//前几个任务显示新手引导
    if(NewhandManager::Instance()->_pCurScript)
    {
        int newhandTask = NewhandManager::Instance()->_pCurScript->taskId; 
        if(newhandTask>0 && newhandTask<=10)
        {
            /*NewhandConst.registerItem(NewhandConst.ITEM_COM_WIN, _panel);
             NewhandConst.registerItem(NewhandConst.ITEM_MAP_AWARD_BTN, _panel["_btnGetAll"]);*/
            NewhandManager::Instance()->touchNextEvent(NewhandConst::EVENT_MAP_AWARD_POP);
        }
    }
	
}

void MapAwardPanel::clearItems()
{
	for ( int i = 0; i<3; i++ )
	{
		if ( _picGoods[i] )
		{
			_pic[i]->removeChild( _picGoods[i], true );
			_txtGoods[i]->setString("");
		}
		_pic[i]->setIsVisible( false );
	}
}

void MapAwardPanel::createItem( int sit, int type, int num )
{
	// gold info
	char fmt[128] = {0};
	char str[54];

	switch ( type )
	{
	case 1:
		{
			// gold pic			
			_picGoods[sit] = CCSprite::spriteWithFile( "assets/icon/goods/11.png" );
			if ( _picGoods[sit] )
			{
				_picGoods[sit]->setAnchorPoint( CCPointZero );
				_pic[sit]->addChild( _picGoods[sit] );
			}			

			sprintf( fmt, "%s", ValuesUtil::Instance()->getString("gold").c_str() );
			strcat( fmt, " +" );
			sprintf( str, "%d", num );
			strcat( fmt, str );
			_txtGoods[sit]->setString( fmt );
			_pic[sit]->setIsVisible( true );
		}
		break;
	case 2:
		{
			// silver pic
			_picGoods[sit] = CCSprite::spriteWithFile( "assets/icon/goods/12.png" );
			if ( _picGoods[sit] )
			{
				_picGoods[sit]->setAnchorPoint( CCPointZero );
				_pic[sit]->addChild( _picGoods[sit] );
			}			

			sprintf( fmt, "%s", ValuesUtil::Instance()->getString("silver").c_str() );
			strcat( fmt, " +" );
			sprintf( str, "%d", num );
			strcat( fmt, str );
			_txtGoods[sit]->setString( fmt );
			_pic[sit]->setIsVisible( true );
		}
		break;
	default:
		{
			// goods pic
			GoodsBasic* vo = g_pGoodsManager->getBasicGood( type );

			sprintf( fmt, "assets/icon/goods/%d.png", type );
			_picGoods[sit] = CCSprite::spriteWithFile( fmt );
			if ( _picGoods[sit] )
			{
				_picGoods[sit]->setAnchorPoint( CCPointZero );
				_pic[sit]->addChild( _picGoods[sit] );
			}			

			_txtGoods[sit]->setColor(  ColorUtil::getGoodColor( vo->quality )  );
			_txtGoods[sit]->setString( vo->goodName.c_str() );

			//var myTip:TipHelps = new TipHelps(true,TipConst.NORMAL);
			//myTip.setToolTips(item, GoodsToolTips.getExplain(vo));	
			_pic[sit]->setIsVisible( true );
		}
		break;
	}
}

void MapAwardPanel::defClickHandler( CCObject* pSender )
{
	g_pHonorMediator->honorChangeClickHandler( _honorId );
	//dispatcher.dispatchEvent(new ParamEvent(GameDispatcher.HONOR_CHANGR, {UseType:1/* 1领取物品奖励 */, id:_honorId}));
	
#if (CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM)
	if(119 ==  _honorId)
	{
		callTapjoyActionComplete();	
	}
#endif
	SoundManager::Instance()->playButtonEffectSound();
}

/**
*获取奖励，关闭面板 
* @param awardId
* 
*/		

void MapAwardPanel::tookItem( int awardId )
{
	if ( this->getisPop() )
	{
		this->setisPop( false );
	}
	
	HonorProxy* _honorProxy = (HonorProxy*)g_pFacade->retrieveProxy(AppFacade_HONOR_PROXY_CHANGE);
	map<int, HonorObject*>::iterator it = _honorProxy->_honorList.find(awardId);
	if ( it != _honorProxy->_honorList.end() )
	{
		HonorObject* obj = it->second;
		obj->award = 1;
	}

	//int newhandTask = NewhandManager::Instance()->_pCurScript->taskId; 
	NewhandManager::Instance()->touchNextEvent(NewhandConst::EVENT_MAP_AWARD_GET);
	if(_taskId>0){
		autoFindNpc(_taskId);
	}
}

//void MapAwardPanel::registerWithTouchDispatcher( void )
//{
//	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer_Common, true);
//}

//bool MapAwardPanel::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
//{
//	return true;
//}

void MapAwardPanel::autoFindNpc( int taskId )
{
	TaskVo *pTaskVo = TaskManager::Instance()->getTask(taskId);
	if(pTaskVo){
		NPCVo *pNpcVo = NPCManager::Instance()->getNPC(pTaskVo->getFinishTaskNpc());
		FindVo findVo;
		findVo._type = TaskType::NPC;
		findVo._sceneId = pNpcVo->_mapId;
		findVo._npcId = pNpcVo->id;
		GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::FIND_ELEMENT, 
			&findVo);
	}
}

void MapAwardPanel::EnableButtonX( bool bVar )
{
	if (_buttonMenuX)
	{
		_buttonMenuX->setIsVisible(bVar);
		_buttonMenuX->setIsTouchEnabled(bVar);
	}	
}

void MapAwardPanel::showBagSeclet()
{
	Confirm* pConfirm = new Confirm();
	std::string stdstr = LangManager::getText( "HOR002" );
	pConfirm->initWithParam(stdstr.c_str(),
		this, menu_selector(MapAwardPanel::okFunction), menu_selector(MapAwardPanel::cancelFunction));

	if (LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame))
	{
		LayerManager::windowLayer->removeChildByTag(WindowLayer::WindowLayerTAG_confirmFrame,true);
	}

	LayerManager::windowLayer->addChild(pConfirm,
		WindowLayer::WindowLayerZ_confirmFrame, WindowLayer::WindowLayerTAG_confirmFrame);

	pConfirm->release();
}

/* process after confirm */
void MapAwardPanel::okFunction( CCObject* pObject )
{
	//GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_BAG, NULL);
	DisplayObjectManager::getInstance()->showAwardEffect();

	Confirm* pConfirm = (Confirm*)LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame);
	if (pConfirm && pConfirm->getParent())
		pConfirm->getParent()->removeChild(pConfirm, true);

	setisPop(false);
}

void MapAwardPanel::cancelFunction( CCObject* pObject )
{
	Confirm* pConfirm = (Confirm*)LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame);
	if (pConfirm && pConfirm->getParent())
		pConfirm->getParent()->removeChild(pConfirm, true);
}
