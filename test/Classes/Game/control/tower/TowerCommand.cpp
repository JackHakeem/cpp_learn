#include "TowerCommand.h"
#include "socket/command/s1b/SCMD1B2.h"
#include "view/guild/GuildMediator.h"
#include "model/guild/vo/MemberVo.h"
#include "socket/command/s1c/SCMD1C3.h"
#include "manager/LangManager.h"
#include "model/guild/vo/GuildInfoVo.h"
#include "socket/command/s1c/SCMD1C1.h"
#include "socket/command/s1b/SCMD1BF.h"
#include "model/player/RoleManage.h"
#include "socket/command/s1c/SCMD1C6.h"
#include "model/guild/vo/TechVo.h"
#include "model/skill/SkillManager.h"
#include "model/guild/vo/ApplyVo.h"
#include "socket/command/s1b/SCMD1BC.h"
#include "socket/command/s1b/SCMD1B8.h"
#include "view/chat/ChatMediator.h"
#include "socket/command/s3b/SCMD3B3.h"
#include "socket/command/s3b/SCMD3B5.h"
#include "socket/command/s3b/SCMD3B7.h"
#include "socket/command/s3c/SCMD3CB.h"
#include "model/tower/vo/TowerPanel1Vo.h"
#include "model/scene/vo/NPCVo.h"
#include "model/scene/MonsterManager.h"
#include "model/backpack/GoodsManager.h"
#include "model/tower/vo/TowerRankItemVo.h"

TowerCommand::TowerCommand()
{
	_towerProxy = 0;
}

void TowerCommand::execute( int32 command, char* data )
{
	if (!_towerProxy)
	{
		_towerProxy = (TowerProxy*)g_pFacade->retrieveProxy( AppFacade_TOWER_PROXY_CHANGE );
	}
	
	switch( command )
	{
	case UPDATE_PANEL_1:
		updatePanel1(data);
		break;
	case UPDATE_PANEL_2:
		updatePanel2(data);
		break;
	case TOWER_FIGHT_RESULT:
		getFightResult(data);
		break;
	case TOWER_RANKING:
		updateTowerRanking(data);
		break;
	}
}

TowerCommand::~TowerCommand()
{

}

//打开幻龙塔面板信息
void TowerCommand::updatePanel1( char* data )
{
	SCMD3B3 cmd = *(SCMD3B3*)data;

	TowerPanel1Vo* vo = new TowerPanel1Vo();
	vo->freeTimes = cmd.a_numFree;
	vo->lastFloor = cmd.c_lastFloor;
	vo->maxFloor = cmd.d_maxFloor;
	vo->myRank = cmd.e_myRank;

	string topRank = "";
	std::list<SCMD3B3::SCMD3B3Node>::iterator it = cmd.f_topRank.begin();
	for ( ; it != cmd.f_topRank.end(); it++ )
	{
		SCMD3B3::SCMD3B3Node& node = *it;

		time_t pTimeT = (time_t)node.b_time;
		struct tm* pTm = localtime(&pTimeT);
		if ( !pTm )
		{
			continue;
		}
		int year = pTm->tm_year + 1900;	//Local time
		int month = pTm->tm_mon + 1;
		int day = pTm->tm_mday;
		char timeStr[28];
		sprintf( timeStr, "%d", year );
		topRank += node.a_name + "  [" + timeStr;
		sprintf( timeStr, "%d", month );
		topRank = topRank+ "." + timeStr;
		sprintf( timeStr, "%d", day );
		topRank = topRank+ "." + timeStr + "]\n";
	}
	vo->topRank = topRank;

	_towerProxy->setpanel1Vo(vo) ;
	_towerProxy->numFree = cmd.a_numFree;
	_towerProxy->numPay = cmd.b_numPay;
}

//服务端返回闯塔面板信息
void TowerCommand::updatePanel2( char* data )
{
	SCMD3B5 cmd = *(SCMD3B5*)data;

	TowerPanel2Vo* vo = new TowerPanel2Vo;
	vo->freeTimes = cmd.a_numFree;
	vo->curFloor = cmd.c_curFloor;
	vo->maxFloor = cmd.d_maxFloor;
	vo->inspire = cmd.k_inspire;
	vo->inspirePrac = cmd.l_inspirePrac;
	vo->showCurBoss = cmd.g_showCurBoss!=0;

	vo->nextMonster = "";
	NPCVo* npcVo = MonsterManager::Instance()->getMonsterGroup(cmd.h_nextMonsterId);
	if(npcVo)
	{
		vo->nextMonster = npcVo->name;
	}

	SCMD3B5Node node;
	std::list<SCMD3B5Node>& curRewards = cmd.f_curRewards;
	std::list<SCMD3B5Node>& nextRewards = cmd.i_nextRewards;

	string iconStr = "";
	char tmp[10] = {0};
	TypeObject typeObj;
	std::list<SCMD3B5Node>::iterator itCur = curRewards.begin();
	for (; itCur != curRewards.end(); itCur++)
	{
		node = *itCur;
		typeObj = getRewardType(node.a_rewardId);
		sprintf( tmp, "%d", node.b_rewardNum );
		iconStr += typeObj.iconStr + "," + tmp + "," + typeObj.rewardStr + "|";
	}
	if(iconStr.length() > 0)
	{
		vo->curIcons = iconStr.substr(0, iconStr.length()-1);
	}
	else
	{
		vo->curIcons = "";
	}

	iconStr = "";
	for (itCur=nextRewards.begin(); itCur != nextRewards.end(); itCur++)
	{
		node = *itCur;
		typeObj = getRewardType(node.a_rewardId);
		sprintf( tmp, "%d", node.b_rewardNum );
		iconStr += typeObj.iconStr + "," + tmp + "," + typeObj.rewardStr + "|";
	}
	if(iconStr.length() > 0){
		vo->nextIcons = iconStr.substr(0, iconStr.length()-1);
	}else{
		vo->nextIcons = "";
	}

	_towerProxy->setpanel2Vo(vo);
}

