#ifndef _MeltingMeltingStrengCreate_H_
#define _MeltingMeltingStrengCreate_H_

#include "BaseType.h"
#include "cocos2d.h"
#include "utils/Singleton.h"
#include "utils/ScaleUtil.h"
using namespace cocos2d;

#define STRENG_CREATE_W POSX(538)
#define STRENG_CREATE_H POSX(428)

class StrengGoodsVo;
class StrengGoods;

class MeltingStrengCreate : public CCLayer
{
public:
	MeltingStrengCreate();
	~MeltingStrengCreate();

public:

	bool init();
	LAYER_NODE_FUNC(MeltingStrengCreate);
	void createGood( StrengGoodsVo* strengGoodsVo,int sitNum );
	void removeSkinChild();
	void updateTip( int id );
	StrengGoods* getStrengGoods( int id );
	CCNode *getNewHandItem(int eqSitNum);

	void setDefaultGoodIndex(int val) { i = val; }
private:
	std::map<int, StrengGoods*> _goodsDic;
	int i;
};

#endif