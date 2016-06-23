#ifndef _VIP_MGR_H_ 
#define _VIP_MGR_H_

#include "BaseType.h"
#include "utils/Singleton.h"

USING_NS_CC;

class VIPMgr : public Singleton<VIPMgr>
{
public:
	VIPMgr();
	virtual ~VIPMgr(){}

	bool hasVIPFunc(int type , int vipLev , bool isVipTrial = false , int var = 0);

public:
};

#endif