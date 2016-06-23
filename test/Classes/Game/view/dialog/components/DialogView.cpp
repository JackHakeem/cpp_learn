#include "DialogView.h"
#include "model/dialog/DialogManager.h"
#include "model/scene/vo/NPCVo.h"
#include "model/scene/NPCManager.h"
#include "model/com/vo/ResourceVo.h"
#include "model/com/ResourceManage.h"
#include "../DialogMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "model/shop/ShopManager.h"
#include "model/dialog/vo/DialogueType.h"
#include "manager/ViewManager.h"
#include "manager/PopEventName.h"
#include "BaseType.h"
#include "model/dialog/vo/DialogueTypeConst.h"
#include "utils/ValuesUtil.h"
#include "view/task/TaskListenerMediator.h"
#include "events/GameDispatcher.h"
#include "PopUIBg.h"
#include "events/TaskEvent.h"
#include "manager/TouchLayerEnum.h"
#include "view/backpack/BagMediator.h"
#include "model/player/RoleManage.h"
#include "manager/LevLimitConst.h"
#include "manager/GlobalManage.h"

#define CCSIZE_DIALOG_LIST CCSizeMake(POSX(468), POSX(158))
#define CCSIZE_DIALOG_LIST_ITEM CCSizeMake(POSX(468), POSX(49))
#define CCSIZE_ITEM_TASK_NAME CCSizeMake(POSX(500), POSX(25))

#define CCPOINT_ITEM_TASK_POINT_TO_SP ccp(POSX(26), POSX(22))
#define CCPOINT_ITEM_TASK_NAME_TO_SP ccp(POSX(63), POSX(16))

#define CCPOINT_ITEM_TASK_NAME ccp(POSX(12), 0)

const float contentFontSize = 20.0f;

const int TAG_PARENT = 1001;
const int TAG_LABEL_NAME = 1002;
const int TAG_LABEL_CONTENT = 1003;
const int TAG_IMAGE_HEAD = 1004;

const int TAG_ITEM_BACKGROUND_NORMAL = 1005;
const int TAG_ITEM_BACKGROUND_PRESSED = 1006;

DialogView::DialogView()
{
	_npcDialogueVo = 0;
	/*m_pSpriteHeadImage = 0;
	m_pLabelNPCName = 0;
	m_pLabelNPCContent = 0;*/
	_pDialogListView = 0;

	_npcId = 0;
	_autoPop = false;
	_noStory = true;
	pFocusTask = NULL;
}

DialogView::~DialogView()
{

	ViewManager::getInstance()->dialogView = 0;
    //Doyang 20120708
    /*std::vector<LayerNode *>::iterator listItemIt;
    for(listItemIt = _listViewItemsList.begin();
        listItemIt != _listViewItemsList.end();
        ++listItemIt)
    {
        CC_SAFE_DELETE(*listItemIt);
    }*/
    _listViewItemsList.clear();
    
	/*std::vector<TaskNodeVo *>::iterator taskItemIt;
    for(taskItemIt = _taskList.begin();
        taskItemIt != _taskList.end();
        ++ taskItemIt)
    {
        CC_SAFE_DELETE(*taskItemIt);
    }
    _taskList.clear();*/

	/*

	std::vector<TaskNodeVo *> taskList;
	std::vector<ShopVo *> chatList;			//Interactive list such as buying and selling
	*/
	//{
	//	//_npcDialogueVo
	//	std::vector<TaskNodeVo *>::iterator taskNodeIt;
	//	for(taskNodeIt = _npcDialogueVo->taskList.begin();
	//		taskNodeIt != _npcDialogueVo->taskList.end();
	//		++ taskNodeIt)
	//	{
	//		CC_SAFE_DELETE(*taskNodeIt);
	//	}
	//	_npcDialogueVo->taskList.clear();		

	//	std::vector<ShopVo *>::iterator chatListIt;
	//	for(chatListIt = _npcDialogueVo->chatList.begin();
	//		chatListIt != _npcDialogueVo->chatList.end();
	//		++ chatListIt)
	//	{
	//		CC_SAFE_DELETE(*chatListIt);
	//	}
	//	_npcDialogueVo->chatList.clear();	

	//	CC_SAFE_DELETE(_npcDialogueVo);
	//}



}

