#ifndef _GOODSINFO_H_
#define _GOODSINFO_H_
#include "BaseType.h"	
#include "model/com/GoodsToolTips.h"

class GoodsInfo
{
public:
	GoodsInfo()
	{
		id = 0;			//物品唯一编号
		goodId = 0;		//类型ID 物品编号
		sitGrid = 0;		//格子坐标
		name = "";		//名称
		type = 0;		//类型 	2 
		subtype = 0;		//子类型
		equip_type = 0;	//(装备的位置 头.项...))
		number = 0;		//数量
		quality = 0;		//品质
		strengthen = 0;	//强化数
		holds = 0;		//打洞数
		//explain = 0;	//说明 kkk
		stamina = 0;		//魔化体格数
		wrist = 0;			//魔化腕力数
		intellect = 0;		//魔化腕力数
	}
	~GoodsInfo()
	{
        //SAFE_DELETE( explain );
	}
	uint32 id; // items only Numbers
	int32 goodId; // type ID items Numbers
	int32 sitGrid; // grid coordinates
	std::string name; // name
	int32 type; // type 2
	int32 subtype; // child type
	int32 equip_type; // (equipment position. A head...) )
	int32 number; // quantity
	int32 quality; // quality
	int32 strengthen; // strengthen number
	int32 holds; // make hole number
	SUBGOODSTIPS explain; // that//kkk
	int32 stamina; // enchantment physical number
	int32 wrist; // enchantment number of achievement
	int32 intellect; // enchantment number of achievement
};

#endif