#include "model/player/FigureBaseManage.h"
#include "model/figure/LevelExpManage.h"
#include "utils/ValuesUtil.h"

//char* careers[7] = {"剑士","游侠","骑士","武斗家","忍者","魔法师","祭司"};

FigureBaseManage::FigureBaseManage()
{
}

void FigureBaseManage::setMercenaryDic(FigureCfgBaseVo* vo)
{
	if(!vo)
		return;
	std::map<int, FigureCfgBaseVo>::iterator it = _mercList.find(vo->mercId);
	if (it != _mercList.end())
	{
		FigureCfgBaseVo& newVo = it->second;
		newVo.explanation = vo->explanation;
		newVo.score = vo->score;
		newVo.mercId = vo->mercId; // Numbers
		newVo.name = vo->name; // name
		newVo.isRole = vo->isRole; // whether leading role
		newVo.sex = vo->sex; // gender
		newVo.careerId = vo->careerId; // professional
		newVo.color = vo->color; // mercenaries color
		newVo.strength = vo->strength; /* achievement */
		newVo.intellect = vo->intellect; // intelligence
		newVo.hitRate = vo->hitRate; // hit
		newVo.agility = vo->agility; // agility
		newVo.crit = vo->crit; // crit
		newVo.stamina = vo->stamina; // physical
		newVo.needPop = vo->needPop; // reputation for
		newVo.cloth = vo->color; // model
		newVo.maxHp = vo->maxHp; // basic health
		newVo.lev = vo->lev; // default class
		newVo.silver = vo->silver; // recruiting the silver COINS
		newVo.exp = vo->exp; // default experience
		newVo.order = vo->order; // used to name the mercenaries are in order
		newVo.requirement = vo->requirement; // requirements
		newVo.skill1 = vo->skill1; // working skills
		newVo.skill2 = vo->skill2; // the upanishads skills
		newVo.recommend = vo->recommend; // recommend order
		newVo.selected = vo->selected; // checked
	}
	else
		_mercList.insert(make_pair(vo->mercId, *vo));
}

FigureCfgBaseVo* FigureBaseManage::getMercBase(int mercId)
{
	std::map<int, FigureCfgBaseVo>::iterator iter = _mercList.find(mercId);
	if(iter == _mercList.end())
		return NULL;
	return &(iter->second);
}

void FigureBaseManage::resetCfgMercList()
{
	std::map<int, FigureCfgBaseVo>::iterator iter = _mercList.begin();
	int lev = 0;
	for(; iter != _mercList.end(); ++iter)
	{
		lev = getLevelExpVo(iter->second.exp);
		iter->second.lev = lev;
		LevelExpVo* levExpVo = LevelExpManage::Instance()->getLevelExp(lev);
		if(levExpVo)
			iter->second.exp -= levExpVo->countExp;
	}
}

int FigureBaseManage::getLevelExpVo(int exp)
{
	return LevelExpManage::Instance()->getLevByExp(exp);
}

std::string FigureBaseManage::getCareerStr(int careerId)
{
	for(int i = 0; i < 7; ++i)
	{
		if(careerId == (0x01 << i))
		{
			string s("CAR");
			char c[8];
			sprintf(c,"%d",careerId);
			s.append(c);
			return ValuesUtil::Instance()->getString(s);
		}
	}
	return NULL;
}

std::map<int, FigureCfgBaseVo>* FigureBaseManage::getCfgMercList()
{
	return &_mercList;
}

std::string FigureBaseManage::getPopMercenary(int pop)
{
	std::map<int, FigureCfgBaseVo>::iterator iter = _mercList.begin();
	for(; iter != _mercList.end(); ++iter)
	{
		if(iter->second.needPop == pop)
			return iter->second.name;
	}
	return NULL;
}

FigureCfgBaseVo* FigureBaseManage::getNextPopMerc(int pop)
{
	int mercId = 0;
	int gap = 2147483647;
	std::map<int, FigureCfgBaseVo>::iterator iter = _mercList.begin();
	for(; iter != _mercList.end(); ++iter)
	{
		if(iter->second.needPop > pop)
		{
			if((iter->second.needPop - pop) < gap)
			{
				gap = iter->second.needPop - pop;
				mercId = iter->second.mercId;
			}
		}
	}
	return &(iter->second);
}