bool DialogView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	//
	setNeedBg(NeedBg_NO);
	//Init key
	key = PopEventName::DIALOGUE;

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	setPopContentSize(size);

	CCLayer *pParentLayer = new CCLayer();
	if(!pParentLayer)
	{
		return false;
	}
	pParentLayer->init();
	pParentLayer->setContentSize(size);
	pParentLayer->setPosition(POS(ccp(28, /*size.height/2 - POSX(160)*/15), ScaleUtil::CENTER_BOTTOM));
	pParentLayer->setAnchorPoint(CCPointZero);
	pParentLayer->setTag(TAG_PARENT);


	// Add background1
	CCUIBackground *pBackground1 = new CCUIBackground();
	pBackground1->initWithSpriteFrame("ui.png", 
		ccp(POSX(26), 0),
		ccp(0,0), 
		CCSizeMake(POSX(887), POSX(307)));
	pParentLayer->addChild(pBackground1);
    pBackground1->release();
    //Doyang 20120708

	// Add background2
	CCUIBackground *pBackground2 = new CCUIBackground();
	pBackground2->initWithSpriteFrame("ui2.png", 
		ccp(POSX(230), POSX(20)),
		ccp(0,0), 
		CCSizeMake(POSX(642), POSX(270)));
	pParentLayer->addChild(pBackground2);
    pBackground2->release();
    //Doyang 20120708
		
	CCSprite *pCloseNormalSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_normal.png");
	CCSprite *pClosePressedSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_pressed.png");
	CCMenuItemSprite *_btnX = CCMenuItemSprite::itemFromNormalSprite(
		pCloseNormalSprite,
		pClosePressedSprite,
		this, 
		menu_selector(PopUIBg::clickCloseHandler) );
	_btnX->setPosition(ccp(POSX(887), POSX(300)));
	CCMenu *buttonMenu = new CCMenu();
	buttonMenu->init();
	buttonMenu->setTouchLayer( TLE::WindowLayer_Common_btn );
	buttonMenu->addChild(_btnX, 0, 0);
	buttonMenu->setPosition(CCPointZero);
	pParentLayer->addChild(buttonMenu, g_layerFront);
	buttonMenu->release();

	this->setIsTouchEnabled( true );

	this->addChild(pParentLayer);
	pParentLayer->release();

	return true;
}

void DialogView::setData( NPCDialogueVo* value )
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	ccColor3B ccColYellow = { 255, 255, 0 };

	//Doyang 20120710
	if(_npcDialogueVo)
	{
		std::vector<TaskNodeVo *>::iterator taskNodeIt;
		for(taskNodeIt = _npcDialogueVo->taskList.begin();
		taskNodeIt != _npcDialogueVo->taskList.end();
		++ taskNodeIt)
		{
			TaskNodeVo *pTempTask = *taskNodeIt;
			if(!pTempTask)
				continue;

			std::vector < DialogueNodeVo * >::iterator dialogNodeIt;
			for(dialogNodeIt = pTempTask->_list.begin();
				dialogNodeIt != pTempTask->_list.end();
				++ dialogNodeIt)
			{
				CC_SAFE_DELETE(*dialogNodeIt);
			}
			CC_SAFE_DELETE(*taskNodeIt);
		}

		CC_SAFE_DELETE(_npcDialogueVo);
	}

	CCLayer *pParentLayer = (CCLayer *) this->getChildByTag(TAG_PARENT);
	if(!pParentLayer)
	{
		return;
	}

	_npcDialogueVo = value;
	NPCVo* npc = NPCManager::Instance()->getNPC(value->npcId);

	if (!npc)
	{
		CCLog("Dialog:Get npc vo failed(void DialogView::setData())");
		return;
	}

	// half body
	ResourceVo* res = ResourceManage::Instance()->getRes( 1, npc->getResId() );
	if ( res )
	{
		// head
		_headImageContain = res->gethalfBodyUrl();

		CCSprite *pSpriteHeadImage = (CCSprite *) pParentLayer->getChildByTag(TAG_IMAGE_HEAD); 
		if ( pSpriteHeadImage )
		{
			pParentLayer->removeChildByTag(TAG_IMAGE_HEAD, true);
		}

		pSpriteHeadImage = CCSprite::spriteWithFile( _headImageContain.c_str() );
		if(pSpriteHeadImage)
		{
			pSpriteHeadImage->setAnchorPoint(CCPointZero);
			pSpriteHeadImage->setPosition( ccp(POSX(26), POSX(10) ) );
			pParentLayer->addChild( pSpriteHeadImage, g_layerFront , TAG_IMAGE_HEAD);
		}
	}

	// Name
	//_NameTxt = npc->name;

	////Doyang 20120711
	//CCLabelTTF *pLabelNPCName = (CCLabelTTF *) pParentLayer->getChildByTag(TAG_LABEL_NAME);
	//if ( !pLabelNPCName )
	//{
	//	pLabelNPCName = CCLabelTTF::labelWithString( _NameTxt.c_str(), 
	//		CCSizeMake(POSX(100), POSX(20)),
	//		CCTextAlignmentLeft,
	//		g_sSimHeiFont,
	//		POSX(contentFontSize));
	//	pLabelNPCName->setColor( ccColYellow );
	//	pLabelNPCName->setAnchorPoint(CCPointZero);
	//	pLabelNPCName->setPosition(  ccp(POSX(149), POSX(116))  );
	//	pParentLayer->addChild(pLabelNPCName, 100, TAG_LABEL_NAME);
	//}
	//else
	//{
	//	pLabelNPCName->setString( _NameTxt.c_str() );
	//}

	// NPC Dialog
	DialogManager* pDialogManager = DialogManager::Instance();
	if ( !pDialogManager )
	{
		cocos2d::CCLog( "DialogManager not init!" );
		return;
	}
	DialogueVo * pDialogueVo = pDialogManager->getDialogs( npc->otherInfos );
	if ( pDialogueVo )
	{
		_dialogTxt = pDialogueVo->content;
	}
	else
	{
		//_dialogTxt = "ï¿½ï¿½Ó­4ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ê¿Ä§ï¿½ï¿½ï¿?ç£?;
		_dialogTxt = ValuesUtil::Instance()->getString("WLC001");
	}

	CCLabelTTF *pLabelNPCContent = (CCLabelTTF *) pParentLayer->getChildByTag(TAG_LABEL_CONTENT);
	if ( !pLabelNPCContent )
	{
		pLabelNPCContent = CCLabelTTF::labelWithString(_dialogTxt.c_str(),
			CCSizeMake(POSX(610), POSX(102)),
			CCTextAlignmentLeft,
			g_sSimHeiFont,
			POSX(contentFontSize));
		pLabelNPCContent->setColor( ccWHITE );
		pLabelNPCContent->setAnchorPoint(CCPointZero);
		pLabelNPCContent->setPosition( ccp( POSX(258), POSX(177) ) );
		pParentLayer->addChild(pLabelNPCContent, g_layerFront, TAG_LABEL_CONTENT);
	}
	else
	{
		pLabelNPCContent->setString( _dialogTxt.c_str() );
	}

	// use or task btn
	buildTaskBtns();
}

