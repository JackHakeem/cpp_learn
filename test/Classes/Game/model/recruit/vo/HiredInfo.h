#ifndef _HIREDINFO_H_
#define _HIREDINFO_H_

#include "BaseType.h"
#include "model/player/vo/PlayerInfoVo.h"
#include "model/player/vo/FigureCfgBaseVo.h"
#include "model/player/vo/FigureBaseVo.h"
#include "model/player/vo/PlayerBaseVo.h"

class HiredInfo
{
public:
	int protoId;  		// ID 
	string name;  		// 
	int sex;      		// 
	int careerId; 		
	int strength; 		
	int hitRate;  		
	int agility;  		
	uint crit;		
	uint stamina;	
	uint cloth;		
	uint requirement,	// 1 Juqing, 2 Mingsheng
	int mainSkill1;		
	int mainSkill2;		
	int aoyiSkill;		

	int mercId;         
	int level;          

	int silver;         
	int blood;          

	int rebornNum;      
public:
	HiredInfo()
	{
		memset( &sex, 0, sizeof( HiredInfo )-sizeof(int)-sizeof(string) );
		requirement = 1;
		name= "";
	}

	void setPlayInfo( PlayerInfoVo* vo )
	{
		if ( !vo )
		{
			return;
		}
		FigureBaseVo* figureBaseInfo = &vo->figureBaseInfo ;
		PlayerBaseVo* playerBaseInfo = &vo->playerBaseInfo;

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

		//mainSkill1 = figureBaseInfo->passiveId;
		//mainSkill2 = figureBaseInfo->equipSkillId;
		//aoyiSkill = figureBaseInfo->aoyiId;

		rebornNum = figureBaseInfo->rebornNum;
		silver = figureBaseInfo->silver;

		blood = playerBaseInfo->hp();
		mercId = playerBaseInfo->id;
		level = playerBaseInfo->lev();
	}
};

#endif