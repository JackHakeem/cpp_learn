#pragma once

#include "BaseType.h"
#include "model/arena/vo/HeroRankVo.h"

class HeroRankItem:public LayerNode
{
public:
	enum
	{
		HeroRankItemZ_bg,
		HeroRankItemZ_rank,
		HeroRankItemZ_name,
		HeroRankItemZ_lv,
	};

	enum
	{
		HeroRankItemTAG_bg,
		HeroRankItemTAG_rank,
		HeroRankItemTAG_name,
		HeroRankItemTAG_lv,
	};

	HeroRankItem();
	~HeroRankItem();

	bool init(HeroRankVo info);
	cocos2d::ccColor3B initColor();
public:
	HeroRankVo _heroRankVo;
};