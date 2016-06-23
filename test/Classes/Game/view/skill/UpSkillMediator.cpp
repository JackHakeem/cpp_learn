#include "UpSkillMediator.h"
#include "manager/ViewManager.h"
#include "manager/GlobalManage.h"
#include "manager/LayerManager.h"
#include "socket/command/s31/SCMD31A.h"
#include "control/skill/SkillCommand.h"
#include "socket/command/c31/CCMD315.h"
#include "socket/command/c31/CCMD313.h"
#include "../figure/components/SkillView.h"
#include "../figure/components/SkillLayer.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"

UpSkillMediator::UpSkillMediator()
{
	_upskillView = 0;
	GameDispatcher::getInstance()->addEventListener(PopEventName::SHOW_UI_UPSKILL,
		this,
		callfuncND_selector(UpSkillMediator::viewPopHandler));
}

void UpSkillMediator::handleNotification(int M2Vcmd, char* data)
{
	switch(M2Vcmd)
	{
	case SKILL_INIT:
		initUpSkill();
		break;
 	case SKILL_UPGRADE:
 		skillUpgrade(data);
 		break;
 	case FORMATION_UPGRADE:
 		formationUpgrade(data);
 		break;
 	case SKILL_ADDED:
		skillAdded(data);
		break;
 	case FORMATION_ADDED:
 		formationAdded(data);
 		break;
// 		case TALENT_ADDED:
// 		talentAdded(data);
// 		break;
// 		case TALENT_UPGRADE:
// 		talentUpgrade(data);
// 		break;
	default:
		break;
	}
}

void UpSkillMediator::popUpSkillView()
{
	_upskillView = ViewManager::getInstance()->_upSkillView;
	if (!_upskillView)
	{
		_upskillView = new UpSkillView();
		if((_upskillView)&&_upskillView->init())
		{
			CCLog("upSkill:initUpSkillView() success");
		}
		else
		{
			CCLog("upSkill:initUpSkillView() failed");
			return;
		}
		ViewManager::getInstance()->_upSkillView = this->_upskillView;
		
	}

	// test
	if (_upskillView)
	{
		//_upskillView->loadSkillItems();
		//_upskillView->loadFormationItems();
		//_upskillView->loadTalentItems();

		//_upskillView->clickSkillHandler(0);

		_upskillView->addButtons();
		if (!_upskillView->getisPop())
		{
			_upskillView->setisPop(!_upskillView->getisPop());
			if (_upskillView)
			{
				_upskillView->release(); //////
			}
			
		}

		if (_upskillView->getisPop())
		{
			

			g_pGlobalManage->setCurFocusGID(LayerManager::windowLayer->getMyFocusGID());
		}
		else
		{
			g_pGlobalManage->setCurFocusGID(LayerManager::sceneLayer->getMyFocusGID());
		}
	}
}

void UpSkillMediator::initUpSkill()
{
	// LH2013.1.5 not need init here
	/*
	_upskillView = ViewManager::getInstance()->_upSkillView;
	if (!_upskillView)
	{
		_upskillView = new UpSkillView();
		if(_upskillView && _upskillView->init())
		{
			CCLog("upSkill:initUpSkillView() success");
		}
		else
		{
			return;
		}
		ViewManager::getInstance()->_upSkillView = this->_upskillView;
	}
	*/

// 
// 	
// 	
// 	_upSkillView->setisPop(!_upSkillView->getisPop());
// 
// 	if(_upSkillView->getisPop())
// 	{
// 		// to create manager cash data
// 		// add code here
// 	}
}


void UpSkillMediator::skillAdded(char *data)
{
	_upskillView = ViewManager::getInstance()->_upSkillView;
	if (!_upskillView)
	{
		//CCAssert(_upskillView != NULL,"");
		CCLog("UPSkill:UPSkillView is not init!");
		return;
	}
	UpGradeInfo * ug = (UpGradeInfo*)data;
	_upskillView->addNewPassiveSkill(ug);

	// refresh skill in figure panel, closed by longhui 0519 because of unused
// 	SkillView * skillView = ViewManager::getInstance()->_skillView;
// 	if (!skillView)
// 	{
// 		CCAssert(skillView != NULL,"");
// 		CCLog("UPSkill:UPSkillView is not init!");
// 		return;
// 	}
// 	SkillLayer * ln = skillView->_skillPopLayer;
// 	if (ln)
// 	{
// 		ln->loadSkillItems();
// 	}
}

