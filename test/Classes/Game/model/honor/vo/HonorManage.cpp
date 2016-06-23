#include "HonorManage.h"

HonorManage::HonorManage()
{

}

void HonorManage::createHonors( HonorGoodVo* info )
{
	if ( !info )
	{
		return;
	}
	_honors.insert( make_pair( info->honorsid, info ) );
}

HonorGoodVo* HonorManage::getHonorGoodsVo( int id )
{
	map<int, HonorGoodVo*>::iterator it = _honors.find( id );
	if ( it != _honors.end() )
	{
		return it->second;
	}

	return 0;
}

HonorManage::~HonorManage()
{
	map<int, HonorGoodVo*>::iterator it;
	for ( it = _honors.begin(); it != _honors.end(); it++ )
	{
	//	CC_SAFE_DELETE( it->second );
	}
	_honors.clear();
}

