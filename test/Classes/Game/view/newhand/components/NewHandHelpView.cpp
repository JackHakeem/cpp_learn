#include "NewHandHelpView.h"
#include "../../../../UIComponent/CCUIBackground.h"
#include "../../../utils/ScaleUtil.h"
#include "manager/GlobalManage.h"
#include "model/task/TaskProxy.h"
#include "control/AppFacade.h"
#include "model/newhand/vo/HelpScriptVo.h"
#include "model/newhand/NewhandManager.h"
#include "utils/ValuesUtil.h"
#include "manager/TouchLayerEnum.h"
#include "model/scene/SceneProxy.h"
#include "manager/ViewManager.h"
#include "events/GameDispatcher.h"

#define Pos_BtnText	ccp(/*POSX(960)/2.0*/ + POSX(30), /*POSX(640)/2.0*/ - POSX(160))
#define Pos_BtnClose	ccp(/*POSX(960)/2.0*/ + POSX(442) , /*POSX(640)/2.0*/ + POSX(160))
#define Pos_BodyIcon		ccp(POSX(130) , /*POSX(640)/2.0*/ + POSX(-12))
#define Pos_TitleText		ccp(/*POSX(960)/2.0*/ + POSX(80), /*POSX(640)/2.0*/ + POSX(160))
#define Pos_Content	ccp(/*POSX(960)/2.0*/ + POSX(66), /*POSX(640)/2.0*/ - POSX(20))

NewHandHelpView::NewHandHelpView()
{
	_curId = 1040;
	init();
}

NewHandHelpView::~NewHandHelpView()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/loading/res_loading.plist");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/loading/res_loading.pvr.ccz");
}

bool NewHandHelpView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	_winSize = CCDirector::sharedDirector()->getWinSize();

	this->setIsTouchEnabled(false);

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/loading/res_loading.plist");

	loadItems();

}

void NewHandHelpView::loadItems()
{
	
	CCUIBackground * pBack = new CCUIBackground();
	pBack->initWithSpriteFrame("ui.png" , ccp(0,0) ,  ccp(0,0)  , CCSizeMake(_winSize.width , POSX(400)));
	pBack->setPosition(ccp(POSX(0) , _winSize.height/2 - POSX(200)));
	this->addChild(pBack);
	pBack->release();

	CCUIBackground * pContentBack = new CCUIBackground();
	pContentBack->initWithSpriteFrame("ui2.png" , ccp(0,0) ,  ccp(0,0)  , CCSizeMake(_winSize.width/2 , POSX(260)));
	pContentBack->setPosition(ccp(POSX(300) *_winSize.width/POSX(960.0f) , _winSize.height/2 - POSX(126)));
	this->addChild(pContentBack,1);
	pContentBack->release();

	addButtons();

	setBodyIcon("loading/girl.png");
	setTitle("");
	setContent("");
	setBtnText("");
}

