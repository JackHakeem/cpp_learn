#include "SkillCommand.h"
#include "socket/command/s31/SCMD319.h"
#include "model/skill/vo/SkillInfo.h"
#include "socket/command/s3c/SCMD3C9.h"
#include "socket/command/s31/SCMD316.h"
#include "model/skill/SkillManager.h"
#include "socket/command/s31/SCMD314.h"
#include "socket/command/s3a/SCMD3AC.h"
#include "socket/command/s31/SCMD31A.h"
#include "socket/command/s31/SCMD31B.h"
#include "model/player/RoleManage.h"
#include "socket/command/s3a/SCMD3AA.h"
#include "view/skill/UpSkillMediator.h"
#include "utils/ValuesUtil.h"
#include "Message.h"

SkillCommand::SkillCommand()
{
	_skillProxy = 0;
	if (!_skillProxy)
	{
		if(g_pFacade)
			_skillProxy = (SkillProxy*)g_pFacade->retrieveProxy(AppFacade_SKILL_PROXY);
	}

	
}

void SkillCommand::execute(int32 command, char* data)
{
	if(g_pFacade)
		_skillProxy = (SkillProxy*)g_pFacade->retrieveProxy(AppFacade_SKILL_PROXY);

	switch(command)
	{
	case INIT_SKILL_DIC:
		initSkillDic(data);
		break;
	case UPGRADE_SKILL:
		updateSkill(data);
		break;
	case UPGRADE_FORMATION:
		updateFormation(data);
		break;
	case ADD_SKILL:
		addSkill(data);
		break;
	case ADD_FORMATION:
		addFormation(data);
		break;
	case ADD_TALENT:
		addTalent(data);
		break;
	case UPGRADE_TALENT:
		updateTalent(data);
		break;
	case INIT_TALENT_DIC:
		initTalentDic(data);
		break;
	}
}

/*Initialize passive skill**/
void SkillCommand::initSkillDic(char* data)
{
	if(!data)
		return;

	SCMD319* cmd = (SCMD319*)data;
	std::vector<SkillInfo>list;
	std::vector<SCMD319Node>::iterator iter= cmd->a_skills.begin();
	for(; iter != cmd->a_skills.end(); ++iter)
	{
		SkillInfo skillInfo;
		skillInfo.id = iter->a_skillId;
		skillInfo.lev = iter->b_skillLel;
		skillInfo.active = (iter->c_active == 1);
		list.push_back(skillInfo);
	}
	if(_skillProxy)
		_skillProxy->initSkillDic(&list);
}

void SkillCommand::initTalentDic(char* data)
{
	if(!data)
		return;

	SCMD3C9* cmd = (SCMD3C9*)data;
	std::vector<SkillInfo>list;
	std::vector<SCMD3C9Node>::iterator iter = cmd->a_TalentArr.begin();
	for(; iter != cmd->a_TalentArr.end(); ++iter)
	{
		SkillInfo skillInfo;
		skillInfo.id = iter->a_talentId;
		skillInfo.lev = iter->b_talentLv;
		list.push_back(skillInfo);
	}
	if(_skillProxy)
		_skillProxy->initTalentDic(&list);
}

/**
* Upgrade passive skill to return to pack
* @param obj
*/
void SkillCommand::updateSkill(char* data)
{
	if(!data)
		return;

	SCMD316* cmd = (SCMD316*)data;
	if(!cmd->a_isOk)
	{
		SkillVo* skillVo = SkillManager::Instance()->getSkill(cmd->b_passiveId);
		if(skillVo)
		{
			std::string skillName = skillVo->name;
			Message::Instance()->show("["+skillName+"]"+ValuesUtil::Instance()->getString("US7"),ccc3(240,33,33),1);
			return ;
		}
	}
	else
	{
		SkillVo* skillVo = SkillManager::Instance()->getSkill(cmd->b_passiveId);
		if(skillVo)
		{
			std::string skillName = skillVo->name;
			Message::Instance()->show("["+skillName+"]"+ValuesUtil::Instance()->getString("US6"),ccc3(12,233,25),1);
		}
		if(_skillProxy)
			_skillProxy->updateSkill(cmd->b_passiveId, cmd->c_passiveLel);
	}
	//sendNotification(Facade_Mediator, AppFacade_SKILL_COMMAND, (char*)data, UpSkillMediator::SKILL_ADDED);
}