//根据id返回对应的奖励类型
TypeObject TowerCommand::getRewardType(int id)
{
	TypeObject typeObj;
	switch(id)
	{
	case 1:		// 金币
		typeObj.rewardStr = ValuesUtil::Instance()->getString("gold");
		typeObj.iconStr = "11";
		break;
	case 2:		// 银币
		typeObj.rewardStr = ValuesUtil::Instance()->getString("silver");
		typeObj.iconStr = "12";
		break;
	case 3:		// 历练
		typeObj.rewardStr = ValuesUtil::Instance()->getString("pat");
		typeObj.iconStr = "13";
		break;
	case 4:		// 名声
		typeObj.rewardStr = ValuesUtil::Instance()->getString("rep");
		typeObj.iconStr = "14";
		break;
	case 5:		// 经验
		typeObj.rewardStr = ValuesUtil::Instance()->getString("exp");
		typeObj.iconStr = "";
		break;
	case 6:		// 精力
		typeObj.rewardStr = ValuesUtil::Instance()->getString("jinli");
		typeObj.iconStr = "";
		break;
	case 7:		// 魔晶石
		typeObj.rewardStr = ValuesUtil::Instance()->getString("stone");
		typeObj.iconStr = "17";
		break;
	default:	//物品
		{
			GoodsBasic* goods = g_pGoodsManager->getBasicGood(id);
			if(goods)
			{
				typeObj.rewardStr = goods->goodName;
			}
			else
			{
				typeObj.rewardStr = LangManager::getText("TWR032");
			}
		}
		break;
	}
	return typeObj;
}

//服务端返回战斗结果信息(若挑战成功，发对应的楼层奖励)
void TowerCommand::getFightResult( char* data )
{
	SCMD3B7 cmd = *(SCMD3B7*)data;


	_towerProxy->showLottery = (cmd.b_isLottery == 1);

	SCMD3B5 cmd2;
	cmd2.a_numFree = cmd.c_numFree;
	cmd2.b_numPay = cmd.d_numPay;
	cmd2.c_curFloor = cmd.f_afterFloor;
	cmd2.d_maxFloor = cmd.g_maxFloor;
	cmd2.e_curMonsterId = cmd.h_curMonsterId;
	cmd2.f_curRewards = cmd.i_curRewards;
	cmd2.h_nextMonsterId = cmd.k_nextMonsterId;
	cmd2.i_nextRewards = cmd.l_nextRewards;
	cmd2.k_inspire = cmd.n_inspire;
	cmd2.l_inspirePrac = cmd.o_inspirePrac;
	cmd2.g_showCurBoss = cmd.j_showCurBoss;
	cmd2.j_showNextBoss = cmd.m_showNextBoss;

	_towerProxy->waitFightEnd = true;
	updatePanel2((char*)&cmd2);
}

//服务端返回请求幻龙塔排位信息
void TowerCommand::updateTowerRanking( char* data )
{
	SCMD3CB cmd = *(SCMD3CB*)data;

	TowerRankListVo* rankVo = new TowerRankListVo();
	rankVo->page = cmd.a_page;
	rankVo->maxFloor = cmd.b_maxFloor;
	rankVo->curFloor = cmd.c_curFloor;
	rankVo->myRank = cmd.d_myRank;
	rankVo->restCount = cmd.d_nRestCount;
	rankVo->lastRank = cmd.d_oLastRank;

	std::list<TowerRankItemVo*> tmpList;
	TowerRankItemVo* rankItem = 0;
	SCMD3CB::SCMD3CBNode node;
	std::list<SCMD3CB::SCMD3CBNode>::iterator it = cmd.e_rankList.begin();
	for ( ; it != cmd.e_rankList.end(); it++ )
	{
		node = *it;

		rankItem = new TowerRankItemVo();
		rankItem->rank = node.a_rank;
		rankItem->floor = node.b_floor;
		rankItem->name = node.c_name;
		rankItem->guild = node.d_guild;
		rankItem->lev = node.e_lev;
		if(node.f_date == 0)
		{
			rankItem->date = LangManager::getText("TWR033");
		}
		else
		{
			time_t pTimeT = (time_t)node.f_date;
			struct tm* pTm = localtime(&pTimeT);
			if ( !pTm )
			{
				continue;
			}
			int year = pTm->tm_year + 1900;	//Local time
			int month = pTm->tm_mon + 1;
			int day = pTm->tm_mday;
			char timeStr[28];
			string topRank = "";
			sprintf( timeStr, "%d", year );
			topRank += timeStr;
			sprintf( timeStr, "%d", month );
			topRank = topRank+ "." + timeStr;
			sprintf( timeStr, "%d", day );
			topRank = topRank+ "." + timeStr;

			rankItem->date = topRank;
		}
		tmpList.push_back(rankItem);
	}

	std::list<TowerRankItemVo*>::reverse_iterator itVo = tmpList.rbegin();
	for ( ; itVo != tmpList.rend(); itVo++ )
	{
		rankVo->rankList.push_back(*itVo);
	}

	_towerProxy->setrankVo(rankVo);

	////数组排序函数
	//function order(vo1:TowerRankItemVo, vo2:TowerRankItemVo)
	//{
	//	if(vo1.rank > vo2.rank){
	//		return 1;
	//	}else if(vo1.rank < vo2.rank){
	//		return -1;
	//	}else{
	//		return 0;
	//	}
	//}
}
