#ifndef HLQS_OnlineRewardManager_H_
#define HLQS_OnlineRewardManager_H_
#include "vo/OnlineRewardVo.h"
#include <list>
#include "utils/Singleton.h"

class OnlineRewardManager: public Singleton<OnlineRewardManager>
{
public:
	OnlineRewardManager();
	virtual ~OnlineRewardManager();

	void addRewardList(OnlineRewardVo & vo);
	std::vector<OnlineRewardVo> * getRewardDic();
	int getSize();

public:
	std::vector<OnlineRewardVo> _rewardDic;
};

#endif