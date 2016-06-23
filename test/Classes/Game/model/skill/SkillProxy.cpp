#include "model/skill/SkillProxy.h"
#include "SkillManager.h"
#include "vo/SkillType.h"
#include "vo/SkillInfo.h"
#include "model/player/RoleManage.h"
#include "model/player/vo/AccountInfoVo.h"
#include "Message.h"
#include "mvc/Facade.h"
#include "view/skill/UpSkillMediator.h"
#include "utils/ValuesUtil.h"
#include "view/formation/FormationMediator.h"
#include "view/figure/FigureMediator.h"
#include "socket/command/s31/SCMD310.h"
#include "socket/command/s31/SCMD312.h"

SkillProxy::SkillProxy()
{
	_isFormationInit = false;
	_isSkillInit = false;
	_isTalentInit = false;
	_formationDic = NULL;
	_skillDic = NULL;
	_talentDic = NULL;
}

/**
* Initialize passive skill list
* @ param arr
*/
void SkillProxy::initSkillDic(std::vector<SkillInfo>* arr)
{
	
	if(!arr)
		return;

//  	if(_isSkillInit)
// 		return;

	_skillDic = SkillManager::Instance()->getSkillsByRank(SkillType::PASSVIE);
	if(_skillDic)
	{
		for(std::vector<SkillInfo>::iterator iter = arr->begin(); iter != arr->end(); ++iter)
		{
			std::map<int, SkillNode>::iterator it = _skillDic->find(iter->id);
			if(it != _skillDic->end())
				_skillDic->erase(it);

			SkillNode node;
			SkillInfo skillInfo;
			skillInfo.id = iter->id;
			skillInfo.lev = iter->lev;
			skillInfo.active = iter->active;
			node.type = 1;
			node.skillInfo = skillInfo;
			_skillDic->insert(make_pair(iter->id, node));
		}
	}

	// add by longhui 0427
	std::map<int, SkillNode>* m_skillDic = SkillManager::Instance()->getLearnedSkillsByRank(SkillType::PASSVIE);
	if(m_skillDic)
	{
		for(std::vector<SkillInfo>::iterator iter = arr->begin(); iter != arr->end(); ++iter)
		{
			std::map<int, SkillNode>::iterator it = m_skillDic->find(iter->id);
			if(it != m_skillDic->end())
				m_skillDic->erase(it);

			SkillNode node;
			SkillInfo skillInfo;// = new SkillInfo;//kevinchange0809
			skillInfo.id = iter->id;
			skillInfo.lev = iter->lev;
			skillInfo.active = iter->active;
			node.type = 1;
			node.skillInfo = skillInfo;
			m_skillDic->insert(make_pair(iter->id, node));
		}
	}
	// add by longhui end

	sendNotification(Facade_Mediator, AppFacade_SKILL_COMMAND, 0, UpSkillMediator::SKILL_INIT);
	//_isSkillInit = true;
}

/**
* Initial formation list
* @ param arr
*/

void SkillProxy::initFormationDic( std::list<FormationInfo*>& flist )
{
	_formationDic = SkillManager::Instance()->getSkillsByRank(SkillType::FORMATION);
	std::list<FormationInfo*>::iterator it;
	if(_formationDic == NULL)
		return;

	for(it = flist.begin(); it != flist.end(); it++)
	{
		if((*it) == NULL)
			continue;

		std::map<int, SkillNode>::iterator it1 = _formationDic->find((int)(*it)->getId());
		if(it1 != _formationDic->end())
		{
			//Doyang 20120711
			CC_SAFE_DELETE(it1->second.formationInfo);
			_formationDic->erase(it1);
		}

		SkillNode node;
		node.type = 0;
		node.formationInfo = *it;
		_formationDic->insert(make_pair((int)(*it)->getId(), node));
	}

	// add by longhui 0427
	std::map<int, SkillNode>* m_formatDic = SkillManager::Instance()->getLearnedSkillsByRank(SkillType::FORMATION);
	if(m_formatDic == NULL)
		return;

	for(it = flist.begin(); it != flist.end(); it++)
	{
		if((*it) == NULL)
			continue;

		std::map<int, SkillNode>::iterator it1 = m_formatDic->find((int)(*it)->getId());
		if(it1 != m_formatDic->end())
		{
			CC_SAFE_DELETE(it1->second.formationInfo); //LH0712
			m_formatDic->erase(it1);
		}

		SkillNode node;
		node.type = 0;
		node.formationInfo = *it;
		m_formatDic->insert(make_pair((int)(*it)->getId(), node));
	}
	// add by longhui end

	_isFormationInit = true;
}


