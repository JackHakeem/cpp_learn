#ifndef _VIP_PROXY_H_
#define _VIP_PROXY_H_
#include "mvc/Proxy.h"
#include "socket/command/s29/SCMD29E.h"

class VipProxy : public Proxy
{
public:
	VipProxy()
	{
		_goldReward = 0;
		_hasReward = false;
	}

	~VipProxy(){}

	int getGoldReward();
	void setGoldReward(int value);

	void updateVipReward(SCMD29E *pData);

private:
	int _goldReward;
	bool _hasReward;
};
#endif