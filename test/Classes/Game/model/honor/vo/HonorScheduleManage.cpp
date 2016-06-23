#include "HonorScheduleManage.h"
#include "HonorManage.h"

HonorScheduleManage::HonorScheduleManage()
{

}

void HonorScheduleManage::updateScheduleData( HonorObject* obj )
{
	HonorGoodVo* honorGoodsVo = HonorManage::Instance()->getHonorGoodsVo(obj->id);
	if(honorGoodsVo)
	{
		//updateScheduleBigDictionary(honorGoodsVo.bigtype);
		//updateScheduleSmallDictionary(honorGoodsVo.type);
		if(honorGoodsVo->m_map!=0)
		{
			map<int, HonorGoodVo*>::iterator it = _scheduleBoss.find(honorGoodsVo->m_map);
			if(it == _scheduleBoss.end())
			{
				_scheduleBoss.insert( make_pair( honorGoodsVo->m_map, honorGoodsVo ) );
			}
		}
	}
}

HonorGoodVo* HonorScheduleManage::getAwardByMap( int id )
{
	map<int, HonorGoodVo*>::iterator it = _scheduleBoss.find( id );
	if ( it != _scheduleBoss.end() )
	{
		return it->second;
	}

	return 0;
}

HonorScheduleManage::~HonorScheduleManage()
{
	map<int, HonorGoodVo*>::iterator it;
	for ( it = _scheduleBoss.begin(); it != _scheduleBoss.end(); it++ )
	{
		CC_SAFE_DELETE( it->second );
	}
	_scheduleBoss.clear();
}

