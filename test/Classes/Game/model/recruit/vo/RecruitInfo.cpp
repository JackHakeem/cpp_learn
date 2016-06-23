#include "RecruitInfo.h"
#include "model/player/vo/FigureBaseVo.h"
#include "model/player/vo/PlayerBaseVo.h"
#include "model/player/FigureBaseManage.h"
#include "model/skill/vo/SkillVo.h"
#include "model/skill/SkillManager.h"

RecruitInfo::RecruitInfo()
{
	mercId = 0;
	sex = 0;
	color = 0;           //
	careerId = 0; 		// 
	strength = 0; 		// Wanli
	hitRate = 0;  		// Mingzhong
	agility = 0;  		// Minjie 
	crit = 0;			//Baoji
	stamina = 0;		//Tige
	needPop = 0;
	cloth = 0;			//modle

	order = 0;			// for mingsheng .

	mainSkill1 = 0;		//skill 1	
	mainSkill2 = 0;		// 2
	aoyiSkill = 0;	    //Aoyi skill
	silver = 0;         //  

	blood = 0;          // hp
	maxHp = 0;
	equilSkill = 0;     // 
	passiveSkill = 0;   //  

	level = 0;			// 
	intell = 0;			// Zhili
	id = 0;     		// figure world ID,  0 haven't recruit 
	rebornNum = 0;      //  
	isHired = 0;		// 
	isRole = 0;		//  
	score = 0;
	isGray = 0;

	name = "";
	explanation = "";
}

void RecruitInfo::setPlayInfo( PlayerInfoVo* vo )
{

	if(!vo)	return;

	FigureBaseVo* figureBaseInfo = &vo->figureBaseInfo ;
	PlayerBaseVo* playerBaseInfo = &vo->playerBaseInfo;

	id = playerBaseInfo->id;	
	mercId = figureBaseInfo->mercId;
	FigureCfgBaseVo* cfgBase = FigureBaseManage::Instance()->getMercBase(mercId);
	setBaseProperty( cfgBase );

	color = playerBaseInfo->color;    //Ôö¼ÓÓ¶±øÑÕÉ«
	name = playerBaseInfo->name;
	sex = playerBaseInfo->sex;
	careerId = playerBaseInfo->career;
	strength = figureBaseInfo->strength;
	hitRate = figureBaseInfo->hitRate;
	agility = figureBaseInfo->agility;
	crit = figureBaseInfo->crit;
	stamina = figureBaseInfo->stamina;
	cloth = playerBaseInfo->cloth;
	//requirement = figureBaseInfo->requirement;
	rebornNum = figureBaseInfo->rebornNum; 
	silver = figureBaseInfo->silver;
	blood = playerBaseInfo->hp();
	maxHp = playerBaseInfo->maxHp();
	level = playerBaseInfo->lev();
	intell = figureBaseInfo->intellect;
	isRole = playerBaseInfo->isRole;

	equilSkill = playerBaseInfo->skill1;
	aoyiSkill = playerBaseInfo->skill2;
	passiveSkill = playerBaseInfo->skill3; 
}

void RecruitInfo::setBaseProperty( FigureCfgBaseVo* vo )
{
	if(!vo)	return ;

	mercId = vo->mercId;
	name = vo->name;
	sex = vo->sex;
	color = vo->color;
	careerId = vo->careerId;
	strength = vo->strength;
	hitRate = vo->hitRate;
	agility = vo->agility;
	crit = vo->crit;
	stamina = vo->stamina;
	needPop = vo->needPop;
	cloth = vo->cloth ;
	order = vo->order;
	requirement = vo->requirement;

	vector<int>::iterator it = vo->skill1.begin();
	if ( it != vo->skill1.end() )
		mainSkill1 = *it;
	it++;
	if ( it != vo->skill1.end() )
		mainSkill2 = *it;
	aoyiSkill = vo->skill2;

	silver = vo->silver;
	blood = vo->maxHp;
	level = vo->lev;
	intell = vo->intellect;
	isRole = vo->isRole;
	explanation	  = vo->explanation;
	score  = vo->score;
}

std::string RecruitInfo::getSkillName( int skillId )
{
	SkillVo* skillVo = SkillManager::Instance()->getSkill( skillId );

	if( !skillVo )	return "";

	return skillVo->name;
}

std::string RecruitInfo::getCareerName( int careerId )
{
	return FigureBaseManage::Instance()->getCareerStr( careerId );
}

