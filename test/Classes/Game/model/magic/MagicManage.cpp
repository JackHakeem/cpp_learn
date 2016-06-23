#include "MagicManage.h"

MagicManage::MagicManage()
{

}

void MagicManage::createMagicInfo( MagicLimitVo* info )
{
	if ( !info )
	{
		return;
	}
	//_enchantDic[magicLimitVO.equipType+ "_" + magicLimitVO.equipLevel + "_" + magicLimitVO.quality] = magicLimitVO ;

	char formtStr[128];
	sprintf( formtStr, "%d_%d_%d", info->equipType, info->equipLevel, info->quality );
	_magicLimitDic.insert( make_pair( formtStr, info ) );
}

MagicLimitVo* MagicManage::getMagicLimit( int type, int lev, int quality )
{
	char key[128];
	sprintf( key, "%d_%d_%d", type, lev, quality );

	map<string, MagicLimitVo*>::iterator it = _magicLimitDic.find(key);
	if ( it != _magicLimitDic.end() )
	{
		return it->second;
	}

	return 0;
}

MagicManage::~MagicManage()
{
	map<string, MagicLimitVo*>::iterator it;
	for ( it = _magicLimitDic.begin(); it != _magicLimitDic.end(); it++ )
	{
		CC_SAFE_DELETE( it->second );
	}
	_magicLimitDic.clear();
}

