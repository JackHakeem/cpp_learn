#ifndef _GOODSDYNAMICMANAGER_H_
#define _GOODSDYNAMICMANAGER_H_

#include "BaseType.h"

class GoodsDynamic;
class GoodsBasic;
class GoodsInfo;
class GoodsDynamicManager
{
public:
	GoodsDynamicManager();
	~GoodsDynamicManager();
public:

	GoodsDynamic* createDynamic(GoodsInfo* goodInfo, GoodsBasic* goodsBasic);
	void addDynamic(GoodsDynamic* params, bool disEvent=false);
	GoodsDynamic* getGoodsDynamic(int32 id);

private:
	std::map<int32, GoodsDynamic*> _goodsDynamic;
};

extern GoodsDynamicManager* g_pGoodsDynamicManager;

#endif