void NewHandHelpView::addButtons()
{
	// main btn
	
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			CCMenuItemSprite *pDoMenuImage = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this,
				menu_selector(NewHandHelpView::onDo));
			pDoMenuImage->setScaleX(2.0);
			CCMenu * pDoMenu = CCMenu::menuWithItem(pDoMenuImage);	
			pDoMenu->setTouchLayer(TLE::TipsLayer);
			pDoMenu->setPosition(ccp(Pos_BtnText.x +  _winSize.width/2, Pos_BtnText.y + _winSize.height/2));
			pDoMenu->setTag(TAG_Btn);
			pDoMenu->setIsVisible(false);
			pDoMenu->setTouchLayer(TLE::WindowLayer_TaskFollowView -1);
			this->addChild(pDoMenu,1);
		}
	}

	// pre btn
	CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
	CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
	CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
	if(!pNormalSprite || !pPressedSprite || !pSelectdSprite)
	{
		return;
	}
	CCMenuItemSprite *pPreMenuImage = CCMenuItemSprite::itemFromNormalSprite(
		pNormalSprite,
		pPressedSprite,
		pSelectdSprite,
		this,
		menu_selector(NewHandHelpView::onPreView));
	CCMenu * pPreMenu = CCMenu::menuWithItem(pPreMenuImage);	
	pPreMenu->setTouchLayer(TLE::TipsLayer);
	pPreMenu->setPosition(ccp(_winSize.width - POSX(100) , _winSize.height/2 + Pos_BtnClose.y - POSX(160)));
	pPreMenu->setTag(TAG_Btn_Pre);
	this->addChild(pPreMenu,1);


	CCLabelTTF * pPreText = CCLabelTTF::labelWithString(
		ValuesUtil::Instance()->getString("NH004").c_str() ,
		CCSizeMake(POSX(96) , POSX(28)) , 
		CCTextAlignmentCenter , "Arial" , POSX(28));
	pPreText->setColor(ccc3(255,215,0));
	pPreText->setPosition(ccp(pPreMenuImage->getContentSize().width/2 , pPreMenuImage->getContentSize().height/2));
	pPreMenuImage->addChild(pPreText,2);

	// next btn
	CCSprite *pNormalSprite1 = CCSprite::spriteWithSpriteFrameName("button.png");
	CCSprite *pPressedSprite1 = CCSprite::spriteWithSpriteFrameName("button1.png");
	CCSprite *pSelectdSprite1 = CCSprite::spriteWithSpriteFrameName("button2.png");
	if(!pNormalSprite1 || !pPressedSprite1 || !pSelectdSprite1)
	{
		return;
	}

	CCMenuItemSprite *pNextMenuImage = CCMenuItemSprite::itemFromNormalSprite(
		pNormalSprite1,
		pPressedSprite1,
		pSelectdSprite1,
		this,
		menu_selector(NewHandHelpView::onNextView));
	CCMenu * pNextMenu = CCMenu::menuWithItem(pNextMenuImage);	
	pNextMenu->setTouchLayer(TLE::TipsLayer);
	pNextMenu->setPosition(ccp(_winSize.width - POSX(100)  , _winSize.height/2 + Pos_BtnClose.y - POSX(260)));
	pNextMenu->setTag(TAG_Btn_Next);
	this->addChild(pNextMenu,1);
	
	CCLabelTTF * pNextText = CCLabelTTF::labelWithString(
		ValuesUtil::Instance()->getString("NH005").c_str() ,
		CCSizeMake(POSX(96) , POSX(28)) , 
		CCTextAlignmentCenter , "Arial" , POSX(28));
	pNextText->setColor(ccc3(255,215,0));
	pNextText->setPosition(ccp(pNextMenuImage->getContentSize().width/2 , pNextMenuImage->getContentSize().height/2));
	pNextMenuImage->addChild(pNextText,2);

	// close btn
	pNormalSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_normal.png");
	pPressedSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_pressed.png");
	CCMenuItemSprite *pCloseMenuImage = CCMenuItemSprite::itemFromNormalSprite(
		pNormalSprite,
		pPressedSprite,
		this,
		menu_selector(NewHandHelpView::onCloseView));
	CCMenu * pCloseMenu = CCMenu::menuWithItem(pCloseMenuImage);	
	pCloseMenu->setTouchLayer(TLE::TipsLayer);
	pCloseMenu->setPosition(ccp(_winSize.width - POSX(40) , Pos_BtnClose.y + _winSize.height/2));
	this->addChild(pCloseMenu,1);
}

void NewHandHelpView::setBodyIcon(std::string strPath)
{
	CCSprite * pBodyIcon = (CCSprite * )this->getChildByTag(TAG_BodyIcon);
	if (pBodyIcon)
	{
		this->removeChildByTag(TAG_BodyIcon , true);
	}

	pBodyIcon = new CCSprite();
	pBodyIcon->initWithSpriteFrameName(strPath.c_str());
	pBodyIcon->setFlipX(true);
	pBodyIcon->setTag(TAG_BodyIcon);
	pBodyIcon->setScale(0.9);
	pBodyIcon->setPosition(ccp(Pos_BodyIcon.x , Pos_BodyIcon.y + _winSize.height/2));
	this->addChild(pBodyIcon);
	pBodyIcon->release();
}

