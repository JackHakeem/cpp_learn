#ifndef _TraderManager_H_
#define _TraderManager_H_

#include "vo/TraderGoodsVo.h"
#include "vo/CityPriceVo.h"
#include "utils/Singleton.h"

class TraderManager : public Singleton<TraderManager>
{
public:
	TraderManager();
	~TraderManager();

	int32 createGoods(TraderGoodsVo* vo);
	TraderGoodsVo* getGoodsById( int id);
	CityPriceVo* getselectedVo();
	void setselectedVo(CityPriceVo* vo);
private:
	std::map<int, TraderGoodsVo* > _traderGoodsDic;
	CityPriceVo* _selectedVo;
};

#endif
