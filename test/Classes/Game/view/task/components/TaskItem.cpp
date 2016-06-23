#include "TaskItem.h"
#include "model/task/vo/TaskVo.h"
#include "model/scene/NPCManager.h"
#include "TaskStrConcat.h"
#include "utils/ScaleUtil.h"
#include "utils/ValuesUtil.h"
#include "../TaskMediator.h"
#include "control/AppFacade.h"
#include "manager/TouchLayerEnum.h"
#include "CCUIBackground.h"
#include "manager/ViewManager.h"

TaskItem::TaskItem(TaskVo * taskVo)
{
	if (!CCLayer::init())
	{
		return;
	}

	if (!taskVo)
	{
		return;
	}
	_taskVo = taskVo;

	// add head icon
	bool isFinish = TaskStrConcat::checkTaskFinish(taskVo->_taskTip);

	NPCVo *pNpcVo = NULL;
	if(isFinish)
	{
		pNpcVo = NPCManager::Instance()->getNPC(taskVo->getFinishTaskNpc());
	}
	else
	{
		if (taskVo->isRecived())
		{
			pNpcVo = NPCManager::Instance()->getNPC(taskVo->getFinishTaskNpc());
		}
		else
		{
			pNpcVo = NPCManager::Instance()->getNPC(taskVo->getCanTaskNpc(taskVo->_id));
		}		
	}

	if(!pNpcVo )
	{
		pNpcVo = NPCManager::Instance()->getNPC(taskVo->getRecTaskNpc());
	}
	

	if (!pNpcVo)
	{
		return;
	}
	
	CCSprite *pNpcIconSprite = new CCSprite();
	char pNpcIconPath[30];
	//sprintf(pNpcIconPath, "assets/res/%d/head.png", pNpcVo->_resId);
	sprintf(pNpcIconPath, "assets/res/%d/halfbody.png", pNpcVo->_resId);
	bool var = pNpcIconSprite->initWithFile(pNpcIconPath);
	if(!var)
	{
		pNpcIconSprite->initWithFile("assets/icon/head/unknown.png");
		pNpcIconSprite->setScale(/*0.815*/1);
	}

	CCSize size = pNpcIconSprite->getContentSize();
	this->setContentSize(size);

	pNpcIconSprite->setAnchorPoint(ccp(0.5 , 0));
	pNpcIconSprite->setPosition(ccp(size.width/2, POSX(17)));
	pNpcIconSprite->setTag(0);
	pNpcIconSprite->setScale(0.400);
	this->addChild(pNpcIconSprite , 0);
	pNpcIconSprite->release();


	//add name 
	/*
	char pName[64] = {0};
	if(taskVo->_type == 1)
	{
		sprintf(pName, "%s%s", ValuesUtil::Instance()->getString("task_lord2").c_str(), pNpcVo->name.c_str());
	}
	else
	{
		sprintf(pName, "%s%s", ValuesUtil::Instance()->getString("task_other2").c_str(), pNpcVo->name.c_str());
	}

	CCSprite * pNameBtnSprite1 = CCSprite::spriteWithSpriteFrameName("ui/tab.png");
	CCSprite * pNameBtnSprite2 = CCSprite::spriteWithSpriteFrameName("ui/tab.png");
	pNameBtnSprite2->setColor(ccc3(12,233,25));
	CCMenuItemSprite * pMenuSpriteName = CCMenuItemSprite::itemFromNormalSprite(
		pNameBtnSprite1,
		pNameBtnSprite2,
		this,
		menu_selector(TaskItem::onClickShowTask));
	pMenuSpriteName->setScale(0.7);
	pMenuSpriteName->setTag(taskVo->_id);
	CCSize mnsize = pMenuSpriteName->getContentSize();
	CCLabelTTF * pNpcNameText = CCLabelTTF::labelWithString((const char *)pName,CCSizeMake(POSX(160) , POSX(24)),CCTextAlignmentCenter , "Arial" , POSX(22));
	pNpcNameText->setPosition(ccp(mnsize.width/2, mnsize.height/2));
	pNpcNameText->setColor(ccc3(255,215,0));
	pMenuSpriteName->addChild(pNpcNameText , 0);
	pMenuSpriteName->setPosition(ccp(size.width/2, POSX(6-6)));
	CCMenu * pMenuName = CCMenu::menuWithItem(pMenuSpriteName);
	pMenuName->setPosition(ccp(0,0));
	pMenuName->setTouchLayer(TLE::SceneUILayer -2);
	pMenuName->setTag(Tag_NameBtn);
	this->addChild(pMenuName , 1);
	*/
	/*
	if (ViewManager::getInstance()->_taskUIView)
	{
		ViewManager::getInstance()->_taskUIView->updateTaskButtonInfo(taskVo);
	}
	*/

	//ennableNameButtonTouch(false);
}

void TaskItem::onClickShowTask(CCObject * pSender)
{
	TaskMediator *pTaskMediator = (TaskMediator *)g_pFacade->retrieveMediator(AppFacade_TASK_MEDIATOR);
	if(pTaskMediator) 
	{
		pTaskMediator->openTaskView();
		if (pTaskMediator->_pTaskView)
		{
			//pTaskMediator->_pTaskView->showTaskListItemByID(((CCNode *)pSender)->getTag());
		}		
	}
}

void TaskItem::setNameTouchPriority(int pri)
{
	CCMenu * pMenuFont = (CCMenu *)this->getChildByTag(Tag_NameBtn);
	if (pMenuFont)
	{
		pMenuFont->setTouchLayer(pri);
	}
}

void TaskItem::ennableNameButtonTouch(bool var)
{
	if (ViewManager::getInstance()->_taskUIView
		&& ViewManager::getInstance()->_taskUIView->_pMenuSpriteName)
	{
		((CCMenuItemSprite *)(ViewManager::getInstance()->_taskUIView->_pMenuSpriteName))->setIsEnabled(var);
	}
}

TaskItem::~TaskItem()
{

}