void NewHandHelpView::setTitle(std::string strTitle)
{
	CCLabelTTF * pTitleText = (CCLabelTTF * )this->getChildByTag(TAG_Title);
	if (pTitleText)
	{
		pTitleText->setString(strTitle.c_str());
	}
	else
	{
		pTitleText = CCLabelTTF::labelWithString(
			strTitle.c_str() , CCSizeMake(POSX(700) , POSX(36) ), 
			CCTextAlignmentCenter , "Arial" , POSX(36));
		pTitleText->setTag(TAG_Title);
		pTitleText->setPosition(ccp(Pos_TitleText.x  + _winSize.width/2 , Pos_TitleText.y + _winSize.height/2));
		this->addChild(pTitleText,2);
	}
}

void NewHandHelpView::setContent(std::string strContent)
{
	CCLabelTTF * pContentText = (CCLabelTTF * )this->getChildByTag(TAG_Content);
	if (pContentText)
	{
		pContentText->setString(strContent.c_str());
	}
	else
	{
		pContentText = CCLabelTTF::labelWithString(
			strContent.c_str() , CCSizeMake(POSX(456) , POSX(280)) , 
			CCTextAlignmentLeft , "Arial" , POSX(36));
		pContentText->setTag(TAG_Content);
		pContentText->setColor(ccc3(255,255,0));
		pContentText->setPosition(ccp(Pos_Content.x + _winSize.width/2 , Pos_Content.y + _winSize.height/2 + POSX(10)));
		this->addChild(pContentText,2);
	}
}

void NewHandHelpView::setBtnText(std::string strBtnTxt)
{
	CCLabelTTF * pBtnText =(CCLabelTTF *) this->getChildByTag(TAG_Btn_Text);
	if (pBtnText)
	{
		pBtnText->setString(strBtnTxt.c_str());
	}
	else
	{
		pBtnText = CCLabelTTF::labelWithString(
			strBtnTxt.c_str() , CCSizeMake(POSX(240) , POSX(28) ), 
			CCTextAlignmentCenter , "Arial" , POSX(28));
		pBtnText->setTag(TAG_Btn_Text);
		pBtnText->setPosition(ccp(Pos_BtnText.x + _winSize.width/2 , Pos_BtnText.y + _winSize.height/2));
		pBtnText->setColor(ccc3(255,215,0));
		pBtnText->setIsVisible(false);
		this->addChild(pBtnText,2);
	}
}

void NewHandHelpView::showOKButton(bool var)
{
	CCMenu * pBtn = (CCMenu *)this->getChildByTag(TAG_Btn);
	if (pBtn)
	{
		pBtn->setIsVisible(var);
	}
	CCLabelTTF * pBtnText = (CCLabelTTF * )this->getChildByTag(TAG_Btn_Text);
	if (pBtnText)
	{
		pBtnText->setIsVisible(var);
	}
}

void NewHandHelpView::onCloseView(CCObject * pSender)
{
	this->setIsVisible(false);
}

HelpScriptVo * NewHandHelpView::getHelpScript(int id)
{
	HelpScriptVo * pHelpScript = 0;
	
	if (id > 1)
	{
		std::map<int, HelpScriptVo *>::iterator iter =  NewhandManager::Instance()->_helpScriptDic.find(id);
		if (iter != NewhandManager::Instance()->_helpScriptDic.end())
		{
			pHelpScript = iter->second;
		}
	}
	else
	{
		int nId = _curId;
		std::map<int, HelpScriptVo *>::iterator iter =  NewhandManager::Instance()->_helpScriptDic.find(nId);
		pHelpScript = iter->second;
		do 
		{
			pHelpScript = 0;
			id ? ++iter : --iter;
			if (iter != NewhandManager::Instance()->_helpScriptDic.end())
			{
				pHelpScript = iter->second;
			}
		}
		while (pHelpScript && pHelpScript->isIgnore);
	}
	return pHelpScript;
}