void DialogView::showString( std::string str, float x, float y, ccColor3B ccCol, int fontSize, bool bold /*= false*/ )
{
	CCLabelTTF* label = CCLabelTTF::labelWithString( str.c_str(), g_sSimHeiFont, contentFontSize );
	label->setColor( ccCol );
	//label->setFlipX()
	label->setAnchorPoint(CCPointZero);
	label->setPosition( ccp(x, y) );
	addChild(label);
}

void DialogView::buildTaskBtns()
{
    //Doyang 20120708
	/*if(_pDialogListView)
	{
	if(_pDialogListView->getParent())
	_pDialogListView->removeFromParentAndCleanup(true);
	CC_SAFE_DELETE(_pDialogListView);
	}*/

	//std::vector<LayerNode *>::iterator listItemIt;
	//for(listItemIt = _listViewItemsList.begin();
	//	listItemIt != _listViewItemsList.end();
	//	++listItemIt)
	//{
	//	LayerNode *tmp = (LayerNode *) *listItemIt;
	//	if(tmp && tmp->getParent())
	//	{
	//		tmp->removeFromParentAndCleanup(true);
	//		tmp->release();
	//	}
	//	//CC_SAFE_DELETE(*listItemIt);
	//}
	////_listValueList.clear();
	//_listViewItemsList.clear();

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	ValuesUtil *pValueUtil = ValuesUtil::Instance();

	std::vector<TaskNodeVo *>::iterator taskIt;
	for(taskIt = _npcDialogueVo->taskList.begin(); taskIt != _npcDialogueVo->taskList.end(); ++ taskIt)
	{
		TaskNodeVo *pTask = *taskIt;
		DialogItem *pTaskLayer = new DialogItem();
		pTaskLayer->setType(DIALOG_ITEM_TASK_BEGIN);
		if(!pTaskLayer || !pTaskLayer->init())
		{
			continue;
		}
		// Add list item value.
		//_listValueList.push_back(pTask);

		CCSprite* spriteBack = CCSprite::spriteWithSpriteFrameName( "npcdialog/npc_talk_list.png" );
		CCSize csSpBack = spriteBack->getContentSize();

		pTaskLayer->setContentSize( csSpBack );
		pTaskLayer->setvisibleSize( csSpBack );


		char pLabelStr[128];
		if(pTask->_type == 1)
		{
			sprintf(pLabelStr, "%s%s", pValueUtil->getString("task_lord").c_str(), pTask->_name.c_str());
		}
		else
		{
			sprintf(pLabelStr, "%s%s", pValueUtil->getString("task_other").c_str(), pTask->_name.c_str());
		}

		CCLabelTTF* pTaskNameLabel = CCLabelTTF::labelWithString(
			pLabelStr, 
			CCSIZE_ITEM_TASK_NAME, 
			CCTextAlignmentLeft, 
			g_sSimHeiFont, 
			POSX(20));
		pTaskNameLabel->setColor(ccc3(255, 255, 0));
		pTaskNameLabel->setPosition( CCPOINT_ITEM_TASK_NAME_TO_SP );
		pTaskNameLabel->setAnchorPoint( CCPointZero );
		pTaskNameLabel->setIsRelativeAnchorPoint(true);

		CCSprite* spritePoint = CCSprite::spriteWithSpriteFrameName( "npcdialog/point.png" );
		spritePoint->setAnchorPoint( CCPointZero );
		spritePoint->setPosition( CCPOINT_ITEM_TASK_POINT_TO_SP );
		spriteBack->addChild( spritePoint );

		spriteBack->setAnchorPoint( CCPointZero );
		spriteBack->setPosition( CCPOINT_ITEM_TASK_NAME );

		pTaskLayer->addChild( spriteBack, 0, TAG_ITEM_BACKGROUND_NORMAL );

		CCSprite* spriteBackPressed = CCSprite::spriteWithSpriteFrameName( "npcdialog/npc_talk_list_pressed.png" );
		CCSprite* spritePoint2 = CCSprite::spriteWithSpriteFrameName( "npcdialog/point.png" );
		spritePoint2->setAnchorPoint( CCPointZero );
		spritePoint2->setPosition( CCPOINT_ITEM_TASK_POINT_TO_SP );
		spriteBackPressed->addChild( spritePoint2 );
		spriteBackPressed->setAnchorPoint( CCPointZero );
		spriteBackPressed->setPosition( CCPOINT_ITEM_TASK_NAME );
		pTaskLayer->addChild( spriteBackPressed, 0, TAG_ITEM_BACKGROUND_PRESSED );

		pTaskLayer->addChild( pTaskNameLabel );
		spriteBackPressed->setIsVisible(false);


		_listViewItemsList.push_back(pTaskLayer);
	}

	// NPCFunction words
	ShopVo* pShopVo = 0;
	std::vector<ShopVo *>::iterator it = _npcDialogueVo->chatList.begin();
	if ( it != _npcDialogueVo->chatList.end() )
	{
		pShopVo = *it;
	}
	bool showShop = false;
	if(pShopVo)
	{
		int lev = RoleManage::Instance()->roleLev();
		if(pShopVo->type == 3 && lev >= 26)
		{
			showShop = true;
		}
		if(pShopVo->type == 4 && lev > 1)
		{
			showShop = true;
		}
		if(pShopVo->type != 3 && pShopVo->type != 4)
		{
			showShop = true;
		}
	}

	CCSize csSpBack;
	if ( showShop ) 
	{
		DialogItem *pShopLayer = new DialogItem();
		pShopLayer->setType(DIALOG_ITEM_SHOP);
		if(pShopLayer && pShopLayer->init())
		{
			// Add list item value.
			//_listValueList.push_back(pShopVo);

			CCSprite* spriteBack = CCSprite::spriteWithSpriteFrameName( "npcdialog/npc_talk_list.png" );
			csSpBack = spriteBack->getContentSize();

			pShopLayer->setContentSize( csSpBack );
			pShopLayer->setvisibleSize( csSpBack );
			_chatList = pShopVo->name;
			// Font Item
			CCLabelTTF *pShopNameLabel = CCLabelTTF::labelWithString(
				_chatList.c_str(), 
				CCSIZE_ITEM_TASK_NAME, 
				CCTextAlignmentLeft, 
				g_sSimHeiFont, 
				POSX(20));
			pShopNameLabel->setColor(ccc3(255, 255, 0));
			pShopNameLabel->setPosition( CCPOINT_ITEM_TASK_NAME_TO_SP );
			pShopNameLabel->setAnchorPoint( CCPointZero );
			pShopNameLabel->setIsRelativeAnchorPoint(true);

			CCSprite* spritePoint = CCSprite::spriteWithSpriteFrameName( "npcdialog/point.png" );
			spritePoint->setAnchorPoint( CCPointZero );
			spritePoint->setPosition( CCPOINT_ITEM_TASK_POINT_TO_SP );
			spriteBack->addChild( spritePoint );

			spriteBack->setAnchorPoint( CCPointZero );
			spriteBack->setPosition( CCPOINT_ITEM_TASK_NAME );

			pShopLayer->addChild( spriteBack, 0, TAG_ITEM_BACKGROUND_NORMAL  );

			CCSprite* spriteBackPressed = CCSprite::spriteWithSpriteFrameName( "npcdialog/npc_talk_list_pressed.png" );
			CCSprite* spritePoint2 = CCSprite::spriteWithSpriteFrameName( "npcdialog/point.png" );
			spritePoint2->setAnchorPoint( CCPointZero );
			spritePoint2->setPosition( CCPOINT_ITEM_TASK_POINT_TO_SP );
			spriteBackPressed->addChild( spritePoint2 );
			spriteBackPressed->setAnchorPoint( CCPointZero );
			spriteBackPressed->setPosition( CCPOINT_ITEM_TASK_NAME );
			pShopLayer->addChild( spriteBackPressed, 0, TAG_ITEM_BACKGROUND_PRESSED );
			spriteBackPressed->setIsVisible(false);
			pShopLayer->addChild( pShopNameLabel );

			// NPC Function icon

			_listViewItemsList.push_back(pShopLayer);
		}
	}

	CCSize listSize = CCSizeMake(POSX(500), POSX(162));
	CCRect listRect = CCRectMake(POSX(241),
		POSX(24),
		listSize.width,
		listSize.height );
	float space = POSX(5);
	if(!_pDialogListView)
	{

		CCLayer *pParentLayer = (CCLayer *) this->getChildByTag(TAG_PARENT);
		if(!pParentLayer)
		{
			return;
		}
		_pDialogListView = CCUIListView::listViewWithCCRect(listRect, false);
		_pDialogListView->setAnchorPoint(CCPointZero);
		_pDialogListView->setSpacingVertical(space);
		//_pDialogListView->setClipLayerRect(CCRECT_DIALOG_LIST);
		_pDialogListView->setWorldSpaceLeftBottomPoint(ccp(pParentLayer->getPosition().x + listRect.origin.x, 
			pParentLayer->getPosition().y + listRect.origin.y));
		_pDialogListView->setOnItemActionListener(this);
		pParentLayer->addChild(_pDialogListView);
		_pDialogListView->release();
	}
	_pDialogListView->setAdapter(this);

	// LH
	bool var = listSize.height - ((csSpBack.height/*+ space*/) * getCount()/* - space*/) < 0 ? true : false;
	_pDialogListView->setIsCanTouchMove(var);	

}

