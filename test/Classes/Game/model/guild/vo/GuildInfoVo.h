#ifndef _GuildInfoVo_H_
#define _GuildInfoVo_H_

#include "BaseType.h"
#include "GuildVoBase.h"

class GuildInfoVo:public GuildVoBase
{
public:
	GuildInfoVo()
	{
		id = 0;
		name = "";
		leaderName = "";
		guildGrade = 0;
		emblemGrade = 0;
		rank = 0;
		members = 0;
		memberLimit = 0;
		ctime = "";
		qq = "";
		notice = "";
		intr = "";
		flag = 0;
		state = 0;
		abortTime = 0;
	}
	virtual ~GuildInfoVo(){}
	virtual int getType() {return GuildVoBase_GuildInfoVo;}
public:
	int id ; 			// 公会ID 
	string name;  // 公会名字
	string leaderName; //会长名字
	/**公会等级*/
	int guildGrade ;  	// 公会等级
	/**军徽等级*/
	int emblemGrade ;  	// 军徽等级
	int rank ;  		// 公会排名
	int members;  		// 成员数
	int memberLimit;  	// 成员数上限
	string ctime;  // 创建时间 
	string qq;   	// QQ群 
	string notice;// 公告 
	string intr;   //公会介绍
	uint flag;          //是否已申请
	uint state;          //是否解散中, 1为解散 中
	int abortTime;      //解散的时间点
};

#endif