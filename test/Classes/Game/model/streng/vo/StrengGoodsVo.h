#ifndef _STRENGOODSVO_H_
#define _STRENGOODSVO_H_
//#include "model\backpack\vo\/"
class GoodsInfo;

class StrengGoodsVo
{
public:
	StrengGoodsVo():type(0),level(0),sitGrid(0),roleId(0),quality(0),StrengGoodsInfo(0){};
	~StrengGoodsVo(){};
	int type; // equipment in what position, 1 package, 3 body
	int level; // wear level
	int sitGrid; // position
	int roleId; // mercenaries ID
	int quality; // quality level

	GoodsInfo* StrengGoodsInfo;
};

#endif