//Open the window. And closed
void DialogView::clickShopItemHandler()
{
	std::vector<ShopVo *>::iterator it = _npcDialogueVo->chatList.begin();
	ShopVo* pShopVo = *it;

	switch ( pShopVo->type )
	{
	case SHOP:		// 
		{
			int param = 1;

			if (ViewManager::getInstance()->figureView)
			{
				ViewManager::getInstance()->figureView->changeStage(1);// = _bankView;
			}
			
			// add code here
			BagMediator* p = (BagMediator*)g_pFacade->retrieveMediator(AppFacade_BAG_PROXY_CHANGE);
			p->bagPop();



			GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_SHOP, &param);
		}
		break;
	case BANK:		// 
		{
			int param = 0;
			GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_BAG, &param);
			GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_BANK, &param);
		}
		break;
	case APPOINT:		// 
		{
			if (RoleManage::Instance()->roleLev() >= LevLimitConst::Limit_Appoint)
			{
				int param = 1;
				GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_APPOINT, &param);
			}
			else
			{
				char path[128] = {0};
				sprintf(path , ValuesUtil::Instance()->getString("APT029").c_str() , LevLimitConst::Limit_Appoint);
				Message::Instance()->show(path , ccc3(233,12,25) , 1);
			}
		}
		break;
	case RECRUIT:		// 
		{
			int param = 0;
			GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_RECRUIT, &param);
		}
		break;
	//case MYSTIC:       // 
	//	{
	//		int param = 1;
	//		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_TRADER, &param);
	//	}
	//	break;
	//case ARMY:        // 
	//	{
	//		int param = 1;
	//		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_ARMY, &param);
	//	}
	//	break;
	case TRADER:       // 
		{
			if (g_pGlobalManage->_isOnBusiness)
			{
				LangManager::msgShow("TRD019");
				return;
			}
			
			if (RoleManage::Instance()->roleLev()<LevLimitConst::Limit_Paoshang)
			{
				char path[128] = {0};
				sprintf(path , ValuesUtil::Instance()->getString("TRD054").c_str() , LevLimitConst::Limit_Paoshang);
				Message::Instance()->show(path , ccc3(233,12,25) , 1);
				return;
			}
			
			int param = 1;
			GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_CITY_TRADER, &param);
		}
		break;
	case COPY:       // 
		{
			int param = 1;
			GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_TEAM_ROOM, &param);
		}
		break;
	}

	if ( this->getParent() )
	{
		this->closeDialog();
	}	
}

