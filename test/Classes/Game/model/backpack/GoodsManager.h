#ifndef _GOODSMANAGER_H_
#define _GOODSMANAGER_H_

#include "BaseType.h"
#include "./vo/GoodsBasic.h"

//class GoodsBasic;

class GoodsManager
{
public:
	GoodsManager();
	~GoodsManager();

	int32 addGood(GoodsBasic* p);

	GoodsBasic* getBasicGood(int32 id)
	{
		std::map<int, GoodsBasic*>::iterator it;
		if ( (it = _goodsBasic.find(id)) != _goodsBasic.end())
		{
			return it->second;
		}
		return 0;
	}

	void getEquips(int level, int type, std::vector<GoodsBasic*>& dstEQ);

private:
	std::map<int, GoodsBasic*> _goodsBasic;

};

extern GoodsManager* g_pGoodsManager;

#endif