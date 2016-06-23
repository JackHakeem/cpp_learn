#ifndef _EQUIPITEMVO_H_
#define _EQUIPITEMVO_H_

#include <string>

struct EquipItemVo
{
	/** 装备原形ID */
    int id;
	/** 装备名称*/
	std::string name;
	/** 强化等级 */
    int lev;
	/** 装备类型 */
    int type;
	/** 装备品质 */
    int quality;
	/** 物品提示 */
	int stamina;
	int wrist;
	int intellect;
};

#endif

