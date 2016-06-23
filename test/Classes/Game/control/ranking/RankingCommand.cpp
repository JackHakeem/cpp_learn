#include "RankingCommand.h"
#include "socket/command/c25/CCMD25B.h"
#include "socket/command/c25/CCMD25D.h"
#include "socket/network/GateServerSocket.h"
#include "model/backpack/vo/GoodsBasic.h"
#include "model/backpack/GoodsManager.h"
#include "model/com/GoodsDynamicManager.h"
#include "model/com/vo/GoodsDynamic.h"
#include "model/com/GoodsToolTips.h"

#define MAX_REQUEST_NUM (50)

RankingCommand::RankingCommand()
{
	_pRankProxy = 0;
	if(g_pFacade)
		_pRankProxy	= dynamic_cast<RankingProxy*>(g_pFacade->retrieveProxy(AppFacade_Ranking_Proxy));
}

RankingCommand::~RankingCommand()
{
}

void RankingCommand::execute(int32 command, char* data)
{	
	switch (command)
	{
	case REQUEST_RANKING_LIST:
		requestRankingList(*((int*)data));
		break;
	case UPDATE_RANKING_LIST:
		updateRankingList((SCMD25C*)data);
		break;
	case UPDATE_EQUIPS_INFO:
		updateEquipsInfo((SCMD25E*)data);
		break;
	case REQUEST_SELECTED_EQUIP_INFO:
		requestSelectedEquipInfo(*((int*)data));
		break;
	}
}

void RankingCommand::updateRankingList(SCMD25C* packet)
{
	do 
	{
		CC_BREAK_IF(! packet || ! _pRankProxy);
		int type = packet->a_type;
		CC_BREAK_IF(type < 0 || type >= RankingProxy::MAX_RANKING_TYPE);

		_pRankProxy->myRank[type] = packet->b_myRank;

		_pRankProxy->rankItems[type].clear();

		std::vector<SCMD25CNode>::iterator ix;
		for (ix = packet->e_ranks.begin(); ix != packet->e_ranks.end(); ++ix)
		{
			RankItemVo vo;
			vo.type = packet->a_type;
			vo.rank = ix->a_rank;
			vo.playerId = ix->b_playerId;
			vo.roleId = ix->g_roleId;
			vo.name = ix->c_name;
			vo.lev = ix->f_lev;

			vo.guild = ix->d_guild;
			vo.grade = ix->e_grade;
			vo.trend = ix->h_trend;
			if (vo.trend > 0)
				vo.trend = 2; //up
			else if (vo.trend < 0)
				vo.trend = 3; //down
			else
				vo.trend = 1; //same
			_pRankProxy->rankItems[type].push_back(vo);
		}
		if (type == (int)_pRankProxy->rankType)
		{
			_pRankProxy->updateRankList();
		}
	} while (0);
}

void RankingCommand::updateEquipsInfo(SCMD25E* packet)
{
	do 
	{
		CC_BREAK_IF(! packet || ! _pRankProxy);
		int type = packet->a_type;
		int playerId = packet->b_player;
		CC_BREAK_IF(type < 0 || type >= RankingProxy::MAX_RANKING_TYPE);

		std::vector<EquipItemVo> array;
		std::vector<SCMD25ENode>::iterator ix;
        for (ix = packet->c_equips.begin(); ix != packet->c_equips.end(); ++ix)
		{
            EquipItemVo vo;
            vo.id = ix->a_id;
            vo.lev = ix->b_lev;
			vo.stamina = ix->c_stamina;
			vo.intellect = ix->e_intellect;
			vo.wrist = ix->d_wrist;
			GoodsBasic* pGoodsBasic = g_pGoodsManager->getBasicGood(vo.id);
			if (! pGoodsBasic)
				continue;
			vo.name = pGoodsBasic->goodName;
			vo.type = pGoodsBasic->equip_type;
			vo.quality = pGoodsBasic->quality;
			array.push_back(vo);
		}
		_pRankProxy->updateEquipments(type, playerId, array);
	} while (0);
}

void RankingCommand::requestRankingList(int type)
{
	do 
	{
		CC_BREAK_IF(! _pRankProxy || type < 0 || type >= RankingProxy::MAX_RANKING_TYPE);

		_pRankProxy->rankType = type;
		if (_pRankProxy->rankItems[type].empty())
		{
			CCMD25B cmd;
			cmd.a_type = (int)_pRankProxy->rankType;
			cmd.c_begin = 1;
			cmd.d_end = MAX_REQUEST_NUM + 1;
			GateServerSocket::getInstance()->sendMessage(&cmd);
		}
		else
		{
			_pRankProxy->updateRankList();
		}

	} while (0);
}

void RankingCommand::requestSelectedEquipInfo(int position)
{
	do 
	{
		int index = _pRankProxy->rankType;
		CC_BREAK_IF(! _pRankProxy || position >= _pRankProxy->rankItems[index].size());
		
		RankItemVo vo = _pRankProxy->rankItems[index][position];
		std::map<int, std::vector<EquipItemVo> >::const_iterator ix = _pRankProxy->equipments[index].find(vo.playerId);
		if (ix != _pRankProxy->equipments[index].end())
		{
			_pRankProxy->updateEquipments(index, vo.playerId, ix->second);
		}
		else
		{
			const RankItemVo& vo = _pRankProxy->rankItems[_pRankProxy->rankType][position];
			CCMD25D cmd;
			cmd.a_type = vo.type;
			cmd.b_playerId = vo.playerId;
			GateServerSocket::getInstance()->sendMessage(&cmd);
		}

	} while (0);
}
