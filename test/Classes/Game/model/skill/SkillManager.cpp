#include "model/skill/SkillManager.h"
#include "model/skill/vo/SkillType.h"
#include "model/player/RoleManage.h"
#include "model/player/vo/PlayerBaseVo.h"
#include "model/player/FigureBaseManage.h"
#include "manager/LangManager.h"

SkillManager::SkillManager()
{
	
}

SkillManager::~SkillManager()
{
	std::map< int, std::map<int, SkillNode> >::iterator iter;//jae change
	for( iter = _skillRankDic.begin();	iter != _skillRankDic.end(); iter++ )
	{
		std::map<int, SkillNode>::iterator it;
		for( it = iter->second.begin(); it != iter->second.end(); it++ )
		{
			CC_SAFE_DELETE( it->second.crystalInfo );
			CC_SAFE_DELETE( it->second.formationInfo );
			//CC_SAFE_DELETE( it->second.skillInfo );
		}
		iter->second.clear();
	}
	_skillRankDic.clear();

	//for( iter = _learnedSkillRankDic.begin();	iter != _learnedSkillRankDic.end(); iter++ )
	//{
	//	std::map<int, SkillNode>::iterator itNode;
	//	for( itNode = iter->second.begin(); itNode != iter->second.end(); itNode++ )
	//	{
	//		SkillNode& node = itNode->second;
	//		CC_SAFE_DELETE( node.crystalInfo );
	//		CC_SAFE_DELETE( node.formationInfo );
	//		CC_SAFE_DELETE( node.skillInfo );
	//	}
	//	iter->second.clear();
	//}
	//_learnedSkillRankDic.clear();

	std::map<int, SkillNode>::iterator itTa;//jae change
	for( itTa = _talentSkillDic.begin(); itTa != _talentSkillDic.end(); itTa++ )
	{
		CC_SAFE_DELETE( itTa->second.crystalInfo );
		CC_SAFE_DELETE( itTa->second.formationInfo );
		//CC_SAFE_DELETE( itTa->second.skillInfo );
	}
	_talentSkillDic.clear();

	_skillDic.clear();
	_levSkillDic.clear();
	_offensiveSkillDic.clear();
}

void SkillManager::createSkill(std::vector<SkillVo>* skillVoList)
{
	SkillVo skillVo1;
	skillVo1.id = 1;
	skillVo1.name = LangManager::getText("SKL020");
	skillVo1.rank = 0;
	skillVo1.icon = 0;
	skillVo1.longAttack = 1;
	skillVo1.resId = 10;
	_skillDic.insert(make_pair(skillVo1.id, skillVo1));

	SkillVo skillVo2;
	skillVo2.id = 2;
	skillVo2.name = LangManager::getText("SKL021");
	skillVo2.rank = 0;
	skillVo2.icon = 0;
	skillVo2.longAttack = 1;
	skillVo2.resId = 10;
	_skillDic.insert(make_pair(skillVo2.id, skillVo2));
			
	SkillVo skillVo3;
	skillVo3.id = 3;
	skillVo3.name = LangManager::getText("SKL022");
	skillVo3.rank = 0;
	skillVo3.icon = 0;
	skillVo3.longAttack = 1;
	skillVo3.resId = 10;
	_skillDic.insert(make_pair(skillVo3.id, skillVo3));
			
	SkillVo skillVo4;
	skillVo4.id = 4;
	skillVo4.name = LangManager::getText("SKL023");
	skillVo4.rank = 0;
	skillVo4.icon = 0;
	skillVo4.longAttack = 1;
	skillVo4.resId = 10;
	_skillDic.insert(make_pair(skillVo4.id, skillVo4));

	if(skillVoList == NULL)
		return;

	std::vector<SkillVo>::iterator it = skillVoList->begin();
	for(; it != skillVoList->end(); ++it)
	{
		if (_skillDic.find(it->id) != _skillDic.end())
		{
			_skillDic.erase(it->id);
		}
		_skillDic.insert(make_pair(it->id, *it));
	}

	std::vector<SkillVo>::iterator iter = skillVoList->begin();

	for(; iter != skillVoList->end(); ++iter)
	{
		std::map<int, SkillNode> ls;
		std::map<int, SkillNode>* list;
		bool needInsert = false;
		std::map<int, std::map<int, SkillNode> >::iterator it = _skillRankDic.find(iter->rank);
		if(it != _skillRankDic.end())
		{
			list = &(it->second);
		}
		else
		{
			list = &ls;
			needInsert = true;
		}

		// LH0713
		std::map<int, SkillNode>::iterator itNode = list->find(iter->id);
		if (itNode != list->end())
		{
			list->erase( itNode );
		}

		if(iter->rank == SkillType::FORMATION)
		{
			SkillNode node;
			FormationInfo* fInfo = new FormationInfo;
			fInfo->setId(iter->id);
			fInfo->lev = 0;
			node.type = 0;
			node.formationInfo = fInfo;
			list->insert( make_pair(iter->id, node) );
		}
		else if(iter->rank == SkillType::PASSVIE)
		{
			SkillNode node;
			SkillInfo sInfo;// = new SkillInfo();//kevinchange0809
			sInfo.id = iter->id;
			sInfo.lev = 0;
			node.type = 1;
			node.skillInfo = sInfo;
			list->insert(make_pair(iter->id, node));
		}
		else if(iter->rank == SkillType::CRYSTAL)
		{
			SkillNode node;
			CrystalInfo* cInfo = new CrystalInfo();
			cInfo->id = iter->id;
			cInfo->name = iter->name;
			cInfo->level = 0;
			node.type = 2;
			node.crystalInfo = cInfo;
			list->insert(make_pair(iter->id, node));
		}
		else if(iter->rank == SkillType::TALENT)
		{
			SkillNode node;
			SkillInfo tInfo;// = new SkillInfo();
			tInfo.id = iter->id;
			tInfo.lev = 0;
			node.type = 1;
			node.skillInfo = tInfo;
			list->insert(make_pair(iter->id, node));
		}
		else if(iter->rank == SkillType::AOYI)
		{//KEVIN
			SkillNode node;
			SkillInfo tInfo;// = new SkillInfo();//kevinchange0809
			tInfo.id = iter->id;
			tInfo.lev = 0;
			node.type = 1;
			node.skillInfo = tInfo;
			list->insert(make_pair(iter->id, node));
		}

		if(needInsert)
			_skillRankDic.insert(make_pair(iter->rank, *list));
	}
}

