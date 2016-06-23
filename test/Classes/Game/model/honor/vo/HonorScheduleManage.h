#ifndef _HonorScheduleManage_H_
#define _HonorScheduleManage_H_

#include "BaseType.h"
#include "utils/Singleton.h"
#include "HonorGoodVo.h"

struct HonorObject
{
	int id;
	int award;
};

class HonorScheduleManage : public Singleton<HonorScheduleManage>
{
public:
	HonorScheduleManage();
	~HonorScheduleManage();
public:
	HonorGoodVo* allocVo(){ return new HonorGoodVo(); };
	void updateScheduleData( HonorObject* info );
	HonorGoodVo* getAwardByMap( int id );
public:
	map<int, HonorGoodVo*> _scheduleBoss;
};

#endif