void DialogView::removeDataObjectChild()
{
	/*if (m_pLabelNPCName)
	{
		m_pLabelNPCName->setString("");
	}	

	if ( m_pSpriteHeadImage && m_pSpriteHeadImage->getParent())
	{
		m_pSpriteHeadImage->removeFromParentAndCleanup( true );
		m_pSpriteHeadImage = 0;
	}
	
	if (m_pLabelNPCContent)
	{
		m_pLabelNPCContent->setString("");
	}	*/

	/*if (_pDialogListView && _pDialogListView->getParent())
	{
		_pDialogListView->removeFromParentAndCleanup(true);
	}*/
	
	if (!_listViewItemsList.empty())
	{
		std::vector<LayerNode *>::iterator listItemIt;
		for(listItemIt = _listViewItemsList.begin();
			listItemIt != _listViewItemsList.end();
			++listItemIt)
		{
			LayerNode *tmp = (LayerNode *) *listItemIt;
			if(tmp && tmp->getParent())
			{
				tmp->removeFromParentAndCleanup(true);
				tmp->release();
			}
		}
		_listViewItemsList.clear();
	}

	// jae 20130125
	CCLayer *pParentLayer = (CCLayer *) this->getChildByTag(TAG_PARENT);
	if(pParentLayer) 
	{
		CCSprite *pSpriteHeadImage = (CCSprite *) pParentLayer->getChildByTag(TAG_IMAGE_HEAD); 
		if ( pSpriteHeadImage )
		{
			pParentLayer->removeChildByTag(TAG_IMAGE_HEAD, true);
		}

		CCTexture2D* pTex = CCTextureCache::sharedTextureCache()->textureForKey(_headImageContain.c_str());
		if (pTex && (pTex->retainCount()==1))
		{
			CCTextureCache::sharedTextureCache()->removeTextureForKey(_headImageContain.c_str());
		}		
	}

	//if(_npcDialogueVo)
	//{
	//	std:vector<TaskNodeVo *>::iterator taskNodeIt;
	//	for(taskNodeIt = _npcDialogueVo->taskList.begin();
	//		taskNodeIt != _npcDialogueVo->taskList.end();
	//		++ taskNodeIt)
	//	{
	//		TaskNodeVo *pTempTask = *taskNodeIt;
	//		if(!pTempTask)
	//			continue;

	//		std::vector < DialogueNodeVo * >::iterator dialogNodeIt;
	//		for(dialogNodeIt = pTempTask->_list.begin();
	//			dialogNodeIt != pTempTask->_list.end();
	//			++ dialogNodeIt)
	//		{
	//			CC_SAFE_DELETE(*dialogNodeIt);
	//		}
	//		CC_SAFE_DELETE(*taskNodeIt);
	//	}

	//	CC_SAFE_DELETE(_npcDialogueVo);
	//}
}
	

