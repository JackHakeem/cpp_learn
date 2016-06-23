#pragma  once
#include "../BaseMediator.h"

class OnlineRewardView;

class RewardMediator : public BaseMediator
{
public:
	RewardMediator();
	virtual ~RewardMediator();

	virtual void handleNotification( int M2Vcmd, char* data );

	void popUIHandler(CCNode * pNode , void * data);
	void openRewardView();

	void sockOLInfo(char * data);
	void sockADInfo(char * data);

	void updateOLInfo(char * data);
	void updateADInfo(char * data);

	void getOLRewardInfo();
	void getADRewardInfo();
	void getOLReward();
	void getADReward();

public:
	enum
	{
		REWARD_OL_UPDATE = 0 , 
		REWARD_AD_UPDATE,
	};

protected:

private:
	OnlineRewardView * _pOLRewardView;
};