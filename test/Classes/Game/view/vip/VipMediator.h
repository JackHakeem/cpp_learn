#ifndef _VIP_MEDIATOR_H_
#define _VIP_MEDIATOR_H_
#include "mvc/Mediator.h"
#include "socket/command/s3c/SCMD3C8.h"
#include "socket/command/s1e/SCMD1EF.h"
#include "socket/command/s1e/SCMD1EE.h"
#include "components/VipView.h"

class VipMediator : public Mediator
{
public:
	VipMediator();

	enum
	{
		TRIAL_VIP_CHANGE = 0,
		UPDATE_VIP_GOLD,
		GET_VIP_REWARD
	};

	virtual void handleNotification( int M2Vcmd, char* data );

	void updateVipGold(int goldNum);
	void onTrialVipChange(SCMD3C8 *pData);
	void onLvChangeHandler(SCMD1EF *pData);
	void onGoldChangeHandler(SCMD1EE *pData);

	void popHandler(CCNode *pNode, void *data);
	void getVipReward(CCNode *pNode, void *pData);
	void onAddVip();


	VipView *_pVipView;

private:
	int _distance;
	bool _onceAlert;
	int _vipLev;

	
};
#endif