#ifndef _RECRUITINFO_H_
#define _RECRUITINFO_H_

#include "BaseType.h"
#include "model/player/vo/PlayerInfoVo.h"
#include "model/player/vo/FigureCfgBaseVo.h"

class RecruitInfo
{
public:
	int mercId;  		// merc ID 
	string name;  		// name
	int sex;      		// 
	int color;           //
	int careerId; 		// 
	int strength; 		// Wanli
	int hitRate;  		// Mingzhong
	int agility;  		// Minjie 
	int crit;			//Baoji
	uint stamina;		//Tige
	uint needPop;
	uint cloth;			//modle

	int order;			// for mingsheng 
	string requirement;	//  

	int mainSkill1;		//skill 1	
	int mainSkill2;		// 2
	int aoyiSkill;	    //Aoyi skill 
	int silver;         //  

	int blood;          // hp
	int maxHp;
	int equilSkill;     // 
	int passiveSkill;   //  

	int level;			// 
	int intell;			// Zhili
	int id;     		// figure world ID,  0 haven't recruit 
	int rebornNum;      //  
	bool isHired;		// 
	bool isRole;		//  
	string explanation;
	int score;

	int isGray;			// 0:not figure  1:gray  2:unknow gray 

public:
	RecruitInfo();
	void setPlayInfo( PlayerInfoVo* vo );
	void setBaseProperty( FigureCfgBaseVo* vo );
	string getSkillName( int skillId );
	string getCareerName( int careerId );
};

#endif