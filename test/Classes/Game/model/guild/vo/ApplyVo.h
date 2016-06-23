#ifndef _ApplyVo_H_
#define _ApplyVo_H_

#include "BaseType.h"
#include "GuildVoBase.h"

class ApplyVo: public GuildVoBase
{
public:
	ApplyVo()
	{
		name = "";
		grade = 0;
		fame = 0;
		ctime = "";
	}
	~ApplyVo(){}
	virtual int getType() {return GuildVoBase_ApplyVo;}
public:
	string name; 	// 名字
	int grade ; 	// 等级
	int fame ; 		// 名声
	string ctime; 	// 申请时间 
};

#endif