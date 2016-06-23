#ifndef _MagicManage_H_
#define _MagicManage_H_

#include "BaseType.h"
#include "utils/Singleton.h"
#include "vo/MagicLimitVo.h"

class MagicManage : public Singleton<MagicManage>
{
public:
	MagicManage();
	~MagicManage();
public:
	MagicLimitVo* allocVo(){ return new MagicLimitVo(); };
	void createMagicInfo( MagicLimitVo* info );
	MagicLimitVo* getMagicLimit( int type, int lev, int quality );
private:
	map<string, MagicLimitVo*> _magicLimitDic;
};

#endif