void UpSkillMediator::skillUpgrade(char *data)
{
	_upskillView = ViewManager::getInstance()->_upSkillView;
	if (!_upskillView)
	{
		//CCAssert(_upskillView != NULL,"");
		CCLog("UPSkill:UPSkillView is not init!");
		return;
	}
	UpGradeInfo * ug = (UpGradeInfo*)data;
	_upskillView->loadSkillItems();
	_upskillView->loadUPSkillTips(ug);	
}

void UpSkillMediator::formationAdded(char *data)
{
	_upskillView = ViewManager::getInstance()->_upSkillView;
	if (!_upskillView)
	{
		//CCAssert(_upskillView != NULL,"");
		CCLog("UPSkill:UPSkillView is not init!");
		return;
	}
	UpGradeInfo * ug = (UpGradeInfo*)data;
	_upskillView->addNewFormation(ug); 
}

void UpSkillMediator::formationUpgrade(char *data)
{
	_upskillView = ViewManager::getInstance()->_upSkillView;
	if (!_upskillView)
	{
		//CCAssert(_upskillView != NULL,"");
		CCLog("UPSkill:UPSkillView is not init!");
		return;
	}
	UpGradeInfo * ug = (UpGradeInfo*)data;
	_upskillView->loadFormationItems();
	_upskillView->loadUPSkillTips(ug);
}

void UpSkillMediator::sendUpgradePassiveSkillRequest(uint16 passiveID)
{
	CCMD315 * c = new CCMD315();
	if (c)
	{
		c->a_passiveId = passiveID;
		GameServerSocket * pSocket = GameServerSocket::getInstance();
		if (pSocket)
		{
			pSocket->sendMessage(c);
			CC_SAFE_DELETE(c); // LH0712LEAK
			CCLog("UPSkill:send upgrade passive skill request success CCMD315");
		}
	}
}

void UpSkillMediator::sendUpgradeFormationRequest(uint16 formationID)
{
	CCMD313 * c = new CCMD313();
	if (c)
	{
		c->a_formationId = formationID;
		GameServerSocket * pSocket = GameServerSocket::getInstance();
		if (pSocket)
		{
			pSocket->sendMessage(c);
			CCLog("UPSkill:send upgrade formation request success CCMD315");
		}
	}
}

void UpSkillMediator::UpSkillInfoListener(char *data)
{
	sendNotification(Facade_Command, AppFacade_SKILL_COMMAND, (char*)data, SkillCommand::INIT_SKILL_DIC);
}

void UpSkillMediator::skillAddedListener(char *data)
{
	sendNotification(Facade_Command, AppFacade_SKILL_COMMAND, (char*)data, SkillCommand::ADD_SKILL);
}

void UpSkillMediator::skillUpgradeListener(char *data)
{
	sendNotification(Facade_Command, AppFacade_SKILL_COMMAND, (char*)data, SkillCommand::UPGRADE_SKILL);
}

void UpSkillMediator::formationInfoListener(char *data)
{
	// has been stored in formation MVC 
}

void UpSkillMediator::formationAddedListener(char *data)
{
	sendNotification(Facade_Command,AppFacade_SKILL_COMMAND,(char*)data,SkillCommand::ADD_FORMATION);
}

void UpSkillMediator::formationUpgradeListener(char *data)
{
	sendNotification(Facade_Command,AppFacade_SKILL_COMMAND,(char*)data,SkillCommand::UPGRADE_FORMATION);
}

void UpSkillMediator::viewPopHandler( CCNode *pNode, void *data )
{
	this->popUpSkillView();
}
