#ifndef _GOODSBASIC_H_
#define _GOODSBASIC_H_

#include "BaseType.h"

class GoodsBasic
{
public:
	uint32 goodId; // items Numbers
	std::string goodName; // items name
	std::string intro; // profile
	int32 throws; // discarding state can cast represents can sell
	int32 type; // large type
	int32 item_type; // item type
	int32 equip_type; // equipment type
	int32 icon;
	int32 price; // purchase price
	int32 sell_price; // selling price
	int32 gold_price; // mall price
	int32 career_id; // professional
	int32 level; // level
	int32 hp; // blood
	int32 att; // attack
	int32 def; // defense
	int32 magicAtt; // the attack
	int32 magicDef; // magic the
	int32 hit; // hit
	int32 dodge; // avoid
	int32 crit; // crit
	int32 back; // counterattack
	int32 suit_id; // suit Numbers
	int32 max_hole; // hole cap
	int32 max_overlap; // overlap
	int32 to_goodID; // debris finished product
	int32 quality; // quality
	int32 growUp; // growth degrees
	int32 expire_time; // due time
	std::string drop_from; // equipment drop location
	int32 enchant_Rate; // enchantment rate
};


#endif 