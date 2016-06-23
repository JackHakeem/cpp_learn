#ifndef _MemberVo_H_
#define _MemberVo_H_

#include "BaseType.h"
#include "GuildVoBase.h"
#include "manager/LangManager.h"

class MemberVo : public GuildVoBase
{
public:
	MemberVo()
	{
		name = "";
		id = 0;
		duty  = "";
		level = 0;
		fame = 0;
		state = "";
		contribution = 0;
	}
	virtual ~MemberVo(){}
	virtual int getType() {return GuildVoBase_MemberVo;}
public:
	string name;  	// 成员名称
	int id;             //成员ID
	string duty;  	// 成员职务（会长，副会长，官员，会员）
	int level ;  		// 等级
	int fame ;  		// 称号
	string state; 	// 状态，-1 在线   0 离线  else 离线X天
	int contribution;		//贡献度

	int dutyValue()
	{
		if(duty == LangManager::getText("GLD038") ) return 4;
		if(duty == LangManager::getText("GLD039") ) return 3;
		if(duty == LangManager::getText("GLD058") ) return 2;
		if(duty == LangManager::getText("GLD059") ) return 1;
		return 0;
	}
};

#endif