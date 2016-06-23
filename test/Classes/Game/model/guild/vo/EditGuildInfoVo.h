#ifndef _EditGuildInfoVo_H_
#define _EditGuildInfoVo_H_

#include "BaseType.h"

class EditGuildInfoVo
{
public:
	~EditGuildInfoVo(){}
public:
	string qq;
	string notice;
	string intro;

	EditGuildInfoVo( string eQQ = "", string eNotice = "", string eIntro = "")
	{
		//if(eQQ)
			qq = eQQ;
		//if(eNotice)
			notice = eNotice;
		//if(eIntro)
			intro = eIntro;
	}
};

#endif