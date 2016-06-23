#pragma once

#include "BaseType.h"
#include "socket/command/s36/SCMD361Node.h"

class ArenaUI;
class FigureBaseManage;

class RankItem:public LayerNode
{
public:
	enum
	{
		RankItemZ_head_bg,
		RankItemZ_head,
		RankItemZ_name,
		RankItemZ_lv,
		RankItemZ_rank_pic,
		RankItemZ_rank,
		RankItemZ_haswin,
	};

	enum
	{
		RankItemTAG_head_bg,
		RankItemTAG_head,
		RankItemTAG_name,
		RankItemTAG_lv,
		RankItemTAG_rank_pic,
		RankItemTAG_rank,
		RankItemTAG_haswin,
	};


	RankItem();
	~RankItem();

	bool initWithParam(ArenaUI* pContainer, SCMD361Node& data);
	void clickHandler(CCObject* pSender);
public:
	ArenaUI* _pContainer;
	SCMD361Node  _data;
	FigureBaseManage* _figureBaseManage;
};