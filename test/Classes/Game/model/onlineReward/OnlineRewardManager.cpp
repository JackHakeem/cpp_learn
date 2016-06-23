#include "OnlineRewardManager.h"

OnlineRewardManager::OnlineRewardManager()
{
	
}

OnlineRewardManager::~OnlineRewardManager()
{
	_rewardDic.clear();
}

void OnlineRewardManager::addRewardList(OnlineRewardVo & vo)
{
	_rewardDic.push_back(vo);
}

std::vector<OnlineRewardVo> * OnlineRewardManager::getRewardDic()
{
	return &_rewardDic;
}

int OnlineRewardManager::getSize()
{
	return _rewardDic.size();
}