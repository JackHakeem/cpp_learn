
#include "VIPMgr.h"
#include "VIPLimitConst.h"
#include "model/player/RoleManage.h"

VIPMgr::VIPMgr()
{

}

bool VIPMgr::hasVIPFunc(int type , int vipLev , bool isVipTrial , int var )
{
	if(type >= VIPLimitConst::VIP_Max)
	{
		return false;
	}
	
	if (vipLev >= type)
	{
		return true;
	}

	//trial VIP
	if(isVipTrial && RoleManage::Instance()->accountInfo()->trialVip())
	{
		return true;
	}

	return false;
}