int DialogView::getCount()
{
	return _listViewItemsList.size();
}

LayerNode * DialogView::getView( int position )
{
	return _listViewItemsList[position];
}

void DialogView::onItemClickListener( LayerNode *itemCell, int position )
{
	CCLog("------pos=%d", position);
	DialogItem *pDialogItem = (DialogItem *) itemCell;
	if(!pDialogItem)
		return;

	DialogItemType type = pDialogItem->getType();

	switch(type)
	{
	case DIALOG_ITEM_TASK_BEGIN:
		{
			// Receive task.
			if(position >= _npcDialogueVo->taskList.size())
				break;
			
			pFocusTask = _npcDialogueVo->taskList[position];

			if(!pFocusTask)
				return;

			DialogueNodeVo *pDialogNodeVo = pFocusTask->_list[pFocusTask->_state];
			this->showDialog(pFocusTask, pDialogNodeVo);
		}
		break;

	case DIALOG_ITEM_TASK_REC:
		{
			// Receive task.
			if(position >= _npcDialogueVo->taskList.size())
				break;

			if(!pFocusTask)
				return;

			DialogueNodeVo *pDialogNodeVo = pFocusTask->_list[1];
			this->showDialog(pFocusTask, pDialogNodeVo);
		}
		break;

	case DIALOG_ITEM_TASK_ACCEPT:
		{
			if(position >= _npcDialogueVo->taskList.size())
				break;

			if(!pFocusTask)
				return;

			TaskEvent *pTaskEvent = new TaskEvent();
			pTaskEvent->taskType = pFocusTask->_type;
			pTaskEvent->id = pFocusTask->_id;
			GameDispatcher::getInstance()->dispatchEvent(TaskEvent::RECEIVE, pTaskEvent);
			/*TaskListenerMediator *taskListenerMediator = (TaskListenerMediator *)g_pFacade->retrieveMediator(AppFacade_TASK_LISTENER_MEDIATOR);
			taskListenerMediator->receiveHandler(pTask->_type, pTask->_id);*/
            CC_SAFE_DELETE(pTaskEvent);
			this->closeDialog();
		}
		break;

	case DIALOG_ITEM_TASK_SUBMIT:
		{
			/*_dispatcher.dispatchEvent(new TaskEvent(TaskEvent.SUBMIT,taskNodeVo.id,taskNodeVo.type));
			_taskVo = TaskManager.getInstance().getTask(taskNodeVo.id);
			if(_taskVo.endDes!=""){
			this.noStory = false;
			ModuleLoaderManage.getInstance().load(ResourceName.CHAPTER_PATH, LoadLevel.HIGH, chapterShown,_taskVo.endDes);
			}*/
			if(position >= _npcDialogueVo->taskList.size())
				break;

			if(!pFocusTask)
				return;

			TaskEvent *pTaskEvent = new TaskEvent();
			pTaskEvent->taskType = pFocusTask->_type;
			pTaskEvent->id = pFocusTask->_id;
			GameDispatcher::getInstance()->dispatchEvent(TaskEvent::SUBMIT, pTaskEvent);
			/*TaskListenerMediator *taskListenerMediator = (TaskListenerMediator *)g_pFacade->retrieveMediator(AppFacade_TASK_LISTENER_MEDIATOR);
			taskListenerMediator->submitHandler(pTask->_type, pTask->_id);*/
            CC_SAFE_DELETE(pTaskEvent);
			this->closeDialog();
		}
		break;

	case DIALOG_ITEM_TASK_NOFINISH:
		{
			if(!pFocusTask)
				return;
			GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::TASK_AUTO_FIND_NPC, 
				TaskManager::Instance()->getTask(pFocusTask->_id));
			this->closeDialog();
		}
		break;

	case DIALOG_ITEM_SHOP:
		clickShopItemHandler();
		break;

	default:
		break;
	}
}

