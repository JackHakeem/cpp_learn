#include "TraderManager.h"

TraderManager::TraderManager()
{
	_selectedVo = 0;
}

TraderManager::~TraderManager()
{
}

int32 TraderManager::createGoods(TraderGoodsVo* vo)
{
	if (vo)
	{
		_traderGoodsDic.insert( make_pair( vo->goodsId, vo) );
	}
	
	return 0;
}

TraderGoodsVo* TraderManager::getGoodsById( int id)
{
	std::map<int, TraderGoodsVo* >::iterator it = _traderGoodsDic.find(id);
	if (it != _traderGoodsDic.end())
	{
		return it->second;
	}
	return 0;
} 

CityPriceVo* TraderManager::getselectedVo()
{
	return _selectedVo;
}

void TraderManager::setselectedVo(CityPriceVo* vo)
{
	_selectedVo = vo;
}
