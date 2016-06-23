#include "ArenaManage.h"

CfgRankVo* ArenaManage::getCfgRank(int rank)
{
	std::map<int, CfgRankVo>::iterator it;
	if ((it = _cfgArenaDic.find(rank)) != _cfgArenaDic.end())
	{
		return &it->second;
	}

	return 0;
}