void NewHandHelpView::onPreView(CCObject * pSender)
{
	HelpScriptVo * pHelpScript = getHelpScript(0);
	if (pHelpScript)
	{
		setTitle(pHelpScript->title);
		setContent(pHelpScript->content);
		setBtnText(pHelpScript->btntxt);
		showOKButton(pHelpScript->isBtnShow);
		_curId = pHelpScript->id;
	}
}

void NewHandHelpView::onNextView(CCObject * pSender)
{
	HelpScriptVo * pHelpScript = getHelpScript(1);
	if (pHelpScript)
	{
		std::string type = pHelpScript->type;
		if (type == "progress")
		{
			SceneProxy * pProxy = (SceneProxy * )g_pFacade->retrieveProxy(AppFacade_SCENE_PROXY);
			if (pProxy)
			{
				int processid = pHelpScript->processid - 40000;
				std::map<int, int>::iterator iter = pProxy->_sceneProgress.find(processid);
				if (iter == pProxy->_sceneProgress.end())
				{
					return;
				}
			}
		}
		else if (type == "task")
		{
			bool isExist = false;
			TaskProxy * pProxy = (TaskProxy * )g_pFacade->retrieveProxy(AppFacade_TASK_PROXY);
			if (pProxy)
			{
				std::vector<TaskVo *>::iterator iter = pProxy->_receivedTaskList.begin();
				for (iter ; iter != pProxy->_receivedTaskList.end() ; iter++)
				{
					if ((*iter)->_id == pHelpScript->processid)
					{
						isExist = true;
						break;
					}
				}
				if (!isExist)
				{
					//return;
				}
			}
		}
		else if (type == "level")
		{
			if (pHelpScript->processid > (10000+RoleManage::Instance()->roleLev()))
			{
				return;
			}
		}
		else if (type == "newhand")
		{

		}

		setTitle(pHelpScript->title);
		setContent(pHelpScript->content);
		setBtnText(pHelpScript->btntxt);
		showOKButton(pHelpScript->isBtnShow);
		_curId = pHelpScript->id;
	}
}

void NewHandHelpView::resetView(int id)
{
	HelpScriptVo * pHelpScript = getHelpScript(id);
	if (pHelpScript)
	{
		setTitle(pHelpScript->title);
		setContent(pHelpScript->content);
		setBtnText(pHelpScript->btntxt);
		showOKButton(pHelpScript->isBtnShow);
		_curId = pHelpScript->id;
	}
}

void NewHandHelpView::initView()
{
	/*
	TaskProxy * pProxy = (TaskProxy * )g_pFacade->retrieveProxy(AppFacade_TASK_PROXY);
	if (pProxy)
	{
		std::vector<TaskVo *>::iterator iter = pProxy->_receivedTaskList.begin();
		for (iter ; iter != pProxy->_receivedTaskList.end() ; iter++)
		{
			if ((*iter)->_id == pHelpScript->processid)
			{
				isExist = true;
				break;
			}
		}
		if (!isExist)
		{
			//return;
		}
	}
	*/
}

void NewHandHelpView::showPreNextButton(bool bPre, bool bNext)
{
	CCMenu * pPreMenu = (CCMenu *)this->getChildByTag(TAG_Btn_Pre);
	if (pPreMenu)
	{
		pPreMenu->setIsVisible(bPre);
	}
	CCMenu * pNextMenu = (CCMenu *)this->getChildByTag(TAG_Btn_Next);
	if (pNextMenu)
	{
		pNextMenu->setIsVisible(bNext);
	}
}

void NewHandHelpView::onDo(CCObject * pSender)
{
	HelpScriptVo * pHelpScript = 0;
	std::map<int, HelpScriptVo *>::iterator iter =  NewhandManager::Instance()->_helpScriptDic.find(_curId);
	if (iter != NewhandManager::Instance()->_helpScriptDic.end())
	{
		pHelpScript = iter->second;
	}
	switch (pHelpScript->action[0])
	{
	case 0:
		{
			return;
		}
		break;
	case 1:
		{
			if (pHelpScript->newhandid)
			{

			}
			else
			{
				showPanel(pHelpScript);
			}
		}
		break;
	case 2:
		{

		}
		break;
	default:
		break;
	}
}