/**
	* Upgrade formation to return to pack
	* @param obj
	*/		
void SkillCommand::updateFormation(char* data)
{
	if(!data)
		return;

	SCMD314* cmd = (SCMD314*)data;
	if(cmd->a_isOk == 1)
	{
		SkillVo* skillVo = SkillManager::Instance()->getSkill(cmd->b_formationId);
		if(!skillVo)
		{
			std::string skillName = skillVo->name;
			Message::Instance()->show("["+skillName+"]"+ValuesUtil::Instance()->getString("US7"),ccc3(240,33,33),1);
			return ;
		}
		else
		{
			SkillVo* skillVo = SkillManager::Instance()->getSkill(cmd->b_formationId);
			if(skillVo)
			{
				std::string skillName = skillVo->name;
				Message::Instance()->show("["+skillName+"]"+ValuesUtil::Instance()->getString("US6"),ccc3(12,233,25),1);
			}
			if(_skillProxy)
				_skillProxy->updateFormation(cmd->b_formationId, cmd->c_formationLel);
		}
	}
}
		
/**
* Upgrade talent to return to pack
* @param obj
*/
void SkillCommand::updateTalent(char* data)
{
	if(!data)
		return;

	SCMD3AC* cmd = (SCMD3AC*)data;
	if(cmd->a_isSuccess != 1)
	{ 
		SkillVo* skillVo = SkillManager::Instance()->getSkill(cmd->b_tltId);
		if(skillVo)
		{
			std::string skillName = skillVo->name;
			std::string msg = "Talent"+skillName+"upgrade failed¡£";
			Message::Instance()->show(msg);
			return ;
		}
	}
	else
	{
		if(_skillProxy)
			_skillProxy->updateTalent(cmd->b_tltId, cmd->c_newLv);
	}
}
		
/**
	* New passive skill to return to pack
	* @param obj
	*/
void SkillCommand::addSkill(char* data)
{
	if(!data)
		return;

	SCMD31A* cmd = (SCMD31A*)data;
	SkillInfo skillInfo;
	skillInfo.id = cmd->a_passiveId;
	skillInfo.lev = cmd->b_passiveLel; 
	skillInfo.active = false;
	if(_skillProxy)
		_skillProxy->addSkill(&skillInfo);
}
/**
	* New formation to return to pack
	* @param obj
	*/
void SkillCommand::addFormation(char* data)
{
	if(!data)
		return;
	/*
	SCMD31B* cmd = (SCMD31B*)data;
	FormationInfo formationInfo;
	formationInfo.setId(cmd->a_formationId);
	formationInfo.lev = cmd->b_formationLel;
	AccountInfoVo* info = RoleManage::Instance()->accountInfo();
	if(info)
	{
		formationInfo.figuresMap.insert(make_pair(cmd->c_roleSit, info->roleId));
	}
	if(_skillProxy)
		_skillProxy->addFormation(&formationInfo);
		*/
	SCMD31B* cmd = (SCMD31B*)data;
	FormationInfo* formationInfo = new FormationInfo();
	formationInfo->setId(cmd->a_formationId);
	formationInfo->lev = cmd->b_formationLel;
	AccountInfoVo* info = RoleManage::Instance()->accountInfo();
	if(info)
	{
		formationInfo->figuresMap.insert(make_pair(cmd->c_roleSit, info->roleId));
	}
	if(_skillProxy)
		_skillProxy->addFormation(formationInfo);
}
		
void SkillCommand::addTalent(char* data)
{
	if(!data)
		return;

	SCMD3AA* cmd = (SCMD3AA*)data;
	SkillInfo skillInfo;
	skillInfo.id = cmd->a_tltId;
	skillInfo.lev = cmd->b_tltLv; 
	skillInfo.active = false;
	if(_skillProxy)
		_skillProxy->addTalent(&skillInfo); 
}