void DialogView::onItemTouchListener( LayerNode *itemCell, int position )
{
	if(!itemCell)
	{
		return;
	}
	CCNode *pNormalNode = itemCell->getChildByTag(TAG_ITEM_BACKGROUND_NORMAL);
	CCNode *pPressedNode = itemCell->getChildByTag(TAG_ITEM_BACKGROUND_PRESSED);
	if(pNormalNode)
	{
		pNormalNode->setIsVisible(false);
	}
	if(pPressedNode)
	{
		pPressedNode->setIsVisible(true);
	}
}

void DialogView::onItemTouchCancelListener( LayerNode *itemCell, int position )
{
	if(!itemCell)
	{
		return;
	}
	CCNode *pNormalNode = itemCell->getChildByTag(TAG_ITEM_BACKGROUND_NORMAL);
	CCNode *pPressedNode = itemCell->getChildByTag(TAG_ITEM_BACKGROUND_PRESSED);
	if(pNormalNode)
	{
		pNormalNode->setIsVisible(true);
	}
	if(pPressedNode)
	{
		pPressedNode->setIsVisible(false);
	}
}

void DialogView::clickTaskOpeItemHandler( TaskNodeVo *pTask )
{
	// was not be used.

}

void DialogView::showDialog( TaskNodeVo *pTask, DialogueNodeVo *pDialog )
{
	if(!pDialog)
		return;

	int type = pDialog->_type;
	switch (type)
	{
	case SHOWTASK:
		this->showTask(pTask, pDialog);
		break;
	case RECEIVETASK:
		this->receiveTask(pTask, pDialog);
		break;
	case FINISHTASK:
		this->finishTask(pTask, pDialog);
		break;
	case NOFINISHTASK:
		this->noFinishTask(pTask, pDialog);
		break;
	default:
		break;
	}
	
}

void DialogView::showTask( TaskNodeVo *pTask, DialogueNodeVo *pDialog )
{
	//m_pLabelNPCContent->removeFromParentAndCleanup(false);
	CCLayer *pParentLayer = (CCLayer *) this->getChildByTag(TAG_PARENT);
	if(pParentLayer)
	{
		CCLabelTTF *pLabelNPCContent = (CCLabelTTF *)pParentLayer->getChildByTag(TAG_LABEL_CONTENT);
		pLabelNPCContent->setString(pDialog->_text.c_str());
	}
	//addChild(m_pLabelNPCContent);
	//Doyang 20120711
	//m_pLabelNPCContent->setString(pDialog->_text.c_str());
	this->addTaskOpeItem(1, pTask);
}

void DialogView::addTaskOpeItem( int type, TaskNodeVo *pTask )
{
	DialogItem *pAnswerItemLayer = new DialogItem();
	std::string labelStr;
	ValuesUtil *pValueUtil = ValuesUtil::Instance();
	switch(type)
	{
	case 1:
		{
			// Task begin.
			DialogueNodeVo *pDialog = pTask->_list[4];
			if(!pDialog)
				return;

			labelStr = pDialog->_text;
			//pAnswerItemLayer->setType(DIALOG_ITEM_TASK_REC);
			pAnswerItemLayer->setType(DIALOG_ITEM_TASK_ACCEPT);
		}
		break;
	case 2:
		{
			labelStr = pValueUtil->getString("task_rec");
			pAnswerItemLayer->setType(DIALOG_ITEM_TASK_ACCEPT);
		}
		break;
	case 3:
		{
			labelStr = pValueUtil->getString("task_sub");
			pAnswerItemLayer->setType(DIALOG_ITEM_TASK_SUBMIT);
		}
		break;
	case 4:
		{
			labelStr = pValueUtil->getString("task_ok");
			pAnswerItemLayer->setType(DIALOG_ITEM_TASK_NOFINISH);
		}
		break;
	default:
		{
			labelStr = "No Words.";
		}
		break;
	}
	if(!pAnswerItemLayer || !pAnswerItemLayer->init())
	{
		return;
	}
	// Add list item value.
	//_listValueList.push_back(pTask);

	CCSprite* spriteBack = CCSprite::spriteWithSpriteFrameName( "npcdialog/npc_talk_list.png" );
	CCSize csSpBack = spriteBack->getContentSize();

	pAnswerItemLayer->setContentSize( csSpBack );
	pAnswerItemLayer->setvisibleSize( csSpBack );

	CCLabelTTF* pTaskNameLabel = CCLabelTTF::labelWithString(
		labelStr.c_str(), 
		CCSIZE_ITEM_TASK_NAME, 
		CCTextAlignmentLeft, 
		"Arial", 
		POSX(20));
	pTaskNameLabel->setColor(ccc3(255, 255, 0));
	pTaskNameLabel->setPosition( CCPOINT_ITEM_TASK_NAME_TO_SP );
	pTaskNameLabel->setAnchorPoint( CCPointZero );
	pTaskNameLabel->setIsRelativeAnchorPoint(true);

	CCSprite* spritePoint = CCSprite::spriteWithSpriteFrameName( "npcdialog/point.png" );
	spritePoint->setAnchorPoint( CCPointZero );
	spritePoint->setPosition( CCPOINT_ITEM_TASK_POINT_TO_SP );
	spriteBack->addChild( spritePoint );

	spriteBack->setAnchorPoint( CCPointZero );
	spriteBack->setPosition( CCPOINT_ITEM_TASK_NAME );

	pAnswerItemLayer->addChild( spriteBack, 0, TAG_ITEM_BACKGROUND_NORMAL  );

	CCSprite* spriteBackPressed = CCSprite::spriteWithSpriteFrameName( "npcdialog/npc_talk_list_pressed.png" );
	CCSprite* spritePoint2 = CCSprite::spriteWithSpriteFrameName( "npcdialog/point.png" );
	spritePoint2->setAnchorPoint( CCPointZero );
	spritePoint2->setPosition( CCPOINT_ITEM_TASK_POINT_TO_SP );
	spriteBackPressed->addChild( spritePoint2 );
	spriteBackPressed->setAnchorPoint( CCPointZero );
	spriteBackPressed->setPosition( CCPOINT_ITEM_TASK_NAME );
	pAnswerItemLayer->addChild( spriteBackPressed, 0, TAG_ITEM_BACKGROUND_PRESSED );
	spriteBackPressed->setIsVisible(false);
	pAnswerItemLayer->addChild( pTaskNameLabel );

	//Doyang 20120711
	//_pDialogListView->removeAllChildrenWithCleanup(true);
	std::vector<LayerNode *>::iterator listItemIt;
	for(listItemIt = _listViewItemsList.begin();
		listItemIt != _listViewItemsList.end();
		++listItemIt)
	{
		LayerNode *tmp = (LayerNode *) *listItemIt;
		if(tmp && tmp->getParent())
		{
			tmp->removeFromParentAndCleanup(true);
			tmp->release();
		}
	}

	_listViewItemsList.clear();
	_listViewItemsList.push_back(pAnswerItemLayer);
	_pDialogListView->setAdapter(this);
}

