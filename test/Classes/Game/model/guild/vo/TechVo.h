#ifndef _TechVo_H_
#define _TechVo_H_

#include "BaseType.h"
#include "GuildVoBase.h"

class TechVo: public GuildVoBase
{
public:
	TechVo()
	{
		id = 0;
		name = "";
		level = 0;
		icon = "";
		des = "";
		progress = 0;
		moneyNeed = 0;
		moneyHave = 0;
		isDefault = false;
	}
	virtual  ~TechVo(){}
public:
	int id;  			// 科技Id
	string name; 	// 科技名称
	int level ;  		// 科技等级 
	string icon;		//科技图标
	string des;		//科技功能描述
	int progress;  	// 进度
	int moneyNeed ; 	// 需要银币
	int moneyHave ;  	// 已有银币 
	bool isDefault;	//是否默认科技
};

#endif