/**
* Initial formation list
* @param arr
*/
void SkillProxy::initTalentDic(std::vector<SkillInfo>* arr)
{
	if(!arr)
		return;

	if(_isTalentInit)
		return;

	_talentDic = SkillManager::Instance()->getSkillsByRank(SkillType::TALENT);
	if(!_talentDic)
		return;

	std::vector<SkillInfo>::iterator iter = arr->begin();
	for(; iter != arr->end(); ++iter)
	{
		SkillNode node;
		SkillInfo skillInfo;
		skillInfo.id = iter->id;
		skillInfo.lev = iter->lev;
		skillInfo.active = iter->active;
		node.type = 1;
		node.skillInfo = skillInfo;
		std::map<int, SkillNode>::iterator it = _talentDic->find(iter->id);
		if(it != _talentDic->end())
			_talentDic->erase(it);

		_talentDic->insert(make_pair(iter->id, node));
	}
	_isTalentInit = true;
}

/**
*Delete specified in the formation of the id characters (after firing calls)
* @param figureId
* 
*/
void SkillProxy::delelteFigureOnFormations(int figureId)
{
	if(!_formationDic)
		return;

	std::map<int, SkillNode>::iterator iter = _formationDic->begin();
	for(; iter != _formationDic->end(); ++iter)
	{
		if(iter->second.formationInfo == NULL)
			continue;

		std::map<int, int>::iterator it = iter->second.formationInfo->figuresMap.find(figureId);
		for(; it != iter->second.formationInfo->figuresMap.end(); ++it)
		{
			iter->second.formationInfo->figuresMap.erase(it);
		}
	}
}

/**
*  Updated skills of activated
* @param skillId
* @param active
* 
*/		
void SkillProxy::updateSkillState(int skillId, bool active)
{
	if(!_skillDic)
		return;

	std::map<int, SkillNode>::iterator iter = _skillDic->find(skillId);
	if(iter != _skillDic->end())
	{
		iter->second.skillInfo.active = active;
	}
}
		
/** 
* Upgrade skills
* @ param skillId passive skill ID
* @ param level after upgrading level
	*/
void SkillProxy::updateSkill(int skillId, int level)
{
	UpGradeInfo* upgradeInfo = transUpgradeInfo(skillId, level);
	if(!upgradeInfo)
	{
		CC_SAFE_DELETE(upgradeInfo);
		return;
	}
	SkillInfo* skillInfo = getSkill(skillId);
	if(!skillInfo)
	{
		CC_SAFE_DELETE(skillInfo);
		return;
	}

	SkillNode node;
	node.type = 1;
	skillInfo->lev = level;
	node.skillInfo = *skillInfo;//kevinchange0809

	if(!_skillDic)
		return;

	std::map<int, SkillNode>::iterator iter = _skillDic->find(skillId);
	if(iter != _skillDic->end())
		_skillDic->erase(iter);

	_skillDic->insert(make_pair(skillId, node));	

	// add by longhui 0427
	std::map<int, SkillNode>* skillDic = SkillManager::Instance()->getSkillsByRank(SkillType::PASSVIE);
	if(!skillDic)
		return;

	std::map<int, SkillNode>::iterator it = skillDic->find(skillId);
	if(it != skillDic->end())
		skillDic->erase(it);
	skillDic->insert(make_pair(skillId,node));

	std::map<int, SkillNode>*skillDic2 = SkillManager::Instance()->getLearnedSkillsByRank(SkillType::PASSVIE);
	if(!skillDic2)
		return;

	std::map<int, SkillNode>::iterator it2 = skillDic2->find(skillId);
	if(it2 != skillDic2->end())
		skillDic2->erase(it2);
	skillDic2->insert(make_pair(skillId,node));
	// add by longhui 0427 end


	sendNotification(Facade_Mediator, AppFacade_SKILL_COMMAND, (char*)upgradeInfo, UpSkillMediator::SKILL_UPGRADE);

	CC_SAFE_DELETE(upgradeInfo); // LH0708
}

