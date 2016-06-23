#include "FormationMediator.h"
#include "control/formation/FormationCommand.h"
#include "control/AppFacade.h"
#include "manager/ViewManager.h"
#include "model/player/RoleManage.h"
#include "model/skill/SkillProxy.h"
#include "manager/GlobalManage.h"
#include "manager/LayerManager.h"
#include "Message.h"
#include "utils/ValuesUtil.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"
#include "socket/command/s31/SCMD310.h"
#include "socket/command/s31/SCMD312.h"
#include "model/newhand/vo/NewhandConst.h"
#include "model/newhand/NewhandManager.h"
#include "model/newhand/vo/TestNewhand.h"
#include "model/skill/SkillManager.h"
#include "model/skill/vo/SkillType.h"

FormationMediator::FormationMediator()
{
	_formationView = 0;
	GameDispatcher::getInstance()->addEventListener(PopEventName::SHOW_UI_FORMATION, this, callfuncND_selector(FormationMediator::popHandler));
}

void FormationMediator::handleNotification( int M2Vcmd, char* data )
{
	switch(M2Vcmd)
	{

	case MEMBER_CHANGE_SUCCESS:
		break;
	case TEAM_MEMBER_INIT:
		break;
	case TEAM_MEMBER_UPDATE:
		break;
	case TEAM_MEMBER_CHANGE_SIT:
		break;
	case UPDATE_FORMATION_LIST:
		break;
	default:
		break;
	}
}

void FormationMediator::initFormationInfo( char* data )

{
	sendNotification(Facade_Command, AppFacade_FORMATION_PROXY_CHANGE, data, FormationCommand::INIT_FORMATION);//这里要通知控制层处理 
}

void FormationMediator::openFormationView()
{
	//_formationView = ViewManager::getInstance()->formationView;
	//if (!_formationView)
	{
		_formationView = new FormationView();
		if((_formationView)&&_formationView->init())
		{
			_formationView->setAnchorPoint(CCPointZero);
			_formationView->setIsRelativeAnchorPoint(true);
			_formationView->setPosition(CCPointZero);
			CCLog("formation:new FormationView() success");
		}
		else
		{
			CCLog("formation:new FormationView() failed");
			return;
		}
		ViewManager::getInstance()->formationView = this->_formationView;
		
	}
	//Doyang 20120829
	popView(); // LH0719
	// test
	_formationView->setisPop(!_formationView->getisPop());
	_formationView->release();//k1220

	if (_formationView->getisPop())
	{
		g_pGlobalManage->setCurFocusGID(LayerManager::windowLayer->getMyFocusGID());
	}
	else
	{
		g_pGlobalManage->setCurFocusGID(LayerManager::sceneLayer->getMyFocusGID());
	}
 
	    //cocos2d::CCLog("new FormationView()");
		//_formationView =new FormationView();
		//ViewManager::getInstance()->formationView=_formationView;

	 
	//_formationView->setisPop(!_formationView->getisPop());
	//popView();
}

void FormationMediator::popView()
{

	//startViewListener();
	//doyang
	_formationView->createHeadList();
	createFormationList();

	_formationView->specialHandlerForInit();
	//_formationView.setBtn();
	cocos2d::CCLog("PopView()");
}

      /**
		 * Create formations list.
		 * 
		 */	


void FormationMediator::createFormationList()
{
	if(_formationView!=NULL)
	{
		if(RoleManage::Instance()->accountInfo() == NULL)
			return;

		int teamStatus = RoleManage::Instance()->accountInfo()->team;
		int watchFormation = 0;
		if(teamStatus==0)
		{
			watchFormation = RoleManage::Instance()->accountInfo()->currFormation;   //Get the current opening formation
		}
		
		 
		SkillProxy* _skillProxy = (SkillProxy*)g_pFacade->retrieveProxy(AppFacade_SKILL_PROXY);

		//Converting a, by liuzhuhua
		std::map<int, FormationInfo*> info;
		//std::map<int, SkillNode>::iterator iter = _skillProxy->_formationDic->begin();

		// modify by LH0727
		std::map<int, SkillNode> * pLearnedFormation = SkillManager::Instance()->getLearnedSkillsByRank(SkillType::FORMATION);
		if (!pLearnedFormation)	{return;	}		
		std::map<int, SkillNode>::iterator iter = pLearnedFormation->begin();
		for(; iter != pLearnedFormation->end(); ++iter)
		{
			if(iter->second.formationInfo)
				info.insert(make_pair(iter->first, iter->second.formationInfo));
		}
		//end
		//doyang
		_formationView->createFormationList(teamStatus, watchFormation,  info);
		
	}
}

void FormationMediator::sockFormationActive( char * data )
{
	sendNotification(Facade_Command,AppFacade_FORMATION_PROXY_CHANGE,data,FormationCommand::FORMATION_ACTIVATE);
}

void FormationMediator::formationActive( char * data )
{
	SCMD312 * cmd = (SCMD312 *)data;
	if (cmd->a_isOk)
	{
		Message::Instance()->show(ValuesUtil::Instance()->getString("ZX1"),ccc3(255,133,22),1);
	}
	else
	{
		Message::Instance()->show(ValuesUtil::Instance()->getString("ZX2"),ccc3(255,133,22),1);
		return;
	}
	
	RoleManage::Instance ()->_accountInfo.currFormation = cmd->b_startId;
	if(ViewManager::getInstance()->formationView)
	{
		// doyang
		ViewManager::getInstance()->formationView->updateActiveFormation(cmd->b_startId);
	}
}

void FormationMediator::updateFormation( char * data )
{
	SCMD310 * pCmd = (SCMD310 *)data;
	if (!pCmd->a_isSuccess)
	{
		Message::Instance()->show(ValuesUtil::Instance()->getString("ZX4"),ccc3(233,44,22),1);
		return;
	}
	if(ViewManager::getInstance()->formationView)
	{
		//doyang
		ViewManager::getInstance()->formationView->updateFormation(data);
	}
}

void FormationMediator::popHandler( CCNode *pNode, void *data )
{
	this->openFormationView();
}

void FormationMediator::sockMemberChange(char * data)
{
	sendNotification(Facade_Command,AppFacade_FORMATION_PROXY_CHANGE,data,FormationCommand::MEMBER_CHANGE);
	//if(NewhandManager::Instance()->_nextEventId == NewhandConst::EVENT_DEPLOY_OP_ROLE_SIT)
	if((!NewhandManager::Instance()->_nextEventIdList.empty()) 
		&& (NewhandManager::Instance()->_nextEventIdList.front() == NewhandConst::EVENT_DEPLOY_OP_ROLE_SIT))
	{
		//Doyang 20120712
		TestNewhand *pTestNewhand = new TestNewhand("evt", NULL, NewhandConst::EVENT_DEPLOY_OP_ROLE_SIT);
		GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::TEST_NEW_HAND,
			pTestNewhand);
		CC_SAFE_DELETE(pTestNewhand);
	}
}