void SkillManager::createLevSkill(LevSkillVo& levSkillVo)
{
	//_levSkillDic[levSkillVo.id] = levSkillVo;
}

SkillVo* SkillManager::getSkill(int skillId)
{
	std::map<int, SkillVo>::iterator iter =  _skillDic.find(skillId);
	if(iter == _skillDic.end())
		return NULL;

	return &(iter->second);
}

LevSkillVo* SkillManager::getLevSkill(int skillId, int lev)
{
	std::map<int, std::map<int, LevSkillVo> >::iterator iter = _levSkillDic.find(skillId);
	if(iter != _levSkillDic.end())
	{
		std::map<int, LevSkillVo>::iterator it = iter->second.find(lev);
		if(it != iter->second.end())
		{
			return &(it->second);
		}
	}
	return NULL;
}

/**
* According to the lowest level for ID LevSkillVo
*/

LevSkillVo* SkillManager::getLowLevSkill(int skillId, int lev)
{
	std::map<int, std::map<int, LevSkillVo> >::iterator iter = _levSkillDic.find(skillId);
	if(iter != _levSkillDic.end())
	{
		if(lev == 0)
		{
			int tmpLev = 1;
			
			while(iter->second.find(tmpLev) != iter->second.end())
			{
				//return &(iter->second.find(tmpLev));
				tmpLev++;
			}
			std::map<int, LevSkillVo>::iterator it = iter->second.find(--tmpLev);
			if(it != iter->second.end())
				return &(it->second);
			else
				return NULL;
		}
		else
		{
			std::map<int, LevSkillVo>::iterator it = iter->second.find(lev);
			if(it != iter->second.end())
				return &(it->second);
		}
	}
	return NULL;
}

/**
* Get the original SkillInfo Dic
*/ 

std::map<int, SkillNode>* SkillManager::getSkillsByRank(int rankId)
{
	//std::map<int/*rank*/, std::map<int/*id*/, SkillNode> > _skillRankDic;
	std::map<int, std::map<int, SkillNode> >::iterator iter =  _skillRankDic.find(rankId);
	if(iter != _skillRankDic.end())
		return &(iter->second);

	return NULL;
}


std::map<int, SkillNode>* SkillManager::getLearnedSkillsByRank(int rankId)
{
	std::map<int, std::map<int, SkillNode> >::iterator iter =  _learnedSkillRankDic.find(rankId);
	if(iter != _learnedSkillRankDic.end())
	{
		return &(iter->second);
	}
	else
	{
		std::map<int/*id*/, SkillNode> skill;
		_learnedSkillRankDic.insert(make_pair(rankId,skill));
		iter =  _learnedSkillRankDic.find(rankId);
		return &(iter->second);
	}
	return NULL;
}

/**
* 
* For the two characters active skills
* @ param figure character Numbers
* @ return Array
*/

std::vector<int>* SkillManager::getOffensiveSkill(int figure)
{
	//std::map<int, std::vector<int> >::iterator iter = _offensiveSkillDic.find(figure);
	//if(iter != _offensiveSkillDic.end())
	//	_offensiveSkillDic.erase(iter);

	PlayerInfoVo* info = RoleManage::Instance()->getMercenary(figure);
	if(!info)
		return NULL;

	int mercId = info->figureBaseInfo.mercId;
	FigureCfgBaseVo* baseInfo = FigureBaseManage::Instance()->getMercBase(mercId);
	if(!baseInfo)
		return NULL;

	std::vector<int>* skill1 = &(baseInfo->skill1);
	if(!skill1)
		return NULL;


	_offensiveSkillDic.insert(make_pair(figure, *skill1));
	//_offensiveSkillDic[figure] = *skill1;
	std::map<int, std::vector<int> >::iterator it = _offensiveSkillDic.find(figure);
	if(it != _offensiveSkillDic.end())
		return &(it->second);
	else
		return NULL;
}