/**
* Upgrade formation
*/
void SkillProxy::updateFormation(int formationId, int level)
{
	UpGradeInfo* upgradeInfo = transUpgradeInfo(formationId, level);
	//if(!upgradeInfo)
	//{
	//	return;
	//}
	FormationInfo* formationInfo = getFormation(formationId);
	if(!formationInfo)
	{
		CC_SAFE_DELETE(formationInfo);
		return;
	}

	formationInfo->lev = level;

	if(!_formationDic)
		return;

	std::map<int, SkillNode>::iterator iter = _formationDic->find(formationId);
	if(iter != _formationDic->end())
	{
		_formationDic->erase(iter);
	}
	SkillNode node;
	node.type = 0;
	node.formationInfo = formationInfo;
	_formationDic->insert(make_pair(formationInfo->getId(), node));// = formationInfo;

	// add by longhui 0427
	std::map<int, SkillNode>* skillDic = SkillManager::Instance()->getSkillsByRank(SkillType::FORMATION);
	if(!skillDic)
		return;

	std::map<int, SkillNode>::iterator it = skillDic->find(formationId);
	if(it != skillDic->end())
		skillDic->erase(it);
	skillDic->insert(make_pair(formationId,node));

	std::map<int, SkillNode>* skillDic2 = SkillManager::Instance()->getLearnedSkillsByRank(SkillType::FORMATION);
	if(!skillDic2)
		return;

	std::map<int, SkillNode>::iterator it2 = skillDic2->find(formationId);
	if(it2 != skillDic2->end())
		skillDic2->erase(it2);
	skillDic2->insert(make_pair(formationId,node));
	// add by longhui 0427 end

	if(upgradeInfo)
		sendNotification(Facade_Mediator, AppFacade_SKILL_COMMAND, (char*)upgradeInfo, UpSkillMediator::FORMATION_UPGRADE);

	CC_SAFE_DELETE(upgradeInfo); // LH0708

	//sendNotification(Facade_Mediator, AppFacade_UPSKILL_MEDIATOR, (char*)upGradeInfo, UpSkillMediator::FORMATION_UPGRADE);

	//int data[2] = {formationId, level};
	//sendNotification(Facade_Mediator, AppFacade_FORMATION_MEDIATOR, (char*)data, FormationMediator::UPDATE_FORMATION_LIST);

	//sendNotification(UpSkillMediator.FORMATION_UPGRADE, {info: upgradeInfo});
	struct Data
	{
		int id;
		int level;
	};
	Data data;
	data.id = formationId;
	data.level = level;
	sendNotification(Facade_Mediator, AppFacade_FORMATION_PROXY_CHANGE, (char*)(&data), FormationMediator::UPDATE_FORMATION_LIST);
}

