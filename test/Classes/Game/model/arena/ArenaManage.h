#pragma once

#include "BaseType.h"
#include "utils/Singleton.h"
#include "vo/CfgRankVo.h"

class ArenaManage : public Singleton<ArenaManage>
{
public:
	CfgRankVo* getCfgRank(int rank);

public:
	std::map<int, CfgRankVo> _cfgArenaDic;
};