void DialogView::closeDialog()
{
	this->setisPop( false );
}

void DialogView::receiveTask( TaskNodeVo *pTask, DialogueNodeVo *pDialog )
{
	//m_pLabelNPCContent->removeFromParentAndCleanup(false);

	CCLayer *pParentLayer = (CCLayer *) this->getChildByTag(TAG_PARENT);
	if(pParentLayer)
	{
		CCLabelTTF *pLabelNPCContent = (CCLabelTTF *)pParentLayer->getChildByTag(TAG_LABEL_CONTENT);
		pLabelNPCContent->setString(pDialog->_text.c_str());
	}
	//m_pLabelNPCContent->setString(pDialog->_text.c_str());
	//addChild(m_pLabelNPCContent);
	this->addTaskOpeItem(2, pTask);
}

void DialogView::finishTask( TaskNodeVo *pTask, DialogueNodeVo *pDialog )
{
	//m_pLabelNPCContent->removeFromParentAndCleanup(false);

	CCLayer *pParentLayer = (CCLayer *) this->getChildByTag(TAG_PARENT);
	if(pParentLayer)
	{
		CCLabelTTF *pLabelNPCContent = (CCLabelTTF *)pParentLayer->getChildByTag(TAG_LABEL_CONTENT);
		pLabelNPCContent->setString(pDialog->_text.c_str());
	}
	//m_pLabelNPCContent->setString(pDialog->_text.c_str());
	//addChild(m_pLabelNPCContent);
	this->addTaskOpeItem(3, pTask);
}

void DialogView::noFinishTask( TaskNodeVo *pTask, DialogueNodeVo *pDialog )
{
	//m_pLabelNPCContent->removeFromParentAndCleanup(false);

	CCLayer *pParentLayer = (CCLayer *) this->getChildByTag(TAG_PARENT);
	if(pParentLayer)
	{
		CCLabelTTF *pLabelNPCContent = (CCLabelTTF *)pParentLayer->getChildByTag(TAG_LABEL_CONTENT);
		pLabelNPCContent->setString(pDialog->_text.c_str());
	}
	//m_pLabelNPCContent->setString(pDialog->_text.c_str());
	//addChild(m_pLabelNPCContent);
	this->addTaskOpeItem(4, pTask);
}

void DialogView::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
}

bool DialogView::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

int DialogView::npcId()
{
	if(_npcDialogueVo){
		_npcId = _npcDialogueVo->npcId;
	}
	return _npcId;
}

CCNode * DialogView::getNewHandItem( int typeId )
{
	if(_pDialogListView)
	{
		if(_pDialogListView->getChilds()->count() > 0)
		{
			return _pDialogListView->getChilds()->getObjectAtIndex(0);
		}
	}
	return NULL;
}