void SkillProxy::updateTalent(int skillId, int level)
{
	UpGradeInfo* upGradeInfo = transUpgradeInfo(skillId, level);
	if(!upGradeInfo)
	{
		Message::Instance()->show("Skill status unvaliable");
		return;
	}
	SkillInfo* skillInfo = getTalent(skillId);
	if(!skillInfo)
		return;

	skillInfo->lev = level;
	SkillNode node;
	node.type = 1;
	node.skillInfo = *skillInfo;//kevinchange0809

	if(!_talentDic)
		return;

	std::map<int, SkillNode>::iterator iter = _talentDic->find(skillId);
	if(iter != _talentDic->end())
		_talentDic->erase(iter);

	_talentDic->insert(make_pair(skillId, node));

	sendNotification(Facade_Mediator, AppFacade_SKILL_COMMAND, (char*)upGradeInfo, UpSkillMediator::TALENT_UPGRADE);

	CC_SAFE_DELETE(upGradeInfo); // LH0708

	//this.sendNotification(UpSkillMediator.TALENT_UPGRADE,  {info: upgradeInfo});
}		
/**
*Skills replacement.
* if is passive skill, need to update _skillDic data, and let update interface;
* if is active skills, no data can be updated, need to update the interface.
* @ param figure
* @ param rank category
* @ param eqId equipment skills
* @ param offId unload skills
* 
*/		
void SkillProxy::exchangeSkill(int figure, int rank, int eqId, int offId)
{
	if(_skillDic && rank == SkillType::PASSVIE)
	{
		std::map<int, SkillNode>::iterator iter = _skillDic->find(eqId);
		if(iter != _skillDic->end())
			iter->second.skillInfo.active = true;
		iter = _skillDic->find(offId);
		if(iter != _skillDic->end())
			iter->second.skillInfo.active = false;
	}

	int data[3] = {rank, eqId, offId};
	sendNotification(Facade_Mediator, AppFacade_FIGURE_MEDIATOR, (char*)data, FigureMediator::EXCHANGE_SKILL);

	//sendNotification(FigureMediator.EXCHANGE_SKILL, {rank:rank, eqId:eqId, offId:offId});
	UpGradeInfo* info = getUpGradeInfo(eqId, rank);
	struct Data
	{
		int figure;
		int rank;
		UpGradeInfo* info;
	} data1;
	data1.figure = figure;
	data1.rank = rank;
	data1.info = info;

	CC_SAFE_DELETE(info); // ADD BY L.H. LEAK

	sendNotification(Facade_Mediator, AppFacade_FIGURE_MEDIATOR, (char*)(&data1), FigureMediator::FIGURE_SKILL_CHANGE);
	//this.sendNotification(FigureMediator.FIGURE_SKILL_CHANGE, {figure:figure, rank:rank, info:info});
}


/**
* New passive skill
* @param skillInfo
*/
void SkillProxy::addSkill(SkillInfo* skillInfo)
{
	if(!_skillDic || !skillInfo)
		return;
	std::map<int, SkillNode>::iterator iter = _skillDic->find(skillInfo->id);
	if(iter == _skillDic->end())
		return;

	UpGradeInfo* upgradeInfo = transUpgradeInfo(skillInfo->id, skillInfo->lev);
	if(!upgradeInfo)
		return;

	SkillInfo sInfo;//kevinchange0809
	sInfo.active = skillInfo->active;
	sInfo.id = skillInfo->id;
	sInfo.lev = skillInfo->lev;
	iter->second.skillInfo = sInfo;

	// add by longhui 0427
	SkillNode node;
	node.type = 1;
	node.skillInfo = *skillInfo;//kevinchange0809
	std::map<int, SkillNode>* skillDic = SkillManager::Instance()->getLearnedSkillsByRank(SkillType::PASSVIE);
	if(skillDic)
		skillDic->insert(make_pair(skillInfo->id,node));
	// add by longhui 0427 end

	sendNotification(Facade_Mediator, AppFacade_SKILL_COMMAND, (char*)upgradeInfo, UpSkillMediator::SKILL_ADDED);

	CC_SAFE_DELETE(upgradeInfo); // jae 20121109
}

/**
* New formation
* @param formationInfo
*/
void SkillProxy::addFormation(FormationInfo* formationInfo)
{
	if(!_skillDic || !_formationDic || !formationInfo)// || !_formationDic.hasOwnProperty(formationInfo.id))
		return;

	std::map<int, SkillNode>::iterator iter = _formationDic->find(formationInfo->getId());
	if(iter == _formationDic->end())
		return;

	UpGradeInfo* upgradeInfo = transUpgradeInfo(formationInfo->getId(), formationInfo->lev);
	if(!upgradeInfo)
		return;

	if(iter->second.formationInfo != NULL)
		delete iter->second.formationInfo;
	
    /*
	FormationInfo* fInfo = new FormationInfo();
	*fInfo = *formationInfo;
	iter->second.formationInfo = fInfo;
*///kevinchange0810
    
	// add by longhui 0427
	SkillNode node;
	node.type = 0;
	node.formationInfo = formationInfo;
	std::map<int, SkillNode>* skillDic = SkillManager::Instance()->getLearnedSkillsByRank(SkillType::FORMATION);
	if(skillDic)
		skillDic->insert(make_pair(formationInfo->getId(),node));
	// add by longhui 0427 end

	// LH0719
	_formationDic->erase(formationInfo->getId());
	_formationDic->insert(make_pair(formationInfo->getId(),node));

	sendNotification(Facade_Mediator, AppFacade_SKILL_COMMAND, (char*)upgradeInfo, UpSkillMediator::FORMATION_ADDED);
	//sendNotification(Facade_Mediator, AppFacade_UPSKILL_MEDIATOR, (char*)upgradeInfo, UpSkillMediator::FORMATION_ADDED);

	CC_SAFE_DELETE( upgradeInfo );
}
		
void SkillProxy::addTalent(SkillInfo* skillInfo)
{
	if(!_talentDic || !skillInfo)//||!_talentDic.hasOwnProperty(skillInfo.id))
		return;

	std::map<int, SkillNode>::iterator iter = _talentDic->find(skillInfo->id);
	if(iter == _talentDic->end())
		return;

	UpGradeInfo* upgradeInfo = transUpgradeInfo(skillInfo->id, skillInfo->lev);
	if(!upgradeInfo)
		return;

	//if(iter->second.skillInfo != NULL)//kevinchange0809
	//	delete iter->second.skillInfo;

	SkillInfo sInfo;//kevinchange0809
	sInfo.active = skillInfo->active;
	sInfo.id = skillInfo->id;
	sInfo.lev = skillInfo->lev;
	iter->second.skillInfo = sInfo;
	sendNotification(Facade_Mediator, AppFacade_SKILL_COMMAND, (char*)upgradeInfo, UpSkillMediator::TALENT_ADDED);

	CC_SAFE_DELETE(upgradeInfo);
}
	 

/**
* Get passive skill SkillInfo
* @param skillId
*/
SkillInfo* SkillProxy::getSkill(int skillId)
{
	if (!_skillDic)// || _skillDic[skillId] == undefined)
	{
		return NULL;
	}
	std::map<int, SkillNode>::iterator iter = _skillDic->find(skillId);
	if(iter == _skillDic->end())
	{
		return NULL;
	}

	return &iter->second.skillInfo;
}
		
SkillInfo* SkillProxy::getTalent(int talentId)
{
	if (!_talentDic)// || _talentDic[talentId] == undefined)
	{
		return NULL;
	}

	std::map<int, SkillNode>::iterator iter = _talentDic->find(talentId);
	if(iter == _talentDic->end())
	{
		return NULL;
	}

	return &iter->second.skillInfo;
}

/** Obtain formationFormationInfo
* @param formationId
*/
FormationInfo* SkillProxy::getFormation(int formationId)
{
	if(!_formationDic)//[formationId] == undefined)
	{
		return NULL;
	}

	std::map<int, SkillNode>::iterator iter = _formationDic->find(formationId);
	if(iter == _formationDic->end() || iter->second.formationInfo == NULL)
		return NULL;

	return iter->second.formationInfo;
}
		
