#ifndef _RANKITEMVO_H_
#define _RANKITEMVO_H_

#include <string>

struct RankItemVo
{
	RankItemVo()
	{
		trend = 1;
	}
	/** 排行类型 */
	int type;
	/** 排名序号 */
	int rank;
	/** 玩家ID */
	int playerId;
	/** 主角原型ID */
	int roleId;
	/** 主角等级 */
	int lev;
	/** 玩家名称 */
	std::string name;
	/** 公会名(若无加入公会，则为空串) */
	std::string guild;
	/** 装备评分 / 玩家名声 / 战斗力 */
	int grade;
	/** 趋势 */
	int trend;
};

#endif
