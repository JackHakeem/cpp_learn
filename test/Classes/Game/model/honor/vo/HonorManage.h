#ifndef _HonorManage_H_
#define _HonorManage_H_

#include "BaseType.h"
#include "utils/Singleton.h"
#include "HonorGoodVo.h"

class HonorManage : public Singleton<HonorManage>
{
public:
	HonorManage();
	~HonorManage();
public:
	HonorGoodVo* allocVo(){ return new HonorGoodVo(); };
	void createHonors( HonorGoodVo* info );
	HonorGoodVo* getHonorGoodsVo( int id );
public:
	map<int, HonorGoodVo*> _honors;
};

#endif