/**
*Get a specific skill of detailed information, used for character skills panel, passive skill list displays
* @ param skillId skills id
* @ param rank skills category
* @return UpGradeInfo
* 
*/
UpGradeInfo* SkillProxy::getUpGradeInfo(int skillId, int rank)
{
	
	if(rank == SkillType::PASSVIE)
	{
		SkillInfo* skillInfo = getSkill(skillId);
		if (skillInfo== NULL)
		{
			UpGradeInfo* upGradeInfo = new UpGradeInfo();
			upGradeInfo->rank = rank;
			return upGradeInfo;
		}
		else
		{
			UpGradeInfo* upGradeInfo = 0;
			upGradeInfo = transUpgradeInfo(skillInfo->id, skillInfo->lev);
			upGradeInfo->active = skillInfo->active;
			return upGradeInfo;
		}
	}
	else if(rank == SkillType::SKILL || rank == SkillType::AOYI)
	{
		UpGradeInfo* upGradeInfo = 0;
		upGradeInfo = transUpgradeInfo(skillId, 1);//Main attack skill and the upanishads skills are always grade 1
		if(upGradeInfo == NULL)
		{
			upGradeInfo = new UpGradeInfo();
		}
		upGradeInfo->rank = rank;
		return upGradeInfo; // LH0708
	}
	return 0;
}
		
/**
	* The current system
	* @return 
	* 
	*/		
FormationInfo* SkillProxy::currFormationList()
{
	AccountInfoVo* info = RoleManage::Instance()->accountInfo();
	if(!info)
		return NULL;
	
	return getFormation(info->currFormation);
}
		
/**
*Get the detailed list of information skills
* @param rank
* @return 
* 
*/		
std::map<int, UpGradeInfo> SkillProxy::transDic(int rank)
{
	std::map<int, UpGradeInfo> levList;
	std::map<int, UpGradeInfo> noLevList;
	std::map<int, SkillNode> tmpArr;

	if(rank == SkillType::PASSVIE)
	{
		tmpArr = formatDic(_skillDic);
		std::map<int, SkillNode>::iterator iter = tmpArr.begin();
		for(; iter != tmpArr.end(); ++iter)//kevinchange0809
		{
			UpGradeInfo* uInfo = transUpgradeInfo(iter->second.skillInfo.id, iter->second.skillInfo.lev);//kevinchange0809
			if(!uInfo)continue;
			UpGradeInfo uInfo1 = *uInfo;

			uInfo1.active = iter->second.skillInfo.active;//kevinchange0809
			iter->second.skillInfo.lev > 0 ? levList.insert(make_pair(uInfo1.id, uInfo1)) : noLevList.insert(make_pair(uInfo1.id, uInfo1));//kevinchange0809
			delete uInfo;
		}
	}
	else if(rank == SkillType::FORMATION)
	{
		tmpArr = formatDic(_formationDic);
		std::map<int, SkillNode>::iterator iter = tmpArr.begin();
		for(; iter != tmpArr.end(); ++iter)
		{
			if(iter->second.formationInfo == NULL)
				continue;

			FormationInfo formationInfo = *(iter->second.formationInfo);
			UpGradeInfo* uInfo = transUpgradeInfo(formationInfo.getId(), formationInfo.lev);
			if(!uInfo)
				continue;

			UpGradeInfo uInfo1 = *uInfo;

			formationInfo.lev > 0 ? levList.insert(make_pair(uInfo1.id, uInfo1)) : noLevList.insert(make_pair(uInfo1.id, uInfo1));
			delete uInfo;
		}
	}
	else if (rank == SkillType::TALENT)
	{
		tmpArr = formatDic(_talentDic);
		std::map<int, SkillNode>::iterator iter = tmpArr.begin();
		for(; iter != tmpArr.end(); ++iter)
		{
			/*if(iter->second.skillInfo == NULL)//kevinchange0809
				continue;*/

			UpGradeInfo* uInfo = transUpgradeInfo(iter->second.skillInfo.id, iter->second.skillInfo.lev);//kevinchange0809
			if(!uInfo)
				continue;

			iter->second.skillInfo.lev > 0 ? levList.insert(make_pair(uInfo->id, *uInfo)) : noLevList.insert(make_pair(uInfo->id, *uInfo));//kevinchange0809
			delete uInfo;
		}
	}
	//levList.sortOn("id", Array.NUMERIC);
	//noLevList.sortOn("id", Array.NUMERIC);
	//To write that, back to watch this whether there is a need to
	std::map<int, UpGradeInfo>::iterator it = noLevList.begin();
	for(; it != noLevList.end(); ++it)
	{
		levList.insert(make_pair(it->first, it->second));
	}
	return levList;
}