void NewHandHelpView::showPanel(HelpScriptVo * pHelpVo)
{
	switch (pHelpVo->action[1])
	{
	case 9: // formation
		{
			if (ViewManager::getInstance() && ViewManager::getInstance()->mainNavigate)
			{
				ViewManager::getInstance()->mainNavigate->popUIHandler9(0);
			}
			//
			doAction(pHelpVo);
		}
		break;
	default :
		{
			
		}
		break;
	}

	onCloseView(0);
}

void NewHandHelpView::doAction(HelpScriptVo * pHelpVo)
{

 	/*
	CCSprite * pActionSprite = new CCSprite();
	pActionSprite->initWithFile("assets/ui/newhand/finger.png");
	pActionSprite->setPosition(ccp(POSX(400),POSX(200)));
	if (LayerManager::newhandLayer->getChildByTag(2012))
	{
		LayerManager::newhandLayer->removeChildByTag(2012 , true);
	}
	LayerManager::newhandLayer->addChild(pActionSprite,0,2012);
	pActionSprite->release();

	CCFiniteTimeAction * pStand = CCMoveBy::actionWithDuration(0.2f , ccp(0,0));
	CCFiniteTimeAction * pMove = CCMoveBy::actionWithDuration(0.6f , ccp(0,POSX(-120)));
	CCAction* pAction =CCSequence::actions(pStand , pMove , 0);
	pActionSprite->runAction(pAction);
	*/
}

void NewHandHelpView::resetView(CCNode * pNode , void * pData)
{
	int id = _curId;
	int data = *(int *)pData;
	bool isModify = false;
	if (data > 40000) // progress id
	{
		id = NewhandManager::Instance()->getIDByProcessID(data);
		if (id)
		{
			resetView(id);
			isModify = true;
		}
		else
		{
			return;
		}
	}
	else if (data > 30000) // task id
	{
		id = NewhandManager::Instance()->getIDByProcessID(data);
		if (id)
		{
			resetView(id);
			isModify = true;
		}
		else
		{
			return;
		}
	}
	else if (data > 20000) // new hand id
	{
		id = NewhandManager::Instance()->getIDByProcessID(data);
		if (id)
		{
			resetView(id);
			isModify = true;
		}
		else
		{
			return;
		}
	}
	else if (data > 10000) // level
	{
		id = NewhandManager::Instance()->getIDByProcessID(data);
		if (id)
		{
			resetView(id);
			isModify = true;
		}
		else
		{
			return;
		}
	}
	else
	{

	}

	if ((!id)||(!isModify))
	{
		return;
	}
	// pop view
	HelpScriptVo * pHelpScriptVo = getHelpScript(id);
	if (pHelpScriptVo)
	{
		int autoPop = pHelpScriptVo->AutoPop;
		switch (autoPop)
		{
		case 0:
			{

			}
			break;
		case 1:
			{
				// highlight
				if (ViewManager::getInstance()->_helpButton)
				{
					CCFiniteTimeAction * pFadeOut = CCFadeOut::actionWithDuration(0.5f );
					CCFiniteTimeAction * pFadeOutR = pFadeOut->reverse();
					CCAction * pAction = CCRepeatForever::actionWithAction(CCSequence::actionOneTwo(pFadeOut , pFadeOutR));
					if (ViewManager::getInstance()->_helpButton->getChildByTag(102))
					{
						ViewManager::getInstance()->_helpButton->getChildByTag(102)->runAction(pAction);
					}
				}
			}
			break;
		case 2:
			{
				// pop out
				if (ViewManager::getInstance()->mainNavigate)
				{
					ViewManager::getInstance()->mainNavigate->popUIHandlerHelp(0);
				}
			}
			break;
		default:
			break;
		}
	}
}