std::map<int, SkillNode> SkillProxy::formatDic(std::map<int, SkillNode>* dic)
{
	std::map<int, SkillNode> tmparr;
	if(!dic)
	{
		return tmparr;
	}

	std::map<int, SkillNode>::iterator iter = dic->begin();
	for(; iter != dic->end(); ++iter)
	{
		if(iter->second.type == 0 && iter->second.formationInfo != NULL
			&& iter->second.formationInfo->lev != 0)
		{
			SkillNode node;
			node = iter->second;
			tmparr.insert(make_pair(iter->second.formationInfo->getId(), node));
		}
		else if(iter->second.type == 1 /*&& iter->second.skillInfo != NULL*///kevinchange0809
			&& iter->second.skillInfo.lev != 0)//kevinchange0809
		{
			SkillNode node;
			node = iter->second;
			tmparr.insert(make_pair(iter->second.skillInfo.id, node));//kevinchange0809
		}
	}
	return tmparr;
}

/**
* According to skill level and get UpGradeInfo ID
* @ param id skills id
* @ param level skill level
	*/
UpGradeInfo* SkillProxy::transUpgradeInfo(int id, int level)
{
	UpGradeInfo* upGradeInfo = new UpGradeInfo();
	upGradeInfo->id = id;
 	upGradeInfo->lev = level;

	SkillVo* skillVo = SkillManager::Instance()->getSkill(id);
	if(!skillVo)
	{
		delete upGradeInfo;
		return NULL;
	}

	upGradeInfo->icon = skillVo->icon;
	upGradeInfo->name = skillVo->name;
	upGradeInfo->rank = skillVo->rank;
	upGradeInfo->desc = skillVo->des;//KEVIN
			
	if(upGradeInfo->rank == SkillType::PASSVIE)
	{
		SkillInfo* skillInfo = getSkill(skillVo->id);
		if(!skillInfo)
		{
			delete upGradeInfo;
			return NULL;
		}
		upGradeInfo->active = skillInfo->active;
	}
	else if(upGradeInfo->rank == SkillType::FORMATION)
	{
		FormationInfo* formationInfo = getFormation(skillVo->id);
		if(!formationInfo)
		{
			delete upGradeInfo;
			return NULL;
		}
		AccountInfoVo* accountInfoVo = RoleManage::Instance()->accountInfo();
		if(accountInfoVo != NULL)
		{
			upGradeInfo->active = (accountInfoVo->currFormation == skillVo->id);
		}
	}

	LevSkillVo* levSkillVo = SkillManager::Instance()->getLowLevSkill(id, level);
	if(levSkillVo)
	{
		upGradeInfo->desc = levSkillVo->des;
		upGradeInfo->cdTime = levSkillVo->cdTime;
		upGradeInfo->needLevel = levSkillVo->roleLevel;
		upGradeInfo->skillExp = levSkillVo->skillEXP;
	}
	else
	{
		//upGradeInfo->desc = "";
		upGradeInfo->cdTime = 0;
		upGradeInfo->needLevel = 0;
		upGradeInfo->skillExp = 0;
	}
	return upGradeInfo;
}
	
std::map<int, SkillNode>* SkillProxy::passvieSkillList()
{
	return _skillDic;
}
/**
*Return all data formation, value: FormationInfo. 10 to 16 single formation; 17 ~ 23 group formation.
* Lev > 0 has learned to.
	* @return 
	* 
	*/		
std::map<int, SkillNode> SkillProxy::formationList(bool lev_request)
{
	std::map<int, SkillNode> dic;

	if(!_formationDic)
		return dic;

	if(!lev_request)
		return *_formationDic;

	for(int i = 10; i<=23; i++)
	{
		std::map<int, SkillNode>::iterator it = _formationDic->find(i);
		if(it != _formationDic->end() && it->second.formationInfo->lev > 0)
		{
			dic.insert(make_pair(it->first, it->second));
		}
	}
	return dic;
}

/**
*Get has learned to single formations. Return: Dictionary, value: FormationInfo, id: 10 to 16
* @ return Dictionary value: FormationInfo
* 
*/
std::map<int, SkillNode> SkillProxy::singleFormationList()
{
	std::map<int, SkillNode> dic;

	if(!_formationDic)
		return dic;

	for(int i = 10; i <= 16; i++)
	{
		std::map<int, SkillNode>::iterator it = _formationDic->find(i);
		if(it != _formationDic->end() && it->second.formationInfo->lev != 0)
		{
			dic.insert(make_pair(it->first, it->second));
		}
	}
	return dic;
}
/**
*Get has learned to party formations. Return: Dictionary, value: FormationInfo, id: 17 to 23
* @ return Dictionary value: FormationInfo
*
*/		
std::map<int, SkillNode> SkillProxy::teamFormationList()
{
	std::map<int, SkillNode> dic;

	if(!_formationDic)
		return dic;

	for(int i = 17; i<=23; i++)
	{
		std::map<int, SkillNode>::iterator it = _formationDic->find(i);
		if(it != _formationDic->end() && it->second.formationInfo->lev != 0)
		{
			dic.insert(make_pair(it->first, it->second));
		}
	}
	return dic;
}
	 



/**
*Formation members change
* @ param formatId formation id
* @ param srcId the original location character id
* @ param srcPos the original location
* @ param desId target position character id
* @ param desPos target position
*
*/		

void SkillProxy::formationMemberChange(char * data)
{
	SCMD310 * pCmd = (SCMD310 *)data;
	if(!_formationDic)
		return;

	if (!pCmd->a_isSuccess)
	{
		return;
	}

	std::map<int, SkillNode>::iterator forIt = _formationDic->find(pCmd->b_formationId);

	if(forIt != _formationDic->end() && forIt->second.formationInfo != NULL)
	{
		FormationInfo* info = forIt->second.formationInfo;
		if(info)
		{
			info->figuresMap.erase(pCmd->d_srcPos);
			info->figuresMap.insert(make_pair(pCmd->d_srcPos, pCmd->c_srcId ));
			info->figuresMap.erase(pCmd->f_destPos);
			info->figuresMap.insert(make_pair(pCmd->f_destPos,pCmd->e_destId ));
		}
	}
	FormationMediator* form=(FormationMediator*)g_pFacade->retrieveMediator(AppFacade_FORMATION_PROXY_CHANGE);
	form->updateFormation(data);
}


void SkillProxy::formationActivateChange(char * data)
{
	SCMD312 * pCmd = (SCMD312 *)data;
	if(!_formationDic)
		return;

	if (!pCmd->a_isOk)
	{
		return;
	}

	std::map<int, SkillNode>::iterator forIt = _formationDic->find(pCmd->b_startId);
	if(forIt != _formationDic->end() && forIt->second.formationInfo != NULL)
	{
		FormationInfo* info = forIt->second.formationInfo;
		if(info)
		{
			info->active = true;
		}
	}

	std::map<int, SkillNode>::iterator iter = _formationDic->find(pCmd->c_stopId);
	if(iter != _formationDic->end() && iter->second.formationInfo != NULL)
	{
		FormationInfo* info = iter->second.formationInfo;
		if(info)
		{
			info->active = false;
		}
	}

	FormationMediator* form=(FormationMediator*)g_pFacade->retrieveMediator(AppFacade_FORMATION_PROXY_CHANGE);
